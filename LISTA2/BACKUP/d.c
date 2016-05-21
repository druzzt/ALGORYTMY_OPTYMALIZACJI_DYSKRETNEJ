#include "headers.h"

/*
argv[0] -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res
argv[0] -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res
*/
int programchecker(int argc,char *argv[])
{
	if(argc	>	sizeofargc++ 		&&
	argc	<=	maxnumofargs)
	{
	if(argc	>	sizeofargc++ 		&&
	argv[dflag][fletter] == d)
	{
	if(argc	>	sizeofargc++ 		&&
	argv[grext][zletter] != eof)
	{
	if(argc	>	sizeofargc++ 		&&
	((argv[ssflag][fletter] == s 	&&
	argv[ssflag][sletter] 	== s)	||
	(argv[p2pflag][fletter]	== p 	&&
	argv[p2pflag][sletter]	== two 	&&
	argv[p2pflag][tletter]  == p)))
	{
	if(argc	>	sizeofargc++ 		&&
	argv[ssext][zletter] != eof)
	{
	if(argc	>	sizeofargc++ 		&&
	((argv[ossflag][fletter] == o 	&&
	argv[ossflag][sletter]   == s 	&&
	argv[ossflag][tletter]   == s)	||
	(argv[op2pflag][fletter] == o 	&&
	argv[op2pflag][sletter]  == p 	&&
 	argv[op2pflag][tletter]  == two &&
 	argv[op2pflag][ftletter] == p)))
	{
	if(argc	>	sizeofargc++ 		&&
	argv[ossext][zletter] != eof)
	{

	// DO THINGS HERE
		

	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	return 0;
}

int main(int argc, char *argv[])
{
	errno = programchecker(argc, argv);

	return errno;
}