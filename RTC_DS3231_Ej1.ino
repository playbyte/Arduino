/* ################## Test RTC DS3231 #############################
* Filename: RTC_DS3231_Ej1.ino
* Descripción: Puesta en hora RTC DS323
* Autor: Jose Mª Morales
* Revisión: 6-04-2017
* Probado: ARDUINO UNO r3 - IDE 1.8.2 (Windows7)
* Web: www.playbyte.es/electronica/
* Licencia: Creative Commons Share-Alike 3.0
* http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ##############################################################
*/

// valores a introducir para configurar el RTC
// ===========================
int ano = 2017; // 0-2099
int mes = 9;   // 0-12
int dia = 27;   // 0-31
int hora= 14;   // 0-23
int min = 9;   // 0-59
int seg = 00;   // 0-59
// ===========================

#include <Wire.h>    // Comunicacion I2C 
#include "RTClib.h"  // libreria ADAFRUIT para DS3231 

RTC_DS3231 RTC;      // creamos el objeto RTC

String dia_semana[]={"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
String newdate = "";


void setup() {

  Serial.begin(9600);
//  Wire.begin(); // Inicia Wire sólo si no se hace dentro de la librería 
//  supone que se usa Wire para comunicar con otros dispositivos, no sólo con el DS3231

  if (!RTC.begin()) {
 
    Serial.println("No se encuentra RTC");
    while (1);

  }else{

   Serial.println("########################################"); 
   Serial.println("Puesta en hora del modulo RTC DS3231");
   Serial.print("Fecha actual: ");
   print_time();    // imprime hora actual del RTC
   Serial.println("########################################"); 
   Serial.println("");   
   Serial.println("Pulsa ENTER para actualizar a"); 
   newdate = "Fecha Nueva-> "
              + String(dia) + "/"
              + String(mes) + "/"
              + String(ano) + " Hora-> "
              + String(hora)+ ":"
              + String(min) + ":"
              + String(seg);
   Serial.println(newdate);
   
   Serial.println("======================================"); 
  }
}

void loop () {

  if(Serial.available())  {
    int inputByte = Serial.read(); // lee byte entrante
       
    if (inputByte==13) {          // caracter fin de linea
      RTC.adjust(DateTime(ano, mes, dia, hora, min, seg));
      Serial.print("Nueva Fecha actualizada: ");
      print_time();  // imprime hora actual del RTC   
    }
  }
}

void print_time() {
   
    DateTime ahora = RTC.now(); // captura valores del tiempo
    Serial.print(ahora.day(), DEC);
    Serial.print('/');
    Serial.print(ahora.month(), DEC);
    Serial.print('/');
    Serial.print(ahora.year(), DEC);

    Serial.print(" (");
    Serial.print(dia_semana[ahora.dayOfTheWeek()]);
    Serial.print(") ");

   if (ahora.hour() <10) Serial.print (0); 
    Serial.print(ahora.hour(), DEC);
    Serial.print(':');
   if (ahora.minute() <10) Serial.print (0); 
    Serial.print(ahora.minute(), DEC);
    Serial.print(':');
   if (ahora.second() <10) Serial.print (0); 
    Serial.print(ahora.second(), DEC);
    Serial.println();
  
}
