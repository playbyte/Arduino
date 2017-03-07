/* ##################   Test LCD Keypad  ####################
*  Filename:    LCD_Keypad_Shield_Ej2.ino
*  Descripción: Scroll de texto introducido por el puerto serie
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
 
int inputByte = 0;                 // Caracter ASCII introducido por el teclado
String    txt = "";                // Variable con el texto a mostrar
String   msg1 = "www.playbyte.es"; // texto a mover linea1
String   msg2 = "TEST scroll";     // texto a mover linea2
// =============================================================

void setup() {

      Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
      Serial.println("###############################################");
      Serial.println("#########  LCD_Keypad_Shield_Ej2 #########");
      Serial.println("#### El texto introducido se pasa     ####");
      Serial.println("#### a la pantalla LCD con un scroll  ####");
      Serial.println("###############################################");

  lcd.begin(16, 2);           // Inicializa libreria
  lcd.print(msg1);            // imprime mensaje linea 1

  lcd.setCursor(0,1);         // cursor en 2ª fila
  lcd.print(msg2);            // imprime mensaje linea 2
  delay(3000);
}// =============================================================


void loop() {

  // cada vez lee un caracter de la pila mientras haya datos en el buffer
  if (Serial.available() > 0) { 
      
      delay(5);                    // Da tiempo a leer el buffer de entrada
      inputByte = Serial.read();   // lee byte entrante:

      if (inputByte!=13)   txt += char(inputByte);  // va completando el texto (excluye ENTER)

  } // FIN captura caracter de entrada 

  if ((txt != "") && (inputByte==13)) { // si se ha terminado de recibir el mensaje 

    msg2 = txt; //
    txt = "";                    // inicializa variable para nueva captura
    
    Serial.println(msg2);
    lcd.clear();
    lcd.setCursor(0,0);         
    lcd.print(msg1);             
    lcd.setCursor(0,1);         // cursor en 2ª fila
    lcd.print(msg2);            // imprime mensaje en linea 2
  
   }

 if (txt == "") scroll_LCD();   //  mueve el texto despues de completar msg2  

}// ==========================================================


void scroll_LCD() {
    
   // scroll a la izda (string length) posiciones
   for (int i = 0; i < msg2.length(); i++) {
    
    lcd.scrollDisplayLeft(); // scroll 1 posicion a la izquierda
    delay(200);
  }

  // scroll a la dcha de (string length + display length) posiciones
  for (int i = 0; i < 16+msg2.length(); i++) {

     lcd.scrollDisplayRight(); // scroll 1 posicion a la izquierda 
     delay(150);
  }
  
    // scroll 16 posiciones (display length + string length) a la izquierda 

  for (int i = 0; i < 16; i++) {
     lcd.scrollDisplayLeft();  // scroll 1 posicion a la izquierda
      delay(150);
  }
    
  delay(2000);  // delay para mostrar text quieto
  
  }
