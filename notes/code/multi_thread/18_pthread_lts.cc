#include <stdio.h>
#include <pthread.h>

pthread_key_t g_thread_log_key;

void write_to_file_log(const char* message) {

    if(NULL == message){
        return;
    }

    FILE *thread_log = (FILE*)pthread_getspecific(g_thread_log_key);
    fprintf(thread_log, "%s\n", message);
    fflush(thread_log);
}


void close_file_log(void *logfile){
    char logfilename[128];
    sprintf(logfilename, "close logfile, thread%ld.log\n", (unsigned long)pthread_self());

    printf("logfilename = %s\n", logfilename);
    fclose((FILE *)logfile);
}

void *thread_function(void *args){
    char logfilename[128];

    sprintf(logfilename, "thread%ld.log", (unsigned long)pthread_self());
    FILE *logfile = fopen(logfilename, "w");
    if(NULL != logfilename){
        pthread_setspecific(g_thread_log_key, logfile);
        write_to_file_log("Thread starting...");
    }

    return NULL;
}

int main(int argc, char* argv[]){

    pthread_t pid[3];
    pthread_key_create(&g_thread_log_key, close_file_log);
    for(int i = 0; i < 3; ++i){
        pthread_create(&pid[i], NULL, thread_function, NULL);
    }
    for (int i = 0; i < 3; ++i) {
        pthread_join(pid[i], NULL);
    }

    return 0;
}