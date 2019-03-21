#define LEDVM 21
#define LEDVD 4
#define bot 14

int bounce = 0;

void setup() {
 Serial.begin(115200);
 Serial1.begin(115200);

 pinMode(LEDVM, OUTPUT);
 pinMode(LEDVD, OUTPUT);
 pinMode(bot, INPUT_PULLUP);

 digitalWrite(LEDVM, LOW);
 digitalWrite(LEDVD, LOW);



 Serial.println("Setup Completo \nPronto para o teste"); 
}

void loop() {
  

  int botState = digitalRead(bot);

  if(Serial1.available()>0){
    int comando = Serial1.read();
    //Serial.println(comando);
    if (comando == '3'){
      digitalWrite (LEDVM, HIGH);
      Serial.print(comando);
      Serial.println(" --> Ligando Led Vermelho");
    } else if (comando == '4'){
      digitalWrite (LEDVM, LOW);
      Serial.print(comando);
      Serial.println(" --> Desligando Led Vermelho");
    }
   }

  if(botState == LOW && bounce == 0){
    //Serial.println(botState);
    digitalWrite(LEDVD, HIGH);
    Serial.println("1 --> Ligando Led Verde");
    Serial1.write("1");
    bounce = 1;
    delay(50);}
    else if(botState == HIGH && bounce == 1){
     // Serial.println(botState);
      digitalWrite(LEDVD, LOW);
      Serial.println("2 --> Desligando Led Verde");
      Serial1.write("2");
      bounce =  0;
      delay(50);      
    } 
  }
