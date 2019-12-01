
课程笔记来自GitChat上《C/C++多线程编程精髓》（范蠡）

课程源码对应于[github链接](https://github.com/balloonwj/gitchat_cppmultithreadprogramming)

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
    * 方法1和2返回的解释`pthread_t`，本质是一块内存地址空间，如下图所示G
        * ![image](https://github.com/StartNowX/Cplusplus/blob/master/notes/imgs/1_thread_id_info.png)
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


## 多线程编程精髓
1. 一个线程函数如果作为类方法，只能是静态方法而不能是实例方法
    * 实例方法的话，C++在编译时，会给方法增加this参数，导致方法的签名不符合**windows或linux下线程的函数签名**

2. C++11则没有固定格式的函数签名的限制，但必须**显示**将线程函数所属的类对象实例指针作为构造函数参数传递给std::thread（类内部即this指针）
3. 在实际开发时（若不使用C++11），往往会在创建线程时将当前对象的地址（this指针）传递给线程函数，然后在线程函数内部，将该指针转为原来的类实例，而通过该实例就可以访问类的所有方法了


## 线程同步技术

### Windows平台上整形变量的原子操作

### C++11对整型变量原子操作的支持
1. C++提供了对整型变量原子操作的相关库，即std::atomic，这是一个模板类型
    ```C++
    tempalte <class T>
    struct atomic;
    ```
    * 可以传入char/bool/int等整型类型对模板进行实例化
    * std库提供了这些实例化的模板类型

2. C++11支持的不同类型的原子操作完整列表如下
    * (完整列表](https://zh.cppreference.com/w/cpp/atomic/atomic)

### Linux下的线程同步对象

#### Linux下的mutex互斥体
Linux下的m互斥体都实现在NPTL(Native POSIX Thread Library), 在NPTL中使用数据结构`pthread_mutex_t`表示一个互斥对象(头文件`pthread.h`)
1. mutex互斥对象初始化
   * 使用`PTHREAD_MUTEX_INITIALIZER`直接给其赋值
     ```C++
     pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
     ```
   * 使用`pthread_mutex_init`动态设置mutex互斥对象的属性,当不需要时,使用`pthread_mutex_destroy`销毁
     ```
     pthread_mutex_t my_mutex;
     pthread_mutex_init(&my_mutex, NULL); // 第二个参数是属性,为NULL时即为普通锁PTHREAD_MUTEX_NORMAL
     pthread_mutex_destroy(&my_mutex);
     ```
   * 设置mutex的属性调用如下接口
     ```C++
     pthread_mutexattr_init(pthread_mutexattr_t *my_mutex_attr);
     pthread_mutexattr_settype(pthread_mutexattr_t *my_mutex_attr, int type);
     pthread_mutexattr_gettype(pthread_mutexattr_t *my_mutex_attr, int *type);
     pthread_mutex_init(&my_mutex, my_mutex_attr); // 将属性使能给互斥体对象
     ```
   * 注意
     * **使用`PTHREAD_MUTEX_INITIALIZER`初始化时不需要销毁**
     * **不要去销毁一个已经加锁或正在被条件变量使用的互斥体对象**,有些系统,销毁一个正在加锁的互斥体对象会报`EBUSY`的错误

2. mutex互斥体对象加锁和解锁
mutex互斥体对象加锁和解锁的方式有如下方式:
   ```C++
   pthread_mutex_lock(pthread_mutex_t *mutex);
   pthread_mutex_trylock(pthread_mutex_t *mutex);
   pthread_mutex_unlock(pthread_mutex_t *mutex);
   ```

3. mutex互斥体中锁的类型
   * 普通锁`PTHREAD_MUTEX_NORMAL`, `pthread_mutex_init`第二个参数为空时的默认值; 对一个线程加上普通锁后,其他线程会阻塞在`pthread_thread_lock`处,直到加锁线程释放锁后才能调用
     * 一个线程如果对一个已经加锁的普通锁再次使用`pthread_mutex_lock`加锁，程序会阻塞在第二次调用`pthread_mutex_lock`代码处,这时如果使用`pthread_thread_trylock`则会返回一个`EBUSY`的错误,而不会阻塞
   * 检错锁`PTHREAD_MUTEX_ERRCHECK`
     * 如果互斥体的属性是`PTHREAD_MUTEX_ERRORCHECK`，当前线程重复调用`pthread_mutex_lock`会直接返回`EDEADLOCK`，其他线程如果对这个互斥体再次调用`pthread_mutex_lock`会阻塞在该函数的调用处
   * 嵌套锁`PTHREAD_MUTEX_RECURSIVE`
     * 该属性允许同一个线程对其持有的互斥体重复加锁，每次成功调用`pthread_mutex_lock`一次, 该互斥体对象的锁引用计数就会增加一次，相反，每次成功调用`pthread_mutex_unlock`一次，锁引用计数就会减少一次, 当锁引用计数值为0时允许其他线程获得该锁，否则其他线程调用`pthread_mutex_lock`时尝试获取锁时, 会阻塞在那里
4. 为了避免因忘记调用`pthread_mutex_lock`出现死锁或者在逻辑出口处有大量解锁的重复代码出现，建议使用`RAII`技术将互斥体对象封装起来

#### Linux下的信号量semaphore
Linux的信号量本质是资源有多份,可以被多个线程访问,常用的API如下
```C++
// 初始化,shared是指该信号量是否可以被初始化该信号量的进程fork出来的子进程共享，取值为0（不可以共享）、1（可以共享）,value是指设置信号量初始状态下资源的数量
// 调用成功返回0,失败返回-1
sem_init(sem_t *semaphore, int shared, unsigned int value);
// 将信号量的资源加1,并解锁该信号量对象，这样其他由于使用sem_wait被阻塞的线程会被唤醒
sem_post(sem_t *semaphore);
// 如果当前信号量资源计数为 0，sem_wait会阻塞调用线程; 直到信号量对象的资源计数大于0时被唤醒，唤醒后将资源计数递减1，然后立即返回
sem_wait(sem_t *semaphore);
// sem_wait的非阻塞版本, 若信号量资源数为0,立即返回-1,错误码被设置为EAGAIN
sem_trywait(sem_t *semaphore);
// sem_wait的带等待时间的版本,若超时等待时间内资源数没有大于0,则返回-1, 错误码被设置为ETIMEDOUT
// 当调用该版本时,abs_timeout不能设置为空
sem_timedwait(sem_t *semaphore, const struct timespec* abs_timeout);
// 销毁信号量
sem_destroy(sem_t *semaphore);
```
其中,
* timespec的结构体如下:
  ```C++
  struct timespec{
      time_t tv_sec;
      long tv_nsec;
  };
  ```
* `sem_wait`、`sem_trywait`、`sem_timedwait`函数将资源计数递减一时会同时锁定信号量对象，因此当资源计数为1时，如果有多个线程调用`sem_wait`等函数等待该信号量时，只会有一个线程被唤醒。当`sem_wait`函数返回时，会释放对该信号量的锁
* `sem_wait`、`sem_trywait`、`sem_timedwait`函数调用成功后返回值均为0，调用失败返回﹣1，可以通过错误码`errno`获得失败原因
* `sem_wait`、`sem_trywait`、`sem_timedwait`可以被Linux信号中断，被信号中断后，函数立即返回，返回值是﹣1，错误码`errno`为`EINTR`

* **这里说的信号量是POSIX信号量,一般用于线程间同步,注意区分SYSTEM V信号量,其常用于进程间同步**

#### Linux下的条件变量
1. 释放互斥体和条件变量等待必须是原子操作,以cond_wait唤醒前不会有其他线程获得互斥对象
2. 条件变量的常用API
   ```C++
   // 初始化和销毁
   pthread_cond_init(pthread_cond_t *my_cond, const pthread_condattr_t* attr);
   pthread_cond_destroy(pthread_cond_t *my_cond);
   // 或者
   pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

   // 等待条件变量
   pthread_cond_wait(pthread_cond_t *my_cond, pthread_condattr_t *my_cv);
   // 上面版本的非阻塞版, abs_time是绝对时间,因此要先获取系统的时间,然后加上欲等待的时间作为timespec参数
   pthread_cond_timedwait(pthread_cond_t *my_cond, pthread_condattr_t *my_cv, const struct timespec* abs_time);

   // 唤醒等待, 两个API成功等到条件变量时,返回0,否则返回-1,可以通过errno获取错误码
   // 一次唤醒一个线程,有多个线程调用pthread_cond_wait时,具体哪个线程被唤醒是随机的
   pthread_cond_signal(pthread_cond_t *my_cond);
   // 可以同时唤醒多个调用pthread_cond_wait的线程
   pthread_cond_broadcast(pthread_cond_t *my_cond);
   ```
3. 注意
   * 条件变量一定要和互斥体一起使用,保证互斥体加锁和释放与条件等待都是原子操作
   * `pthread_cond_wait`阻塞时,会释放其绑定的互斥体,并阻塞线程,因此需要在执行之前有加锁操作
   * `pthread_cond_wait`获得条件变量后,会对其绑定的互斥体进行加锁,因此需要在执行其之后有解锁操作

4. 条件变量的虚假唤醒
以示例程序为例(16_pthread_cv.cc),可能某次操作系统唤醒`pthread_cond_wait`时`tasks.empty()`可能仍然为true，言下之意就是操作系统可能会在一些情况下唤醒条件变量，即使没有其他线程向条件变量发送信号，等待此条件变量的线程也有可能会醒来,因此,**将条件放到while循环中,意味着光唤醒条件变量不行,还得满足条件程序才能继续执行**

   * 为什么会有虚假唤醒?
     * `pthread_cond_wait`是futex系统调用，属于阻塞型的系统调用，当系统调用被信号中断的时候，会返回﹣1，并且把errno错误码置为`EINTR`,很多这种系统调用为了防止被信号中断都会重启系统调用
     * 为了防止某些情况下`pthread_cond_wait`无限等待下去(如`pthread_cond_wait`被中断,在其被中断后,再次调用用,`pthread_cond_singal/broadcast`已经错过了)
     * 条件满足了发送信号，但等到调用`pthread_cond_wait`的线程得到CPU资源时，条件又再次不满足了

5. 条件变量的信号丢失
如果一个条件变量信号条件产生时（调用 pthread_cond_signal 或 pthread_cond_broadcast），没有相关的线程调用`pthread_cond_wait`捕获该信号，那么该信号条件就会永久性地丢失了，再次调用`pthread_cond_wait`会导致永久性的阻塞,当碰到条件变量只会产生一次的逻辑时,要格外注意