
/* ##################   Test LM1638  ####################
*  Filename:    DisplayJY_LM1638_Ej1.ino
*  Descripción: Envía por puerto serie texto al display JY-LKM1638
*  Autor:       Jose Mª Morales
*  Revisión:    19-12-2016
*  Probado:     ARDUINO UNO r3 - IDE 1.6.13 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ##############################################################
*/
#define DATA 8
#define CLK 9
#define STROBE 7

#include <TM1638.h>                 // carga libreria
TM1638 module1(DATA, CLK, STROBE);  // Define modulo y pines

int incomingByte = 0;  // caracter ASCII introducido por el teclado
String txt = "";       // variable con el texto a imprimir
byte c1, c2;           // contadores


void setup() {

      Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
      Serial.println("##############################################");
      Serial.println("########  Test Display JY-LKM1638 Ej:1 #######");
      Serial.println("####   Envia texto por el puerto serial   ####");
      Serial.println("########  y lo escribe en el Display  ########");
      Serial.println("##############################################");

//  module1.setDisplayToString("4",0b10101010);
//  module1.setDisplayToString("88888888", 0b11111111); // Todo encendido, incluidos puntos
  module1.setDisplayToString("PLAYbYTE");
  delay(3000);
  module1.setLEDs(0x00FF); // Enciende leds rojos
  delay(500);
  module1.clearDisplay();  // Apaga display
  delay(100);  
  module1.setLEDs(0xFF00); // Enciende leds verdes
  delay(1000);
  module1.setLEDs(0);      // Apaga leds

  delay(3000);
// display a hexadecimal number and set the left 4 dots
//  module1.setDisplayToHexNumber(0x1234ABCD, 0xF0);
//  module1.setDisplayToString(" HELLO ");
//  delay(1000);
//
//  module1.setLED(TM1638_COLOR_RED, 3);
//module1.setLED(TM1638_COLOR_RED | TM1638_COLOR_GREEN, 7);
}
// =============================================================

void loop() {

  if (Serial.available() > 0) { 
      
      delay(5);               // Da tiempo a leer el buffer de entrada
      if (txt=="") c2=c1=0;   // iguala contadores

      incomingByte = Serial.read();   // lee byte entrante:
      txt = txt + char(incomingByte); // va completando el texto
      c2++; 
  } // FIN captura caracter de entrada 

c1++; 

  if ((txt != "") && (c1 != c2)) {
      Serial.print("Texto enviado: ");
      Serial.println(txt);
      module1.clearDisplay();   // Borra texto anterior
      module1.setDisplayToString(txt);
      txt = "";  // inicializa variable para nueva captura
  }

  press_keys();   //  Lectura de la botonera 
  
} // FIN loop() =======================================================



void press_keys() {

  byte keys = module1.getButtons();   // Byte con el estado de las teclas
  byte lastkeys = 0;
//byte statusled = 0;  

      if (keys != 0)   {
         
          for (int i=0; i<8; i++) {
            // La posicion del 1 en "keys" es la tecla pulsada
            if (bitRead(keys,i)) {        
               Serial.print("Pulsado boton: "); 
               Serial.println(i+1);     
           //    Serial.println(keys);    // keys=1,2,4,8,16,32,64,128 
             }          
          }
//  module1.setLED(TM1638_COLOR_RED | TM1638_COLOR_GREEN, keys);
//    module1.setLED(TM1638_COLOR_RED, keys);
  module1.setLEDs((keys)); // Enciende led rojo (mientras se pulsa)
  delay(200);
      
      if (lastkeys!=keys) {      // Nueva tecla pulsada

      module1.setLEDs((keys & 0xFF) << 8); // Enciende led verde 
      lastkeys = keys;  
      } else module1.setLEDs(0);


   }  
  // light the first 4 red LEDs and the last 4 green LEDs as the buttons are pressed
//  module.setLEDs(((keys & 0xF0) << 8) | (keys & 0xF));
}
