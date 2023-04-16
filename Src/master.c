#ifdef __linux__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

// define default workers num
#define DEFAULT_WORKER_NUM 4
// save workers pid
static pid_t worker[DEFAULT_WORKER_NUM];
// define function pointer
typedef void (*worker_function)();

volatile bool is_running = true;

static worker_function wf;


void start_worker()
{
    pid_t pid;

    for(int i=0; i<DEFAULT_WORKER_NUM; i++){
        // start worker process
        pid = fork();
        if (pid == 0) {

            wf();

        } else if (pid < 0){
            perror("fork failed!");
        } else {
            // father process
            worker[i] = pid;
        }
    }
}

// set daemon
static void daemonize()
{
    pid_t pid = fork();

    if (pid < 0) { 
        perror("fork"); exit(1); 
    }
    else if (pid > 0) {

        printf("MultiProcess Serer Running...\nDaemon PID: %d\n", pid);
        exit(0);
    }
    
    if (setsid() < 0) {
        perror("setsid"); exit(1);
    }

    umask(0);

    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null", O_RDWR);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDONLY);

}


void signal_handle(int signum){

    if(signum == SIGUSR1) {
        is_running = false;
        for(int i=0; i<DEFAULT_WORKER_NUM; i++)
            kill(worker[i], SIGTERM);
    }
}


void check_and_restart()
{
    int i, status;
    pid_t pid;

    while(is_running) {

        for(i=0; i<DEFAULT_WORKER_NUM; i++){

            pid = waitpid(worker[i], &status, WNOHANG);
            if(pid == 0) {

                // worker is running

            } else if (pid == worker[i]) {
                // worker is down
                pid = fork();

                if (pid < 0) {
                    perror("fork failed!");
                    exit(1);
                } else if (pid == 0) {
                    wf();
                    exit(0);
                } else {
                    // father
                    printf("Worker %d has been down, ", worker[i]);
                    worker[i] = pid;
                    printf("Start new worker %d \n", pid);
                }
            } else {
                perror("waitpid failed!");
                exit(1);
            }
        }
        sleep(1);
    }
}


void multi_process_init(worker_function _wf)
{
    wf = _wf;

    // kill -10 pid
    signal(SIGUSR1, signal_handle);

    daemonize();

    start_worker();

    check_and_restart();

}


// worker function
void myworker()
{
    sleep(100);
}


int main() {
    multi_process_init(&myworker);
}
#endif // __linux__