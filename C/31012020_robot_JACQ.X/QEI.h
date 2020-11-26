#ifndef QEI_H
#define	QEI_H
#include  "IO.h"
#ifdef	__cplusplus
extern "C" {
#endif

#define DIAM_CODEUR_ROUE 0.0426 //en m
#define POINT_TO_METER  (PI*DIAM_CODEUR_ROUE)/8192
#define DISTROUES 0.228
#define FREQ_ECH_QEI 250
    
void InitQEI2();
void InitQEI1();
void QEIUpdateData();
void SendPositionData();


#ifdef	__cplusplus
}
#endif

#endif	/* QEI_H */

