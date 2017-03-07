/* ####################  Test LM1640   ######################
*  Filename:    DisplayJY_LM1640_Ej2_scroll.ino
*  Descripción: Envía texto al display JY-LM640 con scroll
*  Autor:       Jose Mª Morales
*  Revisión:    26-03-2012
*  Probado:     ARDUINO UNO r3 - IDE 1.00 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ###########################################################
*/
#include <TM1640.h>
TM1640 module(3, 2);    // define modulo y pines

int incomingByte = 0;	  // caracter ASCII introducido por el teclado
String txt = "";        // variable con el texto a imprimir
byte count1, count2;   // contadores

// =============================================================


void setup() {

      module.setDisplayToString("LM1640 Prueba-2");
      delay(2000);
  
      Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
      Serial.println("##############################################");
      Serial.println("########  Test Display JY-LM640  Ej:2  #######");
      Serial.println("####  Envia texto por el puerto serial y  ####");
      Serial.println("####  hace scroll en el Display JY-LM640  ####");
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
      scroll(txt);   // Realiza el scroll de izda a dcha
      txt = "";      // Inicializa variable para nueva captura
  }
} // FIN loop() =======================================================


void scroll(String txt) {

  for (int i=1; i<16; i++) {

    String txt_scroll="               ";      // inicializa 15 espacios
    txt_scroll = txt_scroll.substring(i) + txt + txt_scroll;  // completa con el texto 
    txt_scroll = txt_scroll.substring(0,15); // recorta 16 caracteres
    module.setDisplayToString(txt_scroll);   
    delay(100);                              // velocidad del scroll
  }
} // FIN scroll() =======================================================
