#include "pico/stdlib.h" 
#include <stdio.h>
#define RGBPIN (1)

uint8_t a;
uint8_t valorR;
uint8_t colorG = 0; //G
uint8_t colorR = 0; //R
uint8_t colorB = 0; //B
uint8_t  VarA;

void PORT_Init(void);

void fun_cero(void);
void fun_uno(void);
void res(void);
void out_color(uint8_t x);

//Función del color Rojo
void red(){
      out_color(0);
      out_color(30);
      out_color(0);
}

//Función del color Verde
void green(){
      out_color(30);
      out_color(0);
      out_color(0);
}

void pink(){
	out_color(0); //G
	out_color(30); //R
	out_color(30); //B
}

void off(){
      out_color(0);
      out_color(0);
      out_color(0);
}

void PORT_Init(void){
    gpio_init(RGBPIN); 
    gpio_set_dir(RGBPIN, GPIO_OUT); 
}

void fun_cero(void)
{
	gpio_put(RGBPIN, 1); //Se manda a estado alto la señal
  	 __asm__ volatile(
  		"push {r0}\n"
   		"mov r0, #0x7 \n"
    		"1: \n"
    		"sub r0, #1 \n"
    		"bne 1b \n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"pop {r0}\n"
	); //Lineas en ensamblador para mantener la señal en estado alto 380 ns
  	gpio_put(RGBPIN, 0); //Se manda a estado bajo  la señal
  	 __asm__ volatile(
  		"push {r0}\n"
   		"mov r0, #0x10 \n"
    		"2: \n"
    		"sub r0, #1 \n"
    		"bne 2b \n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"pop {r0}\n"
	);//Lineas en ensamblador para mantener la señal en estado bajo 880 ns
    }
    
void fun_uno(void)//
{
   gpio_put(RGBPIN, 1); //Se manda a estado alto la señal
  	 __asm__ volatile(
  		"push {r0}\n"
   		"mov r0, #0x10 \n"
    		"3: \n"
    		"sub r0, #1 \n"
    		"bne 3b \n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"pop {r0}\n"
	);//Lineas en ensamblador para mantener la señal en estado alto 780 ns
  	gpio_put(RGBPIN, 0); //Se manda a estado bajo  la señal
  	 __asm__ volatile(
  		"push {r0}\n"
   		"mov r0, #0x6 \n"
    		"4: \n"
    		"sub r0, #1 \n"
    		"bne 4b \n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"nop\n"
    		"pop {r0}\n"
	);//Lineas en ensamblador para mantener la señal en estado bajo 500 ns
}

void res(void)
{
    gpio_put(RGBPIN, 0);
    sleep_us(96);
}

void out_color(uint8_t x){

    int cont=8;
    valorR=x;

   while (cont!=0){
        a=valorR;
        a&=0B10000000;
        if(a==0){
            fun_cero();
        }
        else if (a==0x80)
        {
            fun_uno();
        }
        valorR=valorR<<1 ;
        a=valorR;
        cont--;
}
}

int main(){
	PORT_Init();
	while(1)
	{
	pink();
	res();
}
}








