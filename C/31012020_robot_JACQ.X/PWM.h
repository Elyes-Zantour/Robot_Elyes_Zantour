#ifndef PWM_H
#define	PWM_H

void InitPWM(void);
//void PWMSetSpeed(float vitesseEnPourcentsG, float vitesseEnPourcentD);
void PWMUpdateSpeed(void);
void PWMSetSpeedConsigne (float, char);
void PWMSetSpeedConsignePolaire(void); 

#define MOTEUR_DROITE 0
#define MOTEUR_GAUCHE 1

#define pourcentVitesse 27;
#define Plin 5 //6.5 
#define Ilin 180
#define Pang 4
#define Iang 180

#endif	/* PWM_H */
