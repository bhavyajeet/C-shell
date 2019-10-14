# SHELL

This is a basic replica of bash written in C with all the built-ins , other commands and additional features like piping , redirection etc implemented from scratch 
```
make 
./shell
 ```
* Clean: make clean 

Features implemented 
1) A shell prompt of the form: <username@hostname:curr_dir> with path relative to home 
2) home directory is the directory from which the shell is invoked (as per the assignment pdf)
2) Semi-colon (;) separated commands 
3) & after any command  to run a process in background
4) Some built in commands like cd ,echo ,ls , and pwd re-implemented 
5) Type quit or exit to  exit the shell 
6) Implements foreground and background processes 
7) Process name and id printed when background process terminates 
8) Type pinfo in the prompt to print: pid, process status, memory and executable path (on Linux machines) 
9) As opposed to bash , also prints asynchronously the process name , id and exit status whenever a background process is terminated is terminated to stderr
10) Can take multiple semi colon separated commands as input and execute them sequentially 
11) apart from user defined commands , rest all can be executed in foreground or background 
12) Inpunt Output redirection can be implemented using < , > and >> .
13) Piping of various commands is possible along with file redirection as well 
14) more user defined commands like jobs , kjob , fg , bg , overkill , setenv and unsetenv are implemented 


Bonus:
 1) **nightswatch** \
 1.1) **interrupt** \
 prints the number of times the CPU(s) have been interrupted by the keyboard at every n seconds untill "q" is pressed  
 1.2) **dirty** \
 print the size of the part of the memory which is dirty every n seconds until q is pressed
 
 2)history 
if given with a argument number n , prints the previous n commands that the shell has executed . default value of n is teken to be 10 . preserves history accross shell sessions.
a command beginning with " " is not added to the history (just like bash)

3) **Cronjob**  
<usage> cronjob -c command -t t -p p 
runs a command c every t seconds untill p seconds have passed 

4)Uparrow/Downarrow (without readline)
if the up key is pressed k times and down key l times , the (K-l)th previous command from history is executed . 



Files in Directory:-

1) main.c :- contains the main()  ,print_prompt() and getdir() function . main function calls the print_prompt function ,which is used to print the prompt using getdir() function for the directory to be displayed and take command input .

2) cmdhandle.c :- contains -\
    splitcmd () - to tokenise the commands using ";". separate multiple commands \
    splitargs() - to separate the arguments of every command and store them in an array \
    execute() - to call the self-implemented built in commands or pass others to execvp \
    checkand()- check if a command contains & , to run it separately in the background \
    commandexec()- to call all the above mentioned funtions 


3) ls.c  :- contains ls ,lsl ,get_print_info() function. It handles ls command .\
**FEATURES** \
ls -
works with multiple directories given as input 
displays the executables in green and directries in blue 
works with -l , -a , -al/-la flags (in any order ) 
also displays total blocks of 1024 bytes occupied by any directory

4) echo.c :- contains echo function . It handles echo command.\
 **FEATURES** \
 ECHO -
works with -n flag to give no newline at the end 
removes quotes if given in the beginning and end
also works with environment variables when preceded by a $ sign .

5) cd.c :- contains cd function . It handles cd command. \
**cd FEATURES**- \
works with cd - to jump to any previous directory 
use cd or cd ~ to jump to home 


6) headerfile.h :- contains all the definitions of functions and the definitions of the constants to be used.

7) pinfo.c :- contains pinfo function. It prints the process related info of our shell program. \
**FEATURE pinfo**  \
prints the process related information corresponding to the pid given with the command or to the  
the shell if no pid given

8) pwd.c   :- contains pwd function . It handles pwd command.

9) history.c :- contains the addhis(),inithis(),exithis() and history() functions , handles the history command  
**HISTORY FEATURES** \
a command beginning with " " is not added to the history (just like bash)

10) nightswatch :- contains the nightswatch(), dirty(), interrupt(),keyDown() function . handles the nightswatch command 

11) unimplemented.c :- contains the unimplemented() and the backquit() function .handles all commands that are not manually implemented . also handles the background processeing of commands and printing when they are killed .

12) setenv.c :- contains the setenv and the unsetenv functions 

13) sighnd.c :- contains the signal handlers for Ctrl-C , Ctrl-Z and Ctrl-\

14) bghand.c :- has the function for bg command which sends a running signal to any stopped background process 

15) overkill.c :- has the function for overkill command to kill all background process 

16) uparrow.c :- has the uparrow() and checkuparrow() function . handles the implementation for up/down arrow keys 

17) cronjob.c :- has the cronjob() function which handles the cronjob command \
**CRONJOB FEATURES**   
arguments can be given in any order and the command can be of any number of words 

18) redir.c :- has the tagpiper() function which handles the piping and redirection of commands and the splitpipe() function which splits various commands separated by pipe 

19) jobs.c :- contains the jobs() function , kjobs() function , fg() function and the checkallkill() function 
handles the fg commmand , kjob command ,and jobs commad 
**FG Feature** \
- if no argument is given the process on top of the jobs is taken as argument 


Incase the prompt doesn't appear after a background process is terminated or for any other reason, press ENTER.
