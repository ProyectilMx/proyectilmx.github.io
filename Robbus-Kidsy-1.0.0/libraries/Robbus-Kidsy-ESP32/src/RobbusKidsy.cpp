#include <Arduino.h>
#include <RobbusKidsy.h>

#ifndef _ROBBUSKIDSY_CPP_
#define _ROBBUSKIDSY_CPP_

Adafruit_NeoPixel dot(1, 19, NEO_GRB + NEO_KHZ800);  // 1 neopixel en pin19
TCS34725 tcs = TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

void Robbus :: begin() {

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LEDW, OUTPUT);
  
  pinMode(DCM_LEFT_IN1, OUTPUT);
  pinMode(DCM_LEFT_IN2, OUTPUT);
  pinMode(DCM_RIGHT_IN1, OUTPUT);
  pinMode(DCM_RIGHT_IN2, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  ledcSetup(PWM_CHANNEL_LEFT_IN1, PWM_MOTOR_FREQ, PWM_RESOUTION);
  ledcAttachPin(DCM_LEFT_IN1, PWM_CHANNEL_LEFT_IN1);
  ledcSetup(PWM_CHANNEL_LEFT_IN2, PWM_MOTOR_FREQ, PWM_RESOUTION);
  ledcAttachPin(DCM_LEFT_IN2, PWM_CHANNEL_LEFT_IN2);

  ledcSetup(PWM_CHANNEL_RIGHT_IN1, PWM_MOTOR_FREQ, PWM_RESOUTION);
  ledcAttachPin(DCM_RIGHT_IN1, PWM_CHANNEL_RIGHT_IN1);
  ledcSetup(PWM_CHANNEL_RIGHT_IN2, PWM_MOTOR_FREQ, PWM_RESOUTION);
  ledcAttachPin(DCM_RIGHT_IN2, PWM_CHANNEL_RIGHT_IN2);

  ledcSetup(PWM_CHANNEL_BUZZER, 0, PWM_RESOUTION);
  ledcAttachPin(BUZZER, PWM_CHANNEL_BUZZER);
  ledcWrite(BUZZER, 128);

  ButtonA.pin = BUTTON_A;
  ButtonB.pin = BUTTON_B;

  Led1.pin = LED1;
  Led2.pin = LED2;

  ArrowForward.pin = AN_UP;
  ArrowBackward.pin = AN_DOWN;
  ArrowLeft.pin = AN_LEFT;
  ArrowRight.pin = AN_RIGHT;

  for(int i=0; i<ARROW_BUFFER_SIZE; i++) {
    ArrowForward.analogRead();
    ArrowBackward.analogRead();
    ArrowLeft.analogRead();
    ArrowRight.analogRead();
  }

  dot.begin();
  Neopixel.color(BLACK);
  tcs.begin();

  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
    ColorSensor.gammatable[i] = x;
  }
}

uint8_t Robbus :: buttons :: read() {
  new_state = digitalRead(pin);
  if(new_state == HIGH && old_state == HIGH) status = HOLD_RELEASED;  // button remains released
  if(new_state == HIGH && old_state == LOW) status = RELEASED;        // button is pressed once
  if(new_state == LOW && old_state == HIGH) status = PRESSED;         // button is released once
  if(new_state == LOW && old_state == LOW) status = HOLD_PRESSED;     // button remains pressed
  old_state = new_state;                                              // the last state gets old
  if(status == RELEASED || status == PRESSED) {
    delay(50);
  }
  return(status);
}

void Robbus :: Led :: set(bool new_status) {
  status = new_status;
  digitalWrite(pin, status);
}

void Robbus :: Led :: on() {
  status = ON;
  digitalWrite(pin, status);
}

void Robbus :: Led :: off() {
  status = OFF;
  digitalWrite(pin, status);
}

bool Robbus :: Led :: toggle() {
  status = !status;
  digitalWrite(pin, status);
  return(!status);
}

void Robbus :: movement :: MotorLeft(int16_t vel) {
  if(vel > 255) vel = 255;
  else if(vel < -255) vel = -255;
  if(vel > 0) direction = FRONT;
  else direction = BACK;
  speed = abs(vel);
  if(direction == FRONT) {
    ledcWrite(PWM_CHANNEL_LEFT_IN1, 255 - speed);
    ledcWrite(PWM_CHANNEL_LEFT_IN2, 255);
  }
  else {
    ledcWrite(PWM_CHANNEL_LEFT_IN1, 255);
    ledcWrite(PWM_CHANNEL_LEFT_IN2, 255 - speed);
  }
}

