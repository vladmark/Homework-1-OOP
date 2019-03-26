#ifndef NOD_PERECHE_H
#define NOD_PERECHE_H
#include <istream>
#include <ostream>
using namespace std;

//class multime_perechi;

class nod_pereche
{
  int i1, i2;
    nod_pereche* urm;
    //daca pun public aici, da eroare
    public:
    nod_pereche(int v1=0, int v2=0) {i1=v1; i2=v2; urm=NULL;};
    friend istream& operator>>(istream& i, nod_pereche& p);
    friend ostream& operator<<(ostream& i, nod_pereche p);
    friend class multime_perechi;
    friend istream& operator>>(istream& i, multime_perechi& p);
    friend ostream& operator<<(ostream& i, multime_perechi p);
    friend multime_perechi prod_cart (multime&, multime& );
};

#include "nod_pereche.cpp"
#endif // NOD_PERECHE_H
