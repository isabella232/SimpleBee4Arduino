#include <SBMessenger.h>

//#include <XBee.h>

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

Dispatcher disp;

SBMessenger sbmessenger(Serial,SBEndOfMessage, &disp, SBCheckSum);

SBActuator led1("001");
SBActuator led2("001");

/**
 * List of monitoring devices
 */
SBDevice * stbDeviceList[]={ &led1, &led2, NULL };



void setup() {
  // Start the serial port
  Serial.begin(57600);

  
  // Init STB component
  disp.setDeviceList(stbDeviceList); // set the device List to dispatcher

  // Tell XBee to use Hardware Serial. It's also possible to use SoftwareSerial
  //xbee.setSerial(Serial);

// put your setup code here, to run once:
  char moduleType[] = "124";
  SBMessageIdentificationReq ident(moduleType);
  Serial.print("-sizeof:");
  Serial.println(sizeof(SBMessageIdentificationReq));
  
  //SBCheckSum((char*) &ident, sizeof(SBMessageIdentificationReq) - 3, ident.checksum);
  //Serial.println((char*) &ident);

  delay(2000); // Waiting radio
// Specify the address of the remote XBee (this is the SH + SL)
//uint16_t addr64 = 0x0000;
    // Create a TX Request
//Tx16Request zbTx = Tx16Request(addr64, (uint8_t*)&ident, sizeof(ident));

// Send your request
//xbee.send(zbTx);
  //sbmessenger.send(&ident, sizeof(SBMessageIdentificationReq));
}

void loop() {
  // Looks for incoming message
  sbmessenger.monitor();

}

