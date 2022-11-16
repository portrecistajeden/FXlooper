#define BANK_SW1 2
#define BANK_SW2 3
#define FX_SW1 4
#define FX_SW2 5
#define BANK_DIODE1 6
#define BANK_DIODE2 7
#define EDIT_DIODE 8
#define RELAY1 9
#define RELAY2 10
#define numberOfEffects 2

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

class Switch{
  private:
    byte pin;
  public:
    Switch(byte pin) {
      this->pin = pin;
      init();
    }

    void init(){
      pinMode(pin, INPUT);
    }

    int getState(){
      return digitalRead(pin);
    }
};

class Relay{
  private:
    byte pin;
  public:
    Relay(byte pin) {
      this->pin = pin;
      init();
    }

    void init(){
      pinMode(pin, INPUT);
      high();
    }

    void high(){
      digitalWrite(pin, HIGH);
    }

    void low(){
      digitalWrite(pin, LOW);
    }
};

class Led{
  private:
    byte pin;
  public:
    Led(byte pin){
      this->pin=pin;
      init();
    }

    void init(){
      pinMode(pin, OUTPUT);
      off();
    }

    void on(){
      digitalWrite(pin, HIGH);
    }

    void off(){
      digitalWrite(pin, LOW);
    }
};

class Bank{
  private:
    bool effects[numberOfEffects];
  public:
    Bank(){
      init();
      }

    void init(){
      for(int i=0; i<numberOfEffects; i++) {
        effects[i] = 0;
        }
    }

    void moduloEffect(int index){
      effects[index-1] = !(effects[index-1]);
    }  

    bool getArray(){
      return this->effects;
    }
};

void ledBlink() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(EDIT_DIODE, ledState);
  }
}

Switch bankSW1(BANK_SW1);
Switch bankSW2(BANK_SW2);
Switch fxSW1(FX_SW1);
Switch fxSW2(FX_SW2);
Led bankLED1(BANK_DIODE1);
Led bankLED2(BANK_DIODE2);
Led editLED(EDIT_DIODE);
Relay relay1(RELAY1);
Relay relay2(RELAY2);

Bank bank1();
void setup() {

  Serial.begin(9600);
  
  
Serial.println(bank1.getArray());

  editLED.on();
  delay(1000);
  editLED.off();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(bankSW1.getState());
  if (bankSW1.getState() == HIGH) {
    relay1.low();
  }
  else relay1.high();
  
}
