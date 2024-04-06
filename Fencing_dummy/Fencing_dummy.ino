#include <Ultrasonic.h>
#include <math.h>
// D12 - включение силовой части электроколеса
int power_motor = 12;
// D11 - движение вперед (на размыкании)
int step_motor = 11;
// D10 - переключение направления движения
int revers_motor = 10;
// D09 - включение торможения
int abs_motor = 9;
// HC-SR04 Датчик расстояния
// D08 - Echo
int echo = 8;
// D07 - Trig
int trig = 7;
int pause = 1000;
Ultrasonic ultrasonic (echo, trig);
// ultrasonic.distanceRead();
// Serial.println (ultrasonic.distanceRead());
int distance = 0;
// D06
// D05
// А0 - состояние  HC-SR04 Датчика расстояния (0 - выкл)
int hc_pin = 14;
// A1 - режим работы (выбор программы)  
int option_pin = 15;
// A2 - управление с пульта
// A3
// A4
// A5 
//////////////////
// Конфигурации //
int f_step = 500;
int f_abs = 1000;
int f_pause = 0;
int r_step = 500;
int r_abs = 1000;
int r_pause = 0;
void setup() {
// Насторойка параметров переключателя режимов работы
for (int i = 0; i < sizeof (option_R) ; i++) {
    option_U [i] =  1024 * option_R [0] / (option_R [0] + option_R [i+1]) * 1024;
  }
// Настройка пульта
/*
joystick_A [0] = 1024 * R[0]*R[4]/(R[0]+R[4]) / ( R[0]*R[4]/(R[0]+R[4]) + R[3]); // 930
joystick_A [1] = 1024 * R[0]*R[4]/(R[0]+R[4]) / ( R[0]*R[4]/(R[0]+R[4]) + R[1]*R[3]/(R[1]+R[3])); // 536
joystick_A [2] = 1024 * R[0]*R[4]/(R[0]+R[4]) / ( R[0]*R[4]/(R[0]+R[4]) +  R[2]*R[3]/(R[2]+R[3])); // 236
joystick_A [3] = 1024 * R[0] / ( R[0] + R[3]); // 10
joystick_A [4] = 1024 * R[0] / ( R[0] + R[1]*R[3]/(R[1]+R[3])); // 101
joystick_A [5] = 1024 * R[0] / ( R[0] +  R[2]*R[3]/(R[2]+R[3])); // 29
*/
// Задание портов мотора
  pinMode (power_motor, OUTPUT);
  pinMode (step_motor, OUTPUT);
  pinMode (revers_motor, OUTPUT);
  pinMode (abs_motor, OUTPUT);
  pinMode (power_motor, OUTPUT);
// Сборос настрое мотора
  digitalWrite (power_motor, 0);
  digitalWrite (step_motor, 0);
  digitalWrite (revers_motor, 0);
  digitalWrite (abs_motor, 0);
// Включение мотора
  digitalWrite (power_motor, 1); // включение работы мотора
  //digitalWrite (abs_motor, 1);
  //Serial.begin (9600);
}
void loop() {
  int val = get_Option();
  while (!val){
    switch (val) {
      case 1: combination1();
      break;
      case 2: combination2();
      break;
      case 3: //combination3();
      break;
      case 4: //combination4();
      break;
      case 5: //combination5();
      break;
      case 6: //combination6();
      break;
      case 7: //combination7();
      break;
      case 8: //combination8();
      break;
      }
      val = get_Option();
  }   
}
int get_Option(){
  int value = analogRead(option_pin);
  if (value < 50) return 0;
  else if (value < 120)return 1;
  else if (value < 130)return 2;
  else if (value < 150)return 3;
  else if (value < 200)return 4;
  else if (value < 240)return 5;
  else if (value < 300)return 6;
  else if (value < 400)return 7;
  else return 8;
}
void  combination1 () {
  if (!get_Option()); // возврат в программу
}
int is_the_wall_near (){
  if (ultrasonic.distanceRead() < 50)return 1;
  else return 0;
}
int is_hs_working () {
  int value = analogRead(hc_pin);
  if (value > 100) return 1;
  else return 0;
  }
void step_forward(){
  digitalWrite (abs_motor, 0);
  digitalWrite (step_motor, 1); delay (f_step); digitalWrite (step_motor, 0);
  digitalWrite (abs_motor, 1); delay (f_abs); digitalWrite (abs_motor, 0); 
  delay (f_pause);
}  
void step_back(){
  digitalWrite (revers_motor, 1); delay (100);
  digitalWrite (step_motor, 1); delay (r_step); digitalWrite (step_motor, 0);
  digitalWrite (abs_motor, 1); delay (r_abs); digitalWrite (abs_motor, 0);
  digitalWrite (revers_motor, 0); delay (100);
  delay (r_pause);
}
void  combination2 () {
  step_forward();
  if (is_hs_working ()) { if (!is_the_wall_near ()) step_back();}
  else step_back();
}
