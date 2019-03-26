#include <istream>
#include <ostream>
using namespace std;



multime::~multime() {
    nod* t;
    while (rad){
        t=rad->urm;
        delete rad;
        rad=t;
    }
}

multime::multime() {
    rad=NULL;
    l=0;
    ult=NULL;
}

multime::multime(const multime& A) {
    //cout<<endl<<"Constructorul de copiere e apelat."<<endl;
    int i=0;
    //cout<<"<"<<A.l<<">"<<"  ";
    if(A.l && A.rad) {
        l=A.l;
        rad=new nod;
        rad->urm=NULL;
        rad->val=(A.rad)->val;
        nod* t=rad;
        nod* tA=A.rad;
        i++;
        while (i<A.l) {

            t->urm=new nod;
            t=t->urm;
            t->urm=NULL;
            tA=tA->urm;
            t->val=tA->val;
            //cout<<t->val<<" ";
            i++;
        }
        //cout<<"Am iesit din CC."<<endl;
    }
}

multime::multime(int elem) {
    rad=new nod;
    rad->val=elem;
    rad->urm=NULL;
    l=1;
    ult=rad;
}

bool multime::apartine(int v){
    nod* t=rad;
    while (t) {
        if (t->val==v) return 1;
        t=t->urm;
    }
    return 0;
}

int multime::operator[](int poz) {
    if (poz<=l) {
        nod* t=rad;
        for (int i=1; i<poz; i++) {
            t=t->urm;
        }
        return t->val;
    } else {
        cout<<"Eroare.";
        return 0;
    }
}

multime multime::operator=(const multime& A) {
    if (this!=(&A)) {
        while (rad) {
            nod* t=rad;
            rad=rad->urm;
            delete(t);
        }
        rad=new nod;
        nod* t=rad;
        nod* tA;
        if (A.rad) {
            *rad=*(A.rad);
            rad->urm=NULL;
            tA=(A.rad)->urm;
        }
        else {tA=NULL; rad=NULL; l=0; }
        while (tA) {
            t->urm=new nod;
            t=t->urm;
            *t=*tA;
            t->urm=NULL;
            tA=tA->urm;
        }
        ult=t;
        l=A.l;
    }
    return *this;
}

multime multime::multimifica(int* lista=NULL, int lungime=0) {
    if (lista==NULL) { //transform this-ul deja dat in multime
        nod* t=rad;
        if (t) {
            while (t->urm) {
                nod* incep=rad;
                bool no_remove=1;
                while (incep!=t->urm) { //caut primul element din lista care e egal cu elementul curent si il sterg; ar putea fi chiar radacina
                    if (incep->val==(t->urm)->val) {//spre exemplu radacina are aceeasi valoare cu urmatorul dupa ea
                        /*if (incep==rad) {
                            nod* aux=rad;
                            rad=rad->urm;
                            delete aux;
                            l--;
                            break;
                        } */
                        nod* aux=t->urm;
                        t->urm=(t->urm)->urm;
                        delete(aux);
                        no_remove=0;
                        l--; //scad lungimea cand elimin un element
                        break;
                    }
                    incep=incep->urm;
                }
                ult=t;
                if (no_remove) t=t->urm;
            }
        }
    }
    else {

        while (rad) {
            nod* t=rad;
            rad=rad->urm;
            delete(t);
        }
        rad=NULL;
        ult=NULL;
        if (lungime) {
            rad=new nod;
            nod* t=rad;
            t->val=lista[0];
            t->urm=NULL;
            ult=t;
            l++;
        for (int i=1; i<lungime; i++) {
            bool ok=1;
            for (int j=0; j<i; j++) { //verifica ca elmentele listei sa nu se repete
                if (lista[i]==lista[j]) { ok=0; break; }
            }
            if (ok) {
                t->urm=new nod;
                nod* ante=t;
                t=t->urm;
                t->val=lista[i];
                t->urm=NULL;
                l++; //lungimea retinuta in clasa
            }
        }
        ult=t;
        }
    }
    return (*this);
}

multime multime::operator+(multime& A) {
    A.multimifica();
    multime R;
    R.rad=NULL;
    R.l=l+A.l;//noua lungime (noul cardinal) va fi suma cardinalelor anterioare
    R.ult=NULL;
    nod* t;
    if (l) {
        R.rad=new nod;
        (R.rad)->urm=NULL;
        R.ult=R.rad;
        t=rad;
        (R.ult)->val=t->val;
        }
    for (int i=1; i<l; i++) {
        (R.ult)->urm=new nod;
        R.ult=(R.ult)->urm;
        (R.ult)->urm=NULL;
         t=t->urm;
        (R.ult)->val=t->val;
    }
    if (A.l) {
        if (l==0) {
            R.rad=new nod;
            (R.rad)->urm=NULL;
            R.ult=R.rad;
        } else {
            (R.ult)->urm=new nod;
            R.ult=(R.ult)->urm;
            (R.ult)->urm=NULL;
        }
        t=A.rad;
        (R.ult)->val=t->val;
        }
    for (int i=1; i<A.l; i++) {
        (R.ult)->urm=new nod;
        R.ult=(R.ult)->urm;
        (R.ult)->urm=NULL;
         t=t->urm;
        (R.ult)->val=t->val;
    }
    //cout<<"m1+m2 nemultimificat "<<R<<endl;
    R.multimifica();
    return R;
}

multime multime::operator*(multime& A) {
    multime R;
    R.rad=R.ult=NULL;
    R.l=0;
    nod* t1, t2;
    t1=rad;
    while (t1) {
        if (A.apartine(t1->val)) {
            R.l++;
            if (R.ult==NULL){
                R.rad=new nod;
                (R.rad)->val=t1->val;
                (R.rad)->urm=NULL;
                R.ult=R.rad;
            } else {
                (R.ult)->urm=new nod;
                R.ult=(R.ult)->urm;
                (R.ult)->urm=NULL;
                (R.ult)->val=t1->val;
            }
        }
        t1=t1->urm;
    }
    R.multimifica();
    return R;
}

multime multime::operator-(multime& A) {
    multime R;
    R.rad=R.ult=NULL;
    R.l=0;
    nod* t1;
    t1=rad;
    while (t1) {
        if (!A.apartine(t1->val)) {
            R.l++;
            if (R.ult==NULL){
                R.rad=new nod;
                (R.rad)->val=t1->val;
                (R.rad)->urm=NULL;
                R.ult=R.rad;
            } else {
                (R.ult)->urm=new nod;
                R.ult=(R.ult)->urm;
                (R.ult)->urm=NULL;
                (R.ult)->val=t1->val;
            }
        }
        t1=t1->urm;
    }
    R.multimifica();
    return R;
}

istream& operator>>(istream& i,multime& A) {
    if (A.ult) {
        (A.ult)->urm=new nod; int l;
        A.ult=(A.ult)->urm;
        i>>(A.ult)->val;
        A.l++;
        (A.ult)->urm=NULL;
    } else {
        A.rad=new nod;
        i>>(A.rad)->val;
        (A.rad)->urm=NULL;
        A.ult=A.rad;
        A.l++;
    }
    return i;
}

ostream& operator<<(ostream& i, multime A) { //nu pasez prin referinta pentru ca nu vreau sa modific obiectul A cand citesc
    cout<<"< "<<A.l<<" > ";
    while (A.rad) {
        i<<(A.rad)->val<<" ";
        A.rad=(A.rad)->urm; //obiectul nu e modificat (se copiaza in stiva) deci pot sa schimb radacina
    }
    return i;
}
