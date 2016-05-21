# ARKADIUSZ LEWANDOWSKI 208836
/* The shortest path problem in a directed graph G=<V,A> - Miasta i najkrótsza trasa */

param n, integer, >= 2; # the number of nodes 

set V:={1..n};                  # the set of nodes 
set A  within V cross V;        # the set of arcs 
param max_time, integer, >=0;
param c{(i,j) in A}, >= 0;      # cij  the cost of arc (i,j)
param time{(i,j) in A}, >= 0;   # timeij the time of an arc (i,j)
param s, in V, default 1;       # source s  
param t, in V, != s, default n; # sink t 

var x{(i,j) in A}, integer, >= 0, <= 1;  # calkowitoliczbowosc
/* x[i,j] =1 if  arc belongs to the shortest path, 0 otherwise*/

minimize Cost: sum{(i,j) in A} c[i,j]*x[i,j];
s.t. node{i in V}:
   sum{(j,i) in A} x[j,i] + (if i = s then 1)
   = 
   sum{(i,j) in A} x[i,j] + (if i = t then 1);
s.t. demand: sum{(i,j) in A} time[i,j]*x[i,j] <= max_time;
solve;

display Cost;
display {(i,j) in A} x[i,j];
display sum{(i,j) in A} time[i,j]*x[i,j];
display sum{(i,j) in A} c[i,j]*x[i,j];
end;
