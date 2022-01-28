#define PI 3.14159265358979323846
#include "source.h"

//constructeur défaut
source::source(){
    //Valeurs standard
	Vo = 1;
	phi = 0;
}
//constructeur
source::source(float A, float defasage){
    //Valuers précisés
	Vo = A;
	phi = defasage;
}

//destructeur
source::~source(){
}

// PERIODIQUE //

//constructeur défaut
periodique::periodique(){
    //Valeurs standard
	Vo = 1;
	T = 1;
	phi = 0;
}
//constructeur
periodique::periodique(float A, float defasage, float period){
    //Valuers précisés
	Vo = A;
	T = period;
	phi = defasage;
}
//destructeur
periodique::~periodique(){
}

// APERIODIQUE //

//constructeur défaut
aperiodique::aperiodique(){
    //Valeurs standard
	Vo = 1;
	phi = 0;
}
//constructeur
aperiodique::aperiodique(float A, float defasage){
    //Valuers précisés
	Vo = A;
	phi = defasage;
}
//destructeur
aperiodique::~aperiodique(){
}

// RECT //

//constructeur défaut
rect::rect(){
    //Valeurs standard exemple
	Vo = 1;
	duree = 100*NANO;
	phi = 50*NANO;
}
//constructeur
rect::rect(float A, float defasage, float Thigh){
    //Valuers précisés
	Vo = A;
	duree = Thigh;
	phi = defasage;
}
//destructeur
rect::~rect(){
}
//calcul de la tension de la source
float rect::Ve(float t){
	if (t < 0) return 0;
	else if (t >= phi && t < phi+duree) return Vo;
	else return 0;
}

// CRENEAU //

//constructeur défaut
creneau::creneau(){
    //Valeurs standard exemple
	Vo = 1;
	T = 100*NANO;
	phi = 0;
	duty_cycle = 0.5;
}
//constructeur
creneau::creneau(float A, float defasage, float period, float dc){
    //Valuers précisés
	Vo = A;
	T = period;
	phi = defasage;
	duty_cycle = dc;
}

//destructeur
creneau::~creneau(){
}

//calcul de la tension de la source
float creneau::Ve(float t){
	if(t < 0)
		return 0;
	while(phi >= T) phi -= T; // normalisation de phi (phi -> [0,T[)
	t += (T-phi);
	while(t >= T) t -= T; // normalisation de t (t -> [0,T[)
	if(t < duty_cycle*T) return Vo; // Ve = A si t E [0, duty_cycle[)
	else return 0;

}

// ECHELON //

//constructeur défaut
echelon::echelon(){
    //Valeurs standard exemple
	Vo = 1;
	phi = 1*NANO;
}

//constructeur
echelon::echelon(float A, float defasage){
    //Valuers précisés
	Vo = A;
	phi = defasage;
}
//destructeur
echelon::~echelon(){
}
//calcul de la tension de la source
float echelon::Ve(float t){
	if (t >= phi) return Vo;
	else return 0;
}

// TRIANGULAIRE //

//constructeur défaut
triang::triang(){
    //Valeurs standard exemple
	Vo = 1;
	T = 100*NANO;
	phi = 0;
}
//constructeur
triang::triang(float A, float defasage, float period){
    //Valuers précisés
	Vo = A;
	T = period;
	phi = defasage;
}
//destructeur
triang::~triang(){
}
//calcul de la tension de la source
float triang::Ve(float t){
	if(t < 0) return 0;
	t -= phi; // normalisation de t
	while(t >= T) t -= T; // normalisation de t
	if (t <= 0) return (-(2*Vo/T)*(t));
    else if (t <= T/2) return ((2*Vo/T)*(t));
	else return (Vo - (2*Vo/T)*(t-T/2));

}

// SINUSOIDALE //

//constructeur défaut
sinus::sinus(){
    //Valeurs standard dans l'exemple
	Vo = 1;
	T = 100*NANO;
	phi = 0;
}

//constructeur
sinus::sinus(float A, float defasage, float period){
    //Valuers précisés
	Vo = A;
	T = period;
	phi = defasage;
}
//destructeur
sinus::~sinus(){
}

//calcul de la tension de la source sinus
float sinus::Ve(float t){
	if (t < 0) return 0;
	else return Vo*sin((2*PI/T)*t - phi);
}
