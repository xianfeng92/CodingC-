#include <iostream>

// !!  并行与并发

// !! 并行基础

std::thread 用于创建一个执行的线程实例，所以它是一切并发编程的基础，使用时需要包含 <thread> 头文件，它提供了很多基本的线程操作，例如 get_id() 来获取
所创建线程的线程 ID，使用 join() 来加入一个线程等等，例如:

#include<thread>

int main(int argc, char **argv)
{
    std::thread t([]() ->
                  { std::cout << "hello world." << std::endl; };)
    t.join();
    return 0;
}


// !! 互斥量与临界区

我们在操作系统、亦或是数据库的相关知识中已经了解过了有关并发技术的基本知识，mutex 就是其中的核心之一。 C++11 引入了 mutex 相关的类，其所有相关的函数都放
在 <mutex> 头文件中。

std::mutex 是 C++11 中最基本的 mutex 类，通过实例化 std::mutex 可以创建互斥量，而通过其成员函数 lock() 可以进行上锁，unlock() 可以进行解锁。
但是在实际编写代码的过程中，最好不去直接调用成员函数，因为调用成员函数就需要在每个临界区的出口处调用 unlock()，当然，还包括异常。这时候 C++11 还为互斥量
提供了一个 RAII 语法的模板类 std::lock_guard。

RAII 在不失代码简洁性的同时，很好的保证了代码的异常安全性。

在 RAII 用法下，对于临界区的互斥量的创建只需要在作用域的开始部分，例如：

#include <iostream>
#include <thread>

int v = 1;

void critical_section(int change_v) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    // 执行竞争操作
    v = change_v;

    // 离开此作用域后 mtx 会被释放
}

int main() {
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();

    std::cout << v << std::endl;
    return 0;
}


由于 C++ 保证了所有栈对象在生命周期结束时会被销毁，所以这样的代码也是异常安全的。无论 critical_section() 正常返回、还是在中途抛出异常，都会引发栈回退，
也就自动调用了 unlock()

而 std::unique_lock 则相对于 std::lock_guard 出现的，std::unique_lock 更加灵活，std::unique_lock 的对象会以独占所有权（没有其他的 unique_lock 
对象同时拥有某个 mutex 对象的所有权） 的方式管理 mutex 对象上的上锁和解锁的操作。所以在并发编程中， 推荐使用 std::unique_lock。

std::lock_guard 不能显式的调用 lock 和 unlock， 而 std::unique_lock 可以在声明后的任意位置调用，可以缩小锁的作用范围，提供更高的并发度。

如果你用到了条件变量 std::condition_variable::wait 则必须使用 std::unique_lock 作为参数。

#include <iostream>
#include <thread>

int v = 1;

void critical_section(int change_v) {
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    // 执行竞争操作
    v = change_v;
    std::cout << v << std::endl;
    // 将锁进行释放
    lock.unlock();

    // 在此期间，任何人都可以抢夺 v 的持有权

    // 开始另一组竞争操作，再次加锁
    lock.lock();
    v += 1;
    std::cout << v << std::endl;
}

int main() {
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();
    return 0;
}

// !! 期物

期物（Future）表现为 std::future，它提供了一个访问异步操作结果的途径，这句话很不好理解。为了理解这个特性，我们需要先理解一下在 C++11 之前的多线程行为。

试想，如果我们的主线程 A 希望新开辟一个线程 B 去执行某个我们预期的任务，并返回我一个结果。而这时候，线程 A 可能正在忙其他的事情，无暇顾及 B 的结果，所以我们
会很自然的希望能够在某个特定的时间获得线程 B 的结果。

在 C++11 的 std::future 被引入之前，通常的做法是: 创建一个线程 A，在线程 A 里启动任务 B，当准备完毕后发送一个事件，并将结果保存在全局变量中。而主函数线程
A 里正在做其他的事情，当需要结果的时候，调用一个线程等待函数来获得执行的结果。

而 C++11 提供的 std::future 简化了这个流程，可以用来获取异步任务的结果。自然地，我们很容易能够想象到把它作为一种简单的线程同步手段，即屏障（barrier）。

为了看一个例子，我们这里额外使用 std::packaged_task，它可以用来封装任何可以调用的目标，从而用于实现异步的调用。 举例来说：

#include <iostream>
#include <future>
#include <thread>

