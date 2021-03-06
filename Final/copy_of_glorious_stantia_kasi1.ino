#include <EEPROM.h>

// C++ code
//


//Creamos variables para almacenar las entradas analogas
int valor0 = 0;
int valor1 = 0;
int valor3 = 0;


//Declarar los pines a utilizar
int pin1 = 13;
int pin2 =12;
int pin3 = 11;
int led = 10;


const int pinNum [4] = {2,4,7,8};	//	crea una matriz de números pi
const int numOfPins = 4;							//	eclara el número de pines para parpadear
const int minRate = 50;								//	establecer la velocidad mínima de parpadeo
const int maxRate = 1000;							//	establecer la velocidad máxima de parpadeo


//Definir varible para la intensidad del led y velocidad del motor
int intensidad1 = 0;
int intensidad2 = 0;
int velocidad = 0;


//Definimos las variables para los outputs
int motor = 3;
int ledT1 = 5;
int ledT2 = 6;


int var = 0; //Variable a modificar con pulsadores

void setup()
{
  //Inicializar el serial y configurar los pines de entrada
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  
  //Configurar los pines de Salida
  pinMode(motor,OUTPUT);
  pinMode(ledT1,OUTPUT);
  pinMode(ledT2,OUTPUT);
  
  
  for (int i = 0; i < numOfPins; i++){				//	para loop para configurar pines para la salida
  	pinMode(pinNum[i], OUTPUT);
  }; 
  
  
  //Definir la funcionalidad de los pines utilizados para controlar la variable
  pinMode(led, OUTPUT);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
}

void loop()
{
  //Almacenar los valores leidos 
  valor0 = analogRead(A0);
  valor1 = analogRead(A1);
  valor3 = analogRead(A3);
  

  //Calcular y ejecutar la velocidad del motor
  velocidad = map(valor3, 0, 1023, 255,0);
  analogWrite(motor, velocidad);
  
  
  //Calcular la intensidad luminica de dos leds, con el TMP
  intensidad1 = map(valor0, 20, 358, 0, 255);
  analogWrite(ledT1, intensidad1);
  
  intensidad2 = map(valor1, 20, 358, 0, 255);
  analogWrite(ledT2, intensidad2);
  
  
  //Rutina para calcular la velocidad de blinkeo
  for (int i = 0; i < numOfPins-1; i++){			//	para el bucle que sube los LED
    int pot = analogRead(A2);						//	lee el valor del bote en el pin analógico 0
      pot = map(pot, 0, 1023, maxRate, minRate);	//	asigna la lectura del bote de 0-1024 a maxRate-minRate 
        digitalWrite(pinNum[i], HIGH);				//	establece el pin [i] alto
          delay(pot);								//	establece el pin [i] ALTA duración al valor del bote
        digitalWrite(pinNum[i], LOW);				//	establece el pin bajo
  };
  for(int i = numOfPins-1; i > 0; i--) {			//	para el bucle que baja los LED
    int pot = analogRead(A2);						//	lee el valor del bote en el pin analógico 0
      pot = map(pot, 0, 1023, maxRate, minRate);	//	asigna la lectura del bote de 0-1024 a maxRate-minRate
        digitalWrite(pinNum[i], HIGH);				//	establece el pin [i] alto
          delay(pot);								//	establece el pin [i] ALTA duración al valor del bote
        digitalWrite(pinNum[i], LOW);				//	establece el pin bajo
  };
  
  
  if( digitalRead(pin1)==1)
    {
      if (var > 0)
      {
        var = var -1;
      }
    }
    if(digitalRead(pin3)==0 )
    {
      if ( var < 254)
      {
        var = var +1;
      }
    }
    if (digitalRead(pin2) == 0)
    {
    	Serial.println(var);
  		analogWrite(led,var);
      EEPROM[4] = var;
  		delay(500);
      
      var = 0;
      
    }  
  
  
  
  
  
  // Guardar la informacion en la memoria EEPROM
  EEPROM[0] = intensidad1;
  EEPROM[1] = intensidad2;
  EEPROM[2] = map(analogRead(A2), 0,1023, 0, 255);
  EEPROM[3] = map(valor3, 0, 1023, 0,255);
  
  
  //Mandar la informacion por el Serial
  Serial.write(EEPROM[0]);
  Serial.write(EEPROM[1]);
  Serial.write(EEPROM[2]);
  Serial.write(EEPROM[3]);
  
  
  
  
  
  
  
  delay(1000);
  
  
}