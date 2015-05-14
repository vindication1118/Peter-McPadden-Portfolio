// 
// tsh - A tiny shell program with job control
// 
// <Put your name and login ID here>
//Peter McPadden pemc3641

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>

#include "globals.h"
#include "jobs.h"
#include "helper-routines.h"

//
// Needed global variable definitions
//

static char prompt[] = "tsh> ";
int verbose = 0;

//
// You need to implement the functions eval, builtin_cmd, do_bgfg,
// waitfg, sigchld_handler, sigstp_handler, sigint_handler
//
// The code below provides the "prototypes" for those functions
// so that earlier code can refer to them. You need to fill in the
// function bodies below.
// 

void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

//
// main - The shell's main routine 
//
int main(int argc, char **argv) 
{
  int emit_prompt = 1; // emit prompt (default)

  //
  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  //
  dup2(1, 2);

  /* Parse the command line */
  char c;
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h':             // print help message
      usage();
      break;
    case 'v':             // emit additional diagnostic info
      verbose = 1;
      break;
    case 'p':             // don't print a prompt
      emit_prompt = 0;  // handy for automatic testing
      break;
    default:
      usage();
    }
  }

  //
  // Install the signal handlers
  //

  //
  // These are the ones you will need to implement
  //
  Signal(SIGINT,  sigint_handler);   // ctrl-c
  Signal(SIGTSTP, sigtstp_handler);  // ctrl-z
  Signal(SIGCHLD, sigchld_handler);  // Terminated or stopped child

  //
  // This one provides a clean way to kill the shell
  //
  Signal(SIGQUIT, sigquit_handler); 

  //
  // Initialize the job list
  //
  initjobs(jobs);

  //
  // Execute the shell's read/eval loop
  //
  for(;;) {
    //
    // Read command line
    //
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }

    char cmdline[MAXLINE];

    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      app_error("fgets error");
    }
    //
    // End of file? (did user type ctrl-d?)
    //
    if (feof(stdin)) {
      fflush(stdout);
      exit(0);
    }

    //
    // Evaluate command line
    //
    eval(cmdline);
    fflush(stdout);
    fflush(stdout);
  } 

  exit(0); //control never reaches here
}
  
/////////////////////////////////////////////////////////////////////////////
//
// eval - Evaluate the command line that the user has just typed in
// 
// If the user has requested a built-in command (quit, jobs, bg or fg)
// then execute it immediately. Otherwise, fork a child process and
// run the job in the context of the child. If the job is running in
// the foreground, wait for it to terminate and then return.  Note:
// each child process must have a unique process group ID so that our
// background children don't receive SIGINT (SIGTSTP) from the kernel
// when we type ctrl-c (ctrl-z) at the keyboard.
//
void eval(char *cmdline) 
{
  /* Parse command line */
  //
  // The 'argv' vector is filled in by the parseline
  // routine below. It provides the arguments needed
  // for the execve() routine, which you'll need to
  // use below to launch a process.
  //
  char *argv[MAXARGS];
  //other initializations
  pid_t pid; //process id
  sigset_t mask; //for sigprocmask later on

  //
  // The 'bg' variable is TRUE if the job should run
  // in background mode or FALSE if it should run in FG
  //
  int bg = parseline(cmdline, argv); 
  if (argv[0] == NULL){  
    return;   /* ignore empty lines */
  }
  
  //If this is a built in command, builtin will run the command and return 1, which gets swapped to 0 so
  //this section doesn't run, if it isn't a built in command, builtin_cmd returns 0 which gets flipped to 1
  if(!builtin_cmd(argv)){ 
	  sigemptyset(&mask); //make sure this is empty
	  sigaddset(&mask, SIGCHLD); 
	  sigprocmask(SIG_BLOCK, &mask, NULL);
	  //block sigchild until we are done forking, prevents 
	  //race condition, we guarantee that the child has been added to the jobs list before 
	  //a sigchild signal is caught and sent to the handler, which calls deletejob()
	  //note signals are blocked, not queued, so if another signal comes before a sigchld, it won't 'hear'  it
	  
	  //forking returns a 0 to the child and nonzero to parent, so this one says if child do command
	  if((pid = fork()) == 0){
		 sigprocmask(SIG_UNBLOCK, &mask, NULL); //we don't want sigchld blocked in the child
		 //since it has no children/jobs to add
		 setpgid(0, 0); //done as per writeup instructions 
		 if (execve(argv[0], argv, environ) < 0) { //standard use of execve, will not ret if
			 //no errors, runs program
			 printf("%s: Command not found.\n", argv[0]); //format specified by tshref output
			 exit(0); //kills child on error, sigchld is sent to parent, 
		 }
	  }
	  
	  if (!bg){ //if not running in background, we do upkeep then wait until child terminates
		  addjob(jobs, pid, FG, cmdline); //add job to the joblist
		  sigprocmask(SIG_UNBLOCK, &mask, NULL); //now that we have our job saved in the list we can
		  //accept sigchilds
		  waitfg(pid); //sleep until foreground job changes state (sigchld)
	  }
	  else{ //child runs in background, upkeep, then we can do things
		  addjob(jobs, pid, BG, cmdline); //
		  printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline);//pid2jid gets job id, which is 
		  //set by shell, not to be confused with process group id, also this is
		  //unlike fork() which the OS chooses a pid
		  sigprocmask(SIG_UNBLOCK, &mask, NULL); //unblock sigchld
	  }	  
  }		  
  return;
}


