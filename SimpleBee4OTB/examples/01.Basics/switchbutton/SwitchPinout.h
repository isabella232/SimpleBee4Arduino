/**
 * Override Swtich to process events
 */
class MySwitch : public SBSwitch {
public:
  int pin;
  /**
   * Contructors
   */
  MySwitch(const int pin, unsigned long hearbeat_period_ms=60000) : SBSwitch("001", hearbeat_period_ms) , pin(pin) {
    pinMode(pin, INPUT);
    value=digitalRead(pin);  
  };
  /**
   * Init comm and hardware
   */
  virtual void start(void) {
    SBSwitch::start();
  };


  /**
   * Heart beat
   */  
  virtual void sendHeartBeat(void) {
    value=digitalRead(pin);
    SBSwitch::sendHeartBeat();
  };


  /**
   * check hardware changes
   */  
  virtual void checkChange(void) {
    char actualValue = digitalRead(pin);
    if (actualValue!=value) {
       value=actualValue;
       sendMessageData();
    }
  }
};
