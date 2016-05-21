
#include "headers.h"
/* PROTOTYPES */
int test();
/*
argv[0] -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res
argv[0] -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res
*/
INTEGER V,E;
INTEGER *seeked;
/* FORMAL SPECS *///#######################################
/** Const Complexity */
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
/** Const Complexity */
int programnamechecker(char *argv[])
{
	if(argv[progflag][sletter]== d)  {
	if(argv[progflag][tletter]== j  ||
	   argv[progflag][tletter]== i)  {
	if(argv[progflag][ftletter]==i  ||
	   argv[progflag][ftletter]==j)  {
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
/* LIST INITIALIZERS *///#######################################
/** O(n) complexity */
List *tab2list(List *head, Tablica *tablica)
{
	List *lis, *lis2, *elt;
	INTEGER i = 0;
	printf("E=" I_FORMAT "\n",E);
	ARLOC(lis, List);
	for(i=1; i<=E; i++){
		if(verbose)
		printf("" I_FORMAT ". "  I_FORMAT" " I_FORMAT" " I_FORMAT "\n",i,
		INT(tablica[i].s),INT(tablica[i].t) ,INT(tablica[i].v) );
		//if ( (lis = (el*)malloc(sizeof(el))) == NULL) exit(-1);
		ARLOC_A(lis, List,1);
 		lis->tab.s = tablica[i].s;
 		lis->tab.t = tablica[i].t;
 		lis->tab.v = tablica[i].v;
 		PUSH_BACK(head,lis);
 	}
 	//PRINT(head,elt,printf);
	//free(tablica);
 	return head;
}
/* FILE READERS *///#######################################

/** O(e) complexity */
Tablica *readfile(char argv[], FILE *fp)
{
	if (!(fp = fopen (argv, "r"))) {
        fprintf (stderr, "error: file open failed %s.\n",argv);
        errno=FAILURE;
    }
    //char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char line_type, trash[64];
    printf("READING: <%s>\n",argv);
    INTEGER i=1;
    Tablica* itablica;
    int set = 0;
    List *lis, *lis2, *elt;
    while ((fscanf(fp, "%c", &line_type)) != -1) 
    {
    	if(verbose)
    	printf("%c ",line_type);
     	switch(line_type){
     		case comment_symbol:;
     						fgets(trash, sizeof(trash), fp); 
     						break;
     		case problem_symbol:; 
     						fscanf(fp, " sp "I_FORMAT" "I_FORMAT"", &V, &E);
     						if(set==0) (itablica=malloc((E+2) * sizeof(Tablica)),set=1);
     						if(verbose)
     						printf(" "I_FORMAT" "I_FORMAT"\n",V,E);
     						break;
     		case arc_symbol:; 
     						INTEGER s,t,v;
     					 	fscanf(fp, ""I_FORMAT" "I_FORMAT" "I_FORMAT"", &s,&t,&v); 
     					 	if(verbose)
     					 	printf(""I_FORMAT" "I_FORMAT" "I_FORMAT"\t"I_FORMAT" ",s,t,v,i);
     						ARLOC_A(itablica[i].s,INTEGER,1);
     						VASSIGNP(itablica[i].s,s);
     						ARLOC_A(itablica[i].t,INTEGER,1);
     						VASSIGNP(itablica[i].t,t);
     						ARLOC_A(itablica[i].v,INTEGER,1);
     						VASSIGNP(itablica[i].v,v);
     						i++;
     						break;
     		case source_symbol:;
     						break;

     		default: break;

     	}
    }
    fclose (fp);
	return itablica;
}
int test2(List *head, Queue *Q, INTEGER S)
{
	List *hlis, hlist;
	Queue *Qsli, Qslit;

	

	return 0;
}


int main(int argc, char *argv[])
{
    
	((errno = programnamechecker(argv)),	_ER_CHCK(errno));
	((errno = programchecker(argc, argv)),	_ER_CHCK(errno));
	
	time(&t1);
    printf("%s",_LOG_CTIME(t1));
    List *head = NULL;
	Queue *Q = NULL;
    Tablica *itablica = readfile(argv[grext], D_file);
    head = tab2list(head,itablica);
    INTEGER szukane =1;

    for(i=1;i<=szukane;i++){
    	test2(head,Q,i);
    }

	time(&t2);
	printf("%s",_LOG_CTIME(t2));
	double difference = difftime(t2, t1);
	if(verbose)
	(printf("%f with proc.clocks/s = %d\n",difference,CLOCKS_PER_SEC),
	printf("Clock's ticks in summary: %f\n", difference*CLOCKS_PER_SEC));
	// SAVE OUTPUT

	
	return errno;
}










































//((errno = readfile(argv[grext], D_file)),			_ER_CHCK(errno));
    //((errno = readfile(argv[ssext], SS_P2P_file)),	_ER_CHCK(errno));
    //((errno = readfile(argv[ossext],OSS_OP2P_file)),	_ER_CHCK(errno));
    