int main() {
    // 将一个返回值为 7 的 lambda 表达式封装到 task 中
    // std::packaged_task 的模板参数为要封装函数的类型
    std::packaged_task<int()> task([](){return 7;});
    // 获得 task 的期物
    std::future<int> result = task.get_future(); // 在一个线程中执行 task
    std::thread(std::move(task)).detach();
    std::cout << "waiting...";
    result.wait(); // 在此设置屏障，阻塞到期物的完成
    // 输出执行结果
    std::cout << "done!" << std:: endl << "future result is " << result.get() << std::endl;
    return 0;
}

在封装好要调用的目标后，可以使用 get_future() 来获得一个 std::future 对象，以便之后实施线程同步。

// !! 条件变量

条件变量 std::condition_variable 是为了解决死锁而生，当互斥操作不够用而引入的。比如，线程可能需要等待某个条件为真才能继续执行， 而一个忙等待循环中可能
会导致所有其他线程都无法进入临界区使得条件为真时，就会发生死锁。所以，condition_variable 实例被创建出现主要就是用于唤醒等待线程从而避免死锁。std::condition_variable
的 notify_one() 用于唤醒一个线程； notify_all() 则是通知所有线程。下面是一个生产者和消费者模型的例子：

#include <queue>
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>


int main() 
{
    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;  // 通知信号

    // 生产者
    auto producer = [&]() {
        for (int i = 0; ; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "producing " << i << std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all(); // 此处也可以使用 notify_one
        }
    };

    // 消费者
    auto consumer = [&]() {
        while (true)
        {
            std::unique_lock<std::mutex> lock(mtx);
            while (!notified)
            {  // 避免虚假唤醒
                cv.wait(lock);
            }
            // 短暂取消锁，使得生产者有机会在消费者消费空前继续生产
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 消费者慢于生产者
            lock.lock();
            while (!produced_nums.empty())
            {
                std::cout << "consuming " << produced_nums.front() << std::endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    // 分别在不同的线程中运行
    std::thread p(producer);
    std::thread cs[2];
    for (int i = 0; i < 2; ++i) {
        cs[i] = std::thread(consumer);
    }
    p.join();
    for (int i = 0; i < 2; ++i) {
        cs[i].join();
    }
    return 0;
}

值得一提的是，在生产者中虽然可以使用 notify_one()，但实际上并不建议在此处使用，因为在多消费者的情况下，我们的消费者实现中简单放弃了锁的持有，这使得可能让其他
消费者争夺此锁，从而更好的利用多个消费者之间的并发。话虽如此，但实际上因为 std::mutex 的排他性，我们根本无法期待多个消费者能真正意义上的并行消费队列的中生产的内容，
我们仍需要粒度更细的手段。


// !! 原子操作与内存模型

#include <thread>
#include <iostream>

int main()
{
    int a = 0;
    int flag = 0;

    std::thread t1([&]() {
        while (flag != 1);

        int b = a;
        std::cout << "b = " << b << std::endl;
    });

    std::thread t2([&]() {
        a = 5;
        flag = 1;
    });

    t1.join();
    t2.join();
    return 0;
}


从直观上看，t2 中 a = 5; 这一条语句似乎总在 flag = 1; 之前得到执行，而 t1 中 while (flag != 1) 似乎保证了 std::cout << "b = " << b << std::endl; 
不会再标记被改变前执行。从逻辑上看，似乎 b 的值应该等于 5。但实际情况远比此复杂得多，或者说这段代码本身属于未定义的行为，因为对于 a 和 flag 而言，他们在两个并
行的线程中被读写，出现了竞争。除此之外，即便我们忽略竞争读写，仍然可能受 CPU 的乱序执行，编译器对指令的重排的影响，导致 a = 5 发生在 flag = 1 之后。从而 b 可能
输出 0。

// !! 原子操作

std::mutex 可以解决上面出现的并发读写的问题，但互斥锁是操作系统级的功能，这是因为一个互斥锁的实现通常包含两条基本原理:

1. 提供线程间自动的状态转换，即『锁住』这个状态
2. 保障在互斥锁操作期间，所操作变量的内存与临界区外进行隔离

这是一组非常强的同步条件，换句话说当最终编译为 CPU 指令时会表现为非常多的指令, 这对于一个仅需原子级操作（没有中间态）的变量，似乎太苛刻了。在现代 CPU 体系结构下提
供了 CPU 指令级的原子操作， 因此在 C++11 中多线程下共享变量的读写这一问题上，还引入了 std::atomic 模板，使得我们实例化一个原子类型，将一个原子类型读写操作从一
组指令，最小化到单个 CPU 指令。

std::atomic<int> counter;

并为整数或浮点数的原子类型提供了基本的数值成员函数，举例来说，包括 fetch_add, fetch_sub 等, 同时通过重载方便的提供了对应的 +，- 版本。

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> count = {0};

int main()
{
    std::thread t1([](){
        count.fetch_add(1);
    });
    std::thread t2([](){
        count++;        // 等价于 fetch_add
        count += 1;     // 等价于 fetch_add
    });
    t1.join();
    t2.join();
    std::cout << count << std::endl;
    return 0;
}

// !! 当然并非所有的类型都能提供原子操作, 这是因为原子操作的可行性取决于 CPU 的架构以及所实例化的类型结构是否满足该架构对内存对齐条件的要求

我们可以通过 std::atomic<T>::is_lock_free 来检查该原子类型是否需支持原子操作

#include <atomic>
#include <iostream>

struct A
{
    float x;
    int y;
    long long z;
};

int main()
{
    std::atomic<A> a;
    std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    return 0;
}


// !! 一致性模型

并行执行的多个线程，从某种宏观层面上讨论，可以粗略的视为一种分布式系统。在分布式系统中，任何通信乃至本地操作都需要消耗一定时间，甚至出现不可靠的通信。

如果我们强行将一个变量 v 在多个线程之间的操作设为原子操作，即任何一个线程在操作完 v 后，其他线程均能同步感知到 v 的变化，则对于变量 v 而言，表现为顺序执行的程序，
它并没有由于引入多线程而得到任何效率上的收益。

对此有什么办法能够适当的加速呢？ 

答案便是削弱原子操作的在进程间的同步条件。


从原理上看，每个线程可以对应为一个集群节点，而线程间的通信也几乎等价于集群节点间的通信。削弱进程间的同步条件，通常我们会考虑四种不同的一致性模型：


// !! 内存顺序

为了追求极致的性能，实现各种强度要求的一致性，C++11 为原子操作定义了六种不同的内存顺序 std::memory_order 的选项，表达了四种多线程间的同步模型:

1. 宽松模型

在此模型下，单个线程内的原子操作都是顺序执行的，不允许指令重排，但不同线程间原子操作的顺序是任意的。类型通过 std::memory_order_relaxed 指定

std::atomic<int> counter = {0};
std::vector<std::thread> vt;
for (int i = 0; i < 100; ++i)
{
    vt.emplace_back([&](){
        counter.fetch_add(1, std::memory_order_relaxed);
    });
}

for (auto& t : vt)
{
    t.join();
}
std::cout << "current counter:" << counter << std::endl;


2. 释放/消费模型

在此模型中，我们开始限制进程间的操作顺序，如果某个线程需要修改某个值，但另一个线程会对该值的某次操作产生依赖，即后者依赖前者。具体而言, 线程 A 完成了三次对 x 的写操作,
线程 B 仅依赖其中第三次 x 的写操作，与 x 的前两次写行为无关，则当 A 主动 x.release() 时候（即使用 std::memory_order_release），选项 std::memory_order_consume 
能够确保 B 在调用 x.load() 时候观察到 A 中第三次对 x 的写操作。

3. 顺序一致模型

在此模型下，原子操作满足顺序一致性，进而可能对性能产生损耗。可显式的通过 std::memory_order_seq_cst 进行指定。

std::atomic<int> counter = {0};
std::vector<std::thread> vt;
for (int i = 0; i < 100; ++i) {
    vt.emplace_back([&](){
        counter.fetch_add(1, std::memory_order_seq_cst);
    });
}

for (auto& t : vt) {
    t.join();
}
std::cout << "current counter:" << counter << std::endl;


// !! 总结

C++11 语言层提供了并发编程的相关支持，本节简单的介绍了 std::thread, std::mutex, std::future 这些并发编程中不可回避的重要工具。除此之外，我们还介绍了 C++11 
最重要的几个特性之一的『内存模型』， 它们为 C++ 在标准化高性能计算中提供了重要的基础














