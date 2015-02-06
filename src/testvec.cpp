#include <iostream>
#include "myVector.h"

int main(){

    MyVector vec;
    vec[1] = 2.0;

    cout << vec << endl;
    cout << vec.module() << endl;
}
