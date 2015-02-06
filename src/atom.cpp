#include "atom.h"

// the Param class
Param::Param():gamma(0.5),beta(1.0),dt(0.005){};

// the Atom class
Param Atom::param;
Atom::Atom(){};

Atom::Atom(const MyVector& s, const MyVector& v, double m=1, const string& str="BEAD")
    :name(str),mass(m),site(s),velocity(v){
    _initParam();
};

Atom::Atom(const MyVector& s, double m=1, const string& str="BEAD")
    :name(str),mass(m),site(s){
    _initParam();
};

Atom::Atom(const vector<string>& words):name(words[1]),mass(stod(words[2])){
    for(int i=0; i<site.nDim(); ++i)
	site[i] = stod(words[i+3]);
    _initParam();
};

void Atom::_initParam(){
    pfStruct =  param.dt/(mass + 0.5 * mass * param.gamma * param.dt);
    pfRand   =  sqrt(2 * mass * param.gamma * param.beta / param.dt) * pfStruct;
    pfDrag   =  1 - param.gamma * mass * pfStruct;
}

void Atom::move(){

    // renew the velocity ...
    MyVector oneGauss;
    oneGauss.initGauss();
    
    velocity *= pfDrag;
    velocity += (oneGauss * pfRand);
    velocity += (force * pfStruct);

    // renew the site ...
    site += velocity * param.dt;
}

void Atom::initForce(){force.reinitial();};

ostream& operator<<(ostream& os, const Atom& a){
    os << a.site << "  "
       << a.velocity << "  "
       << a.force;
    return os;
};
