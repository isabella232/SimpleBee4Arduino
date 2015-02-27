/**
 * Override Led to process events
 */
class MyLed : public SBLed {
public:
  int pin;
  /**
   * Contructors
   */
  MyLed(const int pin, unsigned long hearbeat_period_ms=500) : SBLed("001", hearbeat_period_ms) , pin(pin) {};
  /**
   * Init comm and hardware
   */
  virtual void start(void) {
    SBLed::start();
    pinMode(pin, OUTPUT);
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
