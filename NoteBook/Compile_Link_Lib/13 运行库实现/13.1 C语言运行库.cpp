// !! 13.1　C语言运行库

在开始实现 Mini CRT 之前, 首先要对它进行基本的规划。

虽然 Mini CRT 很小, 但它应该具备 CRT 的基本功能以及遵循几个基本设计原则, 这些我们归结为如下几个方面:

1. 首先 Mini CRT 应该以 ANIS C 的标准库为目标, 尽量做到与其接口相一致

2. 具有自己的入口函数 mini_crt_entry

3. 基本的进程相关操作 exit

4. 支持基本的文件操作 (fopen、fread、fwrite、fclose、fseek)

5. 支持基本的字符串操作 (strcpy、strlen、strcmp)

6. 支持格式化字符串和输出操作 (printf、sprintf)

7. 支持 atexit() 函数

8. 最后, Mini CRT 应该是跨平台的。我们计划让 Mini CRT 能够同时支持 Windows 和 Linux 两个操作系统

9. Mini CRT 的实现应该尽量简单, 以展示 CRT 的实现为目的, 并不追求功能和性能, 基本上是点到为止

为了使 CRT 能够同时支持 Linux 和 Windows 两个平台, 必须针对这两个操作系统环境的不同进行条件编译。

在 Mini CRT 中, 我们使用宏 WIN32 为标准来决定是 Windows 还是 Linux。因此实际的代码常常呈现这样的结构:

#ifdef WIN32 
// Windows 部分实现代码
#else
//Linux 部分实现代码
#endif


通常我们会把 CRT 的各个函数的声明放在不同的头文件中, 比如 IO 相关的位于 stdio.h; 字符串和堆相关的放在 stdlib.h 中。为了简单起见, 将 Mini CRT 中所有函数的声
明都放在 minicrt.h 中。


// !! 13.1.1　开始

那么 Mini CRT 首先该从哪儿入手呢?

诚然, 从入口函数开始入手应该是个不错的选择。

1. 程序运行的最初入口点不是 main 函数, 而是由运行库为其提供的入口函数。它主要负责三部分工作: 准备好程序运行环境及初始化运行库; 调用 main 函数执行程序主体; 清理程序运
   行后的各种资源

2. 运行库为所有程序提供的入口函数应该相同, 在链接程序时须要指定该入口函数名


// !! 入口函数

'首先, 须要确定入口函数的函数原型, 包括函数名、输入参数及返回值'。在这里, 入口函数命名为 mini_crt_entry。为了简单起见, 它没有输入参数, 同时没有返回值。其实
 mini_crt_entry 的返回值没有意义, 因为它永远不会返回, 在它返回之前就会调用进程退出函数结束进程。这样, 入口函数具有如下形式:

 void mini_crt_entry(void);

参照上面所描述的入口函数的三部分工作, 以下代码为一个基本框架。

void mini_crt_entry(void) {
    // 初始化部分
    int ret = main();
    // 结束部分
    exit(ret);
}

这里的初始化主要负责准备好程序运行的环境, 包括准备 main 函数的参数、初始化运行库, 包括堆、IO等, 结束部分主要负责清理程序运行资源。在以下内容中, 围绕这个基本框架, 我
们将逐步扩展补充入口函数。


// !! main 参数

我们知道 main 函数的原型为:

int main(int argc, char* argv[]);

其中 argc 和 argv 分别是 main 函数的两个参数, 它们分别表示运行程序时的参数个数和指向参数的字符串指针数组。

当进程被初始化时, 它的堆栈结构中就保存着环境变量和传递给 main 函数的参数, 我们可以通过 ESP 寄存器获得这两个参数。但是一旦进入 mini_crt_entry 之后, ESP 寄存器会随着
函数的执行而被改变通过, 第9章中关于函数对于堆栈帧的知识, 可以知道 EBP 的内容就是进入函数后 ESP + 4 (4是因为函数第一条指令是 push ebp)。那么可以推断出 EBP + 4 所指
向的内容应该就是 argc, 而 EBP + 8 则就是 argv。

整个堆栈的分布可以如图 13-1 所示。


// !! CRT 初始化

完成了获取 main 函数参数的代码后, 还应该在入口函数里对 CRT 进行初始化。由于 Mini CRT 所实现的功能较少, 所以初始化部分十分简单。需要初始化的主要是堆和 IO 部分。在堆
被初始化之前, malloc/free 函数是没有办法使用的。我们定义堆的初始化函数为 mini_crt_heap_init(); IO 部分的初始化函数为 mini_crt_io_init()。
这两个函数的返回值都是整数类型的, 返回非 0 即表示初始化成功, 否则表示失败。


// !! 结束部分

Mini CRT 结束部分很简单, 它要完成两项任务: 一个就是调用由 atexit() 注册的退出回调函数; 另外一个就是实现结束进程。

