#include <iostream>
#include <fstream>

using namespace std;

class multime_perechi;

struct nod {
    int val;
    nod* urm;
};

class multime {
    nod* rad;
    int l;
    nod* ult;
public:
    multime();
    multime(int);
    void afisare();
    bool apartine(int );
    multime& operator=(multime& );
    multime& multimifica (int*, int);
    multime& operator+(multime&);
    multime& operator*(multime&);
    multime& operator-(multime&);
    friend istream& operator>>(istream&, multime&);
    friend ostream& operator<<(ostream&, multime);
    friend multime_perechi& prod_cart(multime&, multime&);
};

class nod_pereche {
    int i1, i2;
    nod_pereche* urm;
    //daca pun public aici, da eroare
    public:
    nod_pereche(int v1=0, int v2=0) {i1=v1; i2=v2; urm=NULL;};
    friend istream& operator>>(istream& i, nod_pereche& p) {
        i>>p.i1;
        i>>p.i2;
        return i;
        };
    friend ostream& operator<<(ostream& i, nod_pereche p) {
        i<<"("<<p.i1<<", "<<p.i2<<") ";
        return i;
    };
    friend class multime_perechi;
    friend istream& operator>>(istream& i, multime_perechi& p);
    friend ostream& operator<<(ostream& i, multime_perechi p);
    friend multime_perechi& prod_cart (multime&, multime& );
};

class multime_perechi {

    nod_pereche* rad;
    nod_pereche* ult;
    int l;
    //daca pun public aici, da eroare
    public:
    multime_perechi() {l=0; rad=NULL; ult=NULL;};
    friend istream& operator>>(istream& i, multime_perechi& p);
    friend ostream& operator<<(ostream& i, multime_perechi p);
    friend multime_perechi& prod_cart (multime&, multime& );
};
istream& operator>>(istream& i, multime_perechi& A) {
        if (A.ult==NULL) {
            A.rad=new nod_pereche;
            (A.rad)->urm=NULL;
            i>>*(A.rad);
            A.ult=A.rad;
        } else {
            (A.ult)->urm=new nod_pereche;
            A.ult=(A.ult)->urm;
            (A.ult)->urm=NULL;
            i>>*(A.ult);
        }
        return i;
};

ostream& operator<<(ostream& i, multime_perechi A) {
        while (A.rad) {
            i<<*(A.rad)<<" ";
            A.rad=(A.rad)->urm;
        }
        return i;
};


multime_perechi& prod_cart(multime& A, multime& B) {
    multime_perechi R;
    R.l=A.l*B.l;
    nod* t1;
    nod*t2;
    t1=A.rad;
    t2=B.rad;
    R.rad=R.ult=NULL;
    while (t1) {
        t2=B.rad;
        while (t2) {
            if(R.ult==NULL) {
                R.rad=new nod_pereche;
                (R.rad)->urm=NULL;
                nod_pereche temp(t1->val, t2->val);
                temp.urm=NULL;
                *(R.rad)=temp;
                R.ult=R.rad;
            } else {
                (R.ult)->urm=new nod_pereche;
                R.ult=(R.ult)->urm;
                (R.ult)->urm=NULL;
                nod_pereche temp(t1->val, t2->val);
                temp.urm=NULL;
                *(R.ult)=temp;
            }
            t2=t2->urm;
        }
        t1=t1->urm;
    }
    return R;
}




multime::multime() {
    rad=NULL;
    l=0;
    ult=NULL;
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

multime& multime::operator=(multime& A) {
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

multime& multime::multimifica(int* lista=NULL, int lungime=0) {
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

multime& multime::operator+(multime& A) {
    int l_noua=l+A.l;
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
    cout<<"m1+m2 nemultimificat "<<R<<endl;
    R.multimifica();
    return R;
}

multime& multime::operator*(multime& A) {
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

multime& multime::operator-(multime& A) {
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

void multime::afisare() {
    nod* t=rad;
    while (t) {
        cout<<t->val<<" ";
        t=t->urm;
    }
    cout<<endl;
    return;
}

istream& operator>>(istream& i,multime& A) {
    if (A.ult) {
        (A.ult)->urm=new nod;
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


int main()
{
    multime m1, m2;
    int v[]={5, 3, 4, 1, 5, 5, 4};
    int u[]={6, 3, 4, 6, 5, 1};
    int lv=sizeof(v)/sizeof(int);
    int lu=sizeof(u)/sizeof(int);
    m1.multimifica(v, lv);
    m2.multimifica(u, lu);
    cout<<endl<<endl;
    cout<<"m1: "<<m1<<"      "<<"m2: "<<m2<<endl;
    multime m3=m1+m2;
    cout<<"m3=m1+m2 "<<m3<<endl;
    multime m4=m1*m2;
    cout<<"m4=m1*m2 "<<m4<<endl;
    multime m5=m3-m4;
    cout<<"m5=m3-m4 "<<m5<<endl;
    multime m6=m4+m5;
    cout<<"m6=m4+m5 "<<m6<<endl;

    ifstream fin("tema1.in");
    int n;
    fin>>n;
    cout<<endl<<"Se vor citi acum "<<n<<" perechi din fisierul tema1.in si li se va face produsul cartezian."<<endl;
    multime_perechi p, pr_cart;
    for (int i=0; i<n; i++) {
            fin>>p;
    }
    cout<<p<<endl;
    cout<<endl<<"Produsul cartezian: "<<endl;
    pr_cart=prod_cart(m1, m2);
    //cout<<prod_cart(m1, m2);
    cout<<pr_cart;
    return 0;
}
