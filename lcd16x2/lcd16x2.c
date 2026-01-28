/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*ASEPAM 
16-enero-25 ya hace 10 dias de los reyes.
valiendonos un poco el mentado copyright de arriba, usaremos este ejemplo como plantilla
base para integrar el resto del ejercicio
*/
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

/* Example code to drive a 16x2 LCD panel via a I2C bridge chip (e.g. PCF8574)

   NOTE: The panel must be capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefore I2C) cannot be used at 5v.

   You will need to use a level shifter on the I2C lines if you want to run the
   board at 5v.

   Connections on Raspberry Pi Pico board, other boards may vary.

   GPIO 4 (pin 6)-> SDA on LCD bridge board
   GPIO 5 (pin 7)-> SCL on LCD bridge board
   3.3v (pin 36) -> VCC on LCD bridge board
   GND (pin 38)  -> GND on LCD bridge board
*/
// commands
const int LCD_CLEARDISPLAY = 0x01;
const int LCD_RETURNHOME = 0x02;
const int LCD_ENTRYMODESET = 0x04;
const int LCD_DISPLAYCONTROL = 0x08;
const int LCD_CURSORSHIFT = 0x10;
const int LCD_FUNCTIONSET = 0x20;
const int LCD_SETCGRAMADDR = 0x40;
const int LCD_SETDDRAMADDR = 0x80;

// flags for display entry mode
const int LCD_ENTRYSHIFTINCREMENT = 0x01;
const int LCD_ENTRYLEFT = 0x02;

// flags for display and cursor control
const int LCD_BLINKON = 0x01;
const int LCD_CURSORON = 0x02;
const int LCD_DISPLAYON = 0x04;

// flags for display and cursor shift
const int LCD_MOVERIGHT = 0x04;
const int LCD_DISPLAYMOVE = 0x08;

// flags for function set
const int LCD_5x10DOTS = 0x04;
const int LCD_2LINE = 0x08;
const int LCD_8BITMODE = 0x10;

// flag for backlight control
const int LCD_BACKLIGHT = 0x08;

const int LCD_ENABLE_BIT = 0x04;

//*****************************************************************************
//enriquecemos el ejercicio
char Mensaje_1[] = "CursoTaller 1-25";

char A1 []= {0x04,0x0A,0x11,0x40,0x40,0x40,0x40,0x40,0x00};
char A2 []= {0x40,0x04,0x02,0x01,0x02,0x04,0x40,0x40,0x00};
char A3 []= {0x40,0x40,0x40,0x40,0x11,0x0A,0x04,0x40,0x00};
char A4 []= {0x40,0x04,0x08,0x10,0x08,0x04,0x40,0x40,0x00};


uint8_t i,tecla;  //acepta notacion c99 y hungara

#define LEDPIN 25
#define PUSHBUTTON 24


//*********************************************************


// By default these LCD display drivers are on bus address 0x27
static int addr = 0x27;

// Modes for lcd_send_byte
#define LCD_CHARACTER  1
#define LCD_COMMAND    0

#define MAX_LINES      2
#define MAX_CHARS      16

/* Quick helper function for single byte transfers */
void i2c_write_byte(uint8_t val) {
#ifdef i2c_default
    i2c_write_blocking(i2c_default, addr, &val, 1, false);
#endif
}

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
#define DELAY_US 600
    sleep_us(DELAY_US);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t val, int mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

// go to location on LCD
void lcd_set_cursor(int line, int position) {
    int val = (line == 0) ? 0x80 + position : 0xC0 + position;
    lcd_send_byte(val, LCD_COMMAND);
}

static inline void lcd_char(char val) {
    lcd_send_byte(val, LCD_CHARACTER);
}

void lcd_string(const char *s) {
    while (*s) {
        lcd_char(*s++);
    }
}
//plagiemos un poco y usemos los nombres ya conocidos
//para nuestras funciones de la interfaz paralela

void BUSY()
{sleep_ms(3);}

//funcion para escribir un caracter al registro de datos
void ESCDAT(char datodis)
{lcd_send_byte(datodis, LCD_CHARACTER);
BUSY();
}

//funcion para escribir un dato al registro de control
void ESCCON(char datodis)
{lcd_send_byte(datodis, LCD_COMMAND);
BUSY();
}



