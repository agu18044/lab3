/*
 * File:   main.c
 * Author: Usuario Dell
 *
 * Created on 27 de enero de 2021, 05:23 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "LCD.h"
#include "ADC.h"
#include "USART.h"

//******************************************************************************
//  Palabra de cofiguración
//******************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//******************************************************************************
//  Variables
//******************************************************************************
#define _XTAL_FREQ 4000000 
uint8_t ADC0, ADC1;
uint8_t contador = 0;
char readUSART = 0;
float V1 = 0, V2 = 0;
char BUFFER[20];

//******************************************************************************
// Interupciones 
//******************************************************************************
void __interrupt() ISR(){
    if (RCIF == 1){
    RCIF = 0;
    readUSART = Read_USART();
    if (readUSART == '+'){
        contador++;
    }
    else if (readUSART == '-'){
        contador--;
    }    
  }
}

//******************************************************************************
//  Prototipos de funciones
//******************************************************************************
void setup(void);
float conversion(uint8_t x);
//uint8_t conversion(uint8_t x);


//******************************************************************************
//  Ciclo principal
//******************************************************************************
void main(void) {       
    setup();
    USART_Init (9600);
    LCD_init();
    clear_LCD();
    while(1){
        ADC0 = ADCmed(0);
        ADC1 = ADCmed(1);
        V1 = conversion(ADC0);
        V2 = conversion(ADC1);
        
        Write_USART_String("V1   V2   contador \n");
        //sprintf(data, "%.1f   %.1f   %d", V1,V2,contador);
        sprintf(BUFFER, "%f %f  %d" , V1,V2,contador);
        Write_USART_String(BUFFER);
        Write_USART(13);
        Write_USART(10);
        clear_LCD();
        set_cursor(1,1);
        write_string("V1   V2   CONT");
        set_cursor(2,0);
        write_string(BUFFER);
        __delay_ms(500);
    }
}

float conversion(uint8_t x){
    /*float y;
    y =x*0.0196*/ 
    return x*0.0196;
}



//******************************************************************************
//  Cofiguración
//******************************************************************************
void setup(void) {
    ANSEL = 0;
    ANSELH = 0;
    PORTD = 0;
    PORTE = 0;
    
    TRISD = 0;
    TRISE = 0;

    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
    PIR1bits.RCIF = 0;
    INTCONbits.GIE = 1;
    
    // configuración ADC
    //ADCON0bits.ADCS = 1;    // Conversion a FOSC/8
    //ADCON1 = 0;             // todos los bits de ADCON en 0
    }