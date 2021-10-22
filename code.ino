//Se incluye la librería Wire para el protocolo I2C
#include <Wire.h>
//Se declara el número de dispositivo para el esclavo
#define SLAVE_ADDR 9

//Se inicializa el valor de los bytes del bus serial
int bcount;
//Se inicializa el valor que recibirá del esclavo
byte temp;
//Puerto del LED
int led = 13;
 
void setup()
{
  //Se comienza la comunicación como maestro
  Wire.begin();
  
  //Se inicia el bus serial en el puerto 9600
  Serial.begin(9600);
}
 
//Función para recibir el valor de la temperatura
byte readI2C(int address) {
  
  //Variable en la que se recibirá el valor de la temperatura
  byte bval ;
  
  //tiempo desde que se inició el programa
  long entry = millis();
  
  //Inicio de solicitud al esclavo
  Wire.requestFrom(address, 1); 
  
  //Espera del valor
  while (Wire.available() == 0 && (millis() - entry) < 100)  Serial.print("Waiting");
  if  (millis() - entry < 100) bval = Wire.read();
  return bval;
}
 
void loop()
{
  //Espera del inicio del bus serial
  while (readI2C(SLAVE_ADDR) < 255) {
    Serial.print("Waiting"); 
  }
  
  //Captación de la temperatura
  temp = readI2C(SLAVE_ADDR);
  
  //Si la temperatura es mayor a 100C°, prender el LED, de lo contrario, apagarlo
  if(temp > 100){
    analogWrite(led, 255);
  }else{
    analogWrite(led, 0);
  }
  
  //Imprimir el valor de la temperatura
  Serial.println(temp);
  
  //Esperar 200ms
  delay(200);
}
