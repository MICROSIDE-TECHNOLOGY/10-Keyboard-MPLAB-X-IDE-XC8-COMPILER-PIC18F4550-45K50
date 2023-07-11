/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F45K50
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"

#define KAS 0b11100111 
#define K0  0b11010111 
#define KNU 0b10110111 
#define KD  0b01110111 

#define K7 0b11101011 
#define K8 0b11011011
#define K9 0b10111011
#define KC 0b01111011

#define K4 0b11101101
#define K5 0b11011101
#define K6 0b10111101
#define KB 0b01111101

#define K1 0b11101110
#define K2 0b11011110
#define K3 0b10111110
#define KA 0b01111110

char keypad_read(void);

void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    //LATB = 0x00;
    while (1) {
        char tecla = keypad_read();
        if (tecla == '1') {
            LED_SetHigh();
        }
        if (tecla == '0') {
            LED_SetLow();
        }
    }
}

char keypad_read() {
    unsigned char count = 0;
    unsigned char bitmask = 0x10;
    uint8_t key = (PORTB | 0xF0);
    uint8_t row;
    if (key != 0xFF) {
        row = 0xF7;
        for (uint8_t i = 0; i < 4; i++) {
            row = (row << 1);
            LATB = row;
            __delay_ms(1);
            uint8_t row_ = (PORTB | 0xF0);
            if (row_ != 0xFF)
                key = (row | 0x0F) & key;
        }
    }


    LATB = 0x0F;
    __delay_ms(2);

    switch (key) {
        case K0:
            return ('0');
            break;
        case K1:
            return ('1');
            break;
        case K2:
            return ('2');
            break;
        case K3:
            return ('3');
            break;
        case K4:
            return ('4');
            break;
        case K5:
            return ('5');
            break;
        case K6:
            return ('6');
            break;
        case K7:
            return ('7');
            break;
        case K8:
            return ('8');
            break;
        case K9:
            return ('9');
            break;
        case KA:
            return ('A');
            break;
        case KB:
            return ('B');
            break;
        case KC:
            return ('C');
            break;
        case KD:
            return ('D');
            break;
        case KAS:
            return ('*');
            break;
        case KNU:
            return ('#');
            break;
        default:
            return (' ');
            break;
    }
}