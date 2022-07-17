// !! 7.7　显式运行时链接

支持动态链接的系统往往都支持一种更加灵活的模块加载方式,'叫做显式运行时链接 (Explicit Runtime Linking)', 有时候也叫做运行时加载。
'也就是让程序自己在运行时控制加载指定的模块, 并且可以在不需要该模块时将其卸载'。

如果动态链接器可以在运行时将共享模块装载进内存并且可以进行重定位等操作, 那么这种运行时加载在理论上也是很容易实现的。而且一般的共享对象不需要进行任何修改就可以进行运行时
装载, 这种共享对象往往被叫做动态装载库 (Dynamic Loading Library), 其实本质上它跟一般的共享对象没什么区别, 只是程序开发者使用它的角度不同。

这种运行时加载使得程序的模块组织变得很灵活, 可以用来实现一些诸如插件、驱动等功能。

当程序需要用到某个插件或者驱动的时候, 才将相应的模块装载进来, 而不需要从一开始就将他们全部装载进来, 从而减少了程序启动时间和内存使用。'并且程序可以在运行的时候重新加载某
个模块, 这样使得程序本身不必重新启动而实现模块的增加、删除、更新等', 这对于很多需要长期运行的程序来说是很大的优势。

在 Linux 中, 从文件本身的格式上来看, 动态库实际上跟一般的共享对象没有区别。

主要的区别是'共享对象是由动态链接器在程序启动之前负责装载和链接的, 这一系列步骤都由动态连接器自动完成, 对于程序本身是透明的'; 而动态库的装载则是通过一系列由动态链接器提
供的 API, 具体地讲共有 4 个函数: 打开动态库 dlopen、查找符号 dlsym、错误处理 dlerror 以及关闭动态库 dlclose, 程序可以通过这几个 API 对动态库进行操作。

这几个 API 的实现是在 /lib/libdl.so.2 里面, 它们的声明和相关常量被定义在系统标准头文件 <dlfcn.h>。


// !! 7.7.1　dlopen()

'dlopen() 函数用来打开一个动态库, 并将其加载到进程的地址空间, 完成初始化过程'. 它的 C 原型定义为:

void * dlopen(const char *filename, int flag);

第一个参数是被加载动态库的路径, 如果这个路径是绝对路径 (以 / 开始的路径), 则该函数将会尝试直接打开该动态库; 如果是相对路径, 那么 dlopen() 会尝试在以一定的顺序去查找该
动态库文件:

1. 查找有环境变量 LD_LIBRARY_PATH 指定的一系列目录

2. 查找由 /etc/ld.so.cache 里面所指定的共享库路径

3. /lib、/usr/lib


当然, 这在理论上不应该成为一个问题, 因为所有的库都应该只存在于某个目录中, 而不应该在多个目录有不同的副本, 这将会导致系统变得极为不可靠。

很有意思的是,'如果我们将 filename 这个参数设置为 0, 那么 dlopen 返回的将是全局符号表的句柄, 也就是说我们可以在运行时找到全局符号表里面的任何一个符号, 并且可以执行它
们', 这有些类似高级语言反射 (Reflection) 的特性。

第二个参数 flag 表示函数符号的解析方式, 常量 RTLD_LAZY 表示使用延迟绑定, 当函数第一次被用到时才进行绑定, 即 PLT 机制; 而 RTLD_NOW 表示当模块被加载时即完成所有的函
数绑定工作, 如果有任何未定义的符号引用的绑定工作没法完成, 那么 dlopen() 就返回错误。

在调试程序的时候我们可以使用 RTLD_NOW 作为加载参数, 因为如果模块加载时有任何符号未被绑定的话, 我们可以使用 dlerror() 立即捕获到相应的错误信息;
而如果使用 RTLD_LAZY 的话, 这种符号未绑定的错误会在加载后发生, 则难以捕获。

'dlopen 的返回值是被加载的模块的句柄, 这个句柄在后面使用 dlsym 或者 dlclose 时需要用到'。如果加载模块失败, 则返回 NULL。如果模块已经通过 dlopen 被加载过了, 那么返
回的是同一个句柄。

