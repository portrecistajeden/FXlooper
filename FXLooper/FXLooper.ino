#define BANK_SW1 9
#define BANK_SW2 10
#define BANK_SW3 11
#define BANK_SW4 12
#define MUTE_SW 13

#define FX_SW1 22
#define FX_SW2 23
#define FX_SW3 24
#define FX_SW4 25
#define FX_SW5 26
#define FX_SW6 27
#define FX_SW7 28
#define FX_SW8 29
#define FX_SW9 30

#define BANK_DIODE1 2
#define BANK_DIODE2 3
#define BANK_DIODE3 4
#define BANK_DIODE4 5

#define EDIT_DIODE 32

#define RELAY1 40
#define RELAY2 41
#define RELAY3 42
#define RELAY4 43

#define numberOfEffects 2
#define numberOfBanks 5
#define LONGPRESS 3000

int currentBank = 1;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;
bool banks[numberOfBanks][numberOfEffects];

int lastState = LOW;
int currentState;
unsigned long pressedTime = 0;
unsigned long timeVal = 0;

bool editMode = 0;

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
      pinMode(pin, OUTPUT);
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
    
    void modulo(){
      if (digitalRead(pin) == 1) off();
      else on();
    }
};


void ledBlink(Led led) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    led.modulo();
  }
}

Switch bankSW1(BANK_SW1);
Switch bankSW2(BANK_SW2);
Switch muteSW(MUTE_SW);
Switch fxSW1(FX_SW1);
Switch fxSW2(FX_SW2);
Led bankLED1(BANK_DIODE1);
Led bankLED2(BANK_DIODE2);
Led editLED(EDIT_DIODE);
Relay relay1(RELAY1);
Relay relay2(RELAY2);

Relay relayArray[2]={relay1, relay2};
Led ledArray[2] = {bankLED1, bankLED2};

void enableBank(int number){
  currentBank = number;
  
  for(int i=0;i<numberOfEffects;i++){
    if( banks[currentBank][i] == 1) relayArray[i].low();
    else relayArray[i].high();
  }
 
    
  for(int i=0; i<2; i++){
    ledArray[i].off();
  }
  ledArray[number].on();
}


void checkForLongPress(Switch button){
  currentState = button.getState();
  if(!currentState) lastState = LOW;
  else{
      if(lastState==LOW && currentState==HIGH){
      pressedTime=millis();
      lastState=HIGH;
    }
    else if(lastState==HIGH && currentState==HIGH){
      timeVal=millis();
      Serial.println(timeVal - pressedTime);
      if (timeVal - pressedTime > 3000){
        editLED.off();
        editMode = !editMode;
        pressedTime=timeVal;
      }
    }
  }
}

void editBank(bool bank){
  while(1){
    Serial.println("while");
    if(fxSW1.getState()) return;
  }
}

void setup() {

  Serial.begin(9600);

  for(int i=0; i<numberOfBanks; i++){
    for(int j=0; j<numberOfEffects; j++){
      banks[i][j]=0;
    }
  }
  
  banks[0][1] = 1;
  banks[1][0] = 1;
  banks[1][1] = 1;
  banks[4][1] = 0;
  banks[4][0] = 0;

  enableBank(0);
  
}

void loop() {

  checkForLongPress(fxSW1);
  
  if(editMode){
    ledBlink(editLED);
    if(bankSW1.getState()){
      delay(100);
      editBank(0);
    }
  }
  else{
    if (muteSW.getState() == HIGH && currentBank!=4) enableBank(4);
    else if (bankSW1.getState() == HIGH && currentBank!=0) enableBank(0);
    else if (bankSW2.getState() == HIGH && currentBank!=1) enableBank(1);     
  } 
}
