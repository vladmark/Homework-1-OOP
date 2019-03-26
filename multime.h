#ifndef MULTIME_H
#define MULTIME_H
#include <istream>
#include <ostream>
using namespace std;

struct nod {
    int val;
    nod* urm;
};
class multime_perechi;
class multime
{
    nod* rad;
    int l;
    nod* ult;
public:
    multime();
    ~multime();
    multime(int);
    multime(const multime& );
    bool apartine(int );
    multime operator=(const multime&);
    multime multimifica (int*, int);
    multime operator+(multime&);
    multime operator*(multime&);
    multime operator-(multime&);
    int operator[](int);
    friend istream& operator>>(istream&, multime&);
    friend ostream& operator<<(ostream&, multime);
    friend multime_perechi prod_cart(multime&, multime&);
};

#include "multime.cpp"

#endif // MULTIME_H
