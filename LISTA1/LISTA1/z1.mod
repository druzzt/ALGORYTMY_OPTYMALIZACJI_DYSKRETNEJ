/* Lotniska i firmy paliwowe */

set F; /* firmy */
set L; /* lotniska */

param a{j in F};            /* mozliwosci firm */
param w{i in L};            /* wymagania lotnisk */
param d{i in L, j in F};    /* koszt za galon */
var x{i in L, j in F} >= 0; /* zmienna do operowania iloscia galonow paliwa */

# MINIMALIZUJ KOSZT, w ktorym suma po zl/galon * ilosc jest optymalna
minimize cost: sum{i in L, j in F} d[i,j] * x[i,j];

# OBSERWUJAC PRZY TYM, ze firma nie moze dac wiecej niz ma
s.t. supply{j in F}: sum{i in L} x[i,j] <= a[j];

# WYMAGAJAC, ze kazde lotnisko dostanie przynajmniej tyle ile wymaga
s.t. demand{i in L}: sum{j in F} x[i,j] >= w[i];

solve;

printf 'Minimum Cost = %.2f\n', cost;
display{i in L, j in F} x[i,j];

data;

# ZBIOR FIRM
set F := F1 F2 F3;

# ZBIOR LOTNISK
set L := L1 L2 L3 L4;

# MAX PODAZ FIRM
param a := F1       275000
           F2       550000
           F3       660000;

# MIN POPYT LOTNISK
param w := L1       110000
           L2       220000
           L3       330000
           L4       440000;

# CENA ZA GALON Lotnisko x Firma
param d :   F1       F2      F3 :=
        L1  10       7       8
        L2  10       11      14
        L3   9       12      4
        L4  11       13      9;

end;

