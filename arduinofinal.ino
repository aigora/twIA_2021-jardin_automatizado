// Referencas a Bibliotecas
#include "DHT.h"
#define SensorPin A0
#define LUZ A1
DHT dht(2, DHT11);

// Enumeraciones que facilitan la lectura del código

// Variables globales
float h;
float t;
float umbmaxt, umbmint, umbmaxh, umbminh; 
float dospinchos;
float valorluz;
int pin=9; //PIN DE SALIDA DE LA BOMBA DE AGUA, SE PUEDE CAMBIAR

void setup()
{
  // Tareas de configuración 

  Serial.begin(9600);
  // PREPARAR LA LIBRERIA PARA COMUNICARSE CON EL SENSOR//
  dht.begin();

  pinMode(pin,OUTPUT);
}

void loop()
{
    
  if (Serial.available() > 0)  // Si hay mensajes procedentes del PC  
    procesar_mensaje();
    procesar_mensaje2();
    activarbomba();
    
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float umbmaxt=30, umbmint=0, umbmaxh=80, umbminh=20;
  float valorluz=0;
  valorluz = analogRead(LUZ);
  float dospinchos = 0;//Valor del sensor//
  for (int i = 0; i <= 100; i++) 
  { 
    dospinchos = dospinchos + analogRead(SensorPin);  
  } 
  dospinchos = dospinchos/100.0; 
  Serial.println(dospinchos);  
}
	
   // Resto de acciones 
void procesar_mensaje(void)
{
 String cadena = Serial.readStringUntil('\n'); // Lee mensaje
 if (cadena.equals("DATOS")) // Requisito 4
 {
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Humedad del suelo: ");
  Serial.println(dospinchos);
  Serial.print(" % ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");// Requisito 6
  Serial.print("Valor luz:");
  Serial.println(valorluz);
 }
}
void procesar_mensaje2(void)
{
  String cadena = Serial.readStringUntil('\n'); 
  if (cadena.equals("Umbrales"))// Lee mensaje hasta que encuentre barra
 {
 Serial.print("Temperatura maxima: ");
 Serial.print(umbmaxt);
 Serial.println(" *C");
 Serial.print("Humedad minima: ");
 Serial.print(umbminh);
 Serial.print(" % ");// Requisito 6
 }
 
 if (cadena.equals("Umbrales=1")) // Requisitos 7 y 8
 {
 String valor = Serial.readStringUntil('\n'); // Lee valor new aforo
 umbmaxt = valor.toInt();
 Serial.print("Temperatura maxima: ");
 Serial.print(umbmaxt);
 Serial.println(" *C"); // Responde al PC
 Serial.print("->NUEVO VALOR UMBRAL");
 }
 
  if (cadena.equals("Umbrales=2")) // Requisitos 7 y 8
 {
 String valor = Serial.readStringUntil('\n'); // Lee valor new aforo
 umbminh= valor.toInt();
 Serial.print("Humedad minima: ");
 Serial.print(umbminh);
 Serial.println(" % "); // Responde al PC
 Serial.print("->NUEVO VALOR UMBRAL");
 }
 if(umbminh<h){
  digitalWrite(pin, HIGH); //PONER EL PIN EN HIGH
  delay (10000);//ESPERAR 10 SEGUNDOS
  digitalWrite(pin,LOW);
  delay(10000);
 }
  if(umbmaxt<t){
  digitalWrite(pin, HIGH); //PONER EL PIN EN HIGH
  delay (10000);//ESPERAR 10 SEGUNDOS
  digitalWrite(pin,LOW);
  delay(10000);
 }
}
 void activarbomba(void)//FUNCION PARA ACTIVAR LA BOMBA DE AGUA 10 SEGUNDOS
 {
 String cadena = Serial.readStringUntil('\n');//Leer valor hasta recibir \n
 if (cadena.equals("BOMBA")) //SI LA CADENA RECIBIDA "DICE" BOMBA
  {digitalWrite(pin, HIGH); //PONER EL PIN EN HIGH
  delay (10000);//ESPERAR 10 SEGUNDOS
  digitalWrite(pin,LOW);
  delay(10000);  
    }
  }
