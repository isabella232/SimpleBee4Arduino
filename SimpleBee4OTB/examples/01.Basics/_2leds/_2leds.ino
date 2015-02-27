/*
 * Copyright (C) 2015 Orange
 *
 * This software is distributed under the terms and conditions of the 'Apache-2.0'
 * license which can be found in the file 'LICENSE.txt' in this package distribution
 * or at 'http://www.apache.org/licenses/LICENSE-2.0'.
 */

/* LED example
 *
 * Version:     0.1.0
 * Created:     2015-02-25 by Franck Roudet
 */
#include <SBMessenger.h>
#include <sbmessage.h>
#include <sbdevice.h>
#include <sbdispatcherdevice.h>


/*
 * CallBack dispatching function type
 */
class Dispatcher : public SBDispatcherDevice {
public:
void dispatch(char * start, int length) {
  SBDispatcherDevice::dispatch(start, length);
  Serial.print("-");
  Serial.print(start);
  Serial.print("\r");
}
};

/**
  * Dispatcher for incoming Simple Bee message 
  */
Dispatcher disp;

/**
 * Simple bee message manager
 */
SBMessenger sbmessenger(Serial,SBEndOfMessage, &disp, SBCheckSum);

class MyLed : public SBLed {
public:
  public:

  MyLed(char * moduleType=0L, unsigned long hearbeat_period_ms=500) : SBLed(moduleType, hearbeat_period_ms) {
	};

  virtual void start(void) {
    SBLed::start();
    pinMode(13, OUTPUT);
    digitalWrite(13,HIGH);
  };

  virtual void newMessage(char *message) {
    SBLed::newMessage(message);
    Serial.print("New Mss :");
    Serial.println((int) value);
    digitalWrite(13,value);
  };
};

/**
 * Declare my devices
 */
MyLed led1("001"); // 001 module type stand for led (see the doc)
SBLed led2("001",3000); // 3sec

/**
 * List of monitoring devices
 */
SBDevice * stbDeviceList[]={ &led1, &led2, NULL }; // WARNING: must ends with NULL



void setup() {
  // Start the serial port
  Serial.begin(57600);

  
  // Set list of device for dispatching
  disp.setDeviceList(stbDeviceList);


  Serial.print("-starting\r");

  delay(2000); // Waiting radio
  
  // Start device if necessary
  //led1.start();
  // start all 
  for (SBDevice **device=stbDeviceList;*device;device++) {
    (*device)->start();
  }
  led1.value=1;
  led1.batteryLevel=5;
  led2.value=2;
  led2.batteryLevel=9;

}

void loop() {
  // Looks for incoming message
  sbmessenger.monitor();

}

