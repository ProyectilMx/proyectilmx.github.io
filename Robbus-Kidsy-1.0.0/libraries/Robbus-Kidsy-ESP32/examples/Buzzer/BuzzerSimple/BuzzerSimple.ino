// ------------------------------------------------ ROBBUS KIDSY ----------------------------------------------
//
// Nivel de dificultad: FACIL
//
// EJEMPLO SIMPLE DE USO DEL BUZZER
// Este ejemplo es de uso libre y esta pensado para dar una introduccion al hardware del robot Robbus Kidsy.
// Autor: Fabian Alfonso Flores
// Empresa: Proyectil Mx
// Fecha: 03 de marzo de 2020
// ------------------------------------------------------------------------------------------------------------
//
// Robbus Kidsy cuenta con 1 buzzer:
// - Buzzer
//
// El buzzer no es otra cosa que una mini bocina, con la que Robbus es capaza de hacer sonidos
// Utilizar el Buzzer es muy sencillo, basta con emplear la funcion Buzzer.playTone().
//
// Un tono es un sonido que se repite muchas veces en un segundo, y dependiendo de esa cantidad de veces, sera
// como lo escuches, grave o agudo. Para que Robbus Kidsy haga sonidos, basta con poner dentro de la funcion
// playTone() la frecuencia (numero de veces por segundo o Hertz o Hz) que tendra tu tono, y, si quieres que el 
// sonido dure cierto tiempo, la cantidad en milisegundos (recuerda que 1 segundo tiene 1000 milisegundos) 
// por ejemplo:
//
// Kisdy.Buzzer.playTone(100, 50);    // Robbus reproduce un sonido grave durante 50 milisegundos
// Kidsy.Buzzer.playTone(1000);       // Robbus reproduce un sonido agudo de forma indefinida
// 
// El odio humano puede escuchar sonidos en el rango de los 20Hz a los 20000Hz
// Los valores cercanos a 20 son sonidos graves, y los valores cercanos a 20000 son sonidos agudos, aunque
// generalmente sonidos mayores a 15000Hz ya son imperceptibles para muchas presonas.
//
// Si usas la segunda forma, Robbus no guardara silencio, a menos que uses la funcion Kidsy.Buzzer.noTone()
//
// Kidsy.Buzzer.playTone(1000);                               // reproduce un sonido agudo de forma indefinida
// if(Kidsy.ButtonA.read() == PRESSED) Kidsy.Buzzer.noTone(); // guarda silencio al presionar el boton A
// ------------------------------------------------------------------------------------------------------------

#include<RobbusKidsy.h>

Robbus Kidsy;      // Crea tu robus Kidsy

void setup() {
  Kidsy.begin();   // Inicializa el hardware del Robbus Kidsy
}

void loop() {
  Kidsy.Buzzer.playTone(500);         // se mantiene sonando
  delay(1000);                        // espera 1 segundo
  Kidsy.Buzzer.playTone(1000);        // se mantiene sonando
  delay(1000);                        // espera 1 segundo
  Kidsy.Buzzer.playTone(1500);        // se mantiene sonando
  delay(1000);                        // espera 1 segundo
  Kidsy.Buzzer.playTone(2000, 1000);  // suena durante 1 segundo
  Kidsy.Buzzer.playTone(2500, 1000);  // suena durante 1 segundo
  Kidsy.Buzzer.noTone();              // deja de sonar
  delay(3000);                        // espera 3 segundos
}