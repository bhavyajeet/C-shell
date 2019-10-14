CFLAGS = -c -g -Wall

all :shell

shell : main.o cmdhandle.o echo.o nightswatch.o pwd.o	unimplemented.o history.o cd.o ls.o pinfo.o setenv.o sighnd.o bghand.o jobs.o overkill.o redir.o cronjob.o uparrow.o
	gcc  ./cmdhandle.o ./pwd.o  cd.o ls.o  pinfo.o unimplemented.o history.o main.o -lreadline nightswatch.o echo.o setenv.o sighnd.o bghand.o jobs.o overkill.o redir.o cronjob.o uparrow.c -o shell  


main.o : main.c
	gcc $(CFLAGS)   main.c -lreadline

cmdhandle.o : cmdhandle.c
	gcc $(CFLAGS) cmdhandle.c


cronjob.o : cronjob.c
	gcc $(CFLAGS) cronjob.c

echo.o : echo.c
	gcc $(CFLAGS) echo.c

nightswatch.o : nightswatch.c
	gcc $(CFLAGS) nightswatch.c

pwd.o : pwd.c
	gcc $(CFLAGS) pwd.c

unimplemented.o : unimplemented.c 
	gcc $(CFLAGS) unimplemented.c

history.o : history.c
	gcc $(CFLAGS) history.c

cd.o : cd.c 
	gcc $(CFLAGS) cd.c 

ls.o : ls.c
	gcc $(CFLAGS) ls.c

pinfo.o : pinfo.c
	gcc $(CFLAGS) pinfo.c
	
setenv.o : setenv.c
	gcc $(CFLAGS) setenv.c

sighnd.o : sighnd.c
	gcc $(CFLAGS) sighnd.c

bghand.o : bghand.c
	gcc $(CFLAGS) bghand.c

jobs.o : jobs.c
	gcc $(CFLAGS) jobs.c

uparrow.o : uparrow.c
	gcc $(CFLAGS) uparrow.c

overkill.o : overkill.c
	gcc $(CFLAGS) overkill.c


redir.o : redir.c
	gcc $(CFLAGS) redir.c

clean:
	rm -r *.o shell
