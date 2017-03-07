/* ##################     Test LM1640    ####################
*  Filename:    DisplayJY_LM1640_Ej1.ino
*  Descripción: Envía por puerto serie texto al display JY-LM640
*  Autor:       Jose Mª Morales
*  Revisión:    26-03-2012
*  Probado:     ARDUINO UNO r3 - IDE 1.00 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ##############################################################
*/

#include <TM1640.h>
TM1640 module(3, 2);    // define modulo y pines

int incomingByte = 0;	  // caracter ASCII introducido por el teclado
String txt = "";        // variable con el texto a imprimir
byte count1;            // contadores
byte count2; 
// =============================================================


void setup() {

      module.setDisplayToString("Prueba-1  LM1640");
      delay(2000);
  
      Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
      Serial.println("##############################################");
      Serial.println("########  Test Display JY-LM640  Ej:1  #######");
      Serial.println("####   Envia texto por el puerto serial   ####");
      Serial.println("####  y lo escribe en el Display JY-LM640 ####");
      Serial.println("##############################################");
}
// =============================================================


void loop() {

  // cada vez lee un caracter de la pila mientras haya datos en el buffer
  if (Serial.available() > 0) { 
      
      delay(5);                       // Da tiempo a leer el buffer de entrada
      if (txt=="") count2=count1=0;   // iguala contadores

      incomingByte = Serial.read();   // lee byte entrante:
      txt = txt + char(incomingByte); // va completando el texto
      count2++; 
  } // FIN captura caracter de entrada 

count1++; 

  if ((txt != "") && (count1 != count2)) {
      Serial.print("Texto tecleado: ");
      Serial.println(txt);
      module.clearDisplay();   // Borra texto anterior
      module.setDisplayToString(txt);
      txt = "";  // inicializa variable para nueva captura
  }

} // FIN loop() =======================================================
