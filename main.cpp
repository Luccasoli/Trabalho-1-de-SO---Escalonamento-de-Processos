#include <bits/stdc++.h>

using namespace std;
#define N_CLIENTES 5
#define INTERVALO 5
#define QUANTUM 2 // Quantidade de somas
// Declaração de funções

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

int tempo;
int t_gera_num = 0;
int t_somatorio = 0;

int gera_num(){

	random_device r;

    // Choose a random mean between 1 and 10000
    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist(1, INTERVALO);

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

// FCFS

void gera_num_fcfs(queue<int>* q){
    int num_gerado;
    for(int i = 1; i <= N_CLIENTES; i++){
        m.lock();

        num_gerado = gera_num();
        t_gera_num += num_gerado;
        
        q->push(num_gerado);
        cout << "\nGERADOR: Numero de posicao " << i << " foi gerado: " << q->back() << " e demora " << t_gera_num/100 << "ms\n";
        

        dorme_milisegundos(num_gerado/100);
    }
}

void fcfs(){
    /*
    * EXPLICAÇÃO:
    * A thread (1)gerador_de_proc executa a função gera_num_fcfs(queue<int>* q), que gera números aleatórios
    * e os insere em uma fila em intervalos de tempos aleatórios.
    * 
    * A função principal invoca a thread (2)escalonador que executa a função somatorio(int valor), essa função
    * realiza o somatório de 1 até o número fornecido, em um tempo proporcional ao tamanho do número fornecido.
    * A função main só é concluida após o (2)escalonador ter esvaziado a fila (processado 100 números).
    */
    queue< int > q;
    thread escalonador;
    thread gerador_de_proc = thread(gera_num_fcfs, &q);
    int cont = 1; // Ele quem diz quando o escalonador deve terminar

    while(1){
        if(q.size()){
            m.lock();

            cout << "\nESCALONADOR: Numero de posicao " << cont << " foi processado:\n";
            escalonador = thread(somatorio, q.front());
            escalonador.join(); // Espera um somatório concluir para depois iniciar outro
            
            q.pop();
            cont++;

    
            dorme_milisegundos(tempo/100000);
        }
        if(cont > N_CLIENTES)
            break;
    }
    gerador_de_proc.join();
}

// SJF NÃO PREEMPTIVO

void gera_num_sjf_nao_preemptivo(priority_queue<int, vector<int>, greater<int> > * q){
    int num_gerado;
    for(int i = 1; i <= N_CLIENTES; i++){
        m.lock();

        num_gerado = gera_num();
        t_gera_num += num_gerado;
        
        cout << "\nGERADOR: Numero de posicao " << i << " foi gerado: " << num_gerado << " e demora " << t_gera_num/100 << "ms\n";
        q->push(num_gerado);
        
        

        //dorme_milisegundos(num_gerado/100);
    }
}

void sjf_nao_preemptivo(){
    priority_queue<int, vector<int>, greater<int> >  pq;

    thread escalonador;
    thread gerador_de_proc = thread(gera_num_sjf_nao_preemptivo, &pq);
    int cont = 1; // Ele quem diz quando o escalonador deve terminar

    while(1){
        if(!pq.empty()){
            m.lock();

            cout << "\nESCALONADOR: Numero de posicao " << cont << " foi processado:\n";
            escalonador = thread(somatorio, pq.top());
            escalonador.join(); // Espera um somatório concluir para depois iniciar outro
            
            pq.pop();
            cont++;

    
            dorme_milisegundos(tempo/100000);
        }
        if(cont > N_CLIENTES)
            break;
    }
    gerador_de_proc.join();
}

// ROUND ROBIN
struct Numero{
    int posicao = 0;
    int concluida = 0;
    int qnt_somas_realizadas = 0;
    int num_gerado = 0;
    int num_atual = 1;
    int soma_atual = 0;
};

void gera_num_round_robin(queue< Numero > * q){
    //int num_gerado;
    int pos = 1;
    for(int i = 1; i <= N_CLIENTES; i++){
        m.lock();

        Numero num;
        num.num_gerado = gera_num();
        num.posicao = pos++;
        t_gera_num += num.num_gerado;
        
        cout << "\nGERADOR: Numero de posicao " << i << " foi gerado: " << num.num_gerado << "\n";
        q->push(num);
        
        

        dorme_milisegundos(num.num_gerado);
    }
}

void somatorio_round_robin(Numero* num){

    int i;
    for(i = num->num_atual; i <= num->num_gerado; i++){
        num->soma_atual += i;
        num->qnt_somas_realizadas++;

        cout << "Numero: " << num->num_gerado << ", de posicao: " << num->posicao << ", o somatorio agora vale: " << num->soma_atual << "\n";
        
        if(num->qnt_somas_realizadas % QUANTUM == 0 and num->qnt_somas_realizadas < num->num_gerado){
            num->num_atual = i+1;
            cout << "Quantum = " << QUANTUM << " estourou do numero: " << num->num_gerado << "\n";
            break;
        }
        //dorme_milisegundos(1);
    }
    if(i >= num->num_gerado){
        num->concluida = 1;
        cout << "Numero: " << num->num_gerado << ", de posicao: " << num->posicao << ", concluido, resultado: " << num->soma_atual << '\n';
    }
    else
        num->concluida = 0;
}

void round_robin(){
    queue< Numero > qn;
    int cont_num_processados = 1;
    thread escalonador;
    thread gerador_de_proc = thread(gera_num_round_robin, &qn);

    while(1){
        if(!qn.empty()){
            m.lock();

            escalonador = thread(somatorio_round_robin, &qn.front());
            escalonador.join();
            //cout << qn.front().num_gerado << " " << qn.front().qnt_somas_realizadas << '\n';
            if(!qn.front().concluida){
                qn.push(qn.front());
                cout << "\nIndo para o proximo da fila!\n";
            }
            else{
                cont_num_processados++;
                cout << "\nConcluiu\n\n";
            }
            qn.pop();
    
        }
        if(cont_num_processados > N_CLIENTES)
            break;
    }
    gerador_de_proc.join();

}

// SRTF (SHORTEST REMAININING TIME FIRST)

volatile bool troca = 0;
mutex m1, m2;

struct Numero_srtf{
    int posicao = 0;
    int concluida = 0;
    int qnt_somas_realizadas = 0;
    int num_gerado = 0;
    int num_atual = 1;
    int soma_atual = 0;

    bool operator<(const Numero_srtf& n) const
    {
        return num_gerado > n.num_gerado;
    }
};

void gera_num_srtf(priority_queue< Numero_srtf > * q){
    //int num_gerado;
    for(int i = 1; i <= N_CLIENTES; i++){
        

        Numero_srtf num;
        num.num_gerado = gera_num();
        num.posicao = i;
        t_gera_num += num.num_gerado;
        
        cout << "\nGERADOR: Numero de posicao " << i << " foi gerado: " << num.num_gerado << "\n";

        if(i > 1){
            if(num.num_gerado < q->top().num_gerado)
                troca = 1;
        }
        q->push(num);

        m1.unlock();
        dorme_milisegundos(num.num_gerado);
    }
}

void somatorio_srtf(Numero_srtf& num, priority_queue<Numero_srtf>& pq){
    int i;
    
    for(i = num.num_atual; i <= num.num_gerado; i++){

        int aux = pq.top().num_gerado;


        if(troca){
            cout << "***Um número menor chegou na fila (" << aux << ").\n";
            break;
        }
        else{
            //m.lock();
            num.soma_atual += i;
            num.qnt_somas_realizadas++;

            cout << "Numero: " << num.num_gerado << ", de posicao: " << num.posicao << ", o somatorio agora vale: " << num.soma_atual << "\n";
            
        }
        
        
        dorme_milisegundos(num.soma_atual % 7);
    }
    //m.lock();
    if(!troca and i >= num.num_gerado){
        num.concluida = 1;
        cout << "Numero: " << num.num_gerado << ", de posicao: " << num.posicao << ", concluido, resultado: " << num.soma_atual << '\n';
    }
    else
        num.concluida = 0;
    m1.unlock();
}

void srtf(){
    priority_queue<Numero_srtf>  pq;

    thread escalonador;
    thread gerador_de_proc = thread(gera_num_srtf, &pq);
    int cont_num_processados = 1; // Ele quem diz quando o escalonador deve terminar

    while(1){
        if(!pq.empty()){
    

            Numero_srtf aux = pq.top();
            
            escalonador = thread(somatorio_srtf, ref(aux), ref(pq));
    
            
            escalonador.join();
    
            //m.lock();
            //cout << qn.front().num_gerado << " " << qn.front().qnt_somas_realizadas << '\n';
    
            if(!aux.concluida){
                pq.push(aux);
                troca = 0;
                cout << "\nIndo para o proximo da fila!\n";
            }
            
            else{
                cont_num_processados++;
                cout << "\nConcluiu\n\n";
            }
            pq.pop();
            dorme_milisegundos(50);
            m1.unlock();
    
        }
        if(cont_num_processados > N_CLIENTES)
            break;
    }
    gerador_de_proc.join();
}

int main(){

    //fcfs();
    //sjf_nao_preemptivo();
    //round_robin();
    srtf();
    
    return 0;
}