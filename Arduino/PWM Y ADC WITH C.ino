//Creamos una variable de tipo entero
int lectura = 0;

//Definimos los pines del motor, led y TMP36
int motor = 6;
int led= 9;
int input = 0;

int duty;   // ciclo util de la PWM

//Creamos una variable de tipo flotante
float brightness = 0.0;

void setup() {
  //Iniciamos la comunicación serial
  Serial.begin(9600);
  pinMode(input, INPUT);
  //analogRead(input);
  pinMode(motor, OUTPUT);   
  //digitalWrite( motor, LOW );
  pinMode(led, OUTPUT);   
  //digitalWrite( led, LOW );
  
  
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

  delay(500);
}