这两项任务都由 exit() 函数完成, 这个函数在 Linux 它调用 Linux 的 1 号系统调用实现进程结束, ebx 表示进程退出码; 而 Windows 则提供了一个叫做 Exit-Process 的 API,
直接调用该 API 即可结束进程。

不过在进行系统调用或 API 之前, exit() 还有一个任务就是调用由 atexit() 注册的退出回调函数, 这个任务通过调用 mini_crt_exit_routine() 实现。


最终 Mini CRT 的入口函数 mini_crt_entry 的代码如清单 13-1 所示。

#include "minicrt.h"

#ifdef WIN32
#include <Windows.h>
#endif

extern int main(int argc, char *argv[]);

void exit();

static void crt_fatal_error(const char* msg) {
    // printf("fatal error: %s", msg);
    exit(-1);
}

void mini_crt_entry(void) {
    int ret;
    #ifdef WIN32
    int flag = 0;
    int argc = 0;
    char* argv[16]; // 最多16个参数
    char* cl = GetCommandLineA();
    // 解析命令行
    argv[0] = cl;
    argc++;
    while(*cl) {
        if(*cl == '\"'){
            if(flag == 0) flag = 1;
            else flag = 0;
        }else if(*cl == ' ' && flag == 0) {
            if(*(cl+1)) {
                argv[argc] = cl + 1;
                argc++;
            }
            *cl = '\0';

        }
         cl++;
    }
    #else
    int argc;
    char** argv;
    char* ebp_reg = 0;
    // ebp_reg = %ebp
    asm("movl %%ebp,%0 \n":"=r"(ebp_reg));
    argc = *(int*)(ebp_reg + 4);
    argv = (char**)(ebp_reg + 8);
    #endif

    if(!mini_crt_heap_init()){
        crt_fatal_error("heap initialize failed");
    }
    if(!mini_crt_io_init()) {
        crt_fatal_error("IO initialize failed");
    }
    ret = main(argc,argv);
     exit(ret);
}

void exit(int exitCode) {
    // mini_crt_call_exit_routine();
    #ifdef WIN32
    ExitProcess(exitCode);
    #else
    asm( "movl %0,%%ebx \n\t"
    "movl $1,%%eax \n\t"
    "int $0x80     \n\t"
    "hlt           \n\t"::"m"(exitCode));
    #endif
}


// !! 13.1.2　堆的实现

有了 CRT 的入口函数、exit() 函数之后, 下一步的目标就是实现堆的操作, 即 malloc() 函数和 free() 函数。

在遵循 Mini CRT 的原则下, 我们将 Mini CRT 堆的实现归纳为下面几条:

1. 实现一个以空闲链表算法为基础的堆空间分配算法

2. 为了简单起见, 堆空间大小固定为 32 MB, 初始化之后空间不再扩展或缩小

3. 在 Windows 平台下不使用 HeapAlloc 等堆分配算法, 采用 VirtualAlloc 向系统直接申请 32MB 空间, 由我们自己的堆分配算法实现 malloc

4. 在 Linux 平台下, 使用 brk 将数据段结束地址向后调整 32MB, 将这块空间作为堆空间

由 brk/sbrk 分配的内存和 VirtualAlloc 分配的一样, 它们仅仅是分配了虚拟空间, 这些空间一开始是不会提交的 (即不分配物理页面), 当进程试图访问某一个地址的时候, 操作系统
会检测到访问异常, 并且为被访问的地址所在的页分配物理页面。

整个堆空间按照是否被占用而被分割成了若干个空闲 Free 块和占用 Used 块, 它们之间由双向链表链接起来。

当用户要申请一块内存时, 堆分配算法将遍历整个链表, 直到找到一块足够大的空闲块, 如果这个空闲块大小刚好等于所申请的大小, 那么直接将这个空闲块标记为占用块, 然后将它的地址返
回给用户; 如果空闲块大小大于所申请的大小, 那么这个空闲块将被分割成两块, 其中一块大小为申请的大小标记为占用, 另外一块为空闲块。

'当用户释放某一块空间时, 堆分配算法会判别被释放块前后两个块是否为空闲块, 如果是, 则将它们合并成一个大的空闲块'。

整个堆分配算法从实现上看十分简单, 仅仅只有 100 行左右, 而且还包含了 Linux 的 brk 系统调用的实现。Mini CRT 的堆分配算法源代码如清单 13-2 所示。

#include "minicrt.h"

typedef struct _heap_header {
    enum {
        HEAP_BLOCK_FREE = 0xABABABAB,   // magic number of free block 
        HEAP_BLOCK_USED = 0xCDCDCDCD,   // magic number of used block
    } type;// block type FREE/USED

    unsigned size;  // block size including header
    struct _heap_header* next;
    struct _heap_header* prev;
} heap_header;

