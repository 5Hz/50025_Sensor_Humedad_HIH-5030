/*
5hz-electronica presenta un ejemplo del funcionamiento del sensor de humedad HIH-5030
usando las formulas descritas en el datasheet del mismo
http://sensing.honeywell.com/index.php?ci_id=49693&la_id=1 
no olvide adquirer un sensor de temp para usar la compensación se recomienda el el sensor DS18B20
*/
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
#define ST 6
#include <OneWire.h>
#include <DallasTemperature.h>  //http://www.5hz-electronica.com/sensordetemperaturadigital-ds18b20.aspx  consiga el sensor de temp empleado para este ejemplo

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int opcion = 0;
int barras;

float RH;
float TrueRH;
float Vcc;
float temp;

int entrada;



#define ONE_WIRE_BUS 8 //pin 8 usado para la comunicación con el sensor de temperatura

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);



void setup(){

  Serial.begin(9600);

  sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
 
    
    
  Serial.print("Obteniendo temperatura para calcular RH real..");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("Listo");
  
  Serial.print("Temp ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.println("C ");
  Serial.println(" ");
    Serial.println(" ");
      Serial.println(" ");
     menu();
}

void loop(){
  if (opcion == 1)  // indica que se seleccionó una opción válida
    leer_sensor();
   if ((opcion == 2))
    menu();
  if (Serial.available()){
    entrada=Serial.read();
    if(entrada=='*'){
      menu();
    }
    
  }
}


void menu(){
  int entradaMenu;
  Serial.println("-------------------5HZ ELECTRONICA---------------------------");
  Serial.println("");
  Serial.println("                     PRESENTA");
  Serial.println("");
  Serial.println("*************************************************************");
  Serial.println("");
  Serial.println("      BIEVENIDO AL PROGRAMA DE PRUEBAS DEL HIH-5030");
  Serial.println("");
  Serial.println("            YA TIENES UNO A LA MANO????");
Serial.println("");
    Serial.println("*************************************************************");
  Serial.println("");
  Serial.println("MENU PRINCIPAL");
  Serial.println("1- TEST");
  Serial.println("2- FORMULAS EMPLEADAS");
 
  
 
  do{
  }while(Serial.available()==0);
      entradaMenu=Serial.read();
    switch(entradaMenu){
   
        case '1':
      Serial.println("");
      Serial.println("INICIO");
      Serial.println(".............");
      delay(1000);
      opcion = 1;
      break;
      
      
        case '2':
 
      Serial.println("");
      Serial.println("FORMULAS PARA LOS NERDILLOS");
      Serial.println("RH=((sensorValue/1024.0)-0.1515)/0.00636    @ 25 C independiente del valor de Vcc");
      Serial.println("TrueRH = (RH)/(1.0546-0.00216*temp)         compensacion de temperatura");
      Serial.println(".............");
      Serial.println(".............");
      Serial.println(".............");
      Serial.println(".............");
      delay(1000);
      opcion = 2;
      break;
      

      
    default:
      Serial.println("Solo hay dos opciones... 1..y 2... =) ");
      opcion = 0;
      break;
    }
    
    if ((opcion == 1))
    Serial.println("Hola soy la TERMINAL DE 5Hz (teclea * para ir al menu) cuando termines ");
    delay(1000);

}

  
  
void leer_sensor() {
  
  

  sensors.requestTemperatures(); // Send the command to get temperatures
  temp = sensors.getTempCByIndex(0); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  
  
  
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
//  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:

RH=((sensorValue/1024.0)-0.1515)/0.00636;
TrueRH = (RH)/(1.0546-0.00216*temp);

  
 // for (int i=0; i <= barras; i++)
 // Serial.print("-");
  Serial.print(" ");
  Serial.print("RH = " );                       
  Serial.print(RH);
  Serial.print("%     Temp = " );                       
  Serial.print(temp); 
  Serial.print("C     True RH = " );                       
  Serial.print(TrueRH);   
  Serial.print("%    output = ");      
  Serial.println(sensorValue);   
  delay(1500);
 
}







