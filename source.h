#ifndef SOURCE_H
#define SOURCE_H


#include <iostream>
#include <math.h>
#include <fstream>


#define NANO 1e-9
#define MICRO 1e-6


//classe m�re
class source{

	public:
		source(); //constructeur d�faut
		source(float A, float start); //constructeur
		~source(); //destructeur

		virtual float Ve(float t) = 0; //methode virtuel pour calcul de la tension de la source
	protected:
		float Vo, phi; // amplitude et d�calage
};

// classe fille periodique qui h�rite de source
class periodique : public source{
	public:
		periodique(); //constructeur d�faut
		periodique(float A, float start, float period); //constructeur (A:amplitude,
        //start: d�calage et p�riode)
		~periodique(); //destructeur
		virtual float Ve(float t) = 0; //methode virtuel pour calcul de la tension de la source
    protected:
        float T; // p�riode
};

// classe fille aperiodique qui h�rite de source
class aperiodique : public source{
	public:
		aperiodique(); //constructeur d�faut
		aperiodique(float A, float start); //constructeur
		~aperiodique(); //destructeur

		virtual float Ve(float t) = 0; //methode virtuel pour calcul de la tension de la source
};


class rect : public aperiodique{ // classe fille rect qui h�rite de aperiodique
	public:
		rect();//constructeur d�faut
		rect(float A, float start, float Thigh);//constructeur
		~rect(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
    private:
        float duree; //dur�e du signal
};


class creneau : public periodique{
	public:
		creneau();//constructeur d�faut
		creneau(float A, float start, float period, float dc);//constructeur
		~creneau(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
    private:
		float duty_cycle; //rapport cyclique du signal
};


class echelon : public aperiodique{
    public:
		echelon();//constructeur d�faut
		echelon(float A, float start);//constructeur
		~echelon(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
};


class triang : public periodique{
	public:
		triang();//constructeur d�faut
		triang(float A, float start, float period);//constructeur
		~triang(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
};


class sinus : public periodique{
	public:
		sinus();//constructeur d�faut
		sinus(float A, float start, float period);//constructeur
		~sinus(); //destructeur
		float Ve(float t); //methode pour calcul de la tension de la source
};


#endif // SOURCE_H
