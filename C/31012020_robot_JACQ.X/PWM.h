#ifndef PWM_H
#define	PWM_H

void InitPWM(void);
//void PWMSetSpeed(float vitesseEnPourcentsG, float vitesseEnPourcentD);
void PWMUpdateSpeed(void);
void PWMSetSpeedConsigne (float, char);
void PWMSetSpeedConsignePolaire(void); 

#define MOTEUR_DROITE 0
#define MOTEUR_GAUCHE 1
#define Plin 0
#define Pangl 0


#endif	/* PWM_H */
