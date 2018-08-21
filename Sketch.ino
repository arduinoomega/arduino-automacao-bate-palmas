/*Código por Lucas Soares Gomes
*Acionar Relé com 2 palmas
*/
#define tmpMaxPalma  100
#define tmpMaxPalmas 500
#define pinMic 7
#define pinRelay 8

unsigned long tmpEspera = 0;
unsigned long tmpPalmas = 0;
int sensorMic;
int contPalmas = 0;
void Action();

void setup() {
  pinMode(pinMic, INPUT);
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, HIGH); //Ligar arduino com Relé desligado
}

void loop() {
  /*Normalmente o sensor mantém sua porta ligada até que uma palma seja detectada.
  A função digitalRead() faz a leitura contínua do microfone de eletreto.
  */
   sensorMic = digitalRead(pinMic);

  //Palma detectada
  if (sensorMic == LOW) {

     /* É necessário um tempo para que uma palma não seja detectada novamente.
      * Incrementamos o contador a cada detecção.
      */
     if ((millis() - tmpEspera) >= tmpMaxPalma) {
        tmpEspera = 0;
     } else if (tmpEspera == 0) {
        tmpEspera = tmpPalmas = millis(); 
        contPalmas++;
     }
  }

  //Para o tempo excedido zeramos o contador de palmas.
  if (((millis() - tmpPalmas) > 500) && (contPalmas != 0)) {
     Action();
     tmpPalmas = millis();
     contPalmas = 0;
  }
}

void Action() {
  /*
   * Pode ser utilizado o switch no lugar do if para mais casos de uso de 3 ou mais palmas.
   */
   if(contPalmas == 2){
    digitalWrite(pinRelay, !digitalRead(pinRelay));
   }
}
