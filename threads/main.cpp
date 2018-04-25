#include <iostream>
#include <thread>
#include <random>
#include "../Gerador_de_numeros/Numero.h"

using namespace std;

void gera_num(){

	Numero n1;
	cout << "Id da thread que me executa: " << this_thread::get_id() << endl;
	cout << n1.valor << endl;
}

void func(){

	cout << "Sou uma thread\n"; 

}

int main(){

	for(int i = 0; i < 5; i++){
		thread t1;
		t1 = thread(gera_num);
		
		thread t2;
		t2 = thread(gera_num);
		t2.join();
		t1.join();
	}

	/*
	cout << "Joinable antes de iniciar: " << t1.joinable() << endl;

	t1 = thread(func);

	cout << "Joinable depois de iniciar: " << t1.joinable() << endl;

	t1.join();

	cout << "Joinable depois do join(): " << t1.joinable() << endl;

	//cout << "thread main id: " << this_thread::get_id() << endl;
	//cout << "thread t1 id: " << t1.get_id() << '\n';
	*/
	return 0;
}