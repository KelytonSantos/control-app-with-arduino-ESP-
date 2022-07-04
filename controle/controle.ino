  #include <LiquidCrystal_I2C.h>

#include <DHT.h>
#include <IRremote.h> //INCLUSÃO DE BIBLIOTECA

#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


 
int RECV_PIN = 2; 
IRrecv irrecv(RECV_PIN); 
decode_results results; 

int LIGAR = 0x6D5D1DB3 ; //16580863
//_________________________________________________________
int VOL_MAIS = 0xE17A6897 ;  //16613503
int VOL_MENOS =0xE17AE817; //16617583

int VOLTAR = 0xE17A18E7 ;//16589023
int AVANCAR = 0xE17A9867; //16605343
//_________________________________________________________
int UM = 0xE17A807F;// 16582903;
int DOIS =0xE17A40BF ; //16615543;
int TREIS =0xE17AC03F ; //16599223;

int QUATRO =0xE17A20DF ; //16590855;
int CINCO =0xE17AA05F ; //16623703;
int SEIS =0xE17A609F ; //16607383;
//_________________________________________________________
 int x = 25;  

 int y = 50;
 int valor;
 int linguagem = 1;
 int modo = 1;
 int graus_x;
 int graus_temp;
 int bola;
 char simbolo;


#define ventilador 6
#define humidificador 7





void setup(){
  
  Serial.begin(9600); 
  irrecv.enableIRIn(); 

dht.begin();
  
  pinMode(ventilador, OUTPUT); 
  pinMode(humidificador, OUTPUT);
}
 












void loop(){
  
float humi = dht.readHumidity();
 float temp = dht.readTemperature();
 
if (isnan(temp) || isnan(humi)) 
  {
    Serial.println("Failed to read from DHT");
  } 


 
  if (irrecv.decode(&results)) {
    
    Serial.print("HEX: ");
    Serial.println(results.value, HEX); 
    Serial.println(""); 
    irrecv.resume(); 
  }
  
      
     
//________________________________________________________________
  while(results.value == 0x6D5D1DB3){
        digitalWrite(ventilador,LOW);
        digitalWrite(humidificador,LOW);
    
       if (irrecv.decode(&results)) {  
         irrecv.resume();} 
    
    /* vai desligar o dislpay também*/}
  
 //__________________________________________________________
    
    
     if(results.value == 0x4B12992B && 0x7E16B93A){
         x = x+5;
         results.value = 0;}
 
     else if(results.value == 0x1BE8C80D && 0xC2A82EEA)  {
         x= x-5;   
        results.value = 0;}


     else if (results.value == 0xE17A08F7)  {
           y=y+5;  
           results.value = 0;}

     else if(results.value == 0xE17A58A7)  {
        y=y-5; 
        results.value = 0;}
  //__________________________________________________________

  
   if(results.value == 0xE17A20DF)
      modo = 1;
  
  else if(results.value == 0xE17AA05F)
      modo = 2;
    
  else if(results.value == 0xE17A609F)
      modo = 3;
  
    
      
    if(modo == 1){
    graus_x = x  ;
      graus_temp = temp;
     simbolo = 'C';
    bola = 0;
  }
  
    else if(modo == 2){
    graus_x = (x * 1.8) + 32 ;
      graus_temp = (temp * 1.8) + 32;
      simbolo = 'F';
      bola = 0;
  }
  
    else if(modo == 3){
     graus_x = x + 273.15 ;
      graus_temp = temp + 273.15;
      simbolo = 'K';
      bola = 1;
  }
  
 //__________________________________________________________
  
   if(results.value == 0xE17A807F )
      linguagem = 1;
  
  else if(results.value == 0xE17A40BF )
      linguagem = 2;
    
  else if(results.value == 0xE17AC03F)
      linguagem = 3;
    
    
    
    if( bola == 1){
       if (linguagem == 1){
     Serial.print("atual: ");
     Serial.print(humi);
     Serial.print("%     ");
     Serial.print(graus_temp);
     Serial.println(simbolo);
     Serial.print("optada: ");
     Serial.print(y);
     Serial.print("%     ");
     Serial.print(graus_x);
     Serial.println(simbolo);
     Serial.println("");
     Serial.println("");
     Serial.println("");    
  }
    
     else if (linguagem == 2){
     Serial.print("actual: ");
     Serial.print(humi);
     Serial.print("%     ");
     Serial.print(graus_temp);
       Serial.println(simbolo);
     Serial.print("chosen: ");
     Serial.print(y);
     Serial.print("%     ");
     Serial.print(graus_x);
          Serial.println(simbolo);
     Serial.println("");
     Serial.println("");
     Serial.println("");
  }
    
    else if (linguagem == 3){
     Serial.print("actual: ");
     Serial.print(humi);
     Serial.print("%     ");
     Serial.print(graus_temp);
     Serial.println(simbolo);
     Serial.print("elegido: ");
     Serial.print(y);
     Serial.print("%     ");
     Serial.print(graus_x);
     Serial.println(simbolo);
     Serial.println("");
     Serial.println("");
     Serial.println("");
    
    }
  
  }    
  else{
    if (linguagem == 1){
     Serial.print("atual: ");
     Serial.print(humi);
     Serial.print("%     ");
     Serial.print(graus_temp);
    Serial.print("*");
     Serial.println(simbolo);
     Serial.print("optada: ");
     Serial.print(y);
     Serial.print("%     ");
     Serial.print(graus_x);
    Serial.print("*");
     Serial.println(simbolo);
     Serial.println("");
     Serial.println("");
     Serial.println("");
     
  }
  
     else if (linguagem == 2){
     Serial.print("actual: ");
     Serial.print(humi);
     Serial.print("%     ");
     Serial.print(graus_temp);
     Serial.print("*");
     Serial.println(simbolo);
     Serial.print("chosen: ");
     Serial.print(y);
     Serial.print("%     ");
     Serial.print(graus_x);
     Serial.print("*");
     Serial.println(simbolo);
     Serial.println("");
     Serial.println("");
     Serial.println("");
  }
     
    else if (linguagem == 3){
     Serial.print("actual: ");
     Serial.print(humi);
     Serial.print("%     ");
     Serial.print(graus_temp);
     Serial.print("*");
     Serial.println(simbolo);
     Serial.print("elegido: ");
     Serial.print(y);
     Serial.print("%     ");
     Serial.print(graus_x);
     Serial.print("*");
     Serial.println(simbolo);
     Serial.println("");
     Serial.println("");
     Serial.println("");
    
    }}

  
   

  delay(1000); 
 //__________________________________________________________
    
  
  
  
  //__________________________________________________________
    
   if (x >= temp ){
          digitalWrite(ventilador,HIGH);  }
          
             else {
              digitalWrite(ventilador,LOW);}
  
        if (y <= humi ){
          digitalWrite(humidificador,HIGH);  }
          
             else {
              digitalWrite(humidificador,LOW);}
  //__________________________________________________________

  
}
