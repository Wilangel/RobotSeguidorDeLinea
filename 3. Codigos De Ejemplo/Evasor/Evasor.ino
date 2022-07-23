


#include <Servo.h> //libreria para manejar el sevo motor


#define motorMA1 3 //definimos los pines que van a controlar los motores, el motor "motorMA"e es de la izquieda, mientras que "motorMB" 
#define motorMA2 5 //e el de la derecha, teneiendo en cuenta que el fente es la parte en donde se encuentra el sensor ultrasonico
#define motorMB1 6 // son dos pines para controlar el giro del motor ya sea en sentido de las maneciallas del reloj ó al contrario
#define motorMB2 9
#define si 7 // sensor de linea izquierda, asociado a motorMA
#define sd 8 // sensor de linea derecho, asociado a motorMB

int  echo=12; //pines para utilizar el sensor ultrasonico 
int trig=13;

//variable para utilizarla en la funcion distancia
int dist=0; 
int lectura=0;
int tiempo=0;
int cm=0;
//Variables para los sensores de linea 

int sensorD=0;
int sensorI=0; 


//variables para calibrar la potencia de los motores, represental la velocidad necesaria
//para que el robot siga la linea y sortee las curvas

int velrecta=180; //pude ir de 0  a 255 con 255 como la maxima potencia
int velcurva=120;//puede ir de 0 a 255 con 255 coomo la maxima potencia dependiendo de la carga de la bateria
Servo servomotor; // creamos un objeto para controlar el servo

int distancia (void); //funcion para obtener la disatancia del sensor ultrasonico
void setup() {
// configuramos los pines 
servomotor.attach(11); //pin al cual esta conectada la señal de control del servo

pinMode(motorMA1,OUTPUT);
pinMode(motorMA2,OUTPUT);
pinMode(motorMB1,OUTPUT);
pinMode(motorMB2,OUTPUT);

pinMode(si,INPUT);
pinMode(sd,INPUT);

pinMode(echo,INPUT);
pinMode(trig,OUTPUT);
}

void loop() {
cm=distancia(); 
/*en este caso lo que hacemos es leer la distancia con el ultrasonido, luego si la distancia es menor a 10cm hacemos 
el robot pare, de reversa y lugo gire para que evada el obstaculo, si la reversa no es lo suficientemente larga, o el giro 
no es el que deseamos, podemos cambiar los tiempor la funcion "delay()", para cuadrarlos a nuestro gusto. si la distancia 
que esta midiendo es mayor a 10cm el robot ira hacia adelante. NOTA esta distancia de deteccion del obstaculo 
tambien la podemos cambia a nuestro gusto -*/
if(cm<10) 
{
  analogWrite(motorMA1,0);
  analogWrite(motorMA2,0);
  analogWrite(motorMB1,0);
  analogWrite(motorMB2,0);
  delay(1000);
  analogWrite(motorMA1,0);
  analogWrite(motorMA2,velrecta);
  analogWrite(motorMB1,0);
  analogWrite(motorMB2,velrecta);
  delay(1500);
  analogWrite(motorMA1,velrecta);
  analogWrite(motorMA2,0);
  analogWrite(motorMB1,0);
  analogWrite(motorMB2,velrecta);
  delay(500);
  
    }
else 
{ analogWrite(motorMA1,velrecta);
  analogWrite(motorMA2,0);
  analogWrite(motorMB1,velrecta);
  analogWrite(motorMB2,0);
    
  }

}
int distancia()
{////////SENSOR DERECHO///////////////// 
 digitalWrite(trig,LOW);
 delayMicroseconds(10);
 digitalWrite(trig,HIGH);
 delayMicroseconds(10); 
 digitalWrite(trig,LOW);
 lectura=digitalRead(echo);
 tiempo =pulseIn(echo,HIGH);
 dist=(tiempo*0.017);
 return dist;
  }

