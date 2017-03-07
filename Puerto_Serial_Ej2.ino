/* ##################   Test Puerto Serial  #################
*  Filename:    Puerto_Serial_Ej2.ino
*  Descripción: Enciende Led al introducir texto predeterminado
*  Autor:       Jose Mª Morales
*  Revisión:    2-03-2012
*  Probado:     ARDUINO UNO r3 - IDE 1.00 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ###########################################################
*/

int inputByte = 0;	  // Caracter ASCII introducido por el teclado
String    txt = "";       // Variable con el texto a imprimir
byte      c1, c2;         // Contadores
String    msg = "ARDUINO";// Clave a teclear 

#define PIN_LED  13       // Pin que incluye led
// =============================================================


void setup() {
      Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
      Serial.println("###############################################");
      Serial.println("#########   Test Puerto Serial  Ej:2  #########");
      Serial.println("#### Al introducir un texto predeterminado ####");
      Serial.println("#### se enciende el LED del pin 13         ####");
      Serial.println("###############################################");

      pinMode(PIN_LED, OUTPUT);
      digitalWrite(PIN_LED, LOW);     //  Apaga el LED
}
// =============================================================


void loop() {

  // cada vez lee un caracter de la pila mientras haya datos en el buffer
  if (Serial.available() > 0) { 
      
      delay(5);                     // Da tiempo a leer el buffer de entrada
      if (txt=="") c2=c1=0;         // iguala contadores

      inputByte = Serial.read();    // lee byte entrante:
      txt = txt + char(inputByte);  // va completando el texto
      c1++; 

  } // FIN captura caracter de entrada 

c2++; 

  if ((txt != "") && (c1 != c2)) {
     if (txt == msg) {              // Comprueba si es la palabra buscada
        Serial.println("Led encendido: ");
        Serial.println(txt);
        digitalWrite(PIN_LED, HIGH);
     }else  digitalWrite(PIN_LED, LOW);
     txt = "";                     // inicializa variable para nueva captura
      
  }

} // FIN loop() ================================================

