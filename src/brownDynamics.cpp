#include "brownDynamics.h"

int main(int argc, char* argv[]){

    // get the input arguments
    Args myargs(argc,argv);
    
    // initial System
    Atom::param = myargs.param;
    Interaction::setCutoff(myargs.cutoff);

    // read the molecule system
    vector<Atom*> atoms;
    vector<Interaction*> interactions;
    readStruct(myargs.infile, atoms, interactions);    

    // do the move and write trajectory
    ofstream TRJ(myargs.outfile.c_str());
    writeFrame(0, atoms, TRJ);
    for(int iStep=1; iStep <= myargs.nTotalStep; ++iStep){
	
        // Initial force ...
        for(auto &pA : atoms)
            (*pA).initForce();

        // get the force ...
        for(auto &pI : interactions)
            (*pI).getForce();

        // get the new velocity and site
        for(auto &pA : atoms )
            (*pA).move();

        // output per nOutputStep
        if(iStep%myargs.nOutputStep == 0)
            writeFrame(iStep, atoms, TRJ);
    }
};


Args::Args(int argc, char** argv):
    infile("molecule.dat"), outfile("trajectory.dat"),
    nTotalStep(10000), nOutputStep(100){

    program = argv[0];

    char ch;
    while ((ch = getopt(argc, argv, "i:g:T:t:N:n:o:c:h")) != -1){
        switch (ch){
            case 'i':
                infile = optarg; break;
            case 'g':
                param.gamma = stod(optarg); break;
            case 'T':
                param.beta = stod(optarg); break;
            case 't':
                param.dt = stod(optarg); break;
            case 'N':
                nTotalStep = stoi(optarg); break;
            case 'n':
                nOutputStep = stoi(optarg); break;
            case 'o':
                outfile = optarg; break;
            case 'c':
                cutoff = stod(optarg); break;
            case 'h':
                usage();
            case '?':
                usage();
        }
    }
}


void Args::usage(){
    cerr << "\nProgram Usage: \n" 
         << program  <<"\n"
         <<" [ -i molecule.dat ]   input molecule atom&interaction file, default: molecule.dat\n"
         <<" [ -g 0.5 ]            gamma of the solution, default: 0.5\n"
         <<" [ -T 1.0 ]            kT of the environment of simulation, default: 1.0\n"
         <<" [ -t 0.005 ]          time interval of per step, default: 0.005\n"
         <<" [ -N 10000 ]          total number of step of simulation, default: 10000\n"
         <<" [ -n 100 ]            output per step, default: 100\n"
         <<" [ -c 3.0 ]            output cut off, default: 3.0\n"
         <<" [ -o trajectory.dat ] output atoms phase file, default: trajectory.dat\n"
         <<" [ -h ]                disply this information\n"
         << endl;
    exit(1);
}


void readStruct(const string& file, vector<Atom*>& atoms, vector<Interaction*>& interactions){

    // open and test the file
    ifstream INF(file.c_str());
    if(!INF){
        cerr << "\nCannot found the input file " << file << endl;
        exit(1);
    }

    for(string line; getline(INF, line); ){
        // check empty line
        if(trim(line).empty())
            continue;
	
        // get the line info
        vector<string> words;
        int nword = separateWord(words, line);

        if(words[0] == "ATOM"){
            Atom *pA = new Atom(words);
            if(pA !=NULL )
                atoms.emplace_back(pA);
        }else {
            Interaction *pA = Interaction::create(atoms, words);
            if(pA != NULL)
                interactions.emplace_back(pA);
        }
    }
    INF.close();    
};

void writeFrame(int step, const vector<Atom*>& atoms, ostream& os){
    int index(-1);
    for( const auto &pA : atoms)
	os << step     << "  "
	   << ++index  << "  "
	   << *pA << endl;
};

