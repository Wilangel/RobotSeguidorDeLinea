
//CODIGO BASE PARA UTILIZAR EL ROBOT M1 COMO SEGUIDOR DE LINEA////
/*El siguiente es un algoritmo sensillo que busaca mantener la linea negra de trayectoria, en medio  
  de los dos senores de linea con los que cuenta el robot. El rente del robot lo idendificando 
  el sensor ultrasonico, el cual parencen dos ojos. si miramos el utrasonido de frente, este 
  correspondera al ferente del robot, lo cual nos permite identificar la izquirda y la derecha del robot.
  Luego de indentificar el fernte del robot, el agoritmo lo que intenta hacer es corregir el rumbo del 
  robot apara que siga la lina, así si el sensor iaquiero toca la linea hay que hacer que el robot corrija
  el rubo dirigiendose a la derecha hasta que el sensor derecho toque la linea negra y se haga lo contrario. 
  mientras la linea este en medio de los dos sensores el robot seguira hacia adelante.
 */




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

int velrecta=200; //pude ir de 0  a 255 con 255 como la maxima potencia
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
 //leemos los sensores de linea y guardamos enlas variables que creeamos para ello 
  
sensorI=digitalRead(si);
delay(10); 
sensorD=digitalRead(sd);
delay(10); 

/////ALGORITMO PARA QUE EL ROBOT SIGA LA LINEA NEGRA//
/*En este primer if lo que hacemos es chequear que lo linea negra este en medio de los dos sensores
si esto sucede ambos sensores estaran viendo el color balanco, por lo que ambos muestran el valor de 
cero si esto se cumple el robot debera de ira hacia adelante. NOTA si uno de los dos motores o los dos
no van hacia adelante, entonces cambimos los valores del segundo argumento dentro de los parentesis 
de la funcion analogWrite e decier el si el motor "motorMA1"no va hacia adelante cambiamos la funcion de la siguente manera 
analogWrite(motorMA1,0);
analogWrite(motorMA2,velrecta); 
y asi con los demas que nos presente el mimos problema, con esto lo que hacemos en cambiar el giro para poder 
coordinar el avance o giro del robot*/
if(sensorI==0 && sensorD==0 )
{analogWrite(motorMA1,velrecta);
 analogWrite(motorMA2,0); 
 analogWrite(motorMB1,velrecta);
 analogWrite(motorMB2,0); 
 
  }
/*En este condicional vemos que el sensor izquierdo detecta la linea negra, caso contrario pasa con el    
sensor derecho, lo que indica que necesitamos corregir el rumbo del robot, haciendo que pase hacia 
la hizquieda, por lo que apagamos el motor izquido y solo dejamos encendido el derecho , utilizando 
la velocidad de curva para que el cambio sea suficiente para corregir el rumbo. NOTA si el robot
no corrige el rumbo para la izquierda debemos cambiar los valores del argumento entre los parentesis, 
como se explico en la funcionanterior*/
if(sensorI==1 && sensorD==0 )
{analogWrite(motorMA1,0);
 analogWrite(motorMA2,0); 
 analogWrite(motorMB1,velrecta);
 analogWrite(motorMB2,0); 
 
  }
/*Esta es la situacion contraria a la anterior, por lo que devemos corregir el rumbo haciendo que el 
robot tiena a la derecha */
if(sensorI==0 && sensorD==1 )
{analogWrite(motorMA1,velcurva);
 analogWrite(motorMA2,0); 
 analogWrite(motorMB1,0);
 analogWrite(motorMB2,0); 
 
  }
/*Cuando ambos sensores muestran "1" quire decir que estan viendo el color negro, esto tambien 
sucedes cuando lo levantamos y los sensores queda lo suficientemente retirados de una superficie, 
por lo que lo apagamos */
if(sensorI==1 && sensorD==1 )
{analogWrite(motorMA1,0);
 analogWrite(motorMA2,0); 
 analogWrite(motorMB1,0);
 analogWrite(motorMB2,0); 
 
  }
///FIN DEL CODIGO//

///PARA UTILIZAR EL ULTRASONIDO///
/*Para utilizar el utrasonido simplemente llamoos la funcion de la siguiente manera 
 
 cm=distancia();
 Serial.println(cm) //conlo que en pantalla pantalla serial aparecera la distancia en centirmos que esta
                    //leyendo el sensor. 
*/
//PARA UTILIZAR EL SERVOMOTOR///
/* Para utilizar el servomotor, utilizamos la siguiente funcion 
servomotor.write(angulo); //el argumento dentro de los parentesis es el angulo al cual queremos que vaya
                          //el seervo
*/

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

