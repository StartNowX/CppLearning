
课程笔记来自GitChat上《C/C++多线程编程精髓》（范蠡）

本次笔记只记录该课程中Linux下的多线程使用及C++11标准中的用法

---



## 线程的基本概念及常见问题
1. 一个进程至少有一个线程，将该线程称之为“主线程”，即一个进程至少有一个“主线程”；
2. 在Linux系统中，如果主线程退出，工作线程一般不会受到影响，还会继续运行下去，但是此时这个进程就会变成所谓的僵尸进程，这是一种不好的做法，实际开发中应该避免产生僵尸进程；
    * `ps -ef`命令查看系统进程列表时，带有<defunct>字样的进程即僵尸进程
3. 进程中某个线程崩溃，是否会对其他线程造成影响？
    * 一般来说，线程之间是相互独立的，每个线程都有自己的上下文，不会比彼此有影响；但通常一个线程崩溃会导致进程内的错误（如segment fault等），操作系统默认对此类信号的处理就是结束进程，因此进程中存在的其他线程也不存在了


## 线程的创建和使用

### Linux线程的创建
1. Linux使用`pthread_create`这个API创建线程，该API使用如下：
    ```C++
    int pthread_create(pthread_t *thread,
                       const pthread_attr_t *attr,
                       void *(*start_route)(void *),
                       void *args)
    ```
    * `thread`是一个输入参数，如果线程创建成功，则通过这个参数可以得到创建成功的线程ID
    * `attr`指定了该线程的属性，一般设置为NULL，表示使用默认属性
    * `start_route`指定了线程函数，这里需要注意的是这个函数的调用方式必须是__cedel调用，因为在C/C++中定义函数时默认的调用方式使用__cedel，所以一般很少有人意识到这一点
    * `args`线程函数的参数，因为是void* 类型，可以方便我们最大化地传入任意多的信息给线程函数
    * 返回值：成功返回0，失败返回相应错误码

2. 参考信息
    * [__cedel/_stdcall等函数调用方式区别](https://www.cnblogs.com/Winston/archive/2008/09/11/1289391.html)


### C++11提供的std::thread类

1. 使用该类，可以使用任何签名形式的函数作为线程函数，如：
    ```C++
    void thread1() {
        std::cout << "this is thread1" << std::endl;
    }

    void thread2(int a, int b) {
        std::cout << "this is thread2, a = " << a << " b = " << b << std::endl;
    }

    int main(int argc, char* argv[]) {

        std::thread t1(thread1);
        std::thread t2(thread2, 3, 5);

        return 0;
    }

    ```

2. 易错：std::thread对象在线程函数运行期间必须是有效的
    * 解决方案一：使用std::thread对象的detach方法，让线程对象与线程函数脱离关系，这样即使线程对象被销毁，仍然不影响线程函数的运行
    * 实际编码中不推荐，代码应该尽量保证线程对象在线程运行期间有效，而不是单纯地调用 detach 方法使线程对象与线程函数的运行分离


## 排除Linux进行CPU使用率过高的问题

开发中由于bug导致某个线程空转，会导致该进程占用CPU过高，排查方式可以结合`pstack`和`top`命令

### pstack命令
* 该命令为gdb调试器提供，若系统无该命令，安装gdb即可
* 该命令查看的程序必须携带调试符号，且所使用用户具有相应权限
* 使用方式`pstack pid`查看相应**进程**中各个线程的调用堆栈
* 使用`top -H`查看进程中各个线程的状态
    * top命令的-H选项的作用是显示每个一个进程的各个线程运行状态（线程模式）


## 线程ID的用处及原理

线程ID即标识一个线程的整型数值

### 线程ID的本质

#### Linux中使用获取线程ID的方式
1. 调用`pthread_create`接口时第一个参数
2. `pthread_self`函数
    ```C++
    pthread_t pthread_self(void); // pthread_t是DWORD类型，是32位无符号整数
    ```
3. 通过系统调用获取
    ```C++
    #include <sys/syscall.h>
    #include <unistd.h>

    int tid = syscall(SYS_gettid);
    ```
4. 备注
    * 方法1和2返回的解释`pthread_t`，本质是一块内存地址空间，如下图所示
        * ![image](https://github.com/StartNowX/Cplusplus/blob/master/notes/imgs/1_%E7%BA%BF%E7%A8%8BID%E7%9A%84%E6%9C%AC%E8%B4%A81.PNG)
    * 由于不同的进程可能拥有同样的地址空间，因此`pthread_t`不太会是全局唯一的，一般是一个很大的数
    * 方法3获取的是**系统范围内全局唯一的**，一般不是一个很大的数，即LWP（light weight process轻量级进程，早期的Linux系统的线程是通过进程来实现的，这种线程被称为轻量级线程）的ID

#### C++11
1. `std::this_thread::get_id()`接口，**类的静态方法**，获取的是一个`std::thread::id`对象，不可强转整型。
    ```C++
    std::thread::id pid = std::this_thead()::get_id();
    ```
    * 一般使用`std::cout`输入输出流控制
    * 或转为`std::ostringstream`，再转为字符串

2. `std::thread::get_id()`方法，获取给定线程的ID，**类的实例方法**

## 如何等待线程结束

### Linux等待线程结束

1. Linux下使用`pthread_join`函数等待线程结束并接受其退出码，接口使用如下:
    ```C++
    /**
     * pid: 需要等待的线程
     * retval：接受等待退出的线程的退出码，可用于pthread_exit或return
    */
    int pthread_join(pthread_t pid, void **retval);

    /**
     * retval可以用pthread_join中拿到的，没有可以设置为Null
    */
    void pthread_exit(void *retval);
    ```
2. `pthread_join`函数等待其他线程退出期间会挂起等待的线程

### C++11提供方法
1. C++11的`std::thread`提供了`join()`方法用来等待退出的线程，但要求线程必须是还在运行中，若线程不在运行中调用该方法，会导致程序崩溃
    * `joinable()`方法用于判断某个线程是否可以`join`，若可以调用时再调用`join`方法