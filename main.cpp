#include "circuit.h"
#include <cstring>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

using namespace std;

void menu(); // on rappele la fonction Menu

//Variable static
static char source_type, circuit_type;
static float t, deltat = 0.1*NANO, tf = 500*NANO;
static float y, Ve, u0, up0, R1, R2, C1, L1, A, phi, duty, T, f;
static char nom_fichier[20] = "out.txt";

static source *gen;
static circuit *circ;


int main(){


    menu();

    // Exemples de sources:
	//gen = new echelon(1,1*NANO);
	//gen = new echelon();
	//gen = new creneau(1,0,100*NANO,0.5);
	//gen = new creneau();
	//gen = new rect(1,50*NANO,100*NANO);
	//gen = new rect();
	//gen = new sinus(1,0,100*NANO);
	//gen = new sinus();
	//gen = new triang(1,0,100*NANO);
	//gen = new triang();

	// Exemples de circuits:
	//circ = new circuitA(gen,0,50,1*NANO);
	//circ = new circuitA(gen);
	//circ = new circuitB(gen,0,36,1*NANO,180);
	//circ = new circuitB(gen);
	//circ = new circuitC(gen,0,0,120,0.1*NANO,1*MICRO);
	//circ = new circuitC(gen);
	//circ = new circuitD(gen,0,0,1.2,0.1*MICRO,10*NANO);
    //circ = new circuitD(gen);


    // creer le fichier de sortie:
	ofstream outfile;
    outfile.open(nom_fichier);
	outfile << "circuit " << circuit_type << "\nt\tVe\tVs" << endl;

	for(t = 0; t < tf; t+=deltat) {  //simulation de t = 0 à temps final tf, avec un pas deltat
		y = (*circ).Vout(t);  //on calcule la tension de sortie du circuit
		Ve = (*circ).get_Vg();  //on calcule la tension de la source
		outfile << t << "\t" << Ve << "\t" << y << endl;
	}
	outfile.close();

    // écriture dans le fichier matlab:

	FILE * fich;
    int npas=100;
    float t,dt=1./float(npas);
    fich=fopen("ve","wt");
    for(int i=0;i<npas+1;i++)
    {
    t=float(i)*PI*dt;
    fprintf(fich,"%f %f \n",t,sin(2*t));
    }
    fclose(fich);
	return 0;
}

void menu(){

    // Dans ce menu on va permettre à l'utilisateur de choisir les paramètres de la simulation
    // il peut prendre les valeurs standard (des exemples du Moodle) ou choisir d'autres valeurs qcq

    char c;
    cout << "\nChoisissez un circuit:\n";
    cout << "A, B, C ou D\n";
    cin >> circuit_type;
    cout << "\nChoisissez une source:\n";
    cout << "rectangulaire(R)\ncreneau (C)\nechelon(E)\n";
    cout << "triangulaire(T)\nsinusoidal(S)\n\nVotre choix: ";
    cin >> source_type;
    cout << "\nUtiliser source comme dans les examples? (o/n) ";
    cin >> c;

    //Choisir le type de source
    switch(source_type){
        case 'r': case 'R':
            if(c == 'n' || c == 'N'){
                cout << "Amplitude: "; cin >> A;
                cout << "phi: "; cin >> phi;
                cout << "Duree: "; cin >> duty;
                gen = new rect(A,phi,duty);} //allocation dynamique
            else gen = new rect(); //constructeur défaut
            break;
        case 'c': case 'C':
            if(c == 'n' || c == 'N'){
                cout << "Amplitude: "; cin >> A;
                cout << "phi: "; cin >> phi;
                cout << "Period: "; cin >> T;
                cout << "Duty cycle: "; cin >> duty;
                gen = new creneau(A,phi,T,duty);}
            else gen = new creneau();
            break;
        case 'e': case 'E':
            if(c == 'n' || c == 'N'){
                cout << "Amplitude: "; cin >> A;
                cout << "phi: "; cin >> phi;
                gen = new echelon(A,phi);}
            else gen = new echelon();
            break;
        case 't': case 'T':
            if(c == 'n' || c == 'N'){
                cout << "Amplitude: "; cin >> A;
                cout << "phi: "; cin >> phi;
                cout << "Period: "; cin >> T;
                gen = new triang(A,phi,T);}
            else gen = new triang();
            break;
        case 's': case 'S':
            if(c == 'n' || c == 'N'){
                cout << "Amplitude: "; cin >> A;
                cout << "phi: "; cin >> phi;
                cout << "Frequence: "; cin >> f; T = 1.0/f;
                gen = new sinus(A,phi,T);}
            else gen = new sinus();
            break;
        default: break;};




    cout << "\nUtiliser circuit comme dans les examples? (o/n) "; cin >> c;
    switch(circuit_type){
        case 'a': case 'A':
            if(c == 'n' || c == 'N'){
                cout << "condition initiale u(0) = "; cin >> u0;
                cout << "R1 = "; cin >> R1;
                cout << "C1 = "; cin >> C1;
                circ = new circuitA(gen,u0,R1,C1);}
            else circ = new circuitA(gen);
            break;

            case 'b': case 'B':
            if(c == 'n' || c == 'N'){
                cout << "condition initiale u(0) = "; cin >> u0;
                cout << "R1 = "; cin >> R1;
                cout << "R2 = "; cin >> R2;
                cout << "C1 = "; cin >> C1;
                circ = new circuitB(gen,u0,R1,C1,R2);}
            else circ = new circuitB(gen);
            break;

            case 'c': case 'C':
            if(c == 'n' || c == 'N'){
                cout << "condition initiale u1(0) = "; std::cin >> u0;
                cout << "condition initiale u2(0) = "; std::cin >> up0;
                cout << "R1 = "; cin >> R1;
                cout << "L1 = "; cin >> L1;
                cout << "C1 = "; cin >> C1;
                circ = new circuitC(gen,u0,up0,R1,C1,L1);}
            else circ = new circuitC(gen);
            break;

            case 'd': case 'D':
            if(c == 'n' || c == 'N'){
                cout << "condition initiale u1(0) = "; std::cin >> u0;
                cout << "condition initiale u2(0) = "; std::cin >> up0;
                cout << "R1 = "; cin >> R1;
                cout << "L1 = "; cin >> L1;
                cout << "C1 = "; cin >> C1;
                circ = new circuitD(gen,u0,up0,R1,C1,L1);}
            else circ = new circuitD(gen);
            break;
        default: break;};



    //Definir les parametres de simulation
    cout << "Parametres de simulation:\n";
    cout << "Pas (delta t) standard? (o/n) "; cin >> c;
	if(c == 'n' || c == 'N'){
        cout << "delta t = "; cin >> deltat;}

	cout << "Temps final standard? (o/n) "; cin >> c;
	if(c == 'n' || c == 'N'){
        cout << "tf = "; cin >> tf;}

	cout << "Fichier de sortie standard? (o/n) "; cin >> c;
	if(c == 'n' || c == 'N'){
        cout << "nom du fichier: "; cin >> nom_fichier;}}

