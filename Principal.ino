#include <DHT.h>//Incluir la librería del sensor DHT11
#define SensorPin A0

//Configurar pines y variables
int SENSOR = 2;//Pin 2 para el valor del sensor DHT11
int temp, humedad;//Configura las variables de temperatura y humedad del DHT11
const int bomba = 13; //Pin 13 para la bomba
const int humedadsuelo = A0; //A0 para la humedad del suelo

DHT dht (SENSOR, DHT11);//Configura el modelo de DHT. Es el DHT11

void setup()
{
  Serial.begin(9600);//Arranca el puerto serie a 9600
  dht.begin();//Arranca el sensor DHT11
  
  //Configurar entradas y salidas
  pinMode(humedadsuelo, INPUT);//Configura humedadsuelo como entrada
  pinMode(bomba, OUTPUT);//Configura bomba como salida
 }

void loop()
{
  if (Serial.available() > 0)  // Si hay mensajes procedentes del PC
  datos();
  humedad_suelo();
  activar_bomba();

}

void datos(void)
{
 String cadena = Serial.readStringUntil('\n'); // Lee mensaje
 if (cadena.equals("DATOS")) 
 {
   //Leer y meter los valores de temperatura y humedad en las variables temp y humedad
  humedad = dht.readHumidity();
  temp = dht.readTemperature();
  
  //Imprimir por el puerto serie los valores de temperatura y humedad del DHT11
  Serial.print("Temperatura: "); Serial.print(temp); Serial.println("ºC");
  Serial.print("Humedad: "); Serial.print(humedad); Serial.println("%");
  delay(1000);
 }
}

void humedad_suelo(void)
{
 String cadena = Serial.readStringUntil('\n'); // Lee mensaje
 if (cadena.equals("HUMEDAD")) 
 {
   int SensorValue = analogRead(humedadsuelo);//Lee el valor de la humedad y lo meto en SensorValue
  
  //Imprimir por el puerto serie el valor de la humedad del suelo
  Serial.print("Humedad del suelo: ");Serial.print(SensorValue); Serial.println("%");
  delay(1000);
 }
}

void activar_bomba(void)
{
 String cadena = Serial.readStringUntil('\n'); // Lee mensaje
 if (cadena.equals("BOMBA")) 
 {
  int SensorValue = analogRead(humedadsuelo);//Lee el valor de la humedad y lo meto en SensorValue
  
  if(SensorValue >= 700) // el valor que se considera seco y hay que regar es de 700
  {
   // Si la tierra está seca, comenzara a regar
   // Riega durante 2 segundos y espera a comprobar la humedad otro segundo
   Serial.println("La tierra está seca, comienza el riego");
   digitalWrite(bomba, HIGH);
   delay(2000);
   digitalWrite(bomba, LOW);
   delay(1000);
  }
   }  
  
  //Si la tierra no está seca, no riega 
  delay(1000);
 }
