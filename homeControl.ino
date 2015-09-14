short _pinStatus[] = {-88, -88, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, -1};

void setPinMode(int pin, int pinStatus){
  if(pinStatus == -1){
    pinMode(pin,INPUT);
    _pinStatus[pin] = pinStatus;
    attachInterrupt(digitalPinToInterrupt(pin), changedInput, CHANGE);
    return;
  }
  if(pinStatus < 2){
    pinMode(pin,OUTPUT);
    setPinLevel(pin, pinStatus);
  }
}

int readPinLevel(int pin){
  return digitalRead(pin);
}

void changedInput(){
  for(int i = 0; i< 14; i++){
    if(_pinStatus[i] == 2){
      int value = digitalRead(i);
      sendDigitalValue(i,value);
    }
  }
  for(int i = 4; i < 12; i++){
    setPinLevel(i,1);
    delay(1000);
  }
  for(int i = 4; i < 12; i++){
    setPinLevel(i,0);
    delay(1000);
  }
}

void readAnalogPin(short pin){
  int value = analogRead(pin);
  sendAnalogValue(pin, value);
}

void sendAnalogValue(short pin, int value){
  sendValue(B10111, pin,value);
}

void sendStatus(short pin){
  sendValue(B10100, pin, _pinStatus[pin]);
}

void sendDigitalValue( short pin, int value){
  sendValue(B10101, pin,value);
}
void sendValue(byte x, short pin,int value){
  char msg[] = {x+32, char(pin+48), char(value+48), '\n'};
  Serial.write(msg);
}


void setPinLevel(int pin, int pinStatus){
  if(pinStatus == 0){
    digitalWrite(pin, LOW);
    _pinStatus[pin] = pinStatus;
  }
  if(pinStatus == 1){
    digitalWrite(pin, HIGH);
    _pinStatus[pin] = pinStatus;
  }
}

void setup() {
 Serial.begin(9600);
 
 for(int i = 0; i< 14; i++){
  setPinMode(i,_pinStatus[i]); 
 }

 Serial.write("Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
 
  //changedInput();
  
  /*for(int i=0; i< 6; i++){
    readAnalogPin(i);
    delay(250);
  }
  delay(5000);
  for(int i=0; i< 14; i++){
    sendStatus(i);
  }*/
  //readAnalogPin(1);
  int i= digitalRead(13);
  sendStatus(13);
  if(i == HIGH){
    for(int i = 0; i< 13; i++){
      setPinLevel(i,1); 
      delay(400);
    }
  }
  delay(100);
  for(int i = 0; i< 13; i++){
    setPinLevel(i,1); 
    delay(400);
  }
  for(int i = 0; i< 13; i++){
    setPinLevel(i,0); 
    delay(1);
  }
  

}
