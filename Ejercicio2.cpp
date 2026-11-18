#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
class RedBlackTree {
    enum Color {ROJO,NEGRO};
    struct Nodo {
        int dato;
        Color color;
        Nodo *izq,*der,*padre;
    };
    Nodo *nil;
    Nodo *raiz;
    void rotarIzquierda(Nodo* x) {
        Nodo* y=x->der;
        x->der=y->izq;
        if(y->izq!=nil)
            y->izq->padre=x;
        y->padre=x->padre;
        if(x->padre==nil)
            raiz=y;
        else if(x==x->padre->izq)
            x->padre->izq=y;
        else x->padre->der=y;y->izq=x;x->padre=y;
    }
    void rotarDerecha(Nodo* x) {
        Nodo* y=x->izq;
        x->izq=y->der;
        if(y->der!=nil)
            y->der->padre=x;
        y->padre=x->padre;
        if(x->padre==nil)
            raiz=y;
        else if(x==x->padre->der)
            x->padre->der=y;
        else x->padre->izq=y;
        y->der=x;
        x->padre=y;
    }
    void corregir(Nodo* z) {
        while(z->padre->color==ROJO) {
            if(z->padre==z->padre->padre->izq) {
                Nodo* t=z->padre->padre->der;
                if(t->color==ROJO) {
                    z->padre->color=NEGRO;
                    t->color=NEGRO;
                    z->padre->padre->color=ROJO;
                    z=z->padre->padre;
                }else{
                    if(z==z->padre->der) {
                    z=z->padre;
                    rotarIzquierda(z);
                }
                    z->padre->color=NEGRO;
                    z->padre->padre->color=ROJO;
                    rotarDerecha(z->padre->padre);
                }
            }else {
                Nodo* t=z->padre->padre->izq;
                if(t->color==ROJO) {
                    z->padre->color=NEGRO;
                    t->color=NEGRO;
                    z->padre->padre->color=ROJO;
                    z=z->padre->padre;
                }else {
                    if(z==z->padre->izq) {
                        z=z->padre;
                        rotarDerecha(z);
                    }
                    z->padre->color=NEGRO;
                    z->padre->padre->color=ROJO;
                    rotarIzquierda(z->padre->padre);
                }
            }
        }
        raiz->color=NEGRO;
    }
    int altura(Nodo* p)const {
        if(p==nil)
            return 0;
        return 1+max(altura(p->izq),altura(p->der));
    }
    void preorden(Nodo* p)const {
        if(p==nil)
            return;
        cout<<p->dato<<(p->color==ROJO?"(R) ":"(N) ");
        preorden(p->izq);
        preorden(p->der);
    }
    int validar(Nodo* p,long long menor,long long mayor)const {
        if(p==nil)
            return p->color==NEGRO?1:-1;
        if(p->dato<=menor||p->dato>=mayor)
            return -1;
        if(p->color==ROJO&&(p->izq->color==ROJO||p->der->color==ROJO))
            return -1;
        int a=validar(p->izq,menor,p->dato);
        int b=validar(p->der,p->dato,mayor);
        if(a<0||a!=b)
            return -1;
        return a+(p->color==NEGRO);
    }
    void liberar(Nodo* p) {
        if(p==nil)
            return;
        liberar(p->izq);
        liberar(p->der);
        delete p;
    }
public:
    RedBlackTree() {
        nil=new Nodo{0,NEGRO,nullptr,nullptr,nullptr};
        nil->izq=nil->der=nil->padre=nil;
        raiz=nil;
    }
    ~RedBlackTree() {
        liberar(raiz);
        delete nil;
    }
    void insertar(int x) {
        Nodo* y=nil;
        Nodo* p=raiz;
        while(p!=nil) {
            y=p;
            if(x==p->dato)
                return;
            p=x<p->dato?p->izq:p->der;
        }
        Nodo* z=new Nodo{x,ROJO,nil,nil,y};
        if(y==nil)
            raiz=z;
        else
            if(x<y->dato)
            y->izq=z;
        else
            y->der=z;
        corregir(z);
    }
    int altura()const {
        return altura(raiz);
    }
    bool verificar()const {
        return nil->color==NEGRO&&(raiz==nil||raiz->color==NEGRO)&&validar(raiz,LLONG_MIN,LLONG_MAX)>0;
    }
    void preorden()const {
        preorden(raiz);
        cout<<'\n';
    }
};
int main() {
    RedBlackTree a;
    for(int i=1;i<=20;i++)a.insertar(i);
    cout<<"Altura RB: "<<a.altura()<<'\n';
    cout<<"Propiedades: "<<(a.verificar()?"VALIDAS":"INVALIDAS")<<'\n';
    cout<<"Preorden: ";a.preorden();
}