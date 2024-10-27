// Запись кодов кнопок на ИК пульте
#define IR_Right_1  0x18
#define IR_Right_2  0x52
#define IR_Left_1   0x40
#define IR_Left_2   0x19

// Подключение библиотек
#include <NecDecoder.h>
#include <Servo.h>

// Создание переменных ИК приемника и сервомоторов
NecDecoder ir;
Servo servo_1;
Servo servo_2;

// Инициализация и подключение сервомоторов
void setup() {
  Serial.begin(9600);
  attachInterrupt(0, irIsr, FALLING);

  servo_1.attach(5);
  servo_2.attach(6);
}

// Вспомогательная функция
void irIsr() {
  ir.tick();
}

// Функция для управления сервомоторами
void Move_Servo(Servo servo, bool mode) {

  // Плавное движение мотора против часовой стрелки
  if (mode) {
    for (int i = servo.read(); i <= 180; i++) {
      servo.write(i);
      delay(15);
    }
  }

  // Плавное движение мотора по часовой стрелки
  else {
    for (int i = servo.read(); i > 0; i--) {
      servo.write(i);
      delay(15);
    }
  }
}

// Основной блок исполняемый программой
void loop() {
  if (ir.available()) {
    // Считываем нажатия на ИК порте
    switch (ir.readCommand()) {

      case IR_Right_1:
        Move_Servo(servo_1, 0);
        break;

      case IR_Right_2:
        Move_Servo(servo_1, 1);
        break;

      case IR_Left_1:
        Move_Servo(servo_2, 0);
        break;

      case IR_Left_2:
        Move_Servo(servo_2, 1);
        break;
    }
  }
}
