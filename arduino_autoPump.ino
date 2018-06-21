
#define rel_pin  9

int millisec = 1000;
unsigned long int waitTime = 30;
unsigned long int delayTime = 15;
unsigned long int currentTime = 0;

void setup() {
  pinMode(rel_pin, OUTPUT);
  digitalWrite(rel_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  
  if (digitalRead(rel_pin) == 1) {
    Serial.println((millis()- currentTime)/millisec);
    if ((millis() - currentTime) >= waitTime*millisec) {
      digitalWrite(rel_pin, LOW);
      currentTime = millis();
      Serial.println("Pump Enabled");
    }
  } else if(digitalRead(rel_pin) == 0){
    Serial.println((millis()- currentTime)/millisec);
    if((millis() - currentTime) >= delayTime*millisec){
      digitalWrite(rel_pin,HIGH);
      currentTime = millis();
      Serial.println("Pump Disabled");
    }
  }
}

