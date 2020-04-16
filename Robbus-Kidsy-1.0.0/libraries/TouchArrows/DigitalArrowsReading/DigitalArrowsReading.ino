// ------------------------------------------------ ROBBUS KIDSY ------------------------------------------------
//
// Nivel de dificultad: FACIL
//
// EJEMPLO DE LECTURA DIGITAL DE LAS FLECHAS DE DIRECCION
// Este ejemplo es de uso libre y esta pensado para dar una introduccion al hardware de Robbus Kidsy.
// Autor: Fabian Alfonso Flores
// Empresa: Proyectil Mx
// Fecha: 28 de febrero de 2020
// --------------------------------------------------------------------------------------------------------------
//
// Robbus Kidsy cuenta con 4 flechas de direccion:
// - ArrowForward
// - ArrowBackward
// - ArrowLeft
// - ArrowRight
//
// Estas flechas son sensibles al tacto. Para leer su valor basta con usar la funcion read() la cual:
// Leera un 1 o TOUCHED cuando se toca
// Leera un 0 o NOTOUCHED cuando no se toca
//
// Y posteriormente usar la variable status para saber su valor, por ejemplo:
//
// Kidsy.ArrowForward.read();                   // Lee la flecha Adelante
// if(Kidsy.ArrowForward.status == TOUCHED) {}  // Evalua si la flecha se presiono
//
// Tambien puedes guardar lo que la funcion leyo en una variable declarada por ti:
// bool forward = Kidsy.ArrowForward.read();
// --------------------------------------------------------------------------------------------------------------

#include<RobbusKidsy.h>

Robbus Kidsy;    // Declara una instancia tipo Robbus, llamada Kidsy

void setup() {
  Serial.begin(115200);   // Inicializa comunicacion serial a 115200 baudios
  Kidsy.begin();          // Inicializa el hardware del Robbus Kidsy
}

void loop() {
  bool forward = Kidsy.ArrowForward.read();      // guarda el valor de flecha Adelante
  bool backward = Kidsy.ArrowBackward.read();    // guarda el valor de flecha Atras
  bool left = Kidsy.ArrowLeft.read();            // guarda el valor de flecha Izquierda
  bool right = Kidsy.ArrowRight.read();          // guarda el valor de flecha Derecha
  
  Serial.print("Forward: ");
  Serial.print(forward);
  Serial.print(", Backward: ");
  Serial.print(backward);
  Serial.print(", Left: ");
  Serial.print(left);
  Serial.print(", Right: ");
  Serial.println(right);
}