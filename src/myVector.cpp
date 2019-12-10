#include "myVector.h"

// the static variation of the class
bool MyVector::_bDim = true;
int MyVector::_nDim = 3;

// the gaussian driver
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
normal_distribution<double> distribution;

void MyVector::nDim(int n){
    if(_bDim){
        _nDim = n;
        _bDim = false;
    }
    else{
        cerr << "Cannot reset the dim of the vector\n" <<endl;
    }
};

int MyVector::nDim(){return _nDim;};

MyVector::MyVector():_data(_nDim, 0.0){
    _bDim = false;
};

double MyVector::module() const{
    return sqrt(mmodule());
};

double MyVector::mmodule() const{
    double sum(0);
    for(int i=0; i<nDim(); ++i)
	sum += _data[i] * _data[i];
    return sum;
}

MyVector MyVector::unit() const{
    double m = module();
    return *this/m;
}

double& MyVector::operator[](int index){
    if(index >= nDim()){
	cerr << "Error: Out the range of the vector when used the operator []\n" <<endl;
	exit(3);
    }
    return _data[index];
};

double MyVector::operator[](int index) const{
    if(index >= nDim()){
	cerr << "Error: Out the range of the vector when used the operator []\n" <<endl;
	exit(3);
    }
    return _data[index];
};

MyVector MyVector::operator+(const MyVector& rhs) const{
    MyVector result;
    for(int i=0; i<_nDim; ++i)
	result[i] = _data[i] + rhs[i];
    return result;
};

MyVector MyVector::operator-(const MyVector& rhs) const{
    MyVector result;
    for(int i=0; i<_nDim; ++i)
	result[i] = _data[i] - rhs[i];
    return result;
};

MyVector MyVector::operator*(double rhs) const{
    MyVector result;
    for(int i=0; i<_nDim; ++i)
	result[i] = _data[i]*rhs;
    return result;
};

MyVector MyVector::operator/(double rhs) const{
    MyVector result;
    rhs = 1/rhs;
    for(int i=0; i<_nDim; ++i)
	result[i] = _data[i]*rhs;
    return result;
};

MyVector& MyVector::operator+=(const MyVector& rhs){
    for(int i=0; i<_nDim; ++i)
	_data[i] += rhs[i];
    return *this;
};

MyVector& MyVector::operator-=(const MyVector& rhs){
    for(int i=0; i<_nDim; ++i)
	_data[i] -= rhs[i];
    return *this;
};

MyVector& MyVector::operator*=(double rhs){
    for(int i=0; i<_nDim; ++i)
	_data[i] *= rhs;
    return *this;
};

void MyVector::initGauss(){
    for(int i=0; i<_nDim; ++i){
	_data[i] = distribution(generator);
    }
}

void MyVector::reinitial(){
    for(int i=0; i<_nDim; ++i){
	_data[i] = 0.0;
    }
}

MyVector operator*(double d, const MyVector& v){
    MyVector result;
    for(int i=0; i<v.nDim(); ++i)
	result[i] = v[i]*d;
    return result;
};

ostream& operator<<(ostream& os, const MyVector& v){
    os << v[0];
    for(int i=1; i<v.nDim(); i++)
        os << "  " << v[i];
    return os;
};


