/* ##################   Test LCD Keypad  ####################
*  Filename:    LCD_Keypad_Shield_Ej3.ino
*  Descripción: Reloj basico
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

int                 hor = 0;
int                 min = 0;
volatile        int seg = 0;   // variable compartida en varias funciones
volatile boolean refresh= true;// variable compartida para actualizar valores
String           tiempo = "";  // Guarda la hora a imprimir
// =============================================================

void setup(){

 lcd.begin(16, 2);              // Inicializa libreria LCD

 lcd.setCursor(0,0);            // cursor en posicion inicial
 lcd.print("Reloj-Ejemplo1");   // imprime mensaje linea 1

 lcd.setCursor(0,1);            // cursor en 2ª fila
 lcd.print("www.playbyte.es");  // imprime mensaje linea 2

 delay(2000);
 lcd.clear();                   // Borramos la pantalla 
 
 Timer1.initialize(1000000);    // interrupcion cada 1e6 microsegundos (1seg)
 Timer1.attachInterrupt(Timer); // se ejecuta en cada interrupcion
}
// =============================================================


void loop(){

  if (refresh == true) {  

      lcd.setCursor(0,1);      // cursor en 2ª fila
      lcd.print(tiempo); 
      refresh = false;         // hasta el proximo cambio  
  } 
}// =============================================================


void Timer(){

  seg++;           // cada interrupcion incrementa un segundo
  refresh = true;  // indica que se ha actualizado el tiempo

  min+= seg / 60;  // incrementa min cuando seg=60 
  seg = seg % 60;  // se queda con resto (0-59)

  hor+= min / 60;  // incrementa hor cuando min=60 
  min = min % 60;

  hor = hor % 24;  // se queda con resto (0-23)

// da formato a la hora en la forma Ej:01:02:06  
  tiempo = "";
  if (hor < 10) tiempo += "0";
  tiempo += String(hor) + ":";
  if (min < 10) tiempo += "0";
  tiempo += String(min) + ":";
  if (seg < 10) tiempo += "0";
  tiempo += String(seg);
}// =============================================================

