#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "Robot.h"
#include "ADC.h"
#include "main.h"
#include "Toolbox.h"
#include "etats.h"
#include "UART.h"
#include "CB_TX1.h"
#include "CB_RX1.h"
#include "UART_protocole.h"
#include <libpic30.h>
int main(void) {

    InitOscillator();
    InitIO();
    InitTimer23();
    InitTimer1();
    InitTimer4();
    InitADC1();
    InitPWM();
    InitUART();
    //SendMessageDirect ((unsigned char *) " Bonjour",7 ) ;
  

    unsigned int *result = ADCGetResult();
    int ADCValue0 = 0, ADCValue1 = 0, ADCValue2 = 0, ADCValue3 = 0, ADCValue4 = 0, ADCValue5 = 0;
    float volts = 0;
    
    /****************************************************************************************************/
    // Boucle Principale
    /****************************************************************************************************/
    while (1) {
        //LED_BLANCHE = !LED_BLANCHE;
        
        //if(compteurInverseur%2)
            //LED_ORANGE = 1;
        //else
            //LED_ORANGE = 0;
            
        if(ADCIsConversionFinished())
            {
                ADCClearConversionFinishedFlag();
                ADCValue0=result[0];
                ADCValue1=result[1];
                ADCValue2=result[2];
                ADCValue3=result[3];
                ADCValue4=result[4];
                ADCValue5=result[5];
                
                //ADCClearConversionFinishedFlag();
                //pourquoi le clear deux fois?
                
                volts=((float)result[5])*3.3/4096*3.2;
                robotState.distanceTelemetreDroit2 = 34/volts-5;
                volts=((float)result[4])*3.3/4096*3.2;
                robotState.distanceTelemetreDroit = 34/volts-5;
                volts=((float)result[2])*3.3/4096*3.2;
                robotState.distanceTelemetreCentre = 34/volts-5;
                volts=((float)result[0])*3.3/4096*3.2;
                robotState.distanceTelemetreGauche = 34/volts-5;
                volts=((float)result[3])*3.3/4096*3.2;
                robotState.distanceTelemetreGauche2 = 34/volts-5;
                
                
                
                unsigned char payload[5] = {(unsigned char) robotState.distanceTelemetreDroit2, (unsigned char) robotState.distanceTelemetreDroit, (unsigned char) robotState.distanceTelemetreCentre, (unsigned char) robotState.distanceTelemetreGauche, (unsigned char) robotState.distanceTelemetreGauche2};
                UartEncodeAndSendMessage(0x0030, 5, payload);
            }
        
        //pour renvoyer ce qui est reçu ?
        int i ;
        for ( i =0; i< CB_RX1_GetDataSize(); i++)
        {
            unsigned char c = CB_RX1_Get();
            UartDecodeMessage(c);
        }
        
    } // fin while

}