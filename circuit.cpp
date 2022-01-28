#include "circuit.h"

//constructeur défaut
circuit::circuit() {
    //on définit les attributs avec des valeurs standard
	src = new rect(1,0,0.5);
	t_pre = 0; h = 0;
}
//constructeur
circuit::circuit(source *gen) {
    //on définit les attributs avec les valeurs précisés
	src = gen;
}
//destructeur
circuit::~circuit(){
}

//get la tension de la source
float circuit::get_Vg(){
    return Vg;
};

//Circuit de 1 ordre //

//constructeur défaut
circuit_1::circuit_1() {
    //on définit les attributs avec des valeurs standard
	src = new echelon(1,0);
}

//constructeur avec source seulement
circuit_1::circuit_1(source *gen) {
	src = gen;
	U = 0;
	t_pre = 0; h = 0;
}

//constructeur avec source et condition initiale
circuit_1::circuit_1(source *gen, float Vout0, float y0){
	src = gen;
	U = y0;
	t_pre = 0; h = 0;
}

//destructeur
circuit_1::~circuit_1(){
}


// Circuit de 2 ordre //

//constructeur défaut
circuit_2::circuit_2() {
	src = new echelon(1,0);
	U[0] = 0;
	U[1] = 0;
	t_pre = 0; h = 0;
}

//constructeur avec source seulement
circuit_2::circuit_2(source *gen) {
	src = gen;
}

//constructeur avec source et conditions initiales
circuit_2::circuit_2(source *gen, float Vout0, float Voutp0, float y0, float yp0){
	src = gen;
	U[0] = y0;
	U[1] = yp0;
	t_pre = 0; h = 0;

}

//destructeur
circuit_2::~circuit_2(){
}

// CIRCUIT A //

//constructeur défaut
circuitA::circuitA(){
    //on définit les attributs avec des valeurs standard
	R1 = 50;
	C1 = 1*NANO;
	src = new echelon(1,0);
	Vs = 0;
}

//constructeur avec source et valeurs standard
circuitA::circuitA(source *gen){
	src = gen;
	R1 = 50;
	C1 = 1*NANO;
	Vs = 0;
}

//constructeur avec tous les attributs
circuitA::circuitA(source *gen, float Vout0, float Res1, float Cap1){
	R1 = Res1;
	C1 = Cap1;
	src = gen;
	Vs = Vout0;
}
//destructeur
circuitA::~circuitA(){
}

//calcul de la tension de sortie
float circuitA::Vout(float t){
    Vg = (*src).Ve(t); //tension de la source
    Vsp = (Vg - Vs)/(R1*C1);
    Vs = euler(Vsp,t);
    return Vs;
}

// CIRCUIT B //

//constructeur défaut
circuitB::circuitB(){
    //Valeurs standard
	R1 = 36;
	C1 = 1*NANO;
	R2 = 180;
	src = new echelon(1,0);
	Vs = 0;
}

//constructeur avec source et valeurs standard
circuitB::circuitB(source *gen){
    src = gen;
	R1 = 36;
	C1 = 1*NANO;
	R2 = 180;
	Vs = 0;
}

//constructeur avec tous les attributs
circuitB::circuitB(source *gen, float Vout0, float Res1, float Cap1, float Res2){
    R1 = Res1;
	C1 = Cap1;
	R2 = Res2;
	src = gen;
	Vs = Vout0;
}
//destructeur
circuitB::~circuitB(){
}

//calcul de la tension de sortie
float circuitB::Vout(float t){
	Vg = (*src).Ve(t); //tension de la source
	// on calcule Vs':
	if(Vg > 0.6)
		Vsp = -(1/C1)*(1/R1+1/R2)*Vs+(Vg - 0.6)/(R1*C1);
	else
		Vsp = -Vs/(R2*C1);
    Vs = euler(Vsp,t); //calcul de L'EDO et sauvegarde le Vs (pour la prochaine itération)
    return Vs;
}


// CIRCUIT C //

