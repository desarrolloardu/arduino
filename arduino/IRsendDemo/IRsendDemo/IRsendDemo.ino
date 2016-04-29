/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
   Conectar el infrarojo y la resistencia de 390 al pin 3!!.
 */

#include "IRremote2.h"
#include <SoftwareSerial.h>

#define RxD 11
#define TxD 10

IRsend irsend;

SoftwareSerial BTSerial(TxD, RxD);
String mensaje = "";
char numero[6];
int arraynumero[200];
int i = 0;
int j = 0;
char command;

int inumero = 0;

//Tele Puro:
int canalsubir[67] = {9000,4450,600,550,600,500,650,500,600,1650,600,1650,600,1650,600,550,600,500,650,1650,600,1650,600,1650,600,550,600,500,600,550,600,1650,600,1650,600,550,600,1650,600,550,550,1700,550,550,600,550,600,550,550,550,600,1650,600,550,550,1700,600,550,550,1700,550,1700,550,1700,600,1650,600};

                              //9000,4500,550,550,600,550,600,500,650,1600,650,1650,600,1650,600,500,600,550,600,1650,600,1700,550,1700,550,550,600,550,600,500,600,1700,550,1700,550,550,600,1650,600,550,600,1650,600,550,550,550,600,550,600,500,600,1700,550,550,600,1650,600,550,600,1650,600,1650,600,1650,600,1650,600,

/*
unsigned int lista[68] = {4400,4550,450,1800,400,1800,450,1800,400,700,450,700,400,700,450,650,450,650,500,1750,450,1750,500,1750,450,650,450,650,450,700,400,700,400,700,450,650,450,1800,400,700,450,650,450,1800,400,700,450,700,400,700,400,1800,450,700,400,1800,400,1850,400,700,400,1800,450,1800,400,1800,450};
// Power ON/OFF
unsigned int S_pwr[68]={4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};

// channel 1 
unsigned int S_1[68]={4650,4300,700,1550,700,1550,650,1550,700,400,700,400,700,400,700,450,700,400,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,400,700,450,650,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,1550,650,1550,700,1500,700,1550,650};

// channel 2
unsigned int S_2[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1500,700,1550,700,400,700,450,650,450,700,400,700,400,700,1500,700,400,700,1550,700,400,700,400,700,450,650,450,700,400,700,400,700,1550,650,450,700,1500,700,1550,650,1550,700,1500,700,1550,650};
// channel up
unsigned int S_pup[68]={4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650};
 
// channel down
unsigned int S_pdown[68]={4650,4300,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,1550,700,400,700,450,650,400,700,1550,700,1500,700,1550,700,1500,700,400,700,1550,650,1550,700,1500,700};


unsigned int on1[74]={8850,4400,650,550,600,600,600,550,650,550,600,600,600,550,650,550,650,550,600,1650,650,550,600,600,600,1650,600,600,600,550,600,600,600,600,600,550,600,600,600,600,600,550,600,600,600,1650,600,1650,650,550,600,600,600,550,650,550,600,600,600,1650,600,600,600,1650,600,600,600,550,600,1700,600,550,600};

unsigned int on2[74]={8850,4400,650,550,600,600,600,550,650,1650,600,550,650,550,650,550,600,550,650,1650,600,600,600,550,650,1650,600,550,600,600,600,600,600,550,600,600,600,600,600,550,600,600,600,600,600,1650,600,1650,600,600,600,550,650,550,600,600,600,550,650,1650,600,550,650,1650,600,550,600,600,600,1650,600,600,600};
unsigned int off1[74]={8850,4400,650,550,600,600,600,550,650,550,650,550,600,550,650,550,650,550,600,1650,650,550,600,600,600,1650,600,600,600,550,600,600,600,600,600,550,600,600,600,600,600,550,650,550,600,1650,600,1700,600,550,600,600,600,600,600,550,600,600,600,1650,600,600,600,1650,600,600,600,550,600,1700,600,550,600};
unsigned int off2[74]={8850,4400,650,550,600,600,600,550,650,1650,600,550,650,550,600,600,600,550,650,1650,600,600,600,550,650,1650,600,550,600,600,600,600,600,550,600,600,600,600,600,550,600,600,600,600,600,1650,600,1650,600,600,600,550,650,550,600,600,600,550,650,1650,600,550,600,1700,600,550,600,600,600,1650,600,600,600};


//TELE
//PRENDER:
unsigned int on3[68]={8950,4450,550,500,600,500,550,550,550,1700,550,1650,550,1700,550,550,550,500,550,1700,550,1700,550,1650,550,550,550,550,550,550,550,1650,550,1700,550,550,550,550,500,1700,550,1700,550,1650,550,600,500,550,550,550,550,1650,550,1700,550,550,550,550,500,550,550,1700,550,1700,550,1650,550};
unsigned int canalarriba[68]={9000,4350,600,500,550,550,550,550,550,1650,600,1650,550,1700,550,500,550,550,550,1700,550,1650,550,1700,550,550,550,550,550,550,500,1700,550,1700,550,550,500,550,550,1700,550,1700,550,500,550,550,550,550,550,550,550,1650,550,1700,550,550,550,550,550,1650,550,1700,550,1650,550,1700,550};

unsigned int temp[]={8800,4400,650,600,600,1650,600,550,650,1650,600,1650,600,600,600,550,650,550,650,1600,650,1650,600,600,600,1650,600,550,650,550,600,600,600,550,650,550,600,600,600,600,600,550,600,600,600,1650,600,1650,600,600,600,600,600,550,600,600,600,600,600,1650,600,600,600,1650,600,550,650,550,600,1650,650,550,600};

unsigned int temp2[99]={3300,1650,350,450,400,450,350,450,400,450,350,450,400,450,400,1250,400,400,450,400,400,400,500,350,450,350,500,350,450,350,450,400,450,350,450,400,450,350,450,1250,450,350,450,1200,450,400,450,350,450,400,450,350,450,400,450,350,450,400,450,350,450,400,450,350,450,1250,400,1250,450,1200,450,350,450,400,400,400,450,400,400,1250,450,400,400,400,450,400,400,400,450,400,400,450,400,400,400,1250,450,400,400};


//AIRE PHILCO DAN
unsigned int on4[276]={3300,1700,400,400,400,500,300,500,500,300,400,400,400,500,400,1200,400,500,500,300,500,300,500,400,500,300,500,300,500,400,400,400,500,300,500,400,400,400,500,1200,400,400,500,1200,400,400,500,400,400,400,400,400,400,500,400,400,400,400,400,500,400,400,400,400,400,1300,400,1300,400,1300,400,400,400,400,400,500,400,400,400,1300,400,400,400,400,400,500,400,400,400,400,400,500,400,400,400,400,400,1300,400,500,300,1300,400,1300,400,400,400,500,400,1200,400,500,400,400,400,400,400,500,400,400,400,400,400,500,400,400,400,1300,400,400,400,1300,400,1300,400,400,400,400,400,500,400,1200,400,500,400,400,400,400,400,500,400,400,400,400,400,500,400,400,400,400,400,500,400,400,400,400,400,500,400,1200,400,500,400,1300,300,1300,400,500,400,400,400,400,400,500,300,500,400,400,400,500,300,500,400,400,400,500,300,500,400,400,400,500,300,500,400,400,400,500,300,500,400,400,400,500,300,500,400,400,400,500,300,500,400,400,400,500,300,500,400,400,400,400,400,500,400,400,400,400,400,500,400,400,400,400,400,500,400,400,400,400,400,500,400,400,400,400,400,500,400,1300,300,1300,400,1300,400,400,400,1300,400,1300,400,400,400,500,300};
*/

 
void setup()
{
 
 // Serial.begin(115200);
  
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(4, HIGH);

  // Configuracion del puerto serie por software
  // para comunicar con el modulo HC-05
  BTSerial.begin(9600);
  BTSerial.flush();
  delay(500);

  // Serial.println("HOLA");
}

