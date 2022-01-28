#ifndef CIRCUIT_H_INCLUDED
#define CIRCUIT_H_INCLUDED

#include <iostream>
#include "source.h"

//classe mère
class circuit{
public:
    circuit(); //constructeur défaut
    circuit(source *gen); //constructeur
    ~circuit(); //destructeur
    float get_Vg(); //calcul de la tension de la source
    virtual float Vout(float t) = 0; //calcul de la tension de sortie (virtuel)
    virtual float euler(float,float) = 0; //calcul du methode Euler(virtuel)
	virtual float get_U(unsigned short) = 0; //méthode pour obtenir la valeur de U
protected:
    float t_pre,h; //le temps précedent et le pas
    float Vg,Vs,Vsp; //tensions de la source, de sortie et dérivée de la sortie
    source *src; //source du circuit
};

// classe des circuits d'ordre 1
class circuit_1 : public circuit{ // classe fille qui hérite de circuit
public:
    circuit_1(); //constructeur défaut
    circuit_1(source *gen); //constructeur
    circuit_1(source *gen, float Vout0, float y0); //constructeur
    ~circuit_1(); //destructeur
    virtual float Vout(float t) = 0; //calcul de la tension de sortie (virtuel)
    float euler(float up, float t); //calcul du methode Euler
	float get_U(unsigned short i); //méthode pour obtenir la valeur de U
protected:
    float U; //Valeur de U
};

// classe des circuits d'ordre 2
class circuit_2 : public circuit{ // classe fille qui hérite de circuit
public:
    circuit_2(); //constructeur défaut
    circuit_2(source *gen); //constructeur
    circuit_2(source *gen, float Vout0, float Voutp0, float y0, float yp0);//constructeur
    ~circuit_2(); //destructeur
    virtual float Vout(float t) = 0; //calcul de la tension de sortie (virtuel)
    float euler(float, float); //calcul du methode Euler
	float get_U(unsigned short); //méthode pour obtenir la valeur de U
protected:
    float Vs2p; //dérivée seconde du signal de sortie
    float U[2]; // Vecteur U
};


class circuitA : public circuit_1{ // classe fille qui hérite de circuit_1
public:
    circuitA(); //constructeur défaut
    circuitA(source *gen); //constructeur
    circuitA(source *gen, float Vout0, float Res1, float Cap1); // constructeur
    ~circuitA(); //destructeur
    float Vout(float t); //calcul de la tension de sortie
private:
    float R1,C1; //composants du circuit
};


class circuitB : public circuit_1{ // classe fille qui hérite de circuit_1
public: circuitB(); //constructeur défaut
        circuitB(source *gen); //constructeur
        circuitB(source *gen, float Vout0, float Res1, float Cap1, float Res2); // constructeur
        ~circuitB(); //destructeur
        float Vout(float t); //calcul de la tension de sortie
private:
	float R1,C1,R2; //composants du circuit
};

class circuitC : public circuit_2{ // classe fille qui hérite de circuit_2
public: circuitC(); //constructeur défaut
        circuitC(source *gen); //constructeur
        circuitC(source *gen, float Vout0, float Voutp0, float Res1, float Cap1, float Ind1); // constructeur
        ~circuitC(); //destructeur
        float Vout(float t); //calcul de la tension de sortie
private:
    float L1,R1,C1; //composants du circuit
};

class circuitD : public circuit_2{ // classe fille qui hérite de circuit_2
public: circuitD(); //constructeur défaut
        circuitD(source *gen); //constructeur
        circuitD(source *gen, float Vout0, float Voutp0, float Res1, float Cap1, float Ind1); // constructeur
        ~circuitD(); //destructeur
        float Vout(float t); //calcul de la tension de sortie
private:
    float L1,R1,C1; //composants du circuit
    float Vgp, Vg_pre, t_pre; //dérivée du signal d'entrée
                              //valeur précedente de Vg
                              //temps précedent
};




#endif // CIRCUIT_H_INCLUDED
