#include <iostream>
#include <stack>
#include <vector>
using namespace std;
struct Nodo {
    int dato;
    Nodo *izq=nullptr;
    Nodo *der=nullptr;
};
bool buscarCamino(Nodo* raiz,int K,vector<int>& resultado){
    if(!raiz)
        return false;
    struct Estado {
        Nodo* nodo;
        int suma;
        vector<int> camino;
    };
    stack<Estado> pila;
    pila.push({raiz,raiz->dato,{raiz->dato}});
    while(!pila.empty()){
        Estado actual=pila.top();
        pila.pop();
        Nodo* p=actual.nodo;
        if(!p->izq&&!p->der&&actual.suma==K) {
            resultado=actual.camino;
            return true;
        }
        if(p->der) {
            auto camino=actual.camino;
            camino.push_back(p->der->dato);
            pila.push({p->der,actual.suma+p->der->dato,camino});
        }
        if(p->izq) {
            auto camino=actual.camino;
            camino.push_back(p->izq->dato);
            pila.push({p->izq,actual.suma+p->izq->dato,camino});
        }
 }
 return false;
}
int main() {
    Nodo a{5},b{4},c{8},d{11},e{13},f{4},g{7},h{2},i{1};
    a.izq=&b;
    a.der=&c;
    b.izq=&d;
    c.izq=&e;
    c.der=&f;
    d.izq=&g;
    d.der=&h;
    f.der=&i;
    vector<int> camino;
    int K=22;
    if(buscarCamino(&a,K,camino)) {
        cout<<"Camino con suma "<<K<<": ";
        for(int x:camino)
            cout<<x<<' ';
        cout<<'\n';
    }
    else
        cout<<"No existe camino\n";
}