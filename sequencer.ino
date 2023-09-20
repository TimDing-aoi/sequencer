const char _juice = 'j'; // 4
const char _filereset = 'f'; // 1
const char _start = 's'; // 2
const char _end = 'e'; // 3
const char _delay = 'p'; // 8
const char _video = 'v'; // 16
const char _stop = 'x'; // 17
const char _stim = 'm';  // 5
                                                                                      
void setup() {
  // put your setup code here, to run once:
//  for (int i = 8; i < 16; i++){
//    pinMode(i, OUTPUT);
//    digitalWrite(i, HIGH);
//    delay(500);
//    digitalWrite(i, LOW);
//  }
  pinMode(15, OUTPUT);
  pinMode(16, INPUT_PULLUP);
  Serial.begin(1000000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!Serial.available()){
    if (digitalRead(16) == HIGH) {
      digitalWrite(15, LOW);
    }
    else {
      digitalWrite(15, HIGH);
    }
  }
  if (Serial.read() == 'i'){
    Serial.println("read");
    char type = Serial.read();
    int len = Serial.available() + 1;
    char buf[len];
    for (int i = 0; i < len; i++){
      buf[i] = Serial.read();
    }
    int t = atoi(buf);

    switch (type){
      case _juice:
        digout(0,0,0,0,0,1,0,0);
        digout(0,1,0,0,0,1,0,0);
        delayMicroseconds(1000);
        digout(0,0,0,0,0,0,0,0);
        activateValve(t);
        break;
      case _filereset:
        digout(0,0,0,0,0,0,0,1);
        delayMicroseconds(t);
        digout(0,1,0,0,0,0,0,1);
        delayMicroseconds(100);
        digout(0,0,0,0,0,0,0,0);
        break;
      case _start:
        digout(0,0,0,0,0,0,1,0);
        digout(0,1,0,0,0,0,1,0);
        delayMicroseconds(t);
        digout(0,0,0,0,0,0,0,0);
        break;
      case _end:
        digout(0,0,0,0,0,0,1,1);
        digout(0,1,0,0,0,0,1,1);
        delayMicroseconds(t);
        digout(0,0,0,0,0,0,0,0);
        break;
      case _delay:
        digout(0,0,0,0,1,0,0,0);
        digout(0,1,0,0,1,0,0,0);
        delayMicroseconds(t);
        digout(0,0,0,0,0,0,0,0);
        break;
      case _video:
        digout(0,0,0,1,0,0,0,0);
        digout(0,1,0,1,0,0,0,0);
        delayMicroseconds(t);
        digout(0,0,0,0,0,0,0,0);
        break;
      case _stop:
        digout(0,0,0,1,0,0,0,1);
        digout(0,1,0,1,0,0,0,1);
        delayMicroseconds(t);
        digout(0,0,0,0,0,0,0,0);
        break;
      case _stim:
        digout(0,0,0,0,0,1,0,1);
        digout(0,1,0,0,0,1,0,1);
        delayMicroseconds(t);
        digout(0,0,0,0,0,0,0,0);
        break;
    }
  }
  else {
    char buf[4];
    //Serial.println(Serial.available());
    for (int i = 0; i <= Serial.available() + 1; i++){
      buf[i] = Serial.read();
      //Serial.println(buf[i]);
    }
    int t = atoi(buf);
    activateValve(t);
  }
}

void activateValve(int t) {
    //Serial.println("HIGH");
    digitalWrite(15,HIGH);
    delay(t);
    digitalWrite(15,LOW);
    //Serial.println("LOW");
}

void digout(int pin0, int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7){
  int pins[8] = {pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7};
  for (int i = 0; i < 8; i++){
    digitalWrite(15 - i, pins[i] == 1 ? HIGH : LOW);
  }
}
