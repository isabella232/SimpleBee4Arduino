#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
SimpleBee base driver emulator
(c) 2015 - Orange Labs Franck Roudet
------------------------------------------------------
"""
#
# Copyright (C) 2015 Orange
# 
#  This software is distributed under the terms and conditions of the 'Apache-2.0'
#  license which can be found in the file 'LICENSE.txt' in this package distribution
#  or at 'http://www.apache.org/licenses/LICENSE-2.0'.
# 
import struct
'''
Created on 23 févr. 2015

@author: franck
'''

import argparse
import logging
import serial
import io
from fysom import Fysom, FysomError

component_name="simplebee"
logger=logging.getLogger(component_name)
global options


def prepareLogger(level):
    logger.setLevel(level)
    # create console handler and set level to debug
    ch = logging.StreamHandler()
    ch.setLevel(level)
    # create formatter
    formatter = logging.Formatter("%(asctime)s - %(levelname)s %(name)s - %(message)s")
    # add formatter to ch
    ch.setFormatter(formatter)
    # add ch to logger
    logger.addHandler(ch)

def enum(*sequential, **named):
    enums = dict(zip(sequential, range(len(sequential))), **named)
    reverse = dict((value, key) for key, value in enums.iteritems())
    enums['reverse_mapping'] = reverse
    return type('Enum', (), enums)


def SBCheckSum(str, length):
    """
    Calc checksum and store in dest.
    res size is 2
    """
    csum=0;
    for current in range(0,length):
        csum += ord(str[current])
    return chr(0x30 + ((csum & 0xF0) >> 4)) + chr(0x30 + (csum & 0x0F))

def checkMsgChecksum(msg):
    chk = SBCheckSum(msg,len(msg)-2)
    #logger.info("chksum %s",chk)
    ok=chk == msg[-2:]
    if not ok:
        logger.error("checksum error on %s", msg)
    return ok

class PseudoDevice(Fysom):
    
    addr_counter = 0
        
    def __init__(self,*args,**kwargs):
        logger.debug("PseudoDevice %s", kwargs)
        self.addr=kwargs.pop('addr', "0000")
        self.typemodule=kwargs.pop('typemodule', None)
        self.ser=kwargs.pop('ser', [])
        Fysom.__init__(self,{ 'initial': 'idle',
                  'events': [
                      {'name': 'evt_askident',   'dst': 'ukn',        'src': ['idle', ]},
                      {'name': 'evt_giveident',  'dst': 'identified', 'src': ['idle', 'ukn',]},
                      {'name': 'evt_newvalue',   'dst': 'newvalue',   'src': ['identified', ]},
                      {'name': 'evt_valueack',   'dst': 'identified',   'src': ['newvalue', ]},
                      ],
                 "callbacks" : {
#                        'onconnected':   self.connected_state,
                        'onidentified':  self.identified_state,
                        'onnewvalue':      self.newvalue_state,
#                        'onidle':        self.idle_state,
                    }
                      })
        logger.debug('Module of type %s at address %s detected', self.typemodule, self.addr)

    def start(self):
        self.evt_askident() if "0000" == self.addr else self.evt_giveident()
            
    
    def sendMsg(self,msg):
        self.ser.write(msg)
        self.ser.write(SBCheckSum(msg, len(msg)))
        self.ser.write(SBEndOfMessage)
        
                      
    #-------------------        
    # State machine
    #-------------------
               
    def identified_state(self,e):
        logger.info("\t[Identified %s]", self.addr)

    def onafterevt_askident(self,e):
        logger.info("-> New addr  %s from %s", e.dst, e.event)
        PseudoDevice.addr_counter = PseudoDevice.addr_counter + 1
        self.addr="%.4i" % PseudoDevice.addr_counter
        msg=struct.pack("c4s",SBMsgReqType.identification.lower(),self.addr)
        self.sendMsg(msg)
        self.evt_giveident()

    def newvalue_state(self,e):
        logger.info("\t[new value from %s]", self.addr)
        logger.info("\t %s", {key:getattr(self,key, None) for key in ["value", "batteryLevel"]})


    @classmethod
    def factory(cls, sensor,**kwargs):
        logger.debug("Build that %s %s",sensor,kwargs)
        if sensor=='C':
            newSBDevice = SensorDevice(**kwargs)
        elif kwargs["typemodule"]=='A002':
            newSBDevice=SandTimerDevice(**kwargs)        
        elif sensor=='A':
            newSBDevice=ActuatorDevice(**kwargs)
        else:
            newSBDevice=None
        return newSBDevice
        


    def __del__(self):
        logger.debug("Disconnecting")
        


class ActuatorDevice(PseudoDevice):
    def onafterevt_newvalue(self,e):
        self.value = str(self.value[:-1]) + str((int(str(self.value[-1])) + 1)%10)
        msg=struct.pack("c4s",SBMsgReqType.request.lower(),self.addr)+ self.value
        logger.info("-> send actuator ack event %s", msg)
        self.sendMsg(msg)
        self.evt_valueack()
        
class SensorDevice(PseudoDevice):
    def onafterevt_newvalue(self,e):
        self.value = str(self.value)
        msg=struct.pack("c4s",str(e.msgType).lower(),self.addr)+ self.value
        logger.info("-> send sensor ack event %s", msg)
        self.sendMsg(msg)
        self.evt_valueack()    
          

class SandTimerDevice(ActuatorDevice):
    
    def __init__(self,*args,**kwargs):
        self.led=6
        super(SandTimerDevice, self).__init__(*args,**kwargs)
            
    def onafterevt_newvalue(self,e):
        if self.value=='008': # reverse restart
            self.led=6
        elif self.value=='800': # flat wait
            pass
        elif self.value=='000': # up decrease
            self.led = 0 if self.led==0 else self.led - 1
        msg="%c%.4s%s" % (str(e.msgType).lower(),self.addr, self.led)
        logger.info("-> send sand ack event %s", msg)
        self.sendMsg(msg)
        self.evt_valueack()    


SBEndOfMessage='\r';
      
SBMsgReqType = enum(identification='I', 
                    watchdog='W',
                    data='D',
                    request='R')
"""
Message Type. First Byte
"""


class SimpleBee(object):
    list_liveObject = {}
    def __init__(self,**kwargs):
        self.port = kwargs.pop('port', None)
        self.baudrate = kwargs.pop('baudrate', None)
        
        
    def start(self):
        self.ser = serial.Serial(self.port, baudrate=self.baudrate)  # open first serial port
        self.sio = io.TextIOWrapper(io.BufferedRWPair(self.ser,self.ser,1), encoding='ascii', newline='\r', line_buffering=False)
        logger.debug("Reading on %s", self.port)
        while True:
            try:
                msg= self.sio.readline().replace('\n','')[:-1]
            except (UnicodeDecodeError) as e :
                logger.error("Bad char ignoring '%s'", e)
                continue
            msgType=msg[0]
            logger.debug("Mesg type='%s' len=%d '%s'", msgType, len(msg), msg)
            
            if SBMsgReqType.identification == msgType :
                (msgType, sensor, typemodule, cksum)  =struct.unpack('cc3s2s', msg)
                if checkMsgChecksum(msg):
                    newSBDevice = SensorDevice(typemodule=sensor+typemodule, ser=self.ser) if sensor=='C' else ActuatorDevice(typemodule=sensor+typemodule, ser=self.ser)
                    newSBDevice.start()
                    self.list_liveObject[newSBDevice.addr]=newSBDevice
            elif msgType in [SBMsgReqType.request, SBMsgReqType.watchdog, SBMsgReqType.data]:
                #(msgType, address, value, batdelimit, batteryLevel, cksum)  =struct.unpack('c4sccc2s', msg)
                address=msg[1:5]
                value=msg[5:-8]
                batteryLevel=msg[-7:-6]
                sensor=msg[-6:-5]
                typemodule=msg[-5:-2]
                cksum=msg[-2:]
                if checkMsgChecksum(msg):
                    device=self.list_liveObject.get(address, None)
                    if not device:
                        logger.error("  ->Unknown device %s auto provide", address)
                        device = PseudoDevice.factory(sensor, addr=str(address), typemodule=sensor+typemodule, ser=self.ser)
                        #device = SensorDevice(addr=str(address), typemodule=sensor+typemodule, ser=self.ser) if sensor=='C' else ActuatorDevice(addr=address, typemodule=sensor+typemodule, ser=self.ser)
                        device.start()
                        self.list_liveObject[device.addr]=device
                    device.value=value
                    device.batteryLevel=batteryLevel
                    device.evt_newvalue(msgType=msgType)
            elif msgType == '-':
                logger.warning("%s", msg)
            else:
                logger.error("ukn msg :'%s'", msg)
            


            
        
def launch_simplebee(parser=None):
    if not parser:
        parser = argparse.ArgumentParser(description='simplebee emulator')
    parser.add_argument('--debug', '-d', dest='debug', action='store_true',
                   default=False, help='Debug mode')
    parser.add_argument('--port', '-p', dest='port', action='store', help='xbee port com')
    parser.add_argument('--baudrate', '-b', dest='baudrate', action='store', help='xbee baudrate', default=57600)
    global options
    options = parser.parse_args()
    prepareLogger(logging.DEBUG if options.debug else logging.INFO)    
    logger.debug("debug is on")
    simplebee = SimpleBee(port=options.port, baudrate=options.baudrate)
    simplebee.start()

if __name__ == "__main__" :
    print(__doc__)
    launch_simplebee()
    
logging.warning("End")
