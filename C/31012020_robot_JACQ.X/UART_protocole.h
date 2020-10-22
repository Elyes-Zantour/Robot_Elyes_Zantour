/* 
 * File:   UART_protocole.h
 * Author: TP_EO_6
 *
 * Created on 14 octobre 2020, 12:54
 */

#ifndef UART_PROTOCOLE_H
#define	UART_PROTOCOLE_H

#ifdef	__cplusplus
extern "C" {
#endif
  unsigned char CalculateChecksum(int msgFunction,  int msgPayloadLength, unsigned char msgPayload[]);
 void UartEncodeAndSendMessage(unsigned short int msgFunction, unsigned short msgPayloadLength, unsigned char* msgPayload);
 void DecodeMessage (char  c);
 
 
#ifdef	__cplusplus
}
#endif

#endif	/* UART_PROTOCOLE_H */

