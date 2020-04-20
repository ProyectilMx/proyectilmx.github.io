// ------------------------------------------------ ROBBUS KIDSY ----------------------------------------------
//
// Nivel de dificultad: FACIL
//
// EJEMPLO DE USO DE LOS LEDS DE USUARIO LED1, LED2 CON LOS BOTONES A Y B CON LA FUNCION SET
// Este ejemplo es de uso libre y esta pensado para dar una introduccion al hardware de Robbus Kidsy.
// Autor: Fabian Alfonso Flores
// Empresa: Proyectil Mx
// Fecha: 17 de febrero de 2020
// ------------------------------------------------------------------------------------------------------------
// Robbus Kidsy cuenta con 4 LEDs de usuario:
// - Led1
// - Led2
// - Led3 (Disponible a partir de la version 3.1)
// - Led4 (Disponible a partir de la version 3.1)
// Nota importante: El LED blanco junto al sensor de color no se puede controlar directamente
//
// En este ejemplo aprenderemos usar la funcion set para prender o apagar un LED. Tambien aprenderemos 
// el uso del signo ! (negacion). Este operador sirve para invertir el estado de una variable booleana, 
// es decir, de un bit 0 o 1.
// Anteponiendo "!" a una variable booleana (1 o 0), su valor cambiara.
//
// Ejemplo:
// bool direccion = 0;      // variable direccion inica en 0
// direccion = !direccion   // invierte el valor, ahora vale 1
// ------------------------------------------------------------------------------------------------------------

#include<RobbusKidsy.h>

Robbus Kidsy;                     // Crea tu Robbus Kidsy

bool state_led1 = 0;              // Led1 comienza encendido
bool state_led2 = 1;              // Led2 comienza apagado

void setup() {
  Kidsy.begin();                  // Inicializa el hardware del Robbus Kidsy
  Kidsy.Led1.set(state_led1);     // La funcion set prende o apaga el lED con 1 o 0 respectivamente
  Kidsy.Led2.set(state_led2);
}

void loop() {
  if(Kidsy.ButtonA.read() == PRESSED) {
    state_led1 = !state_led1;             // Cambia el valor de state_led1
    Kidsy.Led1.set(state_led1);
  }
  if(Kidsy.ButtonB.read() == PRESSED) {
    state_led2 = !state_led2;             // Cambia el valor de state_led2
    Kidsy.Led2.set(state_led2);
  }
} 