void Robbus :: movement :: MotorRight(int16_t vel) {
  if(vel > 255) vel = 255;
  else if(vel < -255) vel = -255;
  if(vel > 0) direction = FRONT;
  else direction = BACK;
  speed = abs(vel);
  if(direction == FRONT) {
    ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255 - speed);
    ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255);
  }
  else {
    ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255);
    ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255 - speed);
  }
}

void Robbus :: movement :: forward(uint8_t vel) {
  if(vel > 255) vel = 255;
  else if(vel < 0) vel = 0;
  speed = vel;
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255 - speed);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255 - speed);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255);
}

void Robbus :: movement :: backward(uint8_t vel) {
  if(vel > 255) vel = 255;
  else if(vel < -255) vel = -255;
  
  if(speed < 0) speed = vel;
  else speed = -vel;
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255 + speed);
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255 + speed);
}

void Robbus :: movement :: turnLeft(uint8_t speed) {
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255 - speed);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255 - speed);
}

void Robbus :: movement :: turnRight(uint8_t speed) {
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255 - speed);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255 - speed);
}

void Robbus :: movement :: closedLeft(uint8_t speed) {
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255 - speed);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255);
}

void Robbus :: movement :: closedRight(uint8_t speed) {
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255 - speed);
}

void Robbus :: movement :: wideLeftFront(uint8_t speed, float factor) {
  float speed_div;
  if(factor > 0 && factor < 12) {
    // ecuation 1
    speed_div = -0.22*factor + 5.8;
  }
  else if(factor >= 12) {
    // ecuation 2
    speed_div = -0.0384*factor + 2.3;
  }
  
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255 - speed);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255 - (int)(speed/speed_div));
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255);
}

void Robbus :: movement :: wideLeftBack(uint8_t speed, float factor) {
  float speed_div;
  if(factor > 0 && factor < 12) {
    // ecuation 1
    speed_div = -0.22*factor + 4.66;
  }
  else if(factor >= 12) {
    // ecuation 2
    speed_div = -0.0384*factor + 2.46;
  }
  
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255 - speed);
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255 - (int)(speed/speed_div));
}

void Robbus :: movement :: wideRightFront(uint8_t speed, float factor) {
  float speed_div;
  if(factor > 0 && factor < 12) {
    // ecuation 1
    speed_div = -0.22*factor + 5.8;
  }
  else if(factor >= 12) {
    // ecuation 2
    speed_div = -0.0384*factor + 2.3;
  }
  
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255 - speed);
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255 - (int)(speed/speed_div));
}

void Robbus :: movement :: wideRightBack(uint8_t speed, float factor) {
  float speed_div;
  if(factor > 0 && factor < 12) {
    // ecuation 1
    speed_div = -0.22*factor + 4.66;
  }
  else if(factor >= 12) {
    // ecuation 2
    speed_div = -0.0384*factor + 2.46;
  }
  
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255 - speed);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255 - (int)(speed/speed_div));
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255);
}

void Robbus :: movement :: stop() {
  ledcWrite(PWM_CHANNEL_RIGHT_IN1, 255);
  ledcWrite(PWM_CHANNEL_RIGHT_IN2, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN1, 255);
  ledcWrite(PWM_CHANNEL_LEFT_IN2, 255);
}

uint8_t Robbus :: Arrows :: analogRead() {
  // subtract the last reading:
  total = total - buffer[readIndex];
  // read from the sensor:
  buffer[readIndex] = touchRead(pin);
  // add the reading to the total:
  total = total + buffer[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= ARROW_BUFFER_LENGHT) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / ARROW_BUFFER_LENGHT;
  analog = average;
  return(average);
}

void Robbus :: Arrows :: calibrate(bool state) {
  if(state == NOTOUCHED) {
    noTouchCalibrate = analogRead();
  }
  else touchCalibrate = analogRead();

  thresshold = (noTouchCalibrate - touchCalibrate) / 2;
}

uint8_t Robbus :: Arrows :: read() {
  analogRead();
  if(analog < thresshold) new_state = HIGH;
  else new_state = LOW;
  if(new_state == LOW && old_state == LOW) status = HOLD_NOTOUCHED;
  if(new_state == LOW && old_state == HIGH) status = NOTOUCHED;
  if(new_state == HIGH && old_state == LOW) status = TOUCHED;
  if(new_state == HIGH && old_state == HIGH) status = HOLD_TOUCHED;
  old_state = new_state;
  return(status);
}

