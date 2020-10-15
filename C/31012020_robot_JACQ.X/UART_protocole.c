#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "CB_RX1.h"
#include "CB_TX1.h"
#include "UART.h"
#include "UART_protocole.h"

unsigned char CalculateChecksum(unsigned short int msgFunction, unsigned short int msgPayloadLength, unsigned char* msgPayload)
{
    int i = 0;
    unsigned char checksum = 0xFE;
    
    checksum = (unsigned char)(checksum ^ msgFunction);
    checksum = (unsigned char)(checksum ^ msgPayloadLength);
    for (i = 0; i < msgPayloadLength; i++)
        checksum ^= msgPayload[i];
    
    return checksum;
}
 void UartEncodeAndSendMessage(unsigned short int msgFunction, unsigned short msgPayloadLength, unsigned char* msgPayload)
        {
            int i=0, j =0;
           unsigned char msg[ 6 + msgPayloadLength];
       

            msg[i++] = 0xFE;

            msg[i++] = msgFunction >> 8;
            msg[i++] = msgFunction;

            msg[i++] = msgPayloadLength >> 8;
            msg[i++] = msgPayloadLength;

            for (j = 0; j < msgPayloadLength; j++)
                msg[i++] = msgPayload[j];

            msg[i++] = CalculateChecksum(msgFunction, msgPayloadLength, msgPayload);
            
            SendMessage(msg,i);

          
        }