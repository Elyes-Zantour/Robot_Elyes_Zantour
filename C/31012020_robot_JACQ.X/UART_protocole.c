#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "CB_RX1.h"
#include "CB_TX1.h"
#include "UART.h"
#include "CB_TX1.h"
#include "CB_TX1.h"
#include "UART_protocole.h"

unsigned char  msgDecodedChecksum;
unsigned char msgCalculatedChecksum;
int isCkecksumOk = -1;
int decodedFlag = 0;
int msgDecodedFunction=0;
int msgDecodedPayloadLenght[128];
int msgDecodedPayloadIndex=0;



enum StateReception
{
    Waiting ,
    FunctionMSB ,
    FunctionLSB ,
    PayloadLengthMSB ,
    PayloadLengthLSB ,
    Payload ,
    CheckSum
};
StateReception rcvState = StateReception.Waiting;
 
    void UartDecodeMessage (unsigned char c ){
          switch (rcvState)
            {
                case StateReception.Waiting:
                    if (c == 0xFE)
                    {
                        rcvState = StateReception.FunctionMSB;
                        decodedFlag = 0;
                    }
                    break;

                case StateReception.FunctionMSB:
                    msgDecodedFunction += c;
                    msgDecodedFunction <<= 8;
                    rcvState = StateReception.FunctionLSB;
                    break;

                case StateReception.FunctionLSB:
                    msgDecodedFunction += c;
                    rcvState = StateReception.PayloadLengthMSB;
                    break;

                case StateReception.PayloadLengthMSB:
                    msgDecodedPayloadLength += c;
                    msgDecodedPayloadLength <<= 8;
                    rcvState = StateReception.PayloadLengthLSB;
                    break;

                case StateReception.PayloadLengthLSB:
                    msgDecodedPayloadLength += c;
                    msgDecodedPayload = unsigned char [msgDecodedPayloadLength];
                    if (msgDecodedPayloadLength == 0)
                        rcvState = StateReception.CheckSum;
                    else
                        rcvState = StateReception.Payload;
                    break;

                case StateReception.Payload:
                    msgDecodedPayload[msgDecodedPayloadIndex++] = c;
                    if (msgDecodedPayloadIndex == msgDecodedPayloadLength)
                        rcvState = StateReception.CheckSum;
                    break;

                case StateReception.CheckSum:
                    msgDecodedChecksum = c;
                    msgCalculatedChecksum = CalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                    decodedFlag = 1;
                    if (msgDecodedChecksum == msgCalculatedChecksum)
                        isCkecksumOk = 1;
                    else
                        isCkecksumOk = 0;
                    break;

                default:
                    rcvState = StateReception.Waiting;
                    break;
          }
    }
    void UartProczsDecodedMessage(int function , int payloadLength, unsigned char* payload){
        
    }

    StateReception rcvState = StateReception.Waiting ;
    int msgDecodedFunction = 0 ;
    int msgDecodedPayloadLength = 0 ;
    unsigned char msgDecodedPayload;
    int msgDecodedPayloadIndex = 0 ;

 unsigned char CalculateChecksum(int msgFunction,  int msgPayloadLength, unsigned char msgPayload[])
{
    int i = 0;
    unsigned char checksum = 0xFE;
    
    checksum = (unsigned char)(checksum ^ msgFunction);
    checksum = (unsigned char)(checksum ^ msgPayloadLength);
    for (i = 0; i < msgPayloadLength; i++)
        checksum ^= msgPayload[i];
 
    return checksum;
}

 void UartEncodeAndSendMessage( int msgFunction, int msgPayloadLength, unsigned char msgPayload[])
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
 