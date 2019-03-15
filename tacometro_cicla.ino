#include <LCD5110_Graph.h> //Declaramos la libreria LCD5110_Graph

#define rueda 2.20

char PinInterrupt = 2;
char pinLed = 1;
float tiempo = 0;
long int ftime = 0;
long int ltime = 0;
float velocidad = 0;
float distancia = 0;
int cont = 0;
char initband= 0;
const float Pi = 3.14159;
long int stoptime = 0;
long int tiemp = 0;
char dist[6];
char vel[6];
char imprimir = 0;
extern uint8_t TinyFont [];
extern uint8_t SmallFont [];
LCD5110 lcd(8,9,10,11,12);//los pines en donde estara conectada nuestra pantalla 

void setup() {
  Serial.begin(9600);
  pinMode(PinInterrupt, INPUT);
  lcd.InitLCD();
  //attachInterrupt(digitalPinToInterrupt(PinInterrupt), blink, LOW);
  // put your setup code here, to run once:
  lcd.clrScr(); //Limpiamos la pantalla 
  //lcd.drawBitmap(0, 0, logo_electronilab_84x48, 80, 45); //Hacemos el llamado a nuestra imagen 
  lcd.setFont(SmallFont);
  lcd.print("A.I.D.",CENTER,5);
  lcd.print("BioHacking",CENTER,15);
  lcd.print("Colombia",CENTER,25);
  lcd.update();
  delay(4000); 

}

void loop() {
  
  if(pulseIn(PinInterrupt, LOW) > 10){
   cont = 0;
    if(initband == 0){
      ftime = millis();
      initband = 1;
    }else if(initband == 1){
      ltime = millis();
      imprimir = 1;
    }

    if(imprimir == 1){
      imprimir = 0;
      tiempo = ltime - ftime;
      ftime = ltime;
      tiempo = tiempo / 1000;
      velocidad = rueda / tiempo;
      velocidad = (velocidad / 1000) * 3600;
      initband = 1;
      distancia = distancia + rueda;
      
     lcdShow();
     delay(1000);
      Serial.println("Velocidad: ");
      Serial.print(velocidad);
      Serial.println(" km/h");
      Serial.println("\n");
      Serial.println("Distancia: ");
      Serial.print(distancia);
      Serial.println(" m");
 
      Serial.println("//////////////////////////////////////////////////////////");
      
    }
   
  }
   
      stoptime = millis();
      tiemp = stoptime - ltime;
      if(tiemp > 3000 && ltime == ftime && cont == 0){
        initband = 0;
        cont = 1;
        velocidad = 0;
        lcdShow();
        Serial.println("Velocidad: ");
        Serial.print(velocidad);
        Serial.println(" km/h");
        Serial.println("\n");
        Serial.println("Distancia: ");
      Serial.print(distancia);
      Serial.println(" m");
 
      Serial.println("//////////////////////////////////////////////////////////");
     
      }

  }
  void convertToString(float number, float number1)
{
   dtostrf(number, 3, 1, dist);
   dtostrf(number1, 3, 1, vel);
}

void lcdShow(){
  convertToString(distancia, velocidad);

  lcd.clrScr();
  lcd.setFont(SmallFont);
  lcd.print("Tacometro",15,0);
  lcd.print("Dist: ",0,11);
  lcd.print(dist,35,11);
  lcd.print("Vel: ",0,22);
  lcd.print(vel,35,22);
  lcd.update(); 
}



