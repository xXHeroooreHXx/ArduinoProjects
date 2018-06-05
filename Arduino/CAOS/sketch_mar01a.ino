#include <dht.h>

#include <LCD.h>

#include <LiquidCrystal.h>
#define DHT11_PIN -10
#define FAN_PIN  -1
bool fan = false;
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(FAN_PIN, OUTPUT);
  delay(100);
  lcd.print("CAOS 0.1");
  lcd.setCursor(0, 1);
  lcd.print("Hello World");
  Serial.print("Bienvenido a CAOS v0.1\n");
  delay(100);
}

void loop() {

  // put your main code here, to run repeatedly:

  if (Serial.available() > 0){
    processInput();
    Serial.println("$ ");
  }
}

int trocearCadena(char* cadena, char* trozos[])
{
  int i = 1;

  if ((trozos[0] = strtok(cadena, " \n\t")) == NULL)
    return 0;
  while ((trozos[i] = strtok(NULL, " \n\t")) != NULL)
    i++;
  return i;
}

int buscarComando(char *trozo) {
  int i;
  String comandos[] = {"show","encender","apagar","auto","cambiarFase","imprimir","hola","\0"};
  for(i=0;(strcmp(comandos[i].c_str(), "\0")!= 0);i++){
    if (strcmp(comandos[i].c_str(),trozo) == 0)
      return i;
  }
  return -1;
}
String obtenerEntrada(){
   char character;
   String content;
   while(Serial.available()) {
    character = Serial.read();
    content.concat(character);
  }
  content.toLowerCase();
  return content;
}
void processInput() {
  char *trozos[10];
  String cadena(Serial.readString());
  cadena.toLowerCase();
  trocearCadena((cadena.c_str()), trozos);
  int opcion = buscarComando(trozos[0]);
  String message(trozos[1]);
  message.concat(" ");
  message.concat(trozos[2]);
  switch (opcion) {
    case 0 :
      displayTemp();
      break;
    case 1:
      power(trozos[1], true);
      break;
    case 2:
      power(trozos[1], false);
      break;
    case 3:
      automatic();
      break;
    case 5:
      lcd.clear();
      lcd.print("CAOS 0.1");
      lcd.setCursor(0,1);
      lcd.print(message);
      Serial.println("Imprimiendo en pantalla...");
      break;
    case 6:
      Serial.println("Hola amigo! Me alegra mucho saber que estás conmigo");
      break;
    case -1:
      Serial.println("Comando no encontrado");
      break;
  }
}

void power(char *instrumento, bool onoff) {
  Serial.print("Encendiendo...");
  if ((strcmp(instrumento, "fan") == 0) || (strcmp(instrumento, "ventilador") == 0)) {
       if((fan == false)&&(onoff == true)){
         Serial.println("Encendiendo ventilador....");
         digitalWrite(FAN_PIN, LOW);
         fan = true;
       }
      else if((fan == true)&&(onoff == false)){
          Serial.println("Apagando ventilador....");
          digitalWrite(FAN_PIN, HIGH );
          fan = false;
     }
  }
}

void displayTemp() {
  dht DHT;
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
}


void automatic(){
  dht DHT;
  int chk = DHT.read11(DHT11_PIN);
  int temp;
  char* fan = strdup("fan");
  Serial.println("Modo Automatico: Envie cualquier caracter para detener");
  while(Serial.available() == 0){
  chk = DHT.read11(DHT11_PIN);
  temp=DHT.temperature;
  Serial.println(temp);
  if(temp>= 26){
    digitalWrite(FAN_PIN,LOW);
  }else{
    digitalWrite(FAN_PIN,HIGH);
  }
  delay(10000);
  }
  Serial.println("Dejando modo automatico");
  Serial.readString();
}


