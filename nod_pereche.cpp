#include <istream>
#include <ostream>

using namespace std;

istream& operator>>(istream& i, nod_pereche& p) {
        i>>p.i1;
        i>>p.i2;
        return i;
        };
ostream& operator<<(ostream& i, nod_pereche p) {
        i<<"("<<p.i1<<", "<<p.i2<<") ";
        return i;
    };