/////////////////////////////////////////////////////////////////////////////
//
// builtin_cmd - If the user has typed a built-in command then execute
// it immediately. The command name would be in argv[0] and
// is a C string. We've cast this to a C++ string type to simplify
// string comparisons; however, the do_bgfg routine will need 
// to use the argv array as well to look for a job number.
//
int builtin_cmd(char **argv) 
{
  string cmd(argv[0]);
  
  if(cmd == "quit"){  //fairly simple string comparisons, if equal strcmpp returns 0
	  exit(0);  //exits shell, fairly self explanatory
  }
  else if(cmd == "jobs"){
	  listjobs(jobs); //function in jobs.cc
	  return 1;
  }
  else if(cmd == "bg" || cmd == "fg"){
	  do_bgfg(argv); //control jumps to the bg fg function
	  return 1;
  }
  
  return 0;     /* not a builtin command */
}

/////////////////////////////////////////////////////////////////////////////
//
// do_bgfg - Execute the builtin bg and fg commands
//
void do_bgfg(char **argv) 
{
  struct job_t *jobp=NULL;
    
  /* Ignore command if no argument */
  if (argv[1] == NULL) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }
    
  /* Parse the required PID or %JID arg */
  if (isdigit(argv[1][0])) {
    pid_t pid = atoi(argv[1]);
    if (!(jobp = getjobpid(jobs, pid))) {
      printf("(%d): No such process\n", pid);
      return;
    }
  }
  else if (argv[1][0] == '%') {
    int jid = atoi(&argv[1][1]);
    if (!(jobp = getjobjid(jobs, jid))) {
      printf("%s: No such job\n", argv[1]);
      return;
    }
  }	    
  else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]);
    return;
  }

  //
  // You need to complete rest. At this point,
  // the variable 'jobp' is the job pointer
  // for the job ID specified as an argument.
  //
  // Your actions will depend on the specified command
  // so we've converted argv[0] to a string (cmd) for
  // your benefit.
  //
  string cmd(argv[0]);
  pid_t pid = jobp->pid; //need vars for pid, jid
  int jid = jobp->jid;
  
  if(cmd == "bg"){  //I'm assuming we send some signal that pauses the process
	  //allowing shell input, this resumes the process, updates state to bg so the shell
	  //can take inputs, and prints out the job info 
	  kill(-pid, SIGCONT);
	  jobp->state = BG;
	  printf("[%d] (%d) %s", jid, pid, jobp->cmdline);
  }
  else{//if it isnt bg it has to be fg
	  //sends a  continue signal, updates the state, and then sleeps while
	  //the child process does its thing
	  kill(-pid, SIGCONT); //-pid instead of pid targets the process group
	  //writup says make sure to target pg instead of just a process when using kill
	  //command, probably because dependent processes would have errors
	  jobp->state = FG;
	  waitfg(pid); //when it gets done waiting for the fg to finish, this returns to
	  //builtin_cmds which returns to eval, which returns to main, which waits for input
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// waitfg - Block until process pid is no longer the foreground process
//
void waitfg(pid_t pid)
{
  while(fgpid(jobs) == pid){  //basically you input a process id, this checks
	  //if the current fg job's pid is the same as your input, if so, sleep, otherwisee
	  //return
	  sleep(0);
  }
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// Signal handlers
//


/////////////////////////////////////////////////////////////////////////////
//
// sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//     a child job terminates (becomes a zombie), or stops because it
//     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//     available zombie children, but doesn't wait for any other
//     currently running children to terminate.  
//
void sigchld_handler(int sig) 
{
	pid_t pid; 
	int status; 
	while((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0){
		//-1 spec tells it to wait for any child process, middle needed a pointer so i made one, 
		//WNOHANG | WUNTRACED means it returns if no zombies and it reports status of
		//terminated or stopped children
		if(WIFSTOPPED(status)){
			//checks for child stopped by SIGTSTP, prints out info then returns
			printf("Job [%d] (%d) stopped by signal %d\n", pid2jid(pid), pid, WSTOPSIG(status));
			struct job_t *jobp = getjobpid(jobs, pid);
			jobp->state = ST;
		}
		else if(WIFSIGNALED(status)){
			//checks for termination from uncaught signals (IE SIGINT)
			//this prints out why something got terminated if uncaught, and then reaps
			//the process
			int sig = WTERMSIG(status);
		    printf("Job [%d] (%d) terminated by signal %d\n", pid2jid(pid), pid, sig);
		    deletejob(jobs, pid);//reaper
		}
		else{
		    deletejob(jobs, pid); //Reaper - removes any nonfunctioning stragglers
		    //that probably exited out normally
		}
	}
  
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigint_handler - The kernel sends a SIGINT to the shell whenver the
//    user types ctrl-c at the keyboard.  Catch it and send it along
//    to the foreground job.  
//
void sigint_handler(int sig) 
{
  pid_t pid = fgpid(jobs); //get pid for foreground process
  kill(-pid, SIGINT); //send sigint to pid's process group 
  //messaging is handled in sigchild
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
//     the user types ctrl-z at the keyboard. Catch it and suspend the
//     foreground job by sending it a SIGTSTP.  
//
void sigtstp_handler(int sig)
{
  pid_t pid = fgpid(jobs); //get pid for foreground job, don't want to signal anything else
  kill(-pid, SIGTSTP);//send sigtstp to pid's process group
  //print messages handled in sigchild
  return;
}

/*********************
 * End signal handlers
 *********************/




