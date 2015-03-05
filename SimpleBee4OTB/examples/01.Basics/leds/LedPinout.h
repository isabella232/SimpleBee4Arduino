/**
 * Override Led to process events
 */
class MyLed : public SBLed {
public:
  int pin;
  /**
   * Contructors
   */
  MyLed(const int pin, unsigned long hearbeat_period_ms=500) : SBLed(hearbeat_period_ms) , pin(pin) {
      pinMode(pin, OUTPUT);
  };
  /**
   * Init comm and hardware
   */
  virtual void start(void) {
    SBLed::start();
    digitalWrite(pin,HIGH);
  };
   
  /**
   * Init comm and hardware
   */
  virtual void setAddr(const char * newAddress) {
    SBLed::setAddr(newAddress);
    digitalWrite(pin,HIGH);
  };
  

  /**
   * on change from OTB
   */
  virtual void newMessage(char *message) {
    SBLed::newMessage(message);
    digitalWrite(pin,value);
  };
};
