/* 
 * File:   QEI.h
 * Author: TP_EO_6
 *
 * Created on 20 novembre 2020, 10:00
 */

#ifndef QEI_H
#define	QEI_H

#ifdef	__cplusplus
extern "C" {
#endif

void InitQEI2();
void InitQEI1();
void QEIUpdateData();
void SendPositionData();


#ifdef	__cplusplus
}
#endif

#endif	/* QEI_H */

