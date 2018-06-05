#define LVERDE 2
#define LAMARILLO 4
#define LROJO 7
#define MEDIDOR 0
#define DELAY 2000
float readAnalogVoltage(int pin){
  float voltage;
  while(voltage == 0){ 
   voltage = analogRead(pin) * 0.0048;
   delay(10);
   if(voltage != analogRead(pin) * 0.0048)
    voltage=0;
   Serial.print(voltage);
   Serial.print("v\n");
  }
  return voltage;
}
void pinDisplay(float voltage){
  
  if(voltage >= 1.6){
    digitalWrite(LVERDE,HIGH);
    delay(100);
    digitalWrite(LVERDE,LOW);
  }else if (voltage >= 1.4){
    digitalWrite(LAMARILLO,HIGH);
    delay(100);
    digitalWrite(LAMARILLO,LOW);
  }else{
    digitalWrite(LROJO,HIGH);
    delay(100);
    digitalWrite(LROJO,LOW);
  }
}
void onAnimation(){
  digitalWrite(LVERDE,HIGH);
  delay(100);
  digitalWrite(LAMARILLO,HIGH);
  delay(100);
  digitalWrite(LROJO,HIGH);
  delay(100);
  digitalWrite(LVERDE,LOW);
  delay(100);
  digitalWrite(LAMARILLO,LOW);
  delay(100);
  digitalWrite(LROJO,LOW);
  delay(100);
}
void setup() {
  Serial.begin(9600);
  pinMode(LVERDE,OUTPUT); 
  pinMode(LAMARILLO,OUTPUT);
  pinMode(LROJO,OUTPUT);
  onAnimation();
}

void loop() {
  // put your main code here, to run repeatedly:
  pinDisplay(readAnalogVoltage(MEDIDOR));

    
  
}

