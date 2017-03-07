/* ##################   Serial Display Led ##################
*  Filename:    Display_SerialLED_Ej3_Milivoltimetro.ino
*  Descripción: Milivoltimetro 5 V
*  Autor:       Jose Mª Morales
*  Revisión:    16-03-2012
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
#define PIN_Rx 2            // pin que recibe los datos serie Rx
#define PIN_Tx 3            // pin que manda los datos serie Tx

SoftwareSerial SerialDisplay(PIN_Rx, PIN_Tx); //  Define canal serie a usar.

#define PIN_ANALG_INPUT 5 // pin (analogico)

int raw_input = 0;        // valor medido
int volt = 0;             // valor a mostrar
// ==========================================================

void setup(){

    pinMode(PIN_Tx, OUTPUT);
    pinMode(PIN_Rx, INPUT);          // No se usa
    pinMode(PIN_ANALG_INPUT, INPUT); // no hace falta declarar la entrada analogica

    Serial.begin (9600);        // inicia comunicacion serial
    SerialDisplay.begin(9600);  // inicializa puerto serie para el display

inicio();                       // Secuencia de inicio
}
// =============================================================

void inicio() {
      Serial.println("##########################################");
      Serial.println("######  Serial Display Led         #######");
      Serial.println("######  Ejemplo 3: Milivoltimetro  #######");
      Serial.println("##########################################");


// inicializa valores, el display los conserva en memoria al iniciar
  SerialDisplay.print("v");   // Reset: borra digitos y situa cursor en el digito 1

  SerialDisplay.print("z");   // comando para regular brillo
  SerialDisplay.write(1);     // 0-254, (0=max, 254=min)

  SerialDisplay.print("w");   // comando para activar/desactivar puntos
  SerialDisplay.write(194);   // Ilumina punto decimal "." (194=11000010)

  SerialDisplay.print("x---");
  delay(1000);
}
// ==========================================================

void loop(){
  // Calcula el voltaje usando como referencia Vcc=5v
  raw_input = analogRead(PIN_ANALG_INPUT);
  volt = (raw_input *5) / 10.24;    // redondea los milivoltios
  
  String msg = String(volt);
  if (volt < 100) msg = "0" + msg;  // pone el cero para el < 1 V
  if (volt < 10)  msg = "0" + msg;  // pone otro cero si es < 0.1 V
  msg = "x"+ msg;                   // el primer digito en blanco
  
  // Escribe el valor por la consola
  Serial.print ("Raw= "+ String(raw_input) +" -> Voltios= ");
  Serial.println ( volt);

  SerialDisplay.print("v");  // Reset
  SerialDisplay.print(msg);  // Muestra el resultado en el display


delay (300); // Espera 0.3 segundos para la siguiente medicion
}
