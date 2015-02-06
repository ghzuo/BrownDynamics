#ifndef BROWNDYNAMICS_H
#define BROWNDYNAMICS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unistd.h>

#include "atom.h"
#include "interaction.h"
#include "stringOpt.h"

struct Args{
    string program, infile, outfile;
    int nTotalStep, nOutputStep;
    double cutoff;
    Param param;

    Args(int, char**);
    void usage();
};

void readStruct(const string&, vector<Atom*>&, vector<Interaction*>&);
void writeFrame(int, const vector<Atom*>&, ostream&);

#endif
