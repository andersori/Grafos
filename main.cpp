#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
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
void dijkstra(Grafo grafo, Matriz matriz_custo, typename Grafo::Localizacao inicio, typename Grafo::Localizacao destino){
    if(!grafo.arestas.count(inicio) || !grafo.arestas.count(destino)){
        cout<<"Algumas ou ambas as vertices nao pertencem ao grafo"<<endl;
        return;
    }

    typedef typename Grafo::Localizacao Localizacao;
    typedef typename Matriz::Custo Custo;

    priority_queue<pair<Custo, Localizacao>,  vector<pair<Custo, Localizacao> >, greater<pair<Custo, Localizacao> > > visitados;
    unordered_set<Localizacao> verificados;

    visitados.push(make_pair(0,inicio));
    verificados.insert(inicio);

    map<Localizacao, Custo> distancia;
    map<Localizacao, Localizacao> antecessor;

    typename map<Localizacao, vector<Localizacao> >::iterator it;

    for(it = grafo.arestas.begin(); it != grafo.arestas.end(); it++){
        //cout<<(*it).first<<endl;
        distancia[(*it).first] = INFINITO;
        antecessor[(*it).first] = inicio;
    }

    distancia[inicio] = 0;

    while(!visitados.empty() && !verificados.count(destino)){
        Localizacao vertice_menor_custo = visitados.top().second;
        visitados.pop();

        if(vertice_menor_custo == destino){
            break;
        }

        vector<Localizacao> visinhos = grafo.visinhos(vertice_menor_custo);

        typename Grafo::iterador it;

        unsigned int i = 0;
        for(it = visinhos.begin(); it != visinhos.end(); it++){

            if(!verificados.count(*it)){
                unsigned int dist = distancia[vertice_menor_custo] + matriz_custo.arestas[vertice_menor_custo][i++];
                if(distancia[*it] > dist){
                    distancia[*it] = dist;
                    antecessor[*it] = vertice_menor_custo;
                }
                visitados.push(make_pair(dist,*it));
                verificados.insert(*it);
            }
        }
    }
    system("pause");

    if(verificados.count(destino)){
        cout<<"Distancia do caminho minimo: "<<distancia[destino]<<endl;
        Localizacao temp = destino;
        while(true){
            cout<<temp<<" ";
            if(temp == inicio)
                break;
            temp = antecessor[temp];
        }
        cout<<"."<<endl;
        return;
    }

    cout<<"Nao ha caminho de "<< inicio<< " ao "<< destino<< "."<<endl;
}



int main()
{
    GrafoSimples<char> example_graph;
    example_graph.arestas['A'] = {'B'};
    example_graph.arestas['B'] = {'A', 'C', 'D'};
    example_graph.arestas['C'] = {'A'};
    example_graph.arestas['D'] = {'A','E'};
    example_graph.arestas['E'] = {'B'};

    Matriz_Custo<char, unsigned int> matriz;
    matriz.arestas['A'] = {5};
    matriz.arestas['B'] = {3,3,2};
    matriz.arestas['C'] = {6};
    matriz.arestas['D'] = {1,3};
    matriz.arestas['E'] = {7};


    busca_em_largura(example_graph, 'B');
    cout<<endl<<endl<<"Menor caminho!"<<endl;
    dijkstra(example_graph, matriz,'C','E');

    return 0;
}
