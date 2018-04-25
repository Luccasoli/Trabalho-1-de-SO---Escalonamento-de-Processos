#include <bits/stdc++.h>
#include "Numero.h"
//#include <random>

using namespace std;

void Numero::gera_num(){

	random_device r;

    // Choose a random mean between 1 and 10000
    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist(1, 10000);

    valor = uniform_dist(e1);
}

int Numero::somatorio(){
	int soma = 0;
	for (int i = 1; i <= valor; ++i)
	{
		soma += i;
	}

	return soma;
}

Numero::Numero(){
	Numero::gera_num();
}
