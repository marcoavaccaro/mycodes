#define LEDVM 21
#define LEDVD 4
#define bot 14

int bounce = 0;

void setup() {
 Serial.begin(115200);
 Serial2.begin(115200);

 pinMode(LEDVM, OUTPUT);
 pinMode(LEDVD, OUTPUT);
 pinMode(bot, INPUT_PULLUP);

 digitalWrite(LEDVM, LOW);
 digitalWrite(LEDVD, LOW);



 Serial.println("Setup Completo \nPronto para o teste"); 
}

void loop() {
  

  int botState = digitalRead(bot);

  if(Serial2.available()>0){
    uint8_t comando = Serial2.read();
    //Serial.println(comando);
    if (comando == '1'){
      digitalWrite (LEDVD, HIGH);
      Serial.print(comando);
      Serial.println(" --> Ligando Led Verde");
    } else if (comando == '2'){
      digitalWrite (LEDVD, LOW);
      Serial.print(comando);
      Serial.println(" --> Desligando Led Verde");
    }
   }

  if(botState == LOW && bounce == 0){
    //Serial.println(botState);
    digitalWrite(LEDVM, HIGH);
    Serial.println("1 --> Ligando Led Vermelho");
    Serial2.write("3");
    bounce = 1;
    delay(50);}
    else if(botState == HIGH && bounce == 1){
     // Serial.println(botState);
      digitalWrite(LEDVM, LOW);
      Serial.println("2 --> Desligando Led Vermelho");
      Serial2.write("4");
      bounce =  0;
      delay(50);      
    } 
  }
