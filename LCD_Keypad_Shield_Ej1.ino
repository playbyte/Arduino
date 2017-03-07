/* ##################   Test LCD Keypad  ####################
*  Filename:    LCD_Keypad_Shield_Ej1.ino
*  Descripción: Prueba de pulsadores y pantalla
*  Autor:       Jose Mª Morales
*  Revisión:    30-12-2016
*  Probado:     ARDUINO UNO r3 - IDE 1.6.13 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ##############################################################
*/

#include <LiquidCrystal.h> // libreria para controlar el display
 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Indicamos los pines usados en el panel LCD
 
int adc_key  = 0;     // valor de la entrada analogica A0

String      btn = "";   // Boton pulsado
String last_key = "";   // Guarda la ultima tecla pulsada
// =============================================================

 
void setup() {
 
 lcd.begin(16, 2);              // Inicializa libreria
 
 lcd.setCursor(0,0);            // cursor en posicion inicial
 lcd.print("TEST pulsadores");  // imprime mensaje linea1

 lcd.setCursor(0,1);            // cursor en 2ª fila
 lcd.print("www.playbyte.es");  // imprime mensaje linea2

}
// =============================================================
  
void loop() {
      delay(100); 

 adc_key = analogRead(0);      // lee tecla pulsada por ADC0

 // Valores obtenidos de mis botones: 0, 127, 303, 476, 719
 // we add approx 50 to those values and check to see if we are close

 if (adc_key > 1000) return;        // Ningun boton pulsaddo
 if (adc_key < 750)  btn="SELECT "; 
 if (adc_key < 550)  btn="IZQDA  ";
 if (adc_key < 350)  btn="ABAJO  ";
 if (adc_key < 150)  btn="ARRIBA ";
 if (adc_key < 50)   btn="DERECHA"; 


 if (btn !=last_key) { // solo imprime si se ha pulsado una tecla nueva
    
    lcd.clear();               // Borra toda la pantalla
    lcd.setCursor(0,0);
    lcd.print("Pulsado: "); 
    lcd.print(btn);
  
    lcd.setCursor(0,1);
    lcd.print("Pin ADC=");
    lcd.print(adc_key);
    lcd.print("    ");
  
    last_key = btn;   // retiene el valor del boton pulsado
 }
} // FIN loop() =======================================================

 
