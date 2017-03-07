/* ##################   Test LCD Keypad  ####################
*  Filename:    LCD_Keypad_Shield_Ej3b.ino
*  Descripción: Reloj 
*               para Shield LCD Keypad
*  Autor:       Jose Mª Morales
*  Revisión:    31-12-2016
*  Probado:     ARDUINO UNO r3 - IDE 1.6.13 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ##############################################################
*/

#include <LiquidCrystal.h> // libreria para controlar el display
#include <TimerOne.h>      // controla el tiempo por interrupciones

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //  pines usados en el panel LCD

volatile          int ss = 0;   // variable compartida en varias funciones
                  int mm = 0;   // variables independientes para segundos, minutos y horas
                  int hh = 0;   
           String tiempo = "";  // Guarda la hora a imprimir
volatile boolean refresh = true;// variable compartida para actualizar valores

       int adc_key = 0;    // valor de la entrada analogica A0
String         btn = "";   // Boton pulsado
String    last_key = "";   // Guarda la ultima tecla pulsada

        int   modo = 1;    // 0=Ajuste, 1=Reloj 
        int cursor = 1;    // posicion del cursor
// =============================================================

void setup(){

 lcd.begin(16, 2);              // Inicializa libreria LCD

 lcd.setCursor(0,0);            // cursor en posicion inicial
 lcd.print("Reloj-Ejemplo2");   // imprime mensaje linea 1

 lcd.setCursor(0,1);            // cursor en 2ª fila
 lcd.print("www.playbyte.es");  // imprime mensaje linea 2

 delay(2000);
 lcd.clear();                   // Borramos la pantalla 
 
 Timer1.initialize(1000000);    // interrupcion cada 1e6 microsegundos (1seg)
 Timer1.attachInterrupt(Timer); // se ejecuta en cada interrupcion
}
// =============================================================


void loop(){

  if (refresh == true) {      // Solo imprime nueva hora cuando se ha actualizado

      lcd.setCursor(0,1);      // cursor en 2ª fila
      lcd.print(tiempo); 
      refresh = false;         // hasta el proximo cambio  

      lcd.setCursor(cursor,1); // posiciona cursor para modo ajuste
  }


  Boton(); // captura valores de btn pulsados

 if (btn != last_key) { // solo pasa si se ha pulsado una tecla nueva

  
    if (btn == "SELECT "){
        modo++;               // cambia al siguiente modo
       if (modo>=2)  modo=0;  // por ahora solo tenemos modo 0 y 1
      } 

    if (modo==0) {
        lcd.setCursor(0,0);
        lcd.print("Poner en hora");

        Ajuste();     // puesta en hora
        lcd.blink();  // parpadea cursor
      }else   {
        lcd.noBlink();
        lcd.setCursor(0,0);
        lcd.print("Reloj           ");
        }

   last_key = btn;   // retiene el valor del boton pulsado 
 }
}// =============================================================


void Timer(){

     ss++;           // cada interrupcion incrementa un segundo
     refresh = true; // indica que se ha actualizado el tiempo
    
    //  if (modo==0) lcd.blink();   // modo puesta en hora
            
    
    
     mm+= ss / 60;  // incrementa mm cuando ss=60 
     ss = ss % 60;  // se queda con resto (0-59)
    
     hh+= mm / 60;  // incrementa hh cuando mm=60 
     mm = mm % 60;
    
     hh = hh % 24;  // se queda con el resto (0-23)
    
    // Da formato a la hora en la forma hh:mm:ss 
     tiempo = "";
     if (hh < 10) tiempo += "0";
     tiempo += String(hh) + ":";
     if (mm < 10) tiempo += "0";
     tiempo += String(mm) + ":";
     if (ss < 10) tiempo += "0";
     tiempo += String(ss);
}// =============================================================


void Boton() {    // actualiza la variable "btn"

   adc_key = analogRead(0);      // lee tecla pulsada por ADC0     
   
   btn = "" ;        // Ningun boton pulsaddo       

   if (adc_key > 650 & adc_key < 750)  btn="SELECT "; 
   if (adc_key > 400 & adc_key < 550)  btn="IZQDA  ";
   if (adc_key > 250 & adc_key < 350)  btn="ABAJO  ";
   if (adc_key >  50 & adc_key < 200)  btn="ARRIBA ";
   if (adc_key < 50)                   btn="DERECHA";       

return;
}// ============================================================= 


void Ajuste() {   // Puesta en hora

// Mueve cursor izquierda y derecha
      if (btn=="DERECHA"){
          cursor = cursor+3;
          if (cursor>=8) cursor=7;
       } 
      if (btn=="IZQDA  "){
          cursor = cursor-3;
          if (cursor<=0) cursor=0;
       }

// Cambia valor de los digitos
          if (cursor==0 | cursor==1) { //cambia las horas
              if (btn=="ARRIBA "){
                  hh++;
                 if (hh>=24) hh=0;
               }
              if (btn=="ABAJO  "){
                  hh--;     
                 if (hh<0) hh=23;
               }
          }
          if (cursor==3 | cursor==4) { // cambia los minutos
              if (btn=="ARRIBA "){
                  mm++;
                 if (mm>=60) mm=0;
               }
              if (btn=="ABAJO  "){
                  mm--;     
                 if (mm<0) mm=59;
               }
          }

          if (cursor==6 | cursor==7) { // cambia los segundos
              if (btn=="ARRIBA "){
                  ss++;
                 if (ss>=60) ss=0;
               }
              if (btn=="ABAJO  "){
                  ss--;     
                 if (ss<0) ss=59;
               }
          }
  
return;
}// ============================================================= 

