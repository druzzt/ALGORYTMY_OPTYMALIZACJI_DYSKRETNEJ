#pragma once
#define INFORM(x,y) (printf("Wrong usage of %d/%d arguments:\n %s -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res\n",y-1,6,x),abort())
#define _ER_CHCK(x) (((x)<0) ? printf("Prog. Status: %d\n",(x)) : printf(""))
#define _COM_DJIKSTRA() (_LOG_SYSTEM("djikstra"))
#define _COM_DIAL() (_LOG_SYSTEM("dial"))
#define _COM_RADIXHEAP() (_LOG_SYSTEM("radixheap"))
#define _COM_WRONGNAME() (_LOG_SYSTEM("wrong name!"), printf("wrong program name!\n"),abort())
#define _COM_ARGSOK()	(_LOG_SYSTEM("arguments ok!"))
#define _LOG_CTIME(x) (ctime(&x))
#define _LOG ">> .log.txt"
#define _LOG_MSG(x) ("echo \"compiled("__TIME__") " #x "\"" _LOG)
#define _LOG_SYSTEM(x) (system(_LOG_MSG(#x)))
#define _STR(x,y) (strcpy((x),(y)))
