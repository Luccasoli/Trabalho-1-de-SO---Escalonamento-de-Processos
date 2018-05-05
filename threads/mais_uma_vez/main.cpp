#include <bits/stdc++.h>

using namespace std;

int somatorio(int valor);
void dorme_segundos(int tempo);
void dorme_milisegundos(int tempo);

void dorme_segundos(int tempo){
    this_thread::sleep_for (std::chrono::seconds(tempo));
}

void dorme_milisegundos(int tempo){
    this_thread::sleep_for (std::chrono::milliseconds(tempo));
}

/*********************************************************************************/
// Começa mesmo aqui

mutex m;
queue<int> q;

int gera_num(){

	random_device r;

    // Choose a random mean between 1 and 10000
    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist(1, 10000);

    int tempo = uniform_dist(e1);

    return tempo;
}

int somatorio(int valor){

	int soma = 0;
	for (int i = 1; i <= valor; ++i)
	{
		soma += i;
	}

    cout << "Resultado da soma: " << soma << "\n";
    dorme_milisegundos(valor/100);

	return soma;
}

void pega_numeros(){
    for(int i = 1; i <= 100; i++){
        m.lock();

        int num_gerado = gera_num();
        dorme_milisegundos(num_gerado/1000);
        q.push(num_gerado);
        cout << "\nGERADOR: Numero de posicao " << i << " foi gerado: " << q.back() << "\n";
        
        m.unlock();
    }
}

void fcfs(){

    thread escalonador;
    thread gerador_de_proc = thread(pega_numeros);
    int cont = 1; // Ele quem diz quando o escalonador deve terminar

    while(1){
        if(q.size()){
            m.lock();
            cout << "\nESCALONADOR: Numero de posicao " << cont << " foi processado:\n";
            escalonador = thread(somatorio, q.front());
            escalonador.join(); // Espera um somatório concluir para depois iniciar outro
            
            q.pop();
            cont++;
            m.unlock();
        }
        if(cont > 100)
            break;
    }
    gerador_de_proc.join();
}

int main(){

    fcfs();
    
    return 0;
}