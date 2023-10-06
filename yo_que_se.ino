char opcion;
String msg;



#define DV A5
#define sensorVoltajepin A1      

unsigned int raw_sensor = 0;
int texto();
int medicionR();
int Divisor;
int Vol();


bool MT = true;

float sensibilidad=0.185;
float Vt=0;
float voltaje_sensado = 0;
float vcc=5;
float R1=0;
float R2=10000;

void setup() {
  Serial.begin(9600);
  pinMode(sensorVoltajepin, INPUT);    

}

void loop()
{
      
if (Serial.available())
{
opcion = Serial.read(); 

 
}


switch(opcion)
{

case 'A':
 if(MT){
  Serial.println("menu de opciones");
  Serial.println("Para medir resistencia pon R");
  Serial.println("para medir otra cosa solo pon r");
  Serial.println("para medir voltaje pon V");
  Serial.println("para medir otra cosa solo pon v");
  Serial.println("para medir corriente por C");  
  Serial.println("para medir otra cosa solo pon c");
  texto();

 MT=false;
break;

case 'V':
Vol();
break; 

case 'R':
medicionR();
break;
  
case 'C':
float Idc=calculoCorriente(500);
Serial.print("corriente: ");
Serial.println(Idc, 3);
delay(100);
break;
    
}
}
}

int medicionR()
{
Divisor=analogRead(DV);
if(Divisor)
{
   Vt=analogRead(DV);
   Vt=Vt*5/1023;
   R1=(R2*5/Vt)-(R2);
   Serial.println(R1);
   delay(2000);
  {
  }

   
    
  } else {
    Serial.println("no hay resistencia");
    delay(500);
    return 0;
    }
}

int texto()
{
Serial.println("que desea medir?");
}

int Vol()
{
  raw_sensor = analogRead(sensorVoltajepin);      //Leo el valor medido por el pin analogico
  voltaje_sensado = fmap(raw_sensor,0,1023,0.0,25.0);   //Linealizo el valor leido y lo convierto 
  Serial.print("El voltaje medido es de: ");
  Serial.println(voltaje_sensado);
  delay(1000);
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x-in_min)*(out_max - out_min)/(in_max - in_min) + out_min;
}

float calculoCorriente(int numeroMuestras)
{
  float leerAcs712 = 0;
  float intensidad = 0;
  for(int i=0; i<numeroMuestras; i++)
  {
    leerAcs712 = analogRead(A0)*(5.02/1023.0);
    intensidad=intensidad+(leerAcs712 * 2.3)/sensibilidad;
  }
  intensidad=intensidad/numeroMuestras;
  return(intensidad);
}

