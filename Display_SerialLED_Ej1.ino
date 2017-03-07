/* ##################   Serial Display Led ##################
*  Filename:    Display_SerialLED_Ej1.ino
*  Descripción: Muestra en el display los caracteres tecleados desde el Serial Monitor
*  Autor:       Jose Mª Morales
*  Revisión:    14-03-2012
*  Probado:     ARDUINO UNO r3 - IDE 1.00 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ###########################################################
*
*  Dispositivo:  Display serial LED 4 Digitos 7-Segmentos
*  Referencia:   Sparkfun COM-09767
*  Proveedor:    http://www.sparkfun.com/products/9767
*  Pinout:
*              PIN1 = Gnd
*              PIN2 = Vcc
*              PIN8 = Rx (entrada TTL del módulo)
*  
* ###########################################################
*/


#include <SoftwareSerial.h> // cargamos la libreria serie

#define PIN_Rx 2    // pin que recibe los datos serie Rx
#define PIN_Tx 3    // pin que manda los datos serie Tx

SoftwareSerial SerialDisplay(PIN_Rx, PIN_Tx); //  Define canal serie a usar.

int incomingByte = 0;  // caracter ASCII que se introduce por el teclado
String  txt = "";      // variable con el texto a mostrar
byte count1 = 0;       // inicializa contadores
byte count2 = 0; 

// ==========================================================

void setup(){

    pinMode(PIN_Tx, OUTPUT);  // Manda datos al Display
    pinMode(PIN_Rx, INPUT);   // No se usa

    Serial.begin (9600);      // inicia comunicacion serial
    SerialDisplay.begin(9600);// inicializa puerto serie para el display

    inicio();                 // Secuencia de inicio
}
// ==========================================================


void inicio() {

      Serial.println("##############################################");
      Serial.println("######  Serial Display Led - Ejemplo 1 #######");
      Serial.println("######  Muestra los caracteres (max 4) #######");
      Serial.println("######  enviados por el serial monitor #######");
      Serial.println("##############################################");

// inicializa valores, el display los conserva en memoria al iniciar
  SerialDisplay.print("v");   // Reset: borra digitos y situa cursor en el digito 1

  SerialDisplay.print("w");   // comando para activar/desactivar puntos
  SerialDisplay.write(192);   // Borra todos los puntos 192=11000000

  SerialDisplay.print("z");   // comando para regular brillo
  SerialDisplay.write(1);     // 0-254, (0=max, 254=min)

  SerialDisplay.print("----");// Texto de prueba inicial
  delay(500);
}
// =============================================================


void InputSerial() {

  if (Serial.available() > 0) { 
      
      delay(5);                     // Da tiempo a leer el buffer de entrada
      if (txt=="") count2=count1=0; // iguala contadores para contar caracteres de entrada

      incomingByte = Serial.read(); // lee byte entrante:
      if (count2 < 4) {             // solo guarda los 4 primero caracteres
        txt = txt + char(incomingByte); // almacena el texto
        count2++; 
      }
  } // FIN captura caracter de entrada 

count1++; 
} 
// ===========================================================


void loop() {

InputSerial();

  if ((txt != "") && (count1 != count2)) {
      Serial.print("Texto enviado: ");
      Serial.println(txt);
      SerialDisplay.print("v");  // Reinicia Display
      delay (50);
      SerialDisplay.print(txt); // Manda texto a mostrar
      txt = "";                 // inicializa variable para nueva captura
  }

delay(100);

} // FIN loop() ==============================================
