#include <bits/stdc++.h>

using namespace std;

struct thing
{
    int a;
    char b;
    bool operator<(const thing& rhs) const
    {
        return a < rhs.a;
    }
};

struct Numero{
    int posicao = 0;
    int concluida = 0;
    int qnt_somas_realizadas = 0;
    int num_gerado = 0;
    int num_atual = 1;
    int soma_atual = 0;

    bool operator<(const Numero& n) const
    {
        return num_gerado > n.num_gerado;
    }
};


int main(){
    atomic< int > pq;
    
    Numero n[3];
    n[0].num_gerado = 2;
    n[1].num_gerado = 1;
    n[2].num_gerado = 5;
    priority_queue<Numero> q;
    q.push(n[2]);
    q.push(n[1]);
    cout << q.top().num_gerado << '\n';
    q.pop();
    cout << q.top().num_gerado << '\n';

}