void Robbus :: Buzzer :: playTone(int16_t frequency, uint16_t duration) {
  ledcSetup(PWM_CHANNEL_BUZZER, frequency, PWM_RESOUTION);
  ledcAttachPin(BUZZER, PWM_CHANNEL_BUZZER);
  ledcWrite(PWM_CHANNEL_BUZZER, 128);
  delay(duration);
  ledcWrite(PWM_CHANNEL_BUZZER, 0);
}

void Robbus :: Buzzer :: playTone(int16_t frequency) {
  if(old_frequency != frequency) {
    ledcSetup(PWM_CHANNEL_BUZZER, frequency, PWM_RESOUTION);
    ledcAttachPin(BUZZER, PWM_CHANNEL_BUZZER);
    ledcWrite(PWM_CHANNEL_BUZZER, 128);
  }
  old_frequency = frequency;
}


void Robbus :: Buzzer :: noTone() {
  ledcSetup(PWM_CHANNEL_BUZZER, 0, PWM_RESOUTION);
  ledcAttachPin(BUZZER, PWM_CHANNEL_BUZZER);
  ledcWrite(PWM_CHANNEL_BUZZER, 0);
  old_frequency = 0;
}

void Robbus :: Buzzer :: playNote(char note, uint16_t duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'x', 'a', 'z', 'b', 'C', 'y', 'D', 'w', 'E', 'F', 'q', 'G', 'i' };
  int tones[] = { 1898, 1690, 1500, 1420, 1265, 1194, 1126, 1063, 1001, 947, 893, 843, 795, 749, 710, 668, 630, 594 };
   
  // play the tone corresponding to the note name
  for (int i = 0; i < 18; i++) {
    if (names[i] == note) {
      playTone((tones[i]), duration);
    }
  }
}

void Robbus :: Buzzer :: r2d2(uint16_t time) {
  for(int i=0; i<time/75; i++) {
    playTone(random(50, 5000), 75);
  }
  noTone();
}

void Robbus :: Neopixel :: color(uint8_t red, uint8_t green, uint8_t blue) {
  if(red < 0) red = 0;
  else if(red > 255) red = 255;
  if(green < 0) green = 0;
  else if(green > 255) green = 255;
  if(blue < 0) blue = 0;
  else if(blue > 255) blue = 255;
  dot.setPixelColor(0, red, green, blue);
  dot.show();
}

void Robbus :: Neopixel :: color(uint8_t color, uint8_t brightness) {
  if(brightness < 1) brightness = 1;
  else if(brightness > 255) brightness = 255;
  switch(color) {
    case BLACK:   off();                                                    break;
    case RED:     dot.setPixelColor(0, brightness, 0, 0);                   break;
    case GREEN:   dot.setPixelColor(0, 0, brightness, 0);                   break;
    case BLUE:    dot.setPixelColor(0, 0, 0, brightness);                   break;
    case YELLOW:  dot.setPixelColor(0, brightness, brightness, 0);          break;
    case CYAN:    dot.setPixelColor(0, 0, brightness, brightness);          break;
    case MAGENTA: dot.setPixelColor(0, brightness, 0, brightness);          break;
    case WHITE:   dot.setPixelColor(0, brightness, brightness, brightness); break;
  }
  dot.show();
}

void Robbus :: Neopixel :: color(uint8_t color) {
  switch(color) {
    case BLACK:   off();                               break;
    case RED:     dot.setPixelColor(0, 255, 0, 0);     break;
    case GREEN:   dot.setPixelColor(0, 0, 255, 0);     break;
    case BLUE:    dot.setPixelColor(0, 0, 0, 255);     break;
    case YELLOW:  dot.setPixelColor(0, 255, 255, 0);   break;
    case CYAN:    dot.setPixelColor(0, 0, 255, 255);   break;
    case MAGENTA: dot.setPixelColor(0, 255, 0, 255);   break;
    case WHITE:   dot.setPixelColor(0, 255, 255, 255); break;
  }
  dot.show();
}

void Robbus :: Neopixel :: off() {
  dot.setPixelColor(0, 0, 0, 0);
  dot.show();
}

void Robbus :: Neopixel :: fadeIn(uint8_t col, uint16_t speed) {
  for(int i=0; i<255; i++) {
    color(col, i);
    delay(speed);
  }
}

