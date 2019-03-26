#include <iostream>
#include <fstream>
#include "multime.h"
#include "nod_pereche.h"
#include "multime_perechi.h"
using namespace std;

int main()
{
    multime m1, m2;
    int v[]={5, 3, 4, 1, 5, 5, 4};
    int u[]={6, 3, 4, 6, 5, 1};
    int lv=sizeof(v)/sizeof(int);
    int lu=sizeof(u)/sizeof(int);
    m1.multimifica(v, lv);
    m2.multimifica(u, lu);
    cout<<endl;
    cout<<"m1: "<<m1<<"      "<<"m2: "<<m2<<endl;
    multime m3=m1+m2+m1;
    cout<<"m3=m1+m2+m1 "<<m3<<endl;
     multime m4=m1*m2;
    cout<<"m4=m1*m2 "<<m4<<endl;
    multime m5=m3-m4;
    cout<<"m5=m3-m4 "<<m5<<endl;
    multime m6=m4+m5;
    cout<<"m6=m4+m5 "<<m6<<endl;
    cout<<"Elementul de pe pozitia 2 a m6: "<<m6[2]<<endl;
    cout<<"m1*m2+m2: "<<m1*m2+m2<<endl;
    cout<<"m1*m2+m1: "<<m1*m2+m1<<endl;
    ifstream fin("tema1.in");
    int n;
    fin>>n;
    cout<<endl<<"Se vor citi acum "<<n<<" perechi din fisierul tema1.in."<<endl;
    multime_perechi p, pr_cart;
    for (int i=0; i<n; i++) {
            fin>>p;
    }
    cout<<p<<endl;
    cout<<endl<<"Produsul cartezian al m1 si m2: "<<endl;
    pr_cart=prod_cart(m1, m2);
    //cout<<prod_cart(m1, m2);
    cout<<pr_cart;
    return 0;
}
