#ifndef SOURCE_H
#define SOURCE_H


#include <iostream>
#include <math.h>
#include <fstream>


#define NANO 1e-9
#define MICRO 1e-6


//classe mère
class source{

	public:
		source(); //constructeur défaut
		source(float A, float start); //constructeur
		~source(); //destructeur

		virtual float Ve(float t) = 0; //methode virtuel pour calcul de la tension de la source
	protected:
		float Vo, phi; // amplitude et décalage
};

// classe fille periodique qui hérite de source
class periodique : public source{
	public:
		periodique(); //constructeur défaut
		periodique(float A, float start, float period); //constructeur (A:amplitude,
        //start: décalage et période)
		~periodique(); //destructeur
		virtual float Ve(float t) = 0; //methode virtuel pour calcul de la tension de la source
    protected:
        float T; // période
};

// classe fille aperiodique qui hérite de source
class aperiodique : public source{
	public:
		aperiodique(); //constructeur défaut
		aperiodique(float A, float start); //constructeur
		~aperiodique(); //destructeur

		virtual float Ve(float t) = 0; //methode virtuel pour calcul de la tension de la source
};


class rect : public aperiodique{ // classe fille rect qui hérite de aperiodique
	public:
		rect();//constructeur défaut
		rect(float A, float start, float Thigh);//constructeur
		~rect(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
    private:
        float duree; //durée du signal
};


class creneau : public periodique{
	public:
		creneau();//constructeur défaut
		creneau(float A, float start, float period, float dc);//constructeur
		~creneau(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
    private:
		float duty_cycle; //rapport cyclique du signal
};


class echelon : public aperiodique{
    public:
		echelon();//constructeur défaut
		echelon(float A, float start);//constructeur
		~echelon(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
};


class triang : public periodique{
	public:
		triang();//constructeur défaut
		triang(float A, float start, float period);//constructeur
		~triang(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
};


class sinus : public periodique{
	public:
		sinus();//constructeur défaut
		sinus(float A, float start, float period);//constructeur
		~sinus(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
};


#endif // SOURCE_H
