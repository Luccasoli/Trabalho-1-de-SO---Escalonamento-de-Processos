#include <iostream>
#include <thread>
#include <random>

using namespace std;

void func(){

	cout << "Sou uma thread\n"; 

}

int main(){

	thread t1;

	cout << "Joinable antes de iniciar: " << t1.joinable() << endl;

	t1 = thread(func);

	cout << "Joinable depois de iniciar: " << t1.joinable() << endl;

	t1.join();

	cout << "Joinable depois do join(): " << t1.joinable() << endl;

	//cout << "thread main id: " << this_thread::get_id() << endl;
	//cout << "thread t1 id: " << t1.get_id() << '\n';

	return 0;
}