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

// 接受msg
int main(int argc, char* argv[]) {
    DataPacket data;
    bool running = true;
    int msg_id = -1;

    // 等于0，表示接收第一个可用的数据，如果是大于0的数，那么只接收实际相同的数据类型（即发送发发送的消息的data.msg_type需要一致）
    long int msg_type = 0;  // 2

    // 如果已经创建了，忽略IPC_CREAT
    msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        cout << "get msg id failed." << endl;
        exit(EXIT_FAILURE);
    }

    while (running) {
        int ret = msgrcv(msg_id, &data, MAX_MSG_LEN, msg_type, 0);
        if (ret == -1) {
            cout << "recv msg info failed." << endl;
            exit(EXIT_FAILURE);
        }

        cout << "recv data is: " << data.data << endl;
        if (strncmp(data.data, "end", 3) == 0) {
            running = false;
        }
    }

    if (msgctl(msg_id, IPC_RMID, 0) == -1) {
        cout << "rm msg queue failed." << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}