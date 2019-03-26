
#include <istream>
#include <ostream>
using namespace std;

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

multime_perechi prod_cart(multime& A, multime& B) {
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
