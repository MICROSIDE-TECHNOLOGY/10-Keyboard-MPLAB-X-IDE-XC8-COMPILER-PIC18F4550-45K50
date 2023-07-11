/*
 * File:   main.c
 * Author: Enrique
 *
 * Created on 27 de noviembre de 2020, 01:34 AM
 */

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)
// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)
// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)
// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)
// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)
// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)
// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)
// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 48000000
#include <xc.h>
#include <pic18f4550.h>

#define write_port LATB             /* latch register to write data on port */
#define read_port PORTB             /* PORT register to read data of port */
#define Direction_Port TRISB

void InitPorts(void);
unsigned char keyfind(void); /* function to find pressed key*/

char key;
unsigned char col_loc, rowloc, temp_col;
unsigned char keypad[4][4] ={'1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'};

void main(void) {
    InitPorts();
    RBPU = 0;
    while (1) {
        key = keyfind();
        if (key == '1')
            PORTAbits.RA4 = 1;
        if (key == '0')
            PORTAbits.RA4 = 0;
    }

    return;
}

void InitPorts(void) {
    LATA = 0;
    TRISAbits.RA4 = 0;
}

unsigned char keyfind(void) {
    Direction_Port = 0xf0;
    write_port = 0xf0;
    do {
        do {

            col_loc = read_port & 0xf0;

        } while (col_loc != 0xf0);
        col_loc = read_port & 0xf0;
    } while (col_loc != 0xf0);

    __delay_ms(50);
    write_port = 0xf0;
    do {
        do {

            col_loc = read_port & 0xf0;
        } while (col_loc == 0xf0);
        col_loc = read_port & 0xf0;
    } while (col_loc == 0xf0);

    __delay_ms(20);
    col_loc = read_port & 0xf0;

    while (1) {
        write_port = 0xfe;
        col_loc = read_port & 0xf0;
        temp_col = col_loc;
        if (col_loc != 0xf0) {
            rowloc = 0;
            while (temp_col != 0xf0) {
                temp_col = read_port & 0xf0;
            }
            break;
        }

        write_port = 0xfd;
        col_loc = read_port & 0xf0;
        temp_col = col_loc;
        if (col_loc != 0xf0) {
            rowloc = 1;
            while (temp_col != 0xf0) {
                temp_col = read_port & 0xf0;
            }
            break;
        }

        write_port = 0xfb;
        col_loc = read_port & 0xf0;
        temp_col = col_loc;
        if (col_loc != 0xf0) {
            rowloc = 2;
            while (temp_col != 0xf0) {
                temp_col = read_port & 0xf0;
            }
            break;
        }

        write_port = 0xf7;
        col_loc = read_port & 0xf0;
        temp_col = col_loc;
        if (col_loc != 0xf0) {
            rowloc = 3;
            while (temp_col != 0xf0) {
                temp_col = read_port & 0xf0;
            }
            break;
        }
    }

    while (1) {
        if (col_loc == 0xe0) {
            return keypad[rowloc][0];
        } else
            if (col_loc == 0xd0) {
            return keypad[rowloc][1];
        } else
            if (col_loc == 0xb0) {
            return keypad[rowloc][2];
        } else {
            return keypad[rowloc][3];
        }
    }
    __delay_ms(300);
}

