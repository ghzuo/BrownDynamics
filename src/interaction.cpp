#include "interaction.h"

double Interaction::cutoff = 9.0;
void Interaction::setCutoff(double d){ cutoff = d * d; };

Interaction* Interaction::create(const vector<Atom*>& atoms,
				 const vector<string>& words){
    Interaction *pF = NULL;
    if(words[0] == "LJ")
	pF = new LJ(atoms, words);
    else if(words[0] == "REP")
    	pF = new Repulse(atoms, words);
    else if(words[0] == "HAR")
    	pF = new Harmonics(atoms, words);
    else
    	cerr << "Wrong lead symbol for interaction: " << words[0] << endl;
    return pF;
};

// LJ potential
LJ::LJ(Atom* a, Atom* b, double e, double d)
    :objA(a),objB(b){
    _initParam(e,d);
};

LJ::LJ(const vector<Atom*>& atoms, const vector<string>& wd)
    :objA(atoms[stoi(wd[1])]), objB(atoms[stoi(wd[2])]){
    _initParam(stod(wd[3]),stod(wd[4]));
};

void LJ::_initParam(double e, double d){
    double dd = d*d;
    double d4 = dd * dd;
    double d6 = d4 * dd;
    param6  = 60 * e * d6;
    param12 = param6 * d6;
}

void LJ::getForce(){
    MyVector r = (*objB).site - (*objA).site;
    double dd = r.mmodule();
    if(dd < cutoff){
        double d4  = dd * dd;
        double d8  = d4 * d4;
        double d14 = d8 * d4 * dd;
        double pf = param12/d14 - param6/d8;
        MyVector f = r * pf;
        (*objA).force -= f;
        (*objB).force += f;
    }
};

// repulse potential
Repulse::Repulse(Atom* a, Atom* b, double d)
    :objA(a),objB(b){
    _initParam(d);
};

Repulse::Repulse(const vector<Atom*>& atoms, const vector<string>& wd)
    :objA(atoms[stoi(wd[1])]),objB(atoms[stoi(wd[2])]){
    _initParam(stod(wd[3]));
};

void Repulse::_initParam(double d){
    double dd = d*d;
    double d4 = dd * dd;
    double d6 = dd * d4;
    param = 12 * d6 * d6;
}

void Repulse::getForce(){
    MyVector r = (*objB).site - (*objA).site;
    double dd = r.mmodule();
    if(dd < cutoff){
        double d4  = dd * dd;
        double d14 = d4 * d4 * d4 * dd;
        double pf = param / d14;
        MyVector f = r * pf;
        (*objA).force -= f;
        (*objB).force += f;
    }
};

// Harmonic Potential
Harmonics::Harmonics(Atom* a, Atom* b, double k, double d)
    :objA(a),objB(b),kk(2*k),d0(d){};

Harmonics::Harmonics(const vector<Atom*>& atoms, const vector<string>& wd)
    :objA(atoms[stoi(wd[1])]), objB(atoms[stoi(wd[2])]),
     kk(2*stod(wd[3])),d0(stod(wd[4])){};

void Harmonics::getForce(){
    MyVector r = (*objB).site - (*objA).site;
    double  pf = kk*(1.0 - d0/r.module());
    MyVector f = r * pf;
    (*objA).force += f;
    (*objB).force -= f;
};
