#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

#include <iostream>

using namespace std;

key_t MSG_KEY = 1711;
const int MAX_MSG_LEN = 1024;

struct DataPacket {
    long int msg_type;
    int priority;
    char data[MAX_MSG_LEN];
};

int main(int argc, char* argv[]) {
    bool running = true;
    // 发送的数据类型，如果接收方的msgget中指定的msg_type参数不是0，则需要和这个msg_type保持一致，不然接收不到数据
    long int msg_type = 1;
    int msg_id = -1;
    char buffer[MAX_MSG_LEN];
    DataPacket data;

    msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        cout << "get msg id failed." << endl;
        exit(EXIT_FAILURE);
    }

    while (running) {
        cout << "input msg: ";
        fgets(buffer, MAX_MSG_LEN, stdin);
        data.msg_type = msg_type;
        strcpy(data.data, buffer);

        if (msgsnd(msg_id, &data, MAX_MSG_LEN, 0) == -1) {
            cout << "snd msg info failed." << endl;
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer, "end", 3) == 0) {
            running = false;
        }
        sleep(1);
    }


    return 0;
}