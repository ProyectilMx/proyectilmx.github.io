// ------------------------------------------------ ROBBUS KIDSY ----------------------------------------------
//
// Nivel de dificultad: FACIL
//
// EJEMPLO DE USO DE LOS BOTONES DE USUARIO A Y B CON PULSACION LARGA Y MANTENIDA
// Este ejemplo es de uso libre y esta pensado para dar una introduccion al hardware de Robbus Kidsy.
// Autor: Fabian Alfonso Flores
// Empresa: Proyectil Mx
// Fecha: 17 de febrero de 2020
// ------------------------------------------------------------------------------------------------------------
// Robbus Kidsy cuenta con 2 Botones de usuario:
// - ButtonA
// - ButtonB
//
// Con este ejemplo entenderas los diferentes usos que se le pueden dar a los botones de tu Robot.
// Los botones de usuario A y B pueden regresar 4 estados diferentes:
//
// 0 - RELEASED       - El boton paso de estar presionado a liberarse
// 1 - PRESSED        - El boton paso de estar en en reposo a presionarse
// 2 - HOLD_PRESSED   - Se mantiene presionado
// 3 - HOLD_RELEASED  - Se mantiene sin preisonar
//
// Nota importante: El boton RESET sirve para reiniciar el programa de tu robot y no se puede programar
// ------------------------------------------------------------------------------------------------------------

#include<RobbusKidsy.h>

Robbus Kidsy;             // Crea tu Robbus Kidsy

int times_A;
int times_B;              // Cuenta las pulsaciones de los botones

void setup() {
  Serial.begin(115200);   // Inicializa comunicacion serial a 115200 baudios
  Kidsy.begin();          // Inicializa el hardware del Robbus Kidsy
}

void loop() {
  Kidsy.ButtonA.read();   // Lee el ultimo estado del boton A
  Kidsy.ButtonB.read();   // Lee el ultimo estado del boton B

  switch(Kidsy.ButtonA.status) {  
    case PRESSED:
      Serial.print("BotonA Presionado ");
      Serial.print(++times_A);    // aumenta el contador y lo imprime
      Serial.println(" veces");
      Kidsy.Led1.on();  // enciende el LED1
      break;
    case RELEASED:
      Serial.println("BotonA suelto");
      break;
    case HOLD_PRESSED:
      // mientras el boton permanezca presionado, entrara en este case
      //Serial.println("BotonA permanece presionado");
      break;
    case HOLD_RELEASED:
      // mientras el boton permanezca suelto, entrara en este case
      //Serial.println("BotonA permanece suelto");
      break;
  }

  switch(Kidsy.ButtonB.status) {
    case PRESSED:
      Serial.print("BotonB Presionado ");
      Serial.print(++times_B);    // aumenta el contador y lo imprime
      Serial.println(" veces");
      Kidsy.Led1.off();   // apaga el LED1
      break;
    case RELEASED:
      Serial.println("BotonB suelto");
      break;
    case HOLD_PRESSED:
      // mientras el boton permanezca presionado, entrara en este case
      //Serial.println("BotonB permanece presionado");
      break;
    case HOLD_RELEASED:
      // mientras el boton permanezca suelto, entrara en este case
      //Serial.println("BotonB permanece suelto");
      break;
  }
} 