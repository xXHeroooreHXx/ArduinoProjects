void tirada(){
  if(random(0,11)>=5){
    digitalWrite(12,HIGH);
  }
  else{
    digitalWrite(13,HIGH);
  }
}

void encendido(){
    pinMode(12,OUTPUT); 
  pinMode(13,OUTPUT);
  for(int i=0; i<10; i++){
     digitalWrite(12,HIGH);
     delay(100);
     digitalWrite(12,LOW);
     digitalWrite(13,HIGH);
     delay(100);
     digitalWrite(13,LOW);
  }
  }

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  encendido();
  tirada();
}


void loop() {
  // put your main code here, to run repeatedly:

  
}
