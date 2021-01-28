  #include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <libpic30.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "Robot.h"
#include "ADC.h"
#include "main.h"
#include "etats.h"
#include "UART.h"
#include "CB_TX1.h"
#include "CB_RX1.h"
#include "UART_protocole.h"
#include "QEI.h"
#include "Utilities.h"


#define POSITION_DATA 0x0061
#define CONSIGNES_DATA 0x0050


void SendVitesseData(){
        unsigned char ConsignesPayload[24];
        getBytesFromFloat(ConsignesPayload, 0, (float)robotState.vitesseLineaireConsigne);
        getBytesFromFloat(ConsignesPayload, 4, (float)robotState.vitesseAngulaireConsigne);
        getBytesFromFloat(ConsignesPayload, 8, (float)robotState.correctionLineairePourcent);
        getBytesFromFloat(ConsignesPayload, 12,(float)robotState.correctionVitesseAngulairePourcent);
        getBytesFromFloat(ConsignesPayload, 16,(float)robotState.erreurVitesseLineaire);
        getBytesFromFloat(ConsignesPayload, 20,(float)robotState.erreurVitesseAngulaire);
        UartEncodeAndSendMessage (CONSIGNES_DATA, 24, ConsignesPayload) ;
     }


void SendPositionData()
    {
        unsigned char positionPayload[24] ;
        getBytesFromInt32(positionPayload, 0, timestamp) ;
        getBytesFromFloat(positionPayload, 4, (float)robotState.xPosFromOdometry);
        getBytesFromFloat(positionPayload, 8, (float)robotState.yPosFromOdometry);
        getBytesFromFloat(positionPayload, 12, (float)robotState.angleRadianFromOdometry);
        getBytesFromFloat(positionPayload, 16, (float)robotState.vitesseLineaireFromOdometry);
        getBytesFromFloat(positionPayload, 20, (float)robotState.vitesseAngulaireFromOdometry);
        UartEncodeAndSendMessage (POSITION_DATA, 24, positionPayload) ;
    }
       
