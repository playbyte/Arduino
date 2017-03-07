/* ##################   Serial Display Led ##################
*  Filename:    Display_SerialLED_Ej2_Reloj.ino
*  Descripción: Display configurado como reloj
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

#define PIN_Rx 2      // pin que recibe los datos serie Rx
#define PIN_Tx 3      // pin que manda los datos serie Tx

SoftwareSerial SerialDisplay(PIN_Rx, PIN_Tx); //  Define canal serie a usar.

// variables necesarias para el reloj
float prev_mseg = 0;  // referencia inicial para cada segundo

int bloque_1;         // Primer bloque de digitos (horas)
int bloque_2;         // Segundo bloque de digitos (minutos)
String time = "0000"; // cadena con el tiempo a mostrar en el display

// =============================================================

void setup(){

    pinMode(PIN_Tx, OUTPUT);    // Manda datos al Display
    pinMode(PIN_Rx, INPUT);     // No se usa

    Serial.begin (9600);        // inicia comunicacion serial
    SerialDisplay.begin(9600);  // inicializa puerto serie para el display

    inicio();                   // Secuencia de inicio
}
// =============================================================

void inicio() {
      Serial.println("##########################################");
      Serial.println("######  Serial Display Led         #######");
      Serial.println("######  Ejemplo 2: Reloj Digital   #######");
      Serial.println("##########################################");

// inicializa valores, el display los conserva en memoria al iniciar
  SerialDisplay.print("v");   // Reset: borra digitos y situa cursor en el digito 1

  SerialDisplay.print("z");   // comando para regular brillo
  SerialDisplay.write(1);     // 0-254, (0=max, 254=min)

  SerialDisplay.print("w");   // comando para activar/desactivar puntos
  SerialDisplay.write(208);   //  Ilumina los ":" (208=11010000)

  SerialDisplay.print(time);
  prev_mseg = millis() ;      // tiempo de referencia del segundo
}
// =============================================================

void loop(){

for (int h=0; h<=23; h++){    // Bucle para las horas
for (int m=0; m<=59; m++){    // Bucle para los minutos
for (int s=0; s<=59; s++){    // Bucle para los segundos

// cambia la configuracion tras la primera hora
  if (h>0)  {bloque_1 = h; bloque_2 = m;}  // configuracion "horas:min"
  else      {bloque_1 = m; bloque_2 = s;}  // configuracion "min:seg"
  
  time = "";                              // Resetea variable
  if (bloque_1 < 10) time = "x";          // Apaga el digito la izda
  time = time + String(bloque_1);
  
  if (bloque_2 < 10) time = time +"0";    // Añade '0' de los segundos la izda
  time = time + String(bloque_2);


// Parpadeo de ':' indicador de los segundos
  SerialDisplay.print("w");
  SerialDisplay.write(208);   // Ilumina los ":"    (208=11010000)
  delay(500);                 // Pausa 0.5 seg      
  SerialDisplay.print("w");
  SerialDisplay.write(192);   // Apaga los ":"      (192=11000000)


// Pausa hasta completar el bucle de 1 segundo 'exacto'
  delay(994 -(millis()-prev_mseg)); // Retardo (aprox 495ms)
  delayMicroseconds(400);           // Ajuste 'fino' retrasa 1 seg por hora

  SerialDisplay.print(time);

  prev_mseg= millis();             // Guarda el valor para el siguiente segundo
}}}
// Completado ciclo de 24 horas
}
