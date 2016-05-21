# ARKADIUSZ LEWANDOWSKI 208836
/* Transportation Problem - Lotniska i firmy paliwowe */

set F;                      /* firmy */
set L;                      /* lotniska */

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
end;

