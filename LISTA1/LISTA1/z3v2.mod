param n, integer, >= 2;                              # ilosc wierzcholkow
set V:={1..n};                                       # zbior wierzcholkow
set V1 within V;                                     # sources - supply nodes
set V3 within V;                                     # sinks - demand nodes
check: (V1 inter V3) within {};                      # check if V1 and V3 are disjoint sets

set V2:=V diff V1 diff V3;                           # transshipment nodes
set A, within V cross V;                             # the set of arcs

set S{i in V}:={j in V: (i,j) in A};                 # the set of direct successors of i
set P{i in V}:={j in V: (j,i) in A};                 # the set of direct predecessors of i

param a{V1}>=0;                                      # the supplies
param b{V3}>=0;                                      # the demands

#check sum{i in V1} a[i] = sum{i in V3} b[i];         # check if the problem is balanced

param c{A}>= 0;                                      # the arc costs
param u{A}>= 0;                                      # the capacities of arcs
param l{A}>= 0;                                      # the lower bounds
var x{(i,j) in A} >= l[i,j], <= u[i,j];              # the flow on arc (i,j)

minimize Cost: sum{(i,j) in A} c[i,j]*x[i,j];


s.t. supplies   {i in V1}: sum{j in S[i]} x[i,j]  -  sum{j in P[i]} x[j,i]      =  a[i];
s.t. trans      {i in V2}: sum{j in S[i]} x[i,j]  -  sum{j in P[i]} x[j,i]      =  0;
s.t. demands    {i in V3}: sum{j in S[i]} x[i,j]  -  sum{j in P[i]} x[j,i]      = -b[i];

solve;

display 'flow';
display{ (i,j) in A}:i,j,'=',x[i,j];
printf '\n cost is %d',Cost;
######################------------------##############################################
######################                  ##############################################
######################   DATA SECTION   ##############################################
######################                  ##############################################
######################------------------##############################################
data;
param n := 6;

set V1:=1 2 3;
set V3:=4 5 6;

param a:=[1] 10 [2] 20 [3] 13;
param b:=[4] 10 [5] 20 [6] 18;

# A is set of Edges
# A(1 4) = p1 -> z1 ||
# A(3 5) = p3 -> z2 ||
# A(2 6) = p2 -> z3  ;
# (l,u,c) = (min liczb radiowoz p/z, max liczb radiowoz p/z, cost)
param : A : l   c   u :=
1 4     2   1   3
1 5     4   1   7
1 6     3   1   5
2 4     3   1   5
2 5     6   1   7
2 6     5   1   10
3 4     5   1   8
3 5     7   1   12
3 6     6   1   10;

end;