#define ADDR_ADD(a, o) (((char*)(a)) + o)
#define HEADER_SIZE (sizeof(heap_header))

static heap_header* list_head = NULL;

void free(void *ptr) {
    heap_header* header = (heap_header*)ADDR_ADD(ptr, -HEADER_SIZE);
    if(header->type != HEAP_BLOCK_USED) {
        return;
    }
    header->type = HEAP_BLOCK_FREE;
    if(header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE) {
        // merge
        header->prev->next = header->next;
        if(header->next != NULL) {
            header->next->prev = header->prev;
        }
        header->prev->size += header->size;
        header = header->prev;
    }

    if(header->next!= NULL && header->next->type == HEAP_BLOCK_FREE) {
        // merge
        header->size += header->next->size;
        header->next = header->next->next;
        if(header->next->next != NULL){
            header->next->next->prev = header;
        }
    }
}

void* malloc(unsigned size) {
    heap_header *header;
    if(size == 0) {
        return NULL;
    }

    header = list_head;
    while(header != 0) {
        if(header->type == HEAP_BLOCK_USED) {
            header = header->next;
            continue;
        }
        if(header->size > size + HEADER_SIZE && header->size <= size + HEADER_SIZE *2) {
            header->type = HEAP_BLOCK_USED;
        }
        if(header->size > size + HEADER_SIZE * 2) {
            // split
            heap_header* next = (heap_header*)ADDR_ADD(header, size + HEADER_SIZE);
            next->prev = header;
            next->next = header->next;
            next->type = HEAP_BLOCK_FREE;
            next->size = header->size - (size - HEADER_SIZE);

            header->next = next;
            header->size = size + HEADER_SIZE;
            header->type = HEAP_BLOCK_USED;
            return ADDR_ADD(header, HEADER_SIZE);
        }
        header = header->next;
    }
    return NULL;
}

#ifndef WIN32
// Linux brk system call
static int brk(void* end_data_segment) {
    int ret = 0;
    // brk system call number: 45
    // in /usr/include/asm-i386/unistd.h:
    // #define __NR_brk 45
     asm( "movl $45, %%eax     \n\t"
     "movl %1, %%ebx    \n\t"
     "int $0x80         \n\t"
     "movl %%eax, %0    \n\t"
     : "=r"(ret): "m"(end_data_segment) );
}
#endif

#ifdef WIN32
#include <Windows.h>
#endif

int mini_crt_heap_init(){
    void* base = NULL;
    heap_header* header = NULL;
    // 32 MB heap size
    unsigned heap_size = 1024 * 1024 * 32;
    #ifdef WIN32
    base = VirtualAlloc(0, heap_size, MEM_COMMIT | MEM_REVERSE, PAGE_READWRITE);
    if(base == NULL){
        return 0;
    }
    #else
    base = (void*)brk(0);
    void* end = ADDR_ADD(base, heap_size);
    end = (void*)brk(end);
    if(!end){
        return 0;
    }
    #endif
    header = (heap_header*)base;
    header->size = heap_size;
    header->type = HEAP_BLOCK_FREE;
    header->next = NULL;
    header->prev = NULL;
    list_head = header;
    return 1;
}



// !! 13.1.3　IO 与文件操作

在为 Mini CRT 添加了 malloc 和 free 之后, 接着将为它们实现 IO 操作。IO 部分在任何软件中都是最为复杂的, 在 CRT 中也不例外。

'在传统的 C 语言和 UNIX 里面, IO 和文件是同一个概念, 所有的 IO 都是通过对文件的操作来实现的'。

因此, 只要实现了文件的基本操作 (fopen、fread、fwrite、fclose 和 fseek), 即完成了 Mini CRT 的 IO 部分。

我们需要为 Mini CRT 的 IO 部分设计一些实现的基本原则:

1. 仅实现基本的文件操作, 包括 fopen、fread、fwrite、fclose 及 fseek

2. 为了简单起见, 不实现缓冲 (Buffer) 机制

3. 不对 Windows 下的换行机制进行转换, 即 "\r\n" 与 "\n" 之间不进行转换

4. 支持三个标准的输入输出 stdin、stdout 和 stderr

5. 在 Windows 下, 文件基本操作可以使用 API: CreateFile、ReadFile、WriteFile、CloseHandle 和 SetFilePointer 实现。   
   Linux 不像 Windows 那样有 API 接口, 我们必须使用'内嵌汇编'实现 open、read、write、close 和 seek 这几个系统调用

6. fopen 时仅区分 r、w和 + 这几种模式及它们的组合, 不对文本模式和二进制模式进行区分, 不支持追加模式 a

Mini CRT 的 IO 部分实现源代码如清单 13-3 所示。