void Robbus :: Neopixel :: fadeOut(uint8_t col, uint16_t speed) {
  for(int i=255; i>=0; i--) {
    color(col, i);
    delay(speed);
  }
}

void Robbus :: Neopixel :: fadeInOut(uint8_t col, uint16_t speed, uint16_t time_between, uint16_t time_end) {
  fadeIn(col, speed);
  delay(time_between);
  fadeOut(col, speed);
  delay(time_end);
}

void Robbus :: Neopixel :: heartBeat(uint8_t col) {
  fadeInOut(col, 1, 0, 0);
  fadeInOut(col, 1, 0, 500);
}

void Robbus :: Neopixel :: rainbow(uint16_t speed) {
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    int pixelHue = firstPixelHue + (65536L / 1);
    dot.setPixelColor(0, dot.gamma32(dot.ColorHSV(pixelHue)));
    dot.show(); // Update strip with new contents
    delay(speed);  // Pause for a moment
  }
}

uint8_t Robbus :: ColorSensor :: read() {
  tcs.getRawData(&red, &green, &blue, &white);
  
  // Hacer rgb medición relativa
  sum = white;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
 
  // Escalar rgb a bytes
  r *= 256; g *= 256; b *= 256;

  // Convertir a hue, saturation, value
  ColorConverter::RgbToHsv(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b), hue, saturation, sat_value);
  hue360 = hue * 360;

  if (hue360 < 30 || hue360 >= 330 && white > BLACK_UMBRAL && white < WHITE_UMBRAL)
  {
    name = "red";
    value = RED;
  }
  else if (hue360 >= 31 && hue360 < 90 && white > BLACK_UMBRAL && white < WHITE_UMBRAL)
  {
    name = "yellow";
    value = YELLOW;
  }
  else if (hue360 >= 91 && hue360 < 150 && white > BLACK_UMBRAL && white < WHITE_UMBRAL)
  {
    name = "green";
    value = GREEN;
  }
  else if (hue360 >= 151 && hue360 < 210 && white > BLACK_UMBRAL && white < WHITE_UMBRAL)
  {
    name = "cyan";
    value = CYAN;
  }
  else if (hue360 >= 210 && hue360 < 270 && white > BLACK_UMBRAL && white < WHITE_UMBRAL)
  {
    name = "blue";
    value = BLUE;
  }
  else if (hue360 >= 270 && hue360 < 330 && white > BLACK_UMBRAL && white < WHITE_UMBRAL)
  {
    name = "magenta";
    value = MAGENTA;
  }
  else if(white <= BLACK_UMBRAL) {
    name = "black";
    value = BLACK;
  }
  else if(white >= WHITE_UMBRAL) {
    name = "white";
    value = WHITE;
  }
  return(value);
}

void Robbus :: ColorSensor :: enable() {
    tcs.enable();
    digitalWrite(LEDW, HIGH);
}

void Robbus :: ColorSensor :: disable() {
    tcs.disable();
    digitalWrite(LEDW, LOW);
}

void ColorConverter :: RgbToHsv(uint8_t red, uint8_t green, uint8_t blue, double& hue, double& saturation, double& sat_value) {
  auto rd = static_cast<double>(red) / 255;
  auto gd = static_cast<double>(green) / 255;
  auto bd = static_cast<double>(blue) / 255;
  auto max = threeway_max(rd, gd, bd), min = threeway_min(rd, gd, bd);
   
  sat_value = max;

  auto d = max - min;
  saturation = max == 0 ? 0 : d / max;

  hue = 0;
  if (max != min) {
    if (max == rd) hue = (gd - bd) / d + (gd < bd ? 6 : 0);
    else if (max == gd) hue = (bd - rd) / d + 2;
    else if (max == bd) hue = (rd - gd) / d + 4;
    hue /= 6;
  }
}

double inline ColorConverter :: threeway_max(double a, double b, double c) {
  return max(a, max(b, c));
}

double inline ColorConverter :: threeway_min(double a, double b, double c) {
  return min(a, min(b, c));
}

double ColorConverter :: hue2rgb(double p, double q, double t) {
  if (t < 0) t += 1;
  if (t > 1) t -= 1;
  if (t < 1 / 6.0) return p + (q - p) * 6 * t;
  if (t < 1 / 2.0) return q;
  if (t < 2 / 3.0) return p + (q - p) * (2 / 3.0 - t) * 6;
  return p;
}

#endif
