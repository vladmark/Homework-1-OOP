#include "nod_pereche.h"
#include <istream>
#include <ostream>
using namespace std;
#ifndef MULTIME_PERECHI_H
#define MULTIME_PERECHI_H


class multime_perechi
{
    nod_pereche* rad;
    nod_pereche* ult;
    int l;
    //daca pun public aici, da eroare
    public:
    multime_perechi() {l=0; rad=NULL; ult=NULL;};
    friend istream& operator>>(istream& i, multime_perechi& p);
    friend ostream& operator<<(ostream& i, multime_perechi p);
    friend multime_perechi prod_cart (multime&, multime& );
};

#include "multime_perechi.cpp"
#endif // MULTIME_PERECHI_H
