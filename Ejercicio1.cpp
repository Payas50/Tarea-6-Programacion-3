#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
struct Nodo {
    int dato;
    Nodo *izq=nullptr;
    Nodo *der=nullptr;
    explicit Nodo(int x):dato(x){}
};
class BST {
    Nodo* raiz=nullptr;
public:
    ~BST(){
        if(!raiz)
            return;
        stack<Nodo*> s;
        s.push(raiz);
        while(!s.empty()) {
            Nodo* p=s.top();
            s.pop();
            if(p->izq)s.push(p->izq);
            if(p->der)s.push(p->der);
            delete p;
        }
    }
    void insertar(int x) {
        Nodo** p=&raiz;
        while(*p) {
            if(x==(*p)->dato)
                return;
            p=x<(*p)->dato?&(*p)->izq:&(*p)->der;
        }
        *p=new Nodo(x);
    }
    void eliminar(int x) {
        Nodo** p=&raiz;
        while(*p&&(*p)->dato!=x)
            p=x<(*p)->dato?&(*p)->izq:&(*p)->der;
        if(!*p)
            return;
        Nodo* t=*p;
        if(t->izq&&t->der) {
            Nodo** q=&t->der;
            while((*q)->izq)q=&(*q)->izq;
            t->dato=(*q)->dato;
            p=q;
            t=*p;
        }
        *p=t->izq?t->izq:t->der;
        delete t;
    }
    void inorden()const {
        stack<Nodo*> s;
        Nodo* p=raiz;
        while(p||!s.empty()){while(p) {
            s.push(p);
            p=p->izq;
        }
            p=s.top();
            s.pop();
            cout<<p->dato<<' ';
            p=p->der;
        }
        cout<<'\n';
    }
    void preorden()const {
        if(!raiz)
            return;
        stack<Nodo*> s;
        s.push(raiz);
        while(!s.empty()) {
            Nodo* p=s.top();
            s.pop();
            cout<<p->dato<<' ';
            if(p->der)s.push(p->der);
            if(p->izq)s.push(p->izq);
        }
        cout<<'\n';
    }
    int altura()const {
        if(!raiz)
            return 0;
        queue<pair<Nodo*,int>> q;
        q.push({raiz,1});
        int h=0;
        while(!q.empty()) {
            auto [p,n]=q.front();
            q.pop();
            h=max(h,n);
            if(p->izq)
                q.push({p->izq,n+1});
            if(p->der)
                q.push({p->der,n+1});
        }
        return h;
    }
};
int main() {
    BST a;
    for(int i=1;i<=20;i++)a.insertar(i);
    cout<<"Altura inicial: "<<a.altura()<<'\n';
    a.eliminar(5);
    a.eliminar(15);
    cout<<"Inorden: ";
    a.inorden();
    cout<<"Preorden: ";
    a.preorden();
    cout<<"Altura final: "<<a.altura()<<'\n';
}