//constructeur défaut
circuitC::circuitC(){
    //Valeurs standard
	R1 = 50;
	C1 = 0.1*NANO;
	L1 = 1*MICRO;
	src = new echelon(1,0);
	Vs = 0;
	Vsp = 0;
}

//constructeur avec source et valeurs standard
circuitC::circuitC(source *gen){
	src = gen;
	R1 = 50;
	C1 = 0.1*NANO;
	L1 = 1*MICRO;
	Vs = 0;
	Vsp = 0;
}

//constructeur avec tous les attributs
circuitC::circuitC(source *gen, float Vout0, float Voutp0, float Res1, float Cap1, float Ind1){
	R1 = Res1;
	C1 = Cap1;
	L1 = Ind1;
	src = gen;
	Vs = Vout0;
	Vsp = Voutp0;
}

//destructeur
circuitC::~circuitC(){
}

//calcul de la tension de sortie
float circuitC::Vout(float t){
    Vg = (*src).Ve(t);
    Vs2p = -(R1/L1)*Vsp + (Vg - Vs)/(L1*C1);
	Vs = euler(Vs2p,t);
	Vsp = get_U(1);
	return Vs;
}


//CIRCUIT D//

//constructeur défaut
circuitD::circuitD(){
    //Valeurs Standard
	R1 = 1.2;
	C1 = 0.1*MICRO;
	L1 = 10*NANO;
	src = new echelon(1,0);
	Vs = 0;
	Vsp = 0;
	Vg_pre = 0;
	t_pre = 0;
	Vgp = 0;
}

//constructeur avec source et valeurs standard
circuitD::circuitD(source *gen){
	src = gen;
	R1 = 1.2;
	C1 = 0.1*MICRO;
	L1 = 10*NANO;
	Vs = 0;
	Vsp = 0;
	Vg_pre = 0;
	t_pre = 0;
	Vgp = (*src).Ve(0);
}

//constructeur avec tous les attributs
circuitD::circuitD(source *gen, float Vout0, float Voutp0, float Res1, float Cap1, float Ind1){
	R1 = Res1;
	C1 = Cap1;
	L1 = Ind1;
	src = gen;
	Vs = Vout0;
	Vsp = Voutp0;
	Vg_pre = 0;
	t_pre = 0;
	Vgp = (*src).Ve(0);
}

//destructeur
circuitD::~circuitD(){
}

//calcul de la tension de sortie
float circuitD::Vout(float t){
	if(t){ //si t = 0, les valeurs définies dans le constructeur restent les mêmes
        Vg = (*src).Ve(t); //tension de la source
        if (t-t_pre) Vgp = (Vg-Vg_pre)/(t-t_pre); //on calcule sa dérivée (Vg')
        // si temps = temps précedent, Vg' est le même
        Vs2p = (Vgp-Vsp)/(R1*C1) - Vs/(L1*C1); //calcule Vs''
        Vs = euler(Vs2p,t); // on résout l'EDO et sauvegarde Vs
        Vsp = get_U(1); // on sauvegarde la valeur de Vs' pour la prochaine itération
        Vg_pre = Vg; // on sauvegarde Ve pour la prochaine itération (calcul de Vg')
        t_pre = t; // on sauvegarde le temps aussi
	}
	return Vs;
}

//méthode d'Euler 1 ordre
float circuit_1::euler(float up, float t) {
	h = t-t_pre; //pas
    U = U + h*up; //on calcule U de Euler
    t_pre = t; //on sauvegarde le temps pour la prochaine itération
	return U;
}

//méthode pour returner la valeur de U
float circuit_1::get_U(unsigned short i) {
	return U;
}

//méthode d'Euler 2 ordre
float circuit_2::euler(float u2p, float t) {
	h = t-t_pre; //pas
    U[0] = U[0] + h*U[1]; //on calcule le vecteur U de Euler
    U[1] = U[1] + h*u2p;
	t_pre = t; //sauvegarder le temps
	return U[0];
}
//méthode pour obtenir la valeur de U[i]
float circuit_2::get_U(unsigned short i) {
	if (i <= 1) return U[i];
	else return 0;
}


