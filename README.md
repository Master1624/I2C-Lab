# Automation Workshop 6

This workshop allow students understand how the concept of I2C works and will show through code the basis of this concept.

This exercise require from students to have knowledge of Arduino and its programming language based on C++, their own TinkerCAD account to simulate the connections and previous knowledge about digital logic and the use of the components shown in this practice.

# Workshop Development

To develop this workshop, first it will be shown how are the different connections made in the 2 Arduinos with the different components. Then, the code will be explained step-by-step, showing what the different functions do and its different variables. 

## I2C Connections

As before, this section will show what how are the connections distributed between the two Arduino Uno, the temperature component, the LED diode and the prototype board.

In the next image it will be shown how are the connections distributed, and then it will be explained each connection.

![InkedI2C Connections_LI](https://user-images.githubusercontent.com/15149995/138533148-946c4510-2854-45f1-b697-029532fbf064.jpg)

1. The first connection (left connection with number one "1") is how the two Arduinos communicate between each other, the left one being the slave who send the information to the parent, the right Arduino.
2. The A4 slots from each of the Arduinos is the SDA or the data connection that will be sent from the slave to the master, and the A5 slots is the SCL or the time clock connection.

One of the other connections are the temperature component with the slave Arduino, who will basically send the ambient temperature information to the slave, and then to the master.

The last connection is the LED diode, which will be ligth up when the temperature is higher than 100°F and will be turned off when the temperature is lower than the value before.

## Code Explanation

The following code explanation will be shown in Spanish in the file.

```c++
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
  
  //Si la temperatura es mayor a 100°F, prender el LED, de lo contrario, apagarlo
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
```
