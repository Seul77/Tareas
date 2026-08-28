#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;

class Funciones{
    public: 
    int sumaIterativa(int n){
        int a = 0;
        for (int i=1; i<=n; i++){
            a = a + i;
    }
    return a;
    };

    int sumaRecursiva(int n){
        if (n==0){
            return 0;
        }
        return n + sumaRecursiva(n-1);
    } 

    int sumaDirecta(int n){
        return (n*(n+1)/2);
    }
};

#endif