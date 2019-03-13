#include "FS.h"
#include "SPIFFS.h"

#define analogInPin 14 //ADC2_CH6
#define burnPin 15
#define ledPin 2

int sensorValue = 0;        // leitura do potenciometro
int outputValue = 0;
int newOutputValue = 0;
int antennaPower;
unsigned long previousMillis = 0;
const long interval = 3000;
int abc = 5;
int bounce = 0;
int burn = 0;
int i = 0;

void setup(){

  pinMode(burnPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  delay(10);

  Serial.println("teste de leitura analógica");

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
 
 //ESCRITA
   File file = SPIFFS.open("/test.txt", FILE_WRITE);

   if(!file){
    Serial.println("There was an error opening the file for writing");
    return;
   }
  
   if(file.print()){
    Serial.println("File was written");
   } else{
    Serial.println("File write failed");
   }
  
   file.close();

 //LEITURA
   File file2 = SPIFFS.open("/test.txt");

   if(!file2){
    Serial.println("Failed to open file for reading");
    return;
   }
   Serial.println("File Content: ");
   while(file2.available()){

      Serial.write(file2.read());
   }
   file2.close();
   Serial.println("");
}



void loop(){

  sensorValue = analogRead(analogInPin);            
  outputValue = map(sensorValue, 0, 4095, 0, 32);  

 int sensorBut = digitalRead(burnPin);

  while(sensorBut == LOW || burn == 1){
    burn = 1;
    Serial.println("Modo de configuração das antenas");
    Serial.println("Por favor, configure a potência das antenas no potênciometro.");
    blinkLed();
    while(newOutputValue == 0){
      attAntena();
    }
    ;
    for(int i=0; sensorBut == LOW; i++){
      Serial.println(i);
      sensorBut = digitalRead(burnPin);
    }
    sensorBut = digitalRead(burnPin);
    if(sensorBut == LOW && i == 2){
      antennaPower = newOutputValue;
      Serial.print(" A nova configuração de potência das antenas é de: ");
      Serial.println(antennaPower);
      Serial.println("");
      bounce = 1;
    }else if(sensorBut == HIGH && i == 2){
      i = 0;
    }
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
  }


  delay(100);
}

void blinkLed(){
int blink = 0;
while(blink < 6){
digitalWrite(ledPin, HIGH);
delay(250);
digitalWrite(ledPin, LOW);
delay(250);
blink++;
}
}

void attAntena(){
  if((newOutputValue - outputValue > 1) ||(newOutputValue - outputValue <-1)){ 
    Serial.print("output = ");      
    Serial.println(outputValue); 
    newOutputValue = outputValue; 
  }
}
