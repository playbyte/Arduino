/* ##################   Test Puerto Serial  ####################
*  Filename:    Puerto_Serial_Ej1.ino
*  Descripción: Envía y recibe texto por el Puerto Serie
*  Autor:       Jose Mª Morales
*  Revisión:    2-03-2012
*  Probado:     ARDUINO UNO r3 - IDE 1.00 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ##############################################################
*/

int inputByte = 0;	      // Caracter ASCII introducido por el teclado
String    txt = "";       // Variable con el texto a imprimir
byte      c1, c2;         // Contadores

// =============================================================


void setup() {
      Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
      Serial.println("#############################################");
      Serial.println("#########   Test Puerto Serial  Ej:1  #######");
      Serial.println("####  Recibe texto por el Puerto Serial  ####");
      Serial.println("#############################################");
}
// =============================================================


void loop() {

  // cada vez lee un caracter de la pila mientras haya datos en el buffer
  if (Serial.available() > 0) { 
      
      delay(5);                     // Da tiempo a leer el buffer de entrada
      if (txt=="") c2=c1=0;         // inicia contadores, se mantienen iguales mientras se reciben datos

      inputByte = Serial.read();    // lee byte entrante:
      txt = txt + char(inputByte);  // va completando el texto
      c1++; 

  } // FIN captura caracter de entrada 

c2++; // cuando no hay datos para leer c1 deja de aumentar

  if ((txt != "") && (c1 != c2)) {
      Serial.print("Texto tecleado: ");
      Serial.println(txt);
      txt = "";                     // inicializa variable para nueva captura
  }

} // FIN loop() =======================================================
