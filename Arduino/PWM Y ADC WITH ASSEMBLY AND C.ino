//Creamos una variable de tipo entero
int lectura = 0;

//Definimos los pines del motor, led y TMP36
int motor = 6;
int led= 9;
int input = 0;

int duty;   // ciclo util de la PWM

//Creamos una variable de tipo flotante
float brightness = 0.0;

asm(
  ".equ DDRD, 0x0A ;Le damos la direccion de los registros \n"
  ".equ PORTD, 0x0B ;Direccion del puerto D \n"
  ".equ DDRB, 0x04 ;Le damos la direccion de los registros \n"
  ".equ PORTB, 0x05 ;Direccion del puerto b \n"
  ".equ DDRC, 0x07 ;Le damos la direccion de los registros \n"
  ".equ PORTC, 0x08 ;Direccion del puerto b \n"
  ".equ PINC, 0x06 ;Direccion del puerto C del input \n"
);

void setup() {
  //Iniciamos la comunicación serial
  /*
  Serial.begin(9600);
  pinMode(input, INPUT);
  //analogRead(input,0);
  pinMode(motor, OUTPUT);   
  //digitalWrite( motor, LOW );
  pinMode(led, OUTPUT);   
  //digitalWrite( led, LOW );
  */
  
  asm(
    "ldi r21,0xFF ;Carga el registro 21 con 255 \n"
    "out DDRB,r21 ;Configura el puerto B como salida \n"
    "out DDRD,r21 ;Configura el puerto D como salida \n"
    "ldi r21,0x00 ;Carga el registro 21 con 0 \n"
    "in  r21,DDRC ;Configura el puerto C como entrada \n" 
    );
  
  
  
  
  
}

void loop() {
  //Tomamos la lectura analógica del pin al cual conectamos
  //la señal de nuestro sensor
  lectura = analogRead(input);

  //Obtenemos la temperatura con la siguiente formula:
  //temperatura = ( lectura * (500.0 / 1023.0) ) - 50.0;
  
  //Prender el pin concorde a la temperatura captada
  brightness= map(lectura,20,358,0,255);
  analogWrite(led,brightness);
  
  // Ajustar el motor de acuerdo el input
  duty  = map(lectura,20,358,255,0);
  analogWrite(motor,duty);
  
  //Imprimimos por monitor serie la temperatura en celcius 
  Serial.println(lectura);
  
  //Call delay
  asm(
    "call delay;	\n"
    );

  //delay(500);
}

asm(
  "			ldi r16,0x00; Carga 0 al registro 16	\n"
  "delay:	ldi	r17,0x00; Carga 0 al registro 17	\n"
  	"delay1:	inc	r17; Incrementa en uno el registro 17	\n"
  		"ldi	r18,0x00; Carga 0 al registro 18	\n"
  		"delay2:	inc	r18; Incrementa en uno el registro 18\n"
  			"cpi	r18,0xFF; Compara el registro 18 con 255\n"
  			"brne	delay2;	Si no se cumple branch al delay2\n"
  			"cpi	r17,0x30;Compara el registro 17 con 48	\n"
  			"brne	delay1;	Si no se cumple salto al delay1\n"
  			"inc	r16; Incrementa en uno el registro 16	\n"
  			"cpi	r16,0xFF; Compara el registro 16 con 255\n"
  			"brne	delay;	Si no se cumple salto al delay	\n"
  
  );
