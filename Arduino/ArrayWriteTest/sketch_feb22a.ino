int array[13]={0,0,0,0,0,0,1,1,0,0,0,0,0};
void initPin(){
  for(int i = 0;i<=12;i++){
    pinMode(i+1,OUTPUT);
    }
  }

void arrayWrite(int array[13]){
  for(int i = 0;i<=12;i++){
    digitalWrite(i+1,array[i]);
  }
}
int readHum(){
  return analogRead(A0);
}
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    initPin();
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(7,1);
    digitalWrite(8,1);

} 
