#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define TXT_NAME "./test.txt"

void* FileWrite2File(void* arg) {
    time_t now = time(NULL);
    struct tm* it = localtime(&now);
    char tmp_str[32] = {0};

    snprintf(tmp_str, 32, "%04d-%02d-%02d %02d:%02d:%02d\n", it->tm_year + 1900,
             it->tm_mon + 1, it->tm_mday, it->tm_hour, it->tm_min, it->tm_sec);

    FILE* fp = fopen(TXT_NAME, "w");
    if (NULL == fp) {
        printf("Failed to get time.\n");
        return 0;
    }

    size_t size_to_write = strlen(tmp_str) + 1;
    size_t ret = fwrite(tmp_str, sizeof(char), size_to_write, fp);
    if (0 != ret) {
        printf("write error.\n");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 0;
}

int main(int argc, char* argv[]) {

    pthread_t pid;
    int ret = pthread_create(&pid, NULL, FileWrite2File, NULL);
    
    int *retval;
    pthread_join(pid, (void**)&retval);

    FILE *fp = fopen(TXT_NAME, "r");
    if(NULL == fp){
        printf("Error read. \n");
        return -2;
    }

    char buf[32] = {0};
    int size_read = fread(buf, 1, 32, fp);
    if(0 == size_read){
        fclose(fp);
        return -3;
    }
  
    printf("current time is %s \n", buf);

    return 0;
}
