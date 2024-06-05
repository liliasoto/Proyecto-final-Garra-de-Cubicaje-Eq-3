// NOMBRES: LILIA SOTO LLAMAS, DIEGO STEVE SILVA MENDEZ, MAURICIO ALEJANDRO GARCÍA
//          MAX YAHIR RODRÍGUEZ GONZÁLEZ, AXEL ALEJANDRO PÉREZ GÓMEZ, DIEGO ALEJANDRO RIVERA LARIOS
// NO. CONTROL: 20460040, 20460709, 20460545
//              20460278, 20460065, 20460321
// DESCRIPCIÓN: GARRA CON SERVOMOTORES Y MÓDULO BLUETOOTH + PANTALLA LCD CON I2C + FOCO CON RELÉ
// FECHA: 14/05/2024
//
#include <Servo.h>
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
//SoftwareSerial BTSerial(6,7);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

int condicion = 0;

#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);

Servo servoMotor1;  // Objeto del primer servomotor
Servo servoMotor2;  // Objeto del segundo servomotor
Servo servoMotor3;  // Objeto del tercer servomotor
Servo servoMotor4;  // Objeto de la base

#define RELAY_PIN 7 //Para relay

bool rutinaEnCurso = false;

char data = 0;

void setup() {
  servoMotor1.write(0);
  servoMotor2.write(90);
  servoMotor3.write(45);
  servoMotor4.write(0);

  servoMotor1.attach(9);  // Se conecta el primer servomotor al pin 9
  servoMotor2.attach(10);  // Se conecta el segundo servomotor al pin 10
  servoMotor3.attach(11);  // Se conecta el segundo servomotor al pin 11
  servoMotor4.attach(12);  // Se conecta el segundo servomotor al pin 12

  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  lcd.createChar(0, new byte[8] {
    0b00111,
    0b00101,
    0b00111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
  });  

  //BTSerial.begin(9600);       // Inicializamos el puerto serie BT que hemos creado
  Serial.begin(9600);   // Inicializamos  el puerto serie  

  pinMode(RELAY_PIN, OUTPUT); //Para el relé
  digitalWrite(RELAY_PIN, HIGH); 

}

void loop() {
    data = Serial.read(); // Lee el dato recibido del módulo Bluetooth
    
    Serial.print("Dato recibido: ");
    Serial.println(data); // Imprime el dato recibido en la consola serial
    
    // Realiza una acción dependiendo del valor recibido
    if (data == 48) {
      Serial.println("Primer rutina");
      bloque3primerPos();
      tomaCubo2();
      apilarSegundaPosicion();
      tomaCubo1();
      apilaTerceraPosicionEspeshal();
      digitalWrite(RELAY_PIN, LOW);
      delay(2000); 
      digitalWrite(RELAY_PIN, HIGH); 
      data = 0;
    } else if (data == 49) {
      Serial.println("Segunda rutina");
      tomaCubo1();
      apilarPrimeraPosicion();
      tomaCubo2();
      apilarSegundaPosicionEspeshal();
      tomaCubo3();
      apilaTerceraPosicion();
      digitalWrite(RELAY_PIN, LOW); 
      delay(2000); 
      digitalWrite(RELAY_PIN, HIGH); 
      data = 0;
    } else if (data == 50) {
      Serial.println("Tercer rutina");
      bloque3primerPos();
      tomaCubo1();
      apilarSegundaPosicion();
      tomaCubo2();
      apilaTerceraPosicionMegaEspeshal();
      digitalWrite(RELAY_PIN, LOW); 
      delay(2000); 
      digitalWrite(RELAY_PIN, HIGH); 
    } else {
      Serial.println("Número no reconocido");
      data = 0;
    }
}

