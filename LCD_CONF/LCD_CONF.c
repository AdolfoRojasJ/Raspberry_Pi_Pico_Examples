#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

uint8_t Temp2;
//#define Vent 1

#define RS 12
#define RW 11
#define E 10
#define D0 9
#define D1 8
#define D2 7
#define D3 6
#define D4 5
#define D5 4
#define D6 3
#define D7 2

#define Limpiar 0x01
#define DDRAM 0x80
#define GRAM 0x40
#define Encendido 0x0f
#define Configuracion 0x38                         

char Mensaje_1[] = "CursoTaller 1-25";

char A1 []= {0x04,0x0A,0x11,0x40,0x40,0x40,0x40,0x40,0x00};
char A2 []= {0x40,0x04,0x02,0x01,0x02,0x04,0x40,0x40,0x00};
char A3 []= {0x40,0x40,0x40,0x40,0x11,0x0A,0x04,0x40,0x00};
char A4 []= {0x40,0x04,0x08,0x10,0x08,0x04,0x40,0x40,0x00};

int Valcon = 0;



void _E()  //GENERA UN PULSO DE 1 uS EN LA TERMINAL E DEL DISPLAY
{
    gpio_put(E, 1);
    sleep_us(1);
    gpio_put(E, 0);
}

void LEECON(){
    for (int i = 0; i < 8; i++) {
        gpio_set_dir(D7 + i, GPIO_IN);
    }
    gpio_put(RS, 0); // RS = 0 para comando
    gpio_put(RW, 1); // RW = 1 para leer
    gpio_put(E, 1);  // Activa Enable
    sleep_us(1);     //retardo para retardo de propagacion
    // Lee los 8 bits del bus de datos
    int temp = 0;
    temp = gpio_get(D7);
    gpio_put(E, 0); // Desactiva Enable
    gpio_put(RW, 0); // RW = 0 para escritura
    sleep_ms(2);
    // Configura los pines de datos como salida de nuevo
    for (int i = 0; i < 8; i++) {
        gpio_set_dir(D7 + i, GPIO_OUT);
    }
    sleep_ms(5);
    Valcon = temp; // Guarda el valor leído en Valcon
}
/*
void BUSY()  //PREGUNTA POR EL ESTADO DE LA BANDERA BUSY Y ESPERA HASTA QUE SEA CERO
{ 
    do{
        LEECON();
    }           // VALCON        1XXX XXXX
    while(Valcon!= 0);   //BIT7 0X80  1000 0000B
    }
*/
void BUSY()  //ESPERA 3 mS
{ 
    sleep_ms(3);
        }

void ESCCON (int x)// ENVIAR COMANDO AL REGISTRO DE CONTROL DEL LCD
{

    gpio_put(RS, 0);
    gpio_put(D0, (x >> 0) & 1);
    gpio_put(D1, (x >> 1) & 1);
    gpio_put(D2, (x >> 2) & 1);
    gpio_put(D3, (x >> 3) & 1);
    gpio_put(D4, (x >> 4) & 1);
    gpio_put(D5, (x >> 5) & 1);
    gpio_put(D6, (x >> 6) & 1);
    gpio_put(D7, (x >> 7) & 1);
    _E();                           //Pulso E
    BUSY(); //VERIFICA LA BANDERA DE BUSY
    }


void INIPORTS() {
    for (int gpio = 1; gpio <= 20; gpio ++){
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);
    }
  
}

void INILCD() 
{
    sleep_ms(20);               //20ms
    ESCCON(Configuracion);   //8 BITS , 2 LINEAS, 5X7
    ESCCON(Encendido);  // ENCENDER DISPLAY CON CURSOR Y DESTELLO
    ESCCON(Limpiar); // BORRAR DISPLAY
    }

void ESCDAT (int x)  //ESCRIBIR UN DATO ALFANUMERICO AL DISPLAY
{
    gpio_put(RS, 1);
    gpio_put(D0, (x >> 0) & 1);
    gpio_put(D1, (x >> 1) & 1);
    gpio_put(D2, (x >> 2) & 1);
    gpio_put(D3, (x >> 3) & 1);
    gpio_put(D4, (x >> 4) & 1);
    gpio_put(D5, (x >> 5) & 1);
    gpio_put(D6, (x >> 6) & 1);
    gpio_put(D7, (x >> 7) & 1);
    _E();//TOGGLE _E()
    BUSY(); //PREGUNTA POR LA BANDERA DE BUSY
    }

void ESCBYTE(uint8_t DByte) //escribe un byte a pantalla  
                            //
{ Temp2=DByte;
    Temp2=Temp2>>4;
    if (Temp2<=0x09)
        Temp2+=0x30;
        else
        Temp2+=0x37;
            ESCDAT(Temp2);
        Temp2=DByte&0x0f;
        if (Temp2<=0x09)
        Temp2+=0x30;
        else
        Temp2+=0x37;
            ESCDAT(Temp2);

}

void ESCPAL(char m[]){
    const char* p;
    for(p = m; *p != '\0'; p++){
        int x = *p;
        ESCDAT(x);
    }
}

void INIANIM(){
    ESCCON(0x40);
    ESCPAL(A1);
    ESCPAL(A2);
    ESCPAL(A3);
    ESCPAL(A4);
}

void CLS(){
     ESCCON(0x01);
    }



int main() {
    INIPORTS();
    INILCD(); //inicializa el display 16 x 2
    INIANIM();
    ESCCON(0x80);
    ESCDAT(0X41);
    ESCDAT(0X42);
    ESCDAT('C');
    ESCDAT(0x00);
    ESCDAT(0x01);
    ESCDAT(0x02);
    ESCDAT(0x03);
    ESCBYTE(0X23);
    sleep_ms(5000);
    ESCCON(0xc0);
    //while(1);
    
    ESCPAL(Mensaje_1);
    sleep_ms(5000);
      CLS();
      while(1);
   
}


