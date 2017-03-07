/* ##################   Serial Display Led ##################
*  Filename:    Display_SerialLED_Ej4_Termometro.ino
*  Descripción: Indicador de Temperatura con LM35
*  Autor:       Jose Mª Morales
*  Revisión:    16-03-2012
*  Probado:     ARDUINO UNO r3 - IDE 1.00 (Windows7)
*  Web:         www.playbyte.es/arduino/
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

#include <SoftwareSerial.h> // cargamos libreria serial
#define PIN_Rx 2            // Pin que recibe los datos serie Rx
#define PIN_Tx 3            // Pin que manda los datos serie Tx

SoftwareSerial SerialDisplay(PIN_Rx, PIN_Tx); //  Define canal serie a usar.

#define PIN_LED 13          // Pin que inluye led
#define PIN_TEMP_SENSOR 5   // Pin (analogico) del sensor de temp

int raw_temp = 0;           // Variable para la temperatura
int celsius = 0;
int fahrenheit = 0;
// =============================================================


void setup(){

    pinMode(PIN_Tx, OUTPUT);
    pinMode(PIN_Rx, INPUT);      // No se usa
    pinMode(PIN_TEMP_SENSOR, INPUT); // no hace falta declarar la entrada analogica
    pinMode(PIN_LED, OUTPUT);
      
    Serial.begin (9600);         // inicia comunicacion serial
    SerialDisplay.begin(9600);

inicio();
}
// =============================================================


void inicio() {
      Serial.println("##########################################");
      Serial.println("######  Serial Display Led         #######");
      Serial.println("######  Ejemplo 4: Termometro      #######");
      Serial.println("##########################################");

// inicializa valores, el display los conserva en memoria al iniciar
  SerialDisplay.print("v");   // Reset: borra digitos y situa cursor en el digito 1

  SerialDisplay.print("z");   // comando para regular brillo
  SerialDisplay.write(1);     // 0-254, (0=max, 254=min)

  SerialDisplay.print("--xC");
  delay(1000);
 
  SerialDisplay.print("w");   // comando para activar/desactivar puntos
  SerialDisplay.write(224);   // Deja el punto del cero de ºC (224=11100000)
}
// ==========================================================


void loop(){

  // Calcula la temperatura usando como referencia 5v
  raw_temp = analogRead(PIN_TEMP_SENSOR);
  celsius = (5.0 * raw_temp * 100.0) / 1024.0;
  fahrenheit = (celsius * 1.8) + 32;

  // Escribe la temperatura por el serial y parpadea el LED
  digitalWrite(PIN_LED, HIGH);
  Serial.print ("Temperatura: ");
  Serial.println (String(celsius) +" C = "+ String(fahrenheit) +" F");
  digitalWrite(PIN_LED, LOW);

  int grados = celsius;         // Admite cambiar la unidad por fahrenheit
  String temp = String(grados) ;

  // Añade espacios en blanco para completar los 4 digitos
  if (grados >= -10 && grados < 100) temp = temp + "x";   // T < 100º
  if (grados >= 0 && grados < 10) temp = "x"+ temp;       // T < 10º
  temp = temp + "C";          // Cambiar por F para fahrenheit

  SerialDisplay.print(temp);  // Muestra el resultado en el display

delay (3000);                 // Espera 3 segundos para la siguiente medida
}