事实上 dlopen 还会在加载模块时执行模块中初始化部分的代码, 我们前面提到过, 动态链接器在加载模块时, 会执行 .init 段的代码, 用以完成模块的初始化工作, dlopen 的加载过程
基本跟动态链接器一致, 在完成装载、映射和重定位以后, 就会执行 .init 段的代码然后返回。


// !! 7.7.2　dlsym()

'dlsym 函数基本上是运行时装载的核心部分, 我们可以通过这个函数找到所需要的符号'。

它的定义如下:

void * dlsym(void *handle, char *symbol);

定义非常简洁, 两个参数, 第一个参数是由 dlopen() 返回的动态库的句柄; 第二个参数即所要查找的符号的名字, 一个以 "\0" 结尾的 C 字符串。

dlsym() 返回的值对于不同类型的符号, 意义是不同的。如果查找的符号是个函数, 那么它返回函数的地址; 如果是个变量, 它返回变量的地址; 如果这个符号是个常量, 那么它返回的是该
常量的值。


这里有一个问题是: 如果常量的值刚好是 NULL 或者 0 呢, 我们如何判断 dlsym() 是否找到了该符号呢? 这就要用到我们下面介绍的 dlerror() 函数了。如果符号找到了, 那么
dlerror() 返回 NULL, 如果没找到, dlerror() 就会返回相应的错误信息。


// !! 符号优先级

'当我们使用 dlsym() 进行符号的地址查找工作时, 这个函数是不是也是按照装载序列的优先级进行符号的查找呢'?

实际的情况是, dlsym() 对符号的查找优先级分两种类型。第一种情况是, 如果我们是在全局符号表中进行符号查找, 即 dlopen() 时, 参数 filename 为 NULL, 那么由于全局符号表
使用的装载序列, 所以 dlsym() 使用的也是装载序列。第二种情况是如果我们是对某个通过 dlopen() 打开的共享对象进行符号查找的话, 那么采用的是一种叫做依赖序列 
(Dependency Ordering) 的优先级。

什么叫依赖序列呢? 它是以被 dlopen() 打开的那个共享对象为根节点, 对它所有依赖的共享对象进行广度优先遍历, 直到找到符号为止。


// !! 7.7.3　dlerror()

'每次我们调用 dlopen()、dlsym() 或 dlclose() 以后, 我们都可以调用 dlerror() 函数来判断上一次调用是否成功'。dlerror() 的返回值类型是 char*, 如果返回 NULL, 
则表示上一次调用成功; 如果不是, 则返回相应的错误消息。


// !! 7.7.4　dlclose()

dlclose() 的作用跟 dlopen() 刚好相反, 它的作用是将一个已经加载的模块卸载。系统会维持一个加载引用计数器, 每次使用 dlopen() 加载某模块时, 相应的计数器加一; 每次使
用 dlclose() 卸载某模块时, 相应计数器减一。只有当计数器值减到 0 时, 模块才被真正地卸载掉。

下面是一个简单的例子, 这段程序将数学库模块用运行时加载的方法加载到进程中, 然后获取 sin() 函数符号地址, 调用 sin() 并且返回结果:

#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[]) {
    void *handle;
    double(*func)(double);
    char *error;

    handle = dlopen(argv[1], RTLD_NOW);
    if(handle == NULL) {
         printf("Open library %s error: %s\n", argv[1], dlerror());
         return -1;
    }

    func = dlsym(handle, "sin");
    if((error = dlerror())!= NULL) {
         printf("Symbol sin not found: %s\n", error);
          goto exit_runso;
    }
    printf( "%f\n", func(3.1415926 / 2) );
    exit_runso:
    dlclose(handle);
    return 0;
}


> gcc -o  RunSoSimple RunSoSimple.c -ldl          
> ./RunSoSimple /lib/x86_64-linux-gnu/libm-2.31.so

1.000000

-ldl 表示使用 DL 库 (Dynamical Loading), 它位于 /lib/libdl.so.2。

// !! 7.7.5　运行时装载的演示程序

