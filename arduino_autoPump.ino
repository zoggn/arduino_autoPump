#define button1 3
#define rel_pin  9

int millisec = 1000;
unsigned long int waitTime = 30;
unsigned long int delayTime = 15;
unsigned long int currentTime = 0;

void setup() {
  pinMode(button1, INPUT_PULLUP);
  attachInterrupt(1,OnButtonClick,FALLING);
  pinMode(rel_pin, OUTPUT);
  digitalWrite(rel_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  
  if (digitalRead(rel_pin) == 1) {
    if ((millis() - currentTime) >= waitTime*millisec) {
      digitalWrite(rel_pin, LOW);
      currentTime = millis();
      Serial.println("Pump Enabled");
    }
  } else if(digitalRead(rel_pin) == 0){
    if((millis() - currentTime) >= delayTime*millisec){
      digitalWrite(rel_pin,HIGH);
      currentTime = millis();
      Serial.println("Pump Disabled");
    }
  }
}

void OnButtonClick(){
  Serial.println("Button Pressed");
}

