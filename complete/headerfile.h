char home [100];
char  cmdlist[15][50] ;
char prevdir[100];
char currpromt[200];
int backpointer ;
void pwd();

void nightswatch(char **);
void cronjob(char **);

void sigquit();

void uparrow(char *);

void addhis (char * );
void history (char **);
void exhis();
void inithist();

int checkuparrow(char *);

void execute(char *);

void tagpiper (char*);


char ** splitargs(char *);

void bghand(char **);
int checkand(char **);

void  print_promt ( );
void getdir(char *);
int  cd (char **);
char * commandexec(char *);
void ls (char **);
void green();
void blue ();
void reset();
void pinfo (char **);
void echo (char **);
char  his_path[200] ;
void unimplemented (char **  ,int );

void seten(char**);
void unseten(char**);

void sigtstp(int);
void ctrlchnd(int);

struct bid{
    int pid;
    char * command;
    int index;
    int status;
};

struct bid runproc;

struct hist{
    char  history[20][100] ;
    int histins;
    int histed;
};
struct hist his;
void unimplemented (char **  ,int );
void backquit(int sig);
struct bid backarray[128];

void jobs(char **);


void killemall(char **);
void kjobs(char **);
void fg(char **);


int mypid;


