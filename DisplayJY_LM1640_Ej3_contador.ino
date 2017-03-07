/* ####################  Test LM1640   ######################
*  Filename:    DisplayJY_LM1640_Ej3_contador.ino
*  Descripción: Contador de 16 digitos display JY-LM640
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

unsigned long seg=0;  
// =============================================================


void setup() {

      module.setDisplayToString("LM1640  Prueba-3");
      delay(2000);
  
      Serial.begin(9600);  // Abre puerto serie, transferencia 9600 bps
      Serial.println("##############################################");
      Serial.println("########  Test Display JY-LM640  Ej:3  #######");
      Serial.println("#######  Contador de milisegundos      #######");
      Serial.println("##############################################");
}
// =============================================================


void loop() {

    String blank = "                ";      // 16 espacios para rellenar
    blank = blank.substring(String(seg).length());   // Quita el espacio que ocupa el numero 
    module.setDisplayToString(blank + String(seg));   

  delay(10);     // pausa que completa un milisegundo
  seg++;
  
} // FIN loop() =======================================================