void tomaCubo1() {
      lcd.clear();
      //LEVANTAR PRIMER BLOQUE (B1)
      //Baja servo1 116° (B1)
      lcd.print("Baja servo1 118");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 118; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      
      //Cierra garra (B1)
      lcd.clear();
      lcd.print("Cierra garra 40");
      lcd.write(byte(0));
      for (int pos = 45; pos >= 5; pos -= 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Sube servo1 116° (B1)
      lcd.clear();
      lcd.print("Sube servo1 118");
      lcd.write(byte(0));
      for (int pos = 118; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
}

void apilarPrimeraPosicion(){
  //APLIACIÓN EN PRIMERA POSICIÓN
      //Gira base 90°(B1)
      lcd.clear();
      lcd.print("Gira base 90");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 90; pos += 1) {
        servoMotor4.write(pos);
        delay(50);
      }
      //Baja servo1 119° (B1)
      lcd.clear();
      lcd.print("Baja servo1 119");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 119; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Abre garra (B1)
      lcd.clear();
      lcd.print("Abre garra 40");
      lcd.write(byte(0));
      for (int pos = 5; pos <= 45; pos += 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Sube servo1 119° (B1)
      lcd.clear();
      lcd.print("Sube servo1 119");
      lcd.write(byte(0));
      for (int pos = 119; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Gira base 90° posicion original (B1)
      lcd.clear();
      lcd.print("Gira base 90");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 0; pos -= 1) {
        servoMotor4.write(pos);
        delay(50);
      }
}

void tomaCubo2(){
        //LEVANTAR SEGUNDO BLOQUE (B2)
      //Baja servo1 80° (B2)
      lcd.clear();
      lcd.print("Baja servo1 80");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 80; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 90° (B2)
      lcd.clear();
      lcd.print("Baja servo2 66");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 24; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Cierra garra (B2)
      lcd.clear();
      lcd.print("Cierra garra 40");
      lcd.write(byte(0));
      for (int pos = 45; pos >= 5; pos -= 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Baja servo2 4° (B2)
      lcd.clear();
      lcd.print("Baja servo2 4");
      lcd.write(byte(0));
      for (int pos = 24; pos >= 20; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Sube servo1 80° (B2)
      lcd.clear();
      lcd.print("Sube servo1 80");
      lcd.write(byte(0));
      for (int pos = 80; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Sube servo2 70° (B2)
      lcd.clear();
      lcd.print("Sube servo2 70");
      lcd.write(byte(0));
      for (int pos = 20; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
}

void apilarSegundaPosicion(){
        //APILACIÓN EN SEGUNDA POSICIÓN
      //Gira base 90° (B2)
      lcd.clear();
      lcd.print("Gira base 90");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 90; pos += 1) {
        servoMotor4.write(pos);
        delay(50);
      }
      //Baja servo1 85° (B2)
      lcd.clear();
      lcd.print("Baja servo1 85");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 85; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 41° (B2)
      lcd.clear();
      lcd.print("Baja servo2 41");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 49; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Abre garra (B2)
      lcd.clear();
      lcd.print("Abre garra 40");
      lcd.write(byte(0));
      for (int pos = 5; pos <= 45; pos += 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Sube servo1 85° (B2)
      lcd.clear();
      lcd.print("Sube servo1 85");
      lcd.write(byte(0));
      for (int pos = 85; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Sube servo2 41° (B2)
      lcd.clear();
      lcd.print("Sube servo2 41");
      lcd.write(byte(0));
      for (int pos = 49; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Gira base pos original (B2)
      lcd.clear();
      lcd.print("Gira base 90");
      lcd.write(byte(0));
        for (int pos = 90; pos >= 0; pos -= 1) {
        servoMotor4.write(pos);
        delay(50);
      }
}

void apilarSegundaPosicionEspeshal(){
          //APILACIÓN EN SEGUNDA POSICIÓN
      //Gira base 88° (B2)
      lcd.clear();
      lcd.print("Gira base 88");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 88; pos += 1) {
        servoMotor4.write(pos);
        delay(50);
      }
      //Baja servo1 85° (B2)
      lcd.clear();
      lcd.print("Baja servo1 85");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 85; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 41° (B2)
      lcd.clear();
      lcd.print("Baja servo2 41");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 49; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Abre garra (B2)
      lcd.clear();
      lcd.print("Abre garra 40");
      lcd.write(byte(0));
      for (int pos = 5; pos <= 45; pos += 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Sube servo1 85° (B2)
      lcd.clear();
      lcd.print("Sube servo1 85");
      lcd.write(byte(0));
      for (int pos = 85; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Sube servo2 41° (B2)
      lcd.clear();
      lcd.print("Sube servo2 41");
      lcd.write(byte(0));
      for (int pos = 49; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Gira base pos original (B2)
      lcd.clear();
      lcd.print("Gira base 88");
      lcd.write(byte(0));
        for (int pos = 88; pos >= 0; pos -= 1) {
        servoMotor4.write(pos);
        delay(50);
      }
}

void tomaCubo3(){
     //LEVANTAR TERCER BLOQUE (B3)
      //Baja servo1 75° (B1)
      lcd.clear();
      lcd.print("Baja servo1 75");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 75; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 82° (B2)
      lcd.clear();
      lcd.print("Baja servo2 85");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 5; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Cierra garra (B1)
      lcd.clear();
      lcd.print("Cierra garra 40");
      lcd.write(byte(0));
      for (int pos = 45; pos >= 5; pos -= 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Baja servo2 5° (B2)
      lcd.clear();
      lcd.print("Baja servo2 5");
      lcd.write(byte(0));
      for (int pos = 5; pos >= 0; pos -= 1) {
        servoMotor2.write(pos);
        delay(100);
      }
        //Sube servo1 75° (B1)
      lcd.clear();
      lcd.print("Sube servo1 75");
      lcd.write(byte(0));
      for (int pos = 75; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Sube servo2 90° (B2)
      lcd.clear();
      lcd.print("Sube servo2 90");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
}

void apilaTerceraPosicion(){
        //APILACIÓN EN TERCERA POSICIÓN
      //Gira base 88° (B2)
      lcd.clear();
      lcd.print("Gira base 88");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 88; pos += 1) {
        servoMotor4.write(pos);
        delay(50);
      }
      //Baja servo1 65° (B2)
      lcd.clear();
      lcd.print("Baja servo1 65");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 65; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 59° (B2)
      lcd.clear();
      lcd.print("Baja servo2 59");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 31; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Abre garra (B2)
      lcd.clear();
      lcd.print("Abre garra 90");
      lcd.write(byte(0));
      for (int pos = 19; pos <= 45; pos += 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Sube servo1 65° (B2)
      lcd.clear();
      lcd.print("Sube servo1 65");
      lcd.write(byte(0));
      for (int pos = 65; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      delay(50);
      //Sube servo2 59° (B2)
      lcd.clear();
      lcd.print("Sube servo2 59");
      lcd.write(byte(0));
      for (int pos = 31; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Gira base pos original (B2)
      lcd.clear();
      lcd.print("Gira base 88");
      lcd.write(byte(0));
        for (int pos = 88; pos >= 0; pos -= 1) {
        servoMotor4.write(pos);
        delay(50);
      }
}

void bloque3primerPos() {
        //LEVANTAR TERCER BLOQUE (B3)
      //Baja servo1 75° (B1)
      lcd.clear();
      lcd.print("Baja servo1 75");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 75; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 82° (B2)
      lcd.clear();
      lcd.print("Baja servo2 85");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 5; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Cierra garra (B1)
      lcd.clear();
      lcd.print("Cierra garra 40");
      lcd.write(byte(0));
      for (int pos = 45; pos >= 5; pos -= 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Baja servo2 5° (B2)
      lcd.clear();
      lcd.print("Baja servo2 5");
      lcd.write(byte(0));
      for (int pos = 5; pos >= 0; pos -= 1) {
        servoMotor2.write(pos);
        delay(100);
      }
        //Sube servo1 75° (B1)
      lcd.clear();
      lcd.print("Sube servo1 75");
      lcd.write(byte(0));
      for (int pos = 75; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Sube servo2 90° (B2)
      lcd.clear();
      lcd.print("Sube servo2 90");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
            //APLIACIÓN EN PRIMERA POSICIÓN
      //Gira base 91°(B1)
      lcd.clear();
      lcd.print("Gira base 91");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 91; pos += 1) {
        servoMotor4.write(pos);
        delay(50);
      }
      //Baja servo1 100° (B1)
      lcd.clear();
      lcd.print("Baja servo1 100");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 100; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 23° (B2)
      lcd.clear();
      lcd.print("Baja servo2 23");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 67; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Abre garra (B1)
      lcd.clear();
      lcd.print("Abre garra 40");
      lcd.write(byte(0));
      for (int pos = 5; pos <= 45; pos += 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Sube servo2 23° (B2)
      lcd.clear();
      lcd.print("Sube servo2 23");
      lcd.write(byte(0));
      for (int pos = 67; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Sube servo1 100° (B1)
      lcd.clear();
      lcd.print("Sube servo1 100");
      lcd.write(byte(0));
      for (int pos = 100; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Gira base 91° posicion original (B1)
      lcd.clear();
      lcd.print("Gira base 91");
      lcd.write(byte(0));
      for (int pos = 91; pos >= 0; pos -= 1) {
        servoMotor4.write(pos);
        delay(50);
      }
}

void apilaTerceraPosicionEspeshal(){
        //APILACIÓN EN TERCERA POSICIÓN
      //Gira base 90° (B2)
      lcd.clear();
      lcd.print("Gira base 90");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 90; pos += 1) {
        servoMotor4.write(pos);
        delay(50);
      }
      //Baja servo1 67° (B2)
      lcd.clear();
      lcd.print("Baja servo1 67");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 67; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 55° (B2)
      lcd.clear();
      lcd.print("Baja servo2 55");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 35; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Abre garra (B2)
      lcd.clear();
      lcd.print("Abre garra 90");
      lcd.write(byte(0));
      for (int pos = 19; pos <= 45; pos += 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Sube servo1 67° (B2)
      lcd.clear();
      lcd.print("Sube servo1 67");
      lcd.write(byte(0));
      for (int pos = 67; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      delay(50);
      //Sube servo2 55° (B2)
      lcd.clear();
      lcd.print("Sube servo2 55");
      lcd.write(byte(0));
      for (int pos = 35; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Gira base pos original (B2)
      lcd.clear();
      lcd.print("Gira base 90");
      lcd.write(byte(0));
        for (int pos = 90; pos >= 0; pos -= 1) {
        servoMotor4.write(pos);
        delay(50);
      }
}

void apilaTerceraPosicionMegaEspeshal(){
        //APILACIÓN EN TERCERA POSICIÓN
      //Gira base 90° (B2)
      lcd.clear();
      lcd.print("Gira base 90");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 90; pos += 1) {
        servoMotor4.write(pos);
        delay(50);
      }
      //Baja servo1 67° (B2)
      lcd.clear();
      lcd.print("Baja servo1 67");
      lcd.write(byte(0));
      for (int pos = 0; pos <= 67; pos += 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      //Baja servo2 59° (B2)
      lcd.clear();
      lcd.print("Baja servo2 59");
      lcd.write(byte(0));
      for (int pos = 90; pos >= 31; pos -= 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Abre garra (B2)
      lcd.clear();
      lcd.print("Abre garra 90");
      lcd.write(byte(0));
      for (int pos = 19; pos <= 45; pos += 1) {
        servoMotor3.write(pos);
        delay(50);
      }
      //Sube servo1 67° (B2)
      lcd.clear();
      lcd.print("Sube servo1 67");
      lcd.write(byte(0));
      for (int pos = 67; pos >= 0; pos -= 1) {
        servoMotor1.write(pos);
        delay(50);
      }
      delay(50);
      //Sube servo2 59° (B2)
      lcd.clear();
      lcd.print("Sube servo2 59");
      lcd.write(byte(0));
      for (int pos = 31; pos <= 90; pos += 1) {
        servoMotor2.write(pos);
        delay(50);
      }
      //Gira base pos original (B2)
      lcd.clear();
      lcd.print("Gira base 90");
      lcd.write(byte(0));
        for (int pos = 90; pos >= 0; pos -= 1) {
        servoMotor4.write(pos);
        delay(50);
      }
}

void activarRele() {
  digitalWrite(RELAY_PIN, LOW);
  delay(5000);
  digitalWrite(RELAY_PIN, HIGH);
}