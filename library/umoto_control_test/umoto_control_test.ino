// Test uMoto board

int dataPin = 5;
int latchPin = 6;
int clockPin = 7;

const int boardCount = 2;

const int motorCount  = boardCount * 2;

byte motorStates[boardCount];

void updateMotors() {
  digitalWrite(latchPin, LOW);

  for (int i = boardCount-1; i >= 0; i--) {
    shiftOut(dataPin, clockPin, MSBFIRST, motorStates[i]);  
  }  

  digitalWrite(latchPin, HIGH);  
}


void setMotorState(int motorNumber, boolean pinOne, boolean pinTwo, boolean pwmPin, boolean standby) {
  int boardNumber = motorNumber / 2;
  int portNumber = motorNumber % 2;

  int offset = portNumber > 0 ? 4 : 0;
  
  bitWrite(motorStates[boardNumber], offset + 0, pwmPin); 
  bitWrite(motorStates[boardNumber], offset + 1, pinOne); 
  bitWrite(motorStates[boardNumber], offset + 2, pinTwo); 
  bitWrite(motorStates[boardNumber], offset + 3, standby); 
          
}

void setMotorOn(int motorNumber, boolean dir) {

  setMotorState(motorNumber, dir, !dir, true, true);    
  updateMotors();  
}

void setMotorOff(int motorNumber) {

  setMotorState(motorNumber, false, false, false, false);    
  updateMotors();  
  
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  for (int i = 0; i < motorCount; i++) {
    setMotorOff(i);
  }
}



void loop() {

  for (int motor = 0; motor < motorCount; motor++) {
  
    setMotorOn(motor, true);  
    delay(1000);
    setMotorOff(motor);
    delay(100);
    setMotorOn(motor, false);  
    delay(1000);
    setMotorOff(motor);
    
  }

  delay(1000);
}


