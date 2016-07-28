#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <typeinfo>
#include <queue>
#include <unordered_set>

#define INFINITO 2030121;

using namespace std;

template<typename L>
struct GrafoSimples{
    typedef L Localizacao;
    typedef typename vector<Localizacao>::iterator iterador;

    map<Localizacao, vector<Localizacao> > arestas;

    inline const vector<Localizacao>& visinhos(Localizacao id){
        return arestas[id];
    }
};

template<typename L, typename C>
struct Matriz_Custo{
    typedef L Localizacao;
    typedef C Custo;
    typedef typename vector<Localizacao>::iterator iterador;

    map<Localizacao, vector<Custo> > arestas;

    inline const vector<Custo>& visinhos(Localizacao id){
        return arestas[id];
    }
    const Custo custo(Localizacao pai, Localizacao adj){
        return arestas[pai][adj];
    }
};


template<typename Grafo>
void busca_em_largura(Grafo grafo, typename Grafo::Localizacao inicio){
    typedef typename Grafo::Localizacao Localiacao;

    queue<Localiacao> fronteira;
    fronteira.push(inicio);

    unordered_set<Localiacao> visitado;
    visitado.insert(inicio);

    while (!fronteira.empty()) {
        auto current = fronteira.front();
        fronteira.pop();

        cout << "Visitando: " << current << endl;
        for (auto next : grafo.visinhos(current)) {
            if (!visitado.count(next)) {
                fronteira.push(next);
                visitado.insert(next);
            }
        }
    }
}

template<typename Grafo, typename Matriz>
void caminho_minimo(Grafo grafo, Matriz matriz_custo, typename Grafo::Localizacao inicio, typename Grafo::Localizacao destino){
    typedef typename Grafo::Localizacao Localizacao;

    priority_queue<pair<unsigned int, Localizacao>,  vector<pair<unsigned int, Localizacao> >, greater<pair<unsigned int, Localizacao> > > verifique;
    unordered_set<Localizacao> visitados;

    verifique.push(make_pair(0,inicio));
    visitados.insert(inicio);

    unsigned int* distancia = new unsigned int[grafo.arestas.size()];
    Localizacao* antecessor = new Localizacao[grafo.arestas.size()];

    for(unsigned int i = 0; i < grafo.arestas.size(); i++){
        distancia[i] = INFINITO;
        antecessor[i] = inicio;
    }

    distancia[inicio] = 0;

    while(!verifique.empty()){
        Localizacao vertice_menor_custo = verifique.top().second;
        verifique.pop();
        visitados.insert(vertice_menor_custo);

        if(vertice_menor_custo == destino){
            break;
        }

        vector<Localizacao> visinhos = grafo.visinhos(vertice_menor_custo);
        typename Grafo::iterador it;

        for(it = visinhos.begin(); it != visinhos.end(); it++){
            if(!visitados.count(vertice_menor_custo)){
                unsigned int dist = distancia[vertice_menor_custo] + matriz_custo.custo(vertice_menor_custo, *it);
                if(distancia[*it] > dist){
                    distancia[*it] = dist;
                    antecessor[*it] = vertice_menor_custo;
                }
            }
        }
    }

    cout<<"Distancia do caminho minimo: "<<distancia[destino]<<endl;
    delete[] distancia;
    delete[] antecessor;
}



int main()
{
    GrafoSimples<char> example_graph;
    example_graph.arestas['A'] = {'B'};
    example_graph.arestas['B'] = {'A', 'C', 'D'};
    example_graph.arestas['C'] = {'A'};
    example_graph.arestas['D'] = {'E', 'A'};
    example_graph.arestas['E'] = {'B'};

    Matriz_Custo<char, unsigned int> matriz;
    matriz.arestas['A'] = {5};
    matriz.arestas['B'] = {3,3,2};
    matriz.arestas['C'] = {6};
    matriz.arestas['D'] = {5,1};
    matriz.arestas['E'] = {7};


    busca_em_largura(example_graph, 'B');

    caminho_minimo(example_graph, matriz,'A','A');

    return 0;
}
