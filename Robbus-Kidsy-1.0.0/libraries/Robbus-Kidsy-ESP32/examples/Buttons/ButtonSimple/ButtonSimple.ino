// ------------------------------------------------ ROBBUS KIDSY ----------------------------------------------
//
// Nivel de dificultad: MUY FACIL
//
// EJEMPLO DE USO DE LOS BOTONES DE USUARIO A Y B
// Este ejemplo es de uso libre y esta pensado para dar una introduccion al hardware del robot Robbus Kidsy.
// Autor: Fabian Alfonso Flores
// Empresa: Proyectil Mx
// Fecha: 12 de febrero de 2020
// ------------------------------------------------------------------------------------------------------------
//
// Robbus Kidsy cuenta con 2 Botones de usuario:
// - ButtonA
// - ButtonB
// Nota importante: El boton RESET sirve para reiniciar el programa de tu Robbus Kidsy y no se puede programar
// 
// Con este ejemplo entenderas el funcionamiento de los botones de usuario de tu Robot
// Simplemente usa la funcion Kidsy.ButtonA.read() para leer el boton A y el boton B.
// ------------------------------------------------------------------------------------------------------------

#include<RobbusKidsy.h>

Robbus Kidsy;             // Crea tu Robbus Kidsy

void setup() {
  Serial.begin(115200);   // Inicializa comunicacion serial a 115200 baudios
  Kidsy.begin();          // Inicializa el hardware de Robbus Kidsy
}

void loop() {
  if(Kidsy.ButtonA.read() == PRESSED) Serial.println("Boton A Presionado");
  if(Kidsy.ButtonB.read() == PRESSED) Serial.println("Boton B Presionado");
} 