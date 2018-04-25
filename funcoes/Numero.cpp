#include "Numero.h"
#include <bits/stdc++.h>

void Numero::gera_num(){
	std::srand(std::time(0));
	valor = rand() % 10000 + 1;
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
