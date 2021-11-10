#include <SoftwareSerial.h>

#include <LiquidCrystal.h>
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
#include <EEPROM.h>




//Texto a mostrar
String texto ="";


int incomingByte = 0; // for incoming serial data

int cont = 1; //Contador de las variables




//Inicializar la libreria con los pines indicados
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// C++ code
//
void setup()
{
  Serial.begin(9600);
  
  
  // Configuramos las filas y las columnas del LCD en este caso 16 columnas y 2 filas
  lcd.begin(COLS, ROWS);
}

void loop()
{
  if (Serial.available() > 0) {
    //Limpiar LCD 
    lcd.clear();
    
    
    // read the incoming byte:
    incomingByte = Serial.read();

    
    //Asignar valor a la variable 
    texto = "Variable ";
    texto += cont;
    cont = cont + 1;
    texto += " :";
    texto += incomingByte;
    
    // Imprimir por Serial
    Serial.println(texto);
    
    
    //Imprimir en LCD
    lcd.print(texto);
    
    
    texto = "";
    if (cont == 5)
    {
      cont = 1;
    }
    delay(1000);
    
  }
}