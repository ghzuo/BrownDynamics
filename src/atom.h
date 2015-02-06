#ifndef ATOM_H
#define ATOM_H

#include "myVector.h"
using namespace std;

struct Param{
    double gamma;
    double beta;
    double dt;

    Param();
};

struct Atom{
    static Param param;

    string name;
    double mass;
    MyVector site;
    MyVector velocity;
    MyVector force;

    double pfRand;
    double pfDrag;
    double pfStruct;

    Atom();
    Atom(const MyVector&, const MyVector&, double, const string&);
    Atom(const MyVector&, double, const string&);
    Atom(const vector<string>&);
    void _initParam();

    void move();
    void initForce();
    friend ostream& operator<<(ostream&, const Atom&);
};

#endif
