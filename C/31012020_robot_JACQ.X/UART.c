#include <xc.h>
#include "UART.h"
#include "ChipConfig.h"

#define BAUDRATE 115200
#define BRGVAL ((FCY/BAUDRATE)/4)-1

void InitUART(void)
{
    U1MODEbits.STSEL = 0;
    U1MODEbits.PDSEL = 0
    U1MODEbits.ABAUD = 0;
    U1MODEbits.BRGH = 1;
    U1BRG = BRGVAL;
    
    U1STAbits.UTXISEL0 = 0;
    U1STAbits.UTXISEL1 = 0;
    IFS0bits.U1TXIF = 0;
    IEC0bits.U1TXIE = 0;
    
    U1STAbits.URXISEL = 0;
    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 0;
    
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
}