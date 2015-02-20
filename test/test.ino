#include <SBMessenger.h>

//#include <XBee.h>

#include <sbmessage.h>


// create the XBee object
//XBee xbee = XBee();
SBMessenger sbmessenger(Serial,SBEndOfMessage,SBCheckSum);

void setup() {
  // Start the serial port
  Serial.begin(57600);
  // Tell XBee to use Hardware Serial. It's also possible to use SoftwareSerial
  //xbee.setSerial(Serial);

// put your setup code here, to run once:
  char moduleType[] = "124";
  SBMessageIdentificationReq ident(moduleType);
  Serial.print("sizeof:");
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
  sbmessenger.send(&ident, sizeof(SBMessageIdentificationReq));
}

void loop() {
  // put your main code here, to run repeatedly
  

}

