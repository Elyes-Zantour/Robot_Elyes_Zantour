#ifndef ROBOT_H
#define ROBOT_H
typedef struct robotStateBITS {

union 
    {
        struct 
        {
            unsigned char taskEnCours;
            float vitesseGaucheConsigne;
            float vitesseGaucheCommandeCourante;
            float vitesseDroiteConsigne;
            float vitesseDroiteCommandeCourante;
            float acceleration;
            float distanceTelemetreGauche;
            float distanceTelemetreCentre;
            float distanceTelemetreDroit;
            float distanceTelemetreDroit2;
            float distanceTelemetreGauche2;
            float vitesseDroitFromOdometry;
            float vitesseGaucheFromOdometry;
            float vitesseLineaireFromOdometry;
            float vitesseAngulaireFromOdometry;
            float xPosFromOdometry_1;
            float yPosFromOdometry_1;
            float angleRadianFromOdometry_1;
            float angleRadianFromOdometry;
            float xPosFromOdometry;
            float yPosFromOdometry; 
            float vitesseLineaireConsigne;
            float vitesseAngulaireConsigne;
            float erreurVitesseLineaire;
            float erreurVitesseAngulaire;
            float correctionVitesseAngulaire;
            float correctionVitesseAngulairePourcent;
            float correctionVitesseLineaire;
            float correctionLineairePourcent;
            float corrPropLin;
            float corrIntLin;
            float corrPropAng;
            float corrIntAng;
            float vitesseAngulaireCommande;
            float vitesseLineaireCommande;
            float lineaireSortie;
            float angulaireSortie;
        }
    ;}
;} 

ROBOT_STATE_BITS;
extern volatile ROBOT_STATE_BITS robotState;
#endif /* ROBOT_H */