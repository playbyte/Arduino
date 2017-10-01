/* ################## Test RTC DS3231 #############################
* Filename: RTC_DS3234_Ej2.ino
* Descripción: Puesta en hora RTC DS3234
* Autor: Jose Mª Morales
* Revisión: 29-09-2017
* Probado: ARDUINO UNO r3 - IDE 1.8.2 (Windows7)
* Web: www.playbyte.es/electronica/
* Licencia: Creative Commons Share-Alike 3.0
* http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ##############################################################
  
  CLK  pin D13
  MOSI pin D11
  MISO pin D12
  SS   pin D8
*/

#include <SPI.h>
const int ss = 8;   //chip select 
String texto = "";

// valores a introducir para configurar el RTC
// ===========================
int ano = 17;   // 0-99
int mes = 9;   // 1-12
int dia = 29;   // 1-31
int hora= 12;   // 0-23
int min = 18;   // 0-59
int seg = 00;   // 0-59
// ===========================

void setup() {
   
   Serial.begin(9600);
   RTC_init();
  
   Serial.println("########################################"); 
   Serial.println("Puesta en hora del modulo RTC DS3234");
   Serial.print("Fecha actual: ");
   print_time();    // imprime hora actual del RTC
   Serial.println("########################################"); 
   Serial.println("");   
   Serial.println("Pulsa ENTER para actualizar a"); 
   texto = "Fecha Nueva-> "
              + String(dia) + "/"
              + String(mes) + "/"
              + String(ano) + " Hora-> "
              + String(hora)+ ":"
              + String(min) + ":"
              + String(seg);
   Serial.println(texto);
   
   Serial.println("======================================");  
}


void loop() {

  if(Serial.available())  {
    int inputByte = Serial.read(); // lee byte entrante
       
    if (inputByte==13) {       // caracter fin de linea
      SetTimeDate(dia,mes,ano,hora,min,seg); 
      Serial.print("Nueva Fecha actualizada: ");
      print_time();           // imprime hora actual del RTC   
    }
  }

}//=====================================


int RTC_init(){ 

    pinMode(ss,OUTPUT); // Chip Select
    SPI.begin();        // Inicia libreria SPI
    SPI.setBitOrder(MSBFIRST); 
    SPI.setDataMode(SPI_MODE3); // Ambos modos 1 y 3 deberían funcionar 
    
    digitalWrite(ss, LOW);  // Set Control 
    SPI.transfer(0x8E);
    SPI.transfer(0x60); // 60= Desactiva Oscilador, Alarmas, onda SQ @1hz, compensacion temperatura
    digitalWrite(ss, HIGH);
    delay(10);
}
//=====================================


int SetTimeDate(int d, int mo, int y, int h, int mi, int s){ 

  int TimeDate [7]={s,mi,h,0,d,mo,y};
  for(int i=0; i<=6;i++){
    if(i==3)
      i++;
    int b= TimeDate[i]/10;
    int a= TimeDate[i]-b*10;
    if(i==2){
      if (b==2)
        b=B00000010;
      else if (b==1)
        b=B00000001;
    } 
    TimeDate[i]= a+(b<<4);
      
    digitalWrite(ss, LOW);
    SPI.transfer(i+0x80); 
    SPI.transfer(TimeDate[i]);        
    digitalWrite(ss, HIGH);
  }
}
//=====================================

void print_time() {

  texto = "";
  int TimeDate [7];    //seg,min,hora,null,dia,mes,ano    
  
  for(int i=0; i<=6;i++){
    if(i==3)
      i++;
    digitalWrite(ss, LOW);
    SPI.transfer(i+0x00); 
    unsigned int n = SPI.transfer(0x00);        
    digitalWrite(ss, HIGH);
    int a=n & B00001111;    
    if(i==2){ 
        int b=(n & B00110000)>>4; // modo 24 horas
        if(b==B00000010)
          b=20;        
        else if(b==B00000001)
          b=10;
        TimeDate[i]=a+b;
      }
    else if(i==4){
        int b=(n & B00110000)>>4;
        TimeDate[i]=a+b*10;
    }
    else if(i==5){
        int b=(n & B00010000)>>4;
        TimeDate[i]=a+b*10;
    }
    else if(i==6){
        int b=(n & B11110000)>>4;
        TimeDate[i]=a+b*10;
    }
    else{ 
        int b=(n & B01110000)>>4;
        TimeDate[i]=a+b*10; 
      }
  }
    texto.concat(TimeDate[4]); 
    texto.concat("/") ;
    texto.concat(TimeDate[5]);
    texto.concat("/") ;
    texto.concat(TimeDate[6]);
    texto.concat(" -->  ") ;
    texto.concat(TimeDate[2]);
    texto.concat(":") ;
    texto.concat(TimeDate[1]);
    texto.concat(":") ;
    texto.concat(TimeDate[0]);
    Serial.println(texto);
}

