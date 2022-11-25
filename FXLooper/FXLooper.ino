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
#define MUTE_DIODE 6

#define EDIT_DIODE 32

#define RELAY1 38
#define RELAY2 39
#define RELAY3 40
#define RELAY4 41
#define RELAY5 42
#define RELAY6 43
#define RELAY7 44
#define RELAY8 45
#define RELAY9 46
#define RELAY10 47
#define RELAY11 48
#define RELAY12 49
#define RELAY13 50
#define RELAY14 51
#define RELAY15 52
#define RELAY16 53

#define numberOfEffects 8
#define numberOfBanks 5
#define LONGPRESS 3000

int currentBank = 0;
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

Switch bankSW1(BANK_SW1);
Switch bankSW2(BANK_SW2);
Switch bankSW3(BANK_SW3);
Switch bankSW4(BANK_SW4);
Switch muteSW(MUTE_SW);

Switch fxSW1(FX_SW1);
Switch fxSW2(FX_SW2);
Switch fxSW3(FX_SW3);
Switch fxSW4(FX_SW4);
Switch fxSW5(FX_SW5);
Switch fxSW6(FX_SW6);
Switch fxSW7(FX_SW7);
Switch fxSW8(FX_SW8);
Switch fxSW9(FX_SW9);

Led bankLED1(BANK_DIODE1);
Led bankLED2(BANK_DIODE2);
Led bankLED3(BANK_DIODE3);
Led bankLED4(BANK_DIODE4);
Led editLED(EDIT_DIODE);
Led muteLED(MUTE_DIODE);

Relay relay1(RELAY1);
Relay relay2(RELAY2);
Relay relay3(RELAY3);
Relay relay4(RELAY4);
Relay relay5(RELAY5);
Relay relay6(RELAY6);
Relay relay7(RELAY7);
Relay relay8(RELAY8);
Relay relay9(RELAY9);
Relay relay10(RELAY10);
Relay relay11(RELAY11);
Relay relay12(RELAY12);
Relay relay13(RELAY13);
Relay relay14(RELAY14);
Relay relay15(RELAY15);
Relay relay16(RELAY16);

Relay relayArray[16]={relay1, relay2, relay3, relay4, relay5, relay6, relay7, relay8, 
                      relay9, relay10, relay11, relay12, relay13, relay14, relay15, relay16};
Led ledArray[5] = {bankLED1, bankLED2, bankLED3, bankLED4, muteLED};

void ledBlink(Led led) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    led.modulo();
    Serial.println("blink");
  }
}

void enableBank(int number){
  currentBank = number;
  
  for(int i=0;i<numberOfEffects;i++){
    if( banks[currentBank][i] == 1) {
      relayArray[2*i].low();
      relayArray[(2*i)+1].low();
    }
    else {
      relayArray[2*i].high();
      relayArray[(2*i)+1].high();
    }
  }
 for (int j=0; j<numberOfEffects; j++){
        if(banks[currentBank][j]) Serial.print("1 ");
        else Serial.print("0 ");
      }
    Serial.println("");

}

void ledsOff(){
  for(int i=0; i<sizeof(ledArray); i++){
    ledArray[i].off();
  }
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

void editBank(){
  while(1){
    
    ledBlink(ledArray[currentBank]);

    if(fxSW2.getState()) {
      banks[currentBank][0] = !banks[currentBank][0];
      enableBank(currentBank);
      delay(300);
    }
    else if(fxSW3.getState()) {
      banks[currentBank][1] = !banks[currentBank][1];
      enableBank(currentBank);
      delay(300);
    }
    else if(fxSW4.getState()) {
      banks[currentBank][2] = !banks[currentBank][2];
      enableBank(currentBank);
      delay(300);
    }
    else if(fxSW5.getState()) {
      banks[currentBank][3] = !banks[currentBank][3];
      enableBank(currentBank);
      delay(300);
    }
    else if(fxSW6.getState()) {
      banks[currentBank][4] = !banks[currentBank][4];
      enableBank(currentBank);
      delay(300);
    }
    else if(fxSW7.getState()) {
      banks[currentBank][5] = !banks[currentBank][5];
      enableBank(currentBank);
      delay(300);
    }
    else if(fxSW8.getState()) {
      banks[currentBank][6] = !banks[currentBank][6];
      enableBank(currentBank);
      delay(300);
    }
    else if(fxSW9.getState()) {
      banks[currentBank][7] = !banks[currentBank][7];
      enableBank(currentBank);
      delay(300);
    }
    
    if(fxSW1.getState()) {
      ledsOff();
      ledArray[currentBank].on();
      
      return;
    }
  }
}

void setup() {

  Serial.begin(9600);

  for(int i=0; i<numberOfBanks; i++){
    for(int j=0; j<numberOfEffects; j++){
      banks[i][j]=1;
    }
  }
 for(int j=0; j<numberOfEffects; j++) banks[4][j]=0;
      
  enableBank(currentBank);
  ledsOff();
  ledArray[currentBank].on();
  
}

void loop() {

  checkForLongPress(fxSW1);
  
  if(editMode){
    editLED.on();
    if(bankSW1.getState()){
      if(currentBank != 0) enableBank(0);
      delay(100);
      ledsOff();
      editBank();
    }
    else if(bankSW2.getState()){
      if(currentBank != 1) enableBank(1);
      delay(100);
      ledsOff();
      editBank();
    }
    else if(bankSW3.getState()){
      if(currentBank != 2) enableBank(2);
      delay(100);
      ledsOff();
      editBank();
    }
    else if(bankSW4.getState()){
      if(currentBank != 3) enableBank(3);
      delay(100);
      ledsOff();
      editBank();
    }
  }
  else{
    if (muteSW.getState() == HIGH && currentBank!=4) {
      enableBank(4);
      ledsOff();
      ledArray[currentBank].on();
    }
    else if (bankSW1.getState() == HIGH && currentBank!=0) {
      enableBank(0);
      ledsOff();
      ledArray[currentBank].on();
    }
    else if (bankSW2.getState() == HIGH && currentBank!=1) {
      enableBank(1);     
      ledsOff();
      ledArray[currentBank].on();
    }
    else if (bankSW3.getState() == HIGH && currentBank!=2) {
      enableBank(2);
      ledsOff();
      ledArray[currentBank].on();
    }
    else if (bankSW4.getState() == HIGH && currentBank!=3) {
      enableBank(3);     
      ledsOff();
      ledArray[currentBank].on();
    }
  } 
}
