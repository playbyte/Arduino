fg/* ##################   Test Puerto Serial  #################
*  Filename:    Puerto_Serial_Ej3.ino
*  Descripción: Captura numeros tecleados en el rango: +/- 2^32
*  Autor:       Jose Mª Morales
*  Revisión:    2-03-2012
*  Probado:     ARDUINO UNO r3 - IDE 1.00 (Windows7)
*  Web:         www.playbyte.es/electronica/
*  Licencia:    Creative Commons Share-Alike 3.0
*    http://creativecommons.org/licenses/by-sa/3.0/deed.es_ES
* ###########################################################
*/

long     num = -1;      // Guarda el numero tecleado (rango: +/- 2^32)
boolean sign = false;   // Guarda signo del numero
int inputByte= 0;       // Caracter ASCII introducido por el teclado
byte c1, c2;            // Contadores


void setup() {
      Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
      Serial.println("##############################################");
      Serial.println("#########  Test Puerto Serial  Ej:3   ########");
      Serial.println("#########  Captura numeros tecleados  ########");
      Serial.println("#########  en el rango: +/- 2^32      ########");
      Serial.println("##############################################");
}


void loop() {

  // cada vez lee un caracter de la pila mientras haya datos en el buffer
  if (Serial.available() > 0) { 
      
      delay(5);                       // Da tiempo a leer el buffer de entrada
      inputByte = Serial.read();      // Lee caracter entrante:
      
      if (num==-1) {                  // Comienza captura de datos
          c2 = c1 = 0;                        // Iguala contadores
          num = 0;                            // Valor inicial
          if (inputByte==45)   sign = true;   // Primer caracter = signo (-)
      }

      if (inputByte>=48 && inputByte<=57)  num = 10*num + (inputByte-48) ;       
      c2++; 

  } // FIN captura caracter de entrada 

c1++; 

  if ((num != -1) && (c1 != c2)) {  // Concluida captura de caracteres
      if (sign)   num = -num;
      Serial.print("Numero: ");
      Serial.println(num);
      num  = -1;                    // inicializa variable para nueva captura
      sign = false;
  }

} // FIN loop() =======================================================
