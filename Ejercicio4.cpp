#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
struct Nodo {
    int dato;
    Nodo *izq=nullptr;
    Nodo *der=nullptr;
};
struct Resultado {
    bool completo;
    int anchoMaximo;
    int profundidadMinima;
};
Resultado analizar(Nodo* raiz){
    if(!raiz)
        return {true,0,0};
    queue<Nodo*> q;
    q.push(raiz);
    bool hueco=false,completo=true;
    int ancho=0,profundidad=0,minima=0;
    while(!q.empty()){
        int cantidad=(int)q.size();
        ancho=max(ancho,cantidad);
        ++profundidad;
        for(int i=0;i<cantidad;i++){
            Nodo* p=q.front();
            q.pop();
            if(!p->izq&&!p->der&&minima==0)
                minima=profundidad;
            if(p->izq) {
                if(hueco)
                    completo=false;
                q.push(p->izq);
            }else
                hueco=true;
            if(p->der) {
                if(hueco)completo=false;
                q.push(p->der);
            }else
                hueco=true;
        }
    }
    return {completo,ancho,minima};
}
int main() {
    Nodo a{1},b{2},c{3},d{4},e{5},f{6};
    a.izq=&b;
    a.der=&c;
    b.izq=&d;
    b.der=&e;
    c.izq=&f;
    auto r=analizar(&a);
    cout<<"Completo: "<<(r.completo?"Si":"No")<<'\n';
    cout<<"Ancho maximo: "<<r.anchoMaximo<<'\n';
    cout<<"Profundidad minima: "<<r.profundidadMinima<<'\n';
}