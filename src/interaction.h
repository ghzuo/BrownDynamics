#ifndef INTERACTION_H
#define INTERACTION_H

#include <vector>
#include "atom.h"
#include "stringOpt.h"

struct Interaction{
    static double cutoff;
    static void setCutoff(double);
    static Interaction* create(const vector<Atom*>&, const vector<string>&);
    
    virtual void getForce() = 0;
};

struct LJ:public Interaction{
    Atom *objA, *objB;
    double param12, param6;

    LJ(Atom* a, Atom* b, double e, double d);
    LJ(const vector<Atom*>&, const vector<string>&);
    void _initParam(double, double);
    
    void getForce() override;
};

struct Repulse:public Interaction{
    Atom *objA, *objB;
    double param;

    Repulse(Atom*, Atom*, double);
    Repulse(const vector<Atom*>&, const vector<string>&);
    void _initParam(double);
    void getForce() override;
};

struct Harmonics:public Interaction{
    Atom *objA, *objB;
    double kk, d0;

    Harmonics(Atom*, Atom*, double, double);
    Harmonics(const vector<Atom*>&, const vector<string>&);
    void getForce() override;
};

#endif