void lcd_init() {
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x02, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}

int main() {
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    lcd_init();

//usaremos algunas definiciones y funciones que hicieron los programadores de la rutina para honrarlos


//'borramos' todo el display
        ESCCON(LCD_CLEARDISPLAY);
//encendemos en el display cursor y parpadeo para no pensar que ya esta muerto el display
        
        ESCCON(LCD_DISPLAYCONTROL|LCD_DISPLAYON|LCD_CURSORON|LCD_BLINKON);
        
     //nos vamos a la linea 0 (primer renglon) tercer caracter
     lcd_set_cursor(0,3);  //esta es funcion de este codigo

        
        ESCDAT('A');
        
        //nos quedamos ahi un segundo
        sleep_ms(1000);
        
        //y mandamos el mensaje del curso al inicio del segundo renglon
        //linea 1 (segundo renglon) caracter 0
        lcd_set_cursor(1,0);  //esta es funcion de este codigo
        
        //y si, podemos usar apuntadores (ia ciente-c c-nora) y cosas bien elegantes pero el viejo y confiable while hace 
         //el trabajo muy bien escribiendo cadenas y de manera mas simple.
         
         i=0;
         
         while(Mensaje_1[i]!=0)
         {
             ESCDAT(Mensaje_1[i++]);
         }
        
        
        //nos pasamos a la primera linea 10o caracter
           lcd_set_cursor(0,10);  //esta es funcion de este codigo
           
           //escribimos la leyenda USR para denotar el pushbutton de usuario en las tarjetas clon
           ESCDAT('U');
           ESCDAT('s');
           ESCDAT('r');
           ESCDAT('='); //al terminar de escribir esto, el cursor estara en la posicion 14 del display, que es a donde
                        //lo regresaremos posteriormente   
       
           
           //configuramos el GPIO24, que es donde esta el push en la tarjeta clon y el
           //GPIO25, donde esta el LED.
           //si tienen la PICO original pues habra que ponerle su push en algun GPIOX, porque el 24 no esta disponible
           //quien sabe porque oscura razon 
           //esto (la inicializacion de los puertos de abajo) se deberia haber hecho desde el principio pero bueno
           
           
           gpio_init(LEDPIN);        //GPIO25 como salida
         gpio_set_dir(LEDPIN,GPIO_OUT);
         gpio_init(PUSHBUTTON);       //GPIO24 como entrada 
           gpio_set_dir(PUSHBUTTON, GPIO_IN);
           gpio_pull_up(PUSHBUTTON); //y le metemos una resistencita de pull-up paque no agarre ruido
           
           //apagamos led
           gpio_put(LEDPIN, 0);
 
           //leemos el push e informaremos de su estado por dos medios: el led y el display
           //si el GPIO24 recibe un '1', se encedera el led y el display mostrara un '1'
           //caso contrario el led estara apagado y el display mostrara '0'

           while(1)
           {
           tecla=gpio_get(PUSHBUTTON)&0x01; // como tecla es de 8 bit, la enmascaramos para solo leer el bit0
            gpio_put(LEDPIN,tecla);
            if(tecla==1)
              {ESCDAT('1');}
              else
              {ESCDAT('0');}
            //y regresamos el cursor a su posicion 14 para que siempre se vea estatico
            lcd_set_cursor(0,14);
           }        
           
           //como ya vieron, el display brinca por la actualizcion del valor usr
           //como ejercicio inmediato, reconfigurar el display para apagar el cursor y el parpadeo
        
       while(1);

//y contunuamos con la programacion fancy

    static char *message[] =
            {
                    "RP2040 by", "Raspberry Pi",
                    "A brand new", "microcontroller",
                    "Twin core M0", "Full C SDK",
                    "More power in", "your product",
                    "More beans", "than Heinz!"
            };

    while (1) {
        for (uint m = 0; m < sizeof(message) / sizeof(message[0]); m += MAX_LINES) {
            for (int line = 0; line < MAX_LINES; line++) {
                lcd_set_cursor(line, (MAX_CHARS / 2) - strlen(message[m + line]) / 2);
                lcd_string(message[m + line]);
            }
            sleep_ms(2000);
            lcd_clear();
        }
    }
#endif
}
