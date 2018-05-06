#include <bits/stdc++.h>

using namespace std;
#define N_CLIENTES 100

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
int tempo;
int t_gera_num = 0;
int t_somatorio = 0;

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

    t_somatorio += soma;

    cout << "Resultado da soma: " << soma << " e demora " << t_somatorio/100000 << "ms\n";
    //dorme_milisegundos(soma/1000);
    tempo = soma;

	return soma;
}

void pega_numeros(){
    int num_gerado;
    for(int i = 1; i <= N_CLIENTES; i++){
        m.lock();

        num_gerado = gera_num();
        t_gera_num += num_gerado;
        
        q.push(num_gerado);
        cout << "\nGERADOR: Numero de posicao " << i << " foi gerado: " << q.back() << " e demora " << t_gera_num/100 << "ms\n";
        
        m.unlock();
        dorme_milisegundos(num_gerado/100);
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
            dorme_milisegundos(tempo/100000);
        }
        if(cont > N_CLIENTES)
            break;
    }
    gerador_de_proc.join();
}

int main(){

    fcfs();
    
    return 0;
}