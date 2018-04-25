# Trabalho 1 de SO - Escalonamento de Processos
Trabalho que compõe as atividades de avaliação da disciplina de Sistemas Operacionais

#### Implementar Quatro (ou mais) dos seguintes algoritmos apresentados em aula:
    1 - FCFS
    2 - SJF
    3 - Round-Robin
    4 - Prioridades
    5 - Loteria
    6 - Múltiplas filas

#### Cenário:
Deve-se ter um servidor que recebe requisições de 100 clientes. Cada cliente envia um número k (entre 1 e 10.000, definido aleatoriamente), onde o servidor recebe a requisição e devolve a soma de todos os número entre 1 e k. Por exemplo, k = 5, então tem-se que a resposta será 1+2+3+4+5=15.

##### As seguintes regras devem ser consideradas:
    - Equipes de 3 alunos, informados na lista de email ate dia 15/04 (após essa data as equipes serão definidas aleatoriamente);
    - A forma de comunicação entre o processo cliente e o processo servidor fica a critério da equipe;
    - Restrição: ao menos dois dos algoritmos devem ser preemptivos, onde o valor do quantum fica a critério da equipe;
    - A linguagem de implementação fica a critério da equipe (recomenda-se C/C++);
    - Métricas de Avaliação: Vazão, Tempo de Resposta e Tempo de Espera.
    - Os critérios utilizados para atender as especificidades de cada algoritmo fica a critério de cada equipe.

Forma de entrega: código desenvolvido e um relatório (entre 4 e 6 páginas, formato SBC (http://www.sbc.org.br/documentos-da-sbc/category/169-templates-para-artigos-e-capitulos-de-livros)) relatando as decisões de implementação.
