
#include "headers.h"
/* PROTOTYPES */
int test();
/*
argv[0] -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res
argv[0] -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res
*/
int programchecker(int argc,char *argv[])
{
	if(argc	>	sizeofargc++ 		&&
	argc	<=	maxnumofargs){
	if(argc	>	sizeofargc++ 		&&
	argv[dflag][fletter] == d){
	if(argc	>	sizeofargc++ 		&&
	argv[grext][zletter] != eof){
	if(argc	>	sizeofargc++ 		&&
	((argv[ssflag][fletter] == s 	&&
	argv[ssflag][sletter] 	== s)	||
	(argv[p2pflag][fletter]	== p 	&&
	argv[p2pflag][sletter]	== two 	&&
	argv[p2pflag][tletter]  == p))){
	if(argc	>	sizeofargc++ 		&&
	argv[ssext][zletter] != eof){
	if(argc	>	sizeofargc++ 		&&
	((argv[ossflag][fletter] == o 	&&
	argv[ossflag][sletter]   == s 	&&
	argv[ossflag][tletter]   == s)	||
	(argv[op2pflag][fletter] == o 	&&
	argv[op2pflag][sletter]  == p 	&&
 	argv[op2pflag][tletter]  == two &&
 	argv[op2pflag][ftletter] == p))){
	if(argc	>	sizeofargc++ 		&&
	argv[ossext][zletter] != eof){
	_COM_ARGSOK();
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	return (SUCCESS);
}

int programnamechecker(char *argv[])
{
	if(argv[progflag][sletter]==d)  {
	if(argv[progflag][tletter]==j  ||
	   argv[progflag][tletter]==i)  {
	if(argv[progflag][ftletter]==i ||
	   argv[progflag][ftletter]==j) {
	_COM_DJIKSTRA();
	PATH_PROB=1;
	}
	if(argv[progflag][ftletter]==a){
	_COM_DIAL();
	PATH_PROB=2;
	}}else{
	INFORM(argv[progflag],PATH_PROB);
	_COM_WRONGNAME();
	}}
	else if(argv[progflag][sletter]==r){
	_COM_RADIXHEAP();
	PATH_PROB=3;
	}else{
	INFORM(argv[progflag],PATH_PROB);
	_COM_WRONGNAME();
	}
	return (SUCCESS);
}

/**
* parseline() - COMPLEXITY O(k) 
* k - # of letters in a single line
*/
int parseline(char *line,unsigned long read)
{
	switch(line[0])
 	{
     		case 'c': 
     		printf("%zu\t<--|\t|%s",read, line); 
     		break;
     		case 'p': 
     		printf("%zu\t<--|\t|%s",read, line); 
				char * pch;
				pch = strtok (line," ");
				pch = strtok (NULL," ");
				while (pch != NULL)
				{
					if (strcmp(pch, "sp") == 0) 
					{
					  printf("shortest path\n");
					} 
					else
					{
						printf("%s",pch);
					}
					pch = strtok (NULL, " ");
				}
     		break;
     		case 'a': 
     		printf("%zu\t<--|\t|%s",read, line); 
     		uint_fast64_t s,t,v;
     		char str[3];
     		sscanf(line, "%s %llu %llu %llu",str, &s,&t,&v );
     		//printf(">%llu\t>%llu\t>%llu\n",s,t,v);

     		break;
     		case 's': 
     		printf("%zu\t<--|\t|%s",read, line); 

     		break;
     		case 'f': 
     		printf("%zu\t<--|\t|%s",read, line); 

     		break;
     		case 'g': 
     		printf("%zu\t<--|\t|%s",read, line); 

     		break;
     		case 't': 
     		printf("%zu\t<--|\t|%s",read, line); 

     		break;
     		case 'q': 
     		printf("%zu\t<--|\t|%s",read, line); 

     		break;
     		case 'd': 
     		printf("%zu\t<--|\t|%s",read, line); 

     		break;
     		default: printf("missing type of line\n"); 
	}
	return (SUCCESS);
}

/** 
* readfile() - COMPLEXITY O(n * k) * parseline = O(n*k^2);
* n - # of lines
* k - # of letters in a single line
*/
int readfile(char argv[], FILE *fp)
{
	if (!(fp = fopen (argv, "r"))) {
        fprintf (stderr, "error: file open failed %s.\n",argv);
        errno=FAILURE;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("READING: <%s>\n",argv);
    while ((read = getline(&line, &len, fp)) != -1) 
    {
     	parseline(line,read);
    }

    free(line);
    fclose (fp);
	return SUCCESS;
}


int main(int argc, char *argv[])
{
    
	((errno = programnamechecker(argv)),	_ER_CHCK(errno));
	((errno = programchecker(argc, argv)),	_ER_CHCK(errno));
	
	time(&t1);
    printf("%s",_LOG_CTIME(t1));
    
    ((errno = readfile(argv[grext], D_file)),		_ER_CHCK(errno));
    ((errno = readfile(argv[ssext], SS_P2P_file)),	_ER_CHCK(errno));
    ((errno = readfile(argv[ossext],OSS_OP2P_file)),_ER_CHCK(errno));
    

	time(&t2);
	printf("%s",_LOG_CTIME(t2));
	double difference = difftime(t2, t1);
	printf("%f with proc.clocks/s = %d\n",difference,CLOCKS_PER_SEC);	
	// SAVE OUTPUT
	

	// SAVE THE TIME DIFFERENCE TO A FILE
	
	return errno;
}




























