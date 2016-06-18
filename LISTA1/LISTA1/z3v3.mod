/* Zmiany i dzielnice patroli */
set P;                                  /* DZIELNICE */
set Z;                                  /* ZMIANY */
#set A, within P cross Z;                /* GRAF PxZ */
param psuml{i in P};                    /* sumaryczne wymaganie dzielnicy */
param pl{i in P, j in Z};               /* wymagania   dzielnic */
param pu{i in P, j in Z};               /* mozliwosci  dzielnic */
param zsuml{j in Z};                    /* sumaryczne wymaganie zmiany */
param zl{j in Z, i in P};               /* wymagania   zmian */
param zu{j in Z, i in P};               /* mozliwosci  zmian */
param d:= 1;                            /* koszt wyslania radiowozu */
var x{i in P,j in Z} >= 0;              /* zmienna do operowania iloscia radiowozow */
# var y{j in Z, i in P} >= 0;
check
# MINIMALIZUJ KOSZT, w ktorym jest optymalna
minimize cost: sum{i in P, j in Z} d * x[i,j];
#minimize cost: sum{j in Z, i in P} d * y[j,i];

# OBSERWUJAC PRZY TYM, ze MAXYMALNIE MOZE DOSTAC
s.t. supply{i in P}: forall{j in Z} x[i,j] <= pu[i,j]; # wzgledem DZIELNIC
#s.t. supply{j in Z}: forall{i in P} x[i,j] <= zu[j,i]; # wzgledem ZMIAN

# WYMAGAJAC, ze DOSTANIE CO NAJMNIEJ
s.t. demand{i in P}: forall{j in Z} x[i,j] >= pl[i,j]; # wzgledem DZIELNIC
#s.t. demand{j in Z}: forall{i in P} x[i,j] >= zl[j,i]; # wzgledem ZMIAN
s.t. demand{i in P}: sum{j in Z} x[i,j] >= psuml[i]; # sumarycznie wzgledem DZIELNIC
#s.t. demand{j in Z}: sum{i in P} x[i,j] >= zsuml[j]; # sumarycznie wzgledem ZMIAN

solve;

printf 'Minimum Cost = %.2f\n', Cost;


data;

# ZBIOR DZIELNIC
set P := p1 p2 p3;

# ZBIOR ZMIAN
set Z := z1 z2 z3;

# MIN DZIELNIC
param pl : p1  p2  p3 :=
        z1  2   3   5
        z2  4   6   7
        z3  3   5   6;

# MAX DZIELNIC
param pu : p1  p2  p3 :=
        z1  3   5   8
        z2  7   7   12
        z3  5   10  10;

# MIN ZMIAN
param zl : z1   z2  z3 :=
        p1  2   4   3
        p2  3   6   5
        p3  5   7   6;

# MAX ZMIAN
param zu :  z1  z2  z3 :=
        p1  3   7   5
        p2  5   7   10
        p3  8   12  10;

# sumaryczny MIN POPYT DZIELNIC
param psuml :=  p1       10
                p2       20
                p3       13;

# sumaryczny MIN POPYT ZMIAN
param zsuml :=  z1       10
                z2       20
                z3       18;
end;