void loop()
{
  // Esperamos ha recibir datos.
  //String mensaje = "";
  

  if (BTSerial.available())
  {
    
   // Serial.println("leyendo");
    // La funcion read() devuelve un caracter 
    command = BTSerial.read();
    BTSerial.flush();
    // Serial.println(command);
    if(command == ';')
    {
     // Serial.println(mensaje);
      numero[i] = '\0';
      inumero = atoi(numero);
      i = 0;
      //Serial.println(inumero);
      arraynumero[j] = inumero;
      
      arraynumero[j+1] = '\0';
      j = 0;
     
      Enviar(arraynumero);
    //  mensaje = "";
    }
    else
    {
      if(command == ',')
      {  
        numero[i] = '\0';
        inumero = atoi(numero);
        i = 0;
        arraynumero[j] = inumero;
        j++;
     //   Serial.println(inumero);
        
      }
      else
      {
        numero[i] = command;
        i++;
       // mensaje = mensaje + String(command);
      }
    }
//Serial.println("Enviar");
   // Enviar("GGG");
  }

}


void Enviar(int* value)
{
  //irsend.sendRaw((unsigned int)value, sizeof((unsigned int)value)/2, 38);   //dividido 2 porque el sizeof cuenta la cantidad de bytes que ocupa el array y canalsubir(la variable) es unsigned int.
 //Serial.println("Enviar::::::");
  int a = 0;
  //Serial.println(sizeof(*value));
  while(value[a] != '\0')
  {
    //Serial.println(value[a]);
    a++;
  }
   //Serial.println("tam:");
   //Serial.println(a);

   irsend.sendRaw2(value, a, 38);   //dividido 2 porque el sizeof cuenta la cantidad de bytes que ocupa el array y canalsubir(la variable) es unsigned int.

//for(int i = 0; i < 200; i++)
 

 
 //irsend.sendRaw2(canalsubir, sizeof(canalsubir)/2, 38);   //dividido 2 porque el sizeof cuenta la cantidad de bytes que ocupa el array y canalsubir(la variable) es unsigned int.
  

}
/*
void loop() {
 Serial.println("enviandoBBB");
 Serial.println(sizeof(canalsubir));
 
  irsend.sendRaw(canalsubir, sizeof(canalsubir)/2, 38);   //dividido 2 porque el sizeof cuenta la cantidad de bytes que ocupa el array y canalsubir(la variable) es unsigned int.
  
    
  delay(1000);
}
*/