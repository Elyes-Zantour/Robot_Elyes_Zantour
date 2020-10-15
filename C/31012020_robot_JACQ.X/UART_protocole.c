#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "CB_RX1.h"
#include "CB_TX1.h"
#include "UART.h"
#include "CB_TX1.h"
#include "CB_TX1.h"
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
 
 public enum StateReception
{
    Waiting ,
    FunctionMSB ,
    FunctionLSB ,
    PayloadLengthMSB ,
    PayloadLengthLSB ,
    Payload ,
    CheckSum
}
StateReceptionrcvState = StateReception.Waiting ;
int msgDecodedFunction = 0 ;
int msgDecodedPayloadLength = 0 ;
byte [] msgDecodedPayload ;
int msgDecodedPayloadIndex = 0 ;
private void DecodeMessage (byte c)
{
    switch ( rcvState )
{
        case StateReception.Waiting :

            break ;
        case StateReception.FunctionMSB :

            break ;
        case StateReception.FunctionLSB :

            break ;
        case StateReception.PayloadLengthMSB :
        
            break ;
        case StateReception.PayloadLengthLSB :

            break ;
        case StateReception.Payload :

            break ;
        case StateReception.CheckSum :

        if ( calculatedChecksum == receivedChecksum )
            {
// Succe s s , on a un message v a l i d e
            }

            break ;
    default :
       rcvState = StateReception.Waiting ;
    break ;
    }