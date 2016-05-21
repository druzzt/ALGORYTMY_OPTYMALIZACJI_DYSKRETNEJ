#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "bilist.h"
#include <unistd.h>
#include <ctype.h>
#include "macroes.h"


int   errno 		= 0; 		// error indicating flag

short maxnumofargs 	= 7; 		// maximum number of arguments passed to program
short progflag 		= 0;		// which number in arguments is program name
short dflag 		= 1; 		// which number in arguments is -d flag
short ssflag 		= 3; 		// which number in arguments is -ss flag
short ossflag 		= 5; 		// which number in arguments is -oss flag
short grext 		= 2;		// extension number for gr flag - .gr
short ssext 		= 4;		// extension number for ss flag - .ss
short ossext 		= 6;		// extension number for oss flag - .ss.res
short p2pflag 		= 3;		// which number in arguments is -p2p flag
short op2pflag 		= 5;		// which number in arguments is -op2p flag

short sizeofargc 	= 0;		// current size of argc parameter in programchecker()
short zletter 		= 0;		// zero letter in flagchecking
short fletter 		= 1;		// first letter in flagchecking
short sletter 		= 2;		// second letter in flagchecking
short tletter 		= 3;		// third letter in flagchecking
short ftletter		= 4;		// fourth letter in flagchecking

char  d 			= 'd';		// d-letter in flagchecking
char  eof 			= ' ';		// eof or missing parameter in flagchecking
char  s 			= 's';		// s-letter in flagchecking
char  p 			= 'p';		// p-letter in flagchecking
char  two 			= '2';		// 2-letter in flagchecking
char  o 			= 'o';		// o-letter in flagchecking


/*
c Linia zaczynajaca sie od c jest komentarzem
c Przyklad sieci z kosztami plik plik_z_danymi.gr
c
p sp 6 8
c p (problem) sp (shortest path) siec zawiera 6 wierzcholkow i 8 lukow c wierzcholki ponumerowane sa od 1 do 6
c
a 1 2 17
c luk z wierzcholka 1 do wierzcholka 2 o koszcie 17
c
a 1 3 10
a242
a350
a430
a463
a520
a 5 6 20
*/

/*
c
c Przyklad pliku zrodla.ss, w ktorym zadane sa zrodla
c
p aux sp ss 3
c podane sa 3 zrodla w nastepujacych liniach
c algorytm powinien policzyc nakrotsze sciezki miedzy zrodlem 1
c i wszystkimi wierzcholkami sieci
c zadanej w pliku plik_z_danymi.gr, nastepnie miedzy zrodlem 3 i wszystkimi... c
s1
s3
s5
*/

/*
c Przyklad pliku wynikowego wyniki.ss.res
c dla problemu najkrotszych sciezek z jednym źródłem
p res sp ss dikstry
c ----------------------------------------------------------------
c
c wyniki testu dla sieci zadanej w pliku plik_z_danymi.gr i zrodel zrodla.ss:
f plik_z_danymi.gr zrodla.ss
c
c graf zawiera 1024 wierzcholkow, 4096 lukow, z kosztami nalezacymi do [0,1024]: g 1024 4094 0 1024
c
c sredni czas wyliczenia najkrotszych sciezek miedzy zrodlem a wszystkimi
c wierzcholkami wynosi 12.71 msec:
t 12.71
*/

/*
c Przyklad pliku pary.p2p (point-to-point), w ktorym zadane sa pary wierzchołkow c miedzy, ktorymi nalezy policzyc najkrotsze sciezki
c
p aux sp p2p 3
cpodanesa3pary(1,5),(5,1) i(1,2) c
q15
q51
q12
*/

/*
c Przyklad pliku wynikowego wyniki.p2p.res dla
c problemu najkrotszej sciezki miedzy para wierzcholkow
c wyniki testu dla sieci zadanej w pliku plik_z_danymi.gr i par pary.p2p: f plik_z_danymi.gr pary.p2p
c
c siec ma 2048 wierzcholkow, 8192 lukow, koszty naleza do przedzialu [0,1024]:
g 2048 8192 0 1024
c
c dlugosci najkrotszych sciezek, np. miedzy para (1,5) dlugosc sciezki wynosi 4351: d 1 5 4351
d 5 1 7541
d 1 2 231
*/

/*
• Podobnie dla algorytmr Dial:
dial -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res
dial -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res
• Podobnie dla algorytmr Radix Heap:
radixheap -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res 
radixheap -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res
*/