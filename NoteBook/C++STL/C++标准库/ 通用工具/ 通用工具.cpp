// !! 通用工具

本章讲解 C++ 标准库的通用工具。'它们由短小精干的类和函数构成, 执行最一般性的工作'。


1. class pair<> 和 class tuple<>

2. smart pointer class(shared_ptr unique_ptr)

3. 数值极值(Numeric limit)

4. Type trait 和 type utility

5.辅助函数--max()、min()、swap()

6. class Radio<>

7. Clock 和 timer

8. 若干重要的 C 函数

大部分通用工具描述于 C++standard 的 "General Utilities"。其余工具则与标准库中一些较主要的组件一起描述, 原因是该类工具主要便是和那些组件共同
使用, 或是基于历史因素。例如某些通用辅助函数被定义于<algorithm> 头文件中, 但按照 STL 的定义它们不算是算法。

这些工具中的一部分也被 C++ 标准库使用, 例如类型pair<>, 凡需要将两个 value 视为一个单元的场合——例如函数必须"返回两个 value"或容器元素是
key/value pair——就必须用到它。而当需要复杂的类型转换时, 就会用上type trait。


// !! Pair和Tuple

C++ 标准库的第 1 版, C++98, 提供了一个简单的class, 用来处理类型不同的两个(一对)值, 而不需为它们再定义特别的 class。当标准函数需要返回一个
value pair, 或者当容器元素是个 key/value pair 时, 就会用上这样一个 C++98 class。


TR1 引入了一个 tuple class, 它将上述概念延伸, 接受任意(但仍有限)个元素。标准库实现保证可移植的范围是: 允许 tuple 带有最多 10 个类型不同的元素。

到了 C++11, tuple class 被重新实现, 采用 variadic template 概念。现在我们有了一个标准的 tuple class, 可用于任意大小的异质集合
(heterogeneous collection)。而与此同时, class pair 仍旧为两个元素服务, 用来组合一个双元素的 tuple。

不过, C++11的 pair class 也有很大扩展, 某种程度上展示了C++语言及其标准库的提升。


// !! Pair

Class pair 可将两个 value 视为一个单元。C++ 标准库内多处用到了这个 class。尤其容器 map、multimap、unordered_map 和 unordered_multimap 
就是使用 pair 来管理其以 key/value pair 形式存在的元素。任何函数如果需返回两个 value, 也需要用到 pair, 例如 minmax()。

Struct pair 定义于 <utility> 。原则上你可以对 pair<> 执行 create、copy/assign/swap及compare操作。此外它还提供 first_type 和 
second_type 类型定义式, 用来表示第一 value 和第二 value 的类型。

namespace std
{
    template <typename T1,typename T2>
    struct pair
    {
        T1 first;
        T2 second;
        ...
    };
}


typedef std::pair<int, float> IntFloatPair;

IntFloatPair p(42,12.22);
p.first;
p.second;
std::get(0)(p);
std::get(1)(p);



// !! 构造函数和赋值

Default 构造函数生成一个 pair 时, 以两个"被 default 构造函数分别初始化"的元素作为初值。根据语言规则, 基础类型(如 int) 的 default 
构造函数也可以引起适当的初始化动作,所以:

std::pair<int, float> p;// initial p.first and p.second with Zero

就是以 int() 和 float() 来初始化 p。这两个构造函数都传回零值。


Copy 构造函数同时存在两个版本, 版本 1 接受相同类型的 pair, 版本 2 是个 member template, 在"构造过程中需要隐式类型转换"时被调用。如果 pair
对象被复制, 调用的是被隐式合成的那个 copy 构造函数。例如:

void f(std::pair<int, const char *>);
void g(std::pair<const int, std::string>);

...

void foo()
{
    std::pair<int, const char *> p(42, "hello");
    f(p);// okay
    g(p);// ok.call template constructor
}

自 C++11 开始, 如果 pair<> 用到了某个类型而该类型只有一个 nonconstant copy 构造函数, 将不再编译成功:


class A
{
public:
    ...
    A(A&);// non const copy constructor
    ...

};

std::pair<A,int> p;// Error. since C++ 11


// !! 逐块式构造（Piecewise Construction）

class pair<> 提供三个构造函数, 用以初始化 first 和 second 成员:

namespace std
{
    template <typename T1, typename T2>
    struct pair
    {
        ...
        pair(const T1& x,const T2& y);
        template <typename U, typename V> pair(U&& x,V&& y);
        template <typename ...Args1, typename ...Args2>
        pair(piecewise_construct_t, tuple<Args1...> first, tuple<Args2...> second);
        ...
    };
}

前两个构造函数提供的是惯常行为: 传递一个实参给 first, 另一个实参给 second, 并且涵盖对 move semantic 和隐式类型转换的支持。

第三个构造函数有点特别, 它允许传递两个 tuple(那是一种“拥有不定个数之元素且元素类型各不相同”的对象), 但以另一种方式处理它们。正常而言, 如果传递
1 或 2 个tuple, 最前面两个构造函数允许初始化一个 pair, 其 first 或 second 是 tuple。但第三个构造函数使用 tuple, 将其元素传递给 first 和
second 的构造函数。为了强迫执行这样的行为, 你必须传递 std::piecewise_construct 作为额外的第一实参。举个例子:

#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

class Foo {
 public:
  Foo(tuple<int, float>) { cout << "Foo::Foo(tup_c)" << endl; }

  template <typename... Args>
  Foo(Args... args) {
    cout << "Foo::Foo(args) " << endl;
  }
};

int main()
{
    tuple<int, float> t(12,12.341);

    // pass the tuple as a whole to the constructor of Foo
    pair<int, Foo> p1(42, t);

    // pass the elements of tuple to the constructor of Foo
    pair<int, Foo> p2(piecewise_construct, make_tuple(42), t);
    
    return 0;
}


 » g++ --std=c++11 pairdemo1.cpp 
--------------------------------------------------------------------------------
 » ./a.out
Foo::Foo(tup_c)
Foo::Foo(args) 

只有当 std::piecewise_construct 被当作第一实参, class Foo 才会被迫使用那个接受 tuple 的元素(一个 int 和一个 float)而非 tuple 整体
的构造函数。这意味着, 此例中被调用的是 Foo 那个"实参数量不定(varargs)的构造函数。如果提供了 Foo::Foo(int, float) 的话,被调用的将是它。

如你所见, 两个实参都必须是 tuple 才会强迫导致这个行为。因此, 第一实参 42 被显式转换为一个 tuple, 用的是 make_tuple()。

// !! 便捷函数 make_pair()

Template 函数 make_pair() 使你无须写出类型就能生成一个 pair 对象。举个例子, 你不必这样写:

std::pair<int, int> p1(1,2);

可以写成这样:

std::make_pair(1,2);

在 C++11 之前, 这个函数的声明和定义如下:

namespace std
{
    template <typename T1, typename T2>
    pair<T1, T2> make_pair(const T1& x1, const T2& x2)
    {
        return pair<T1, T2>(x1, x2);
    }
}

然而自 C++11 起, 事情变得比较复杂, 因为这个 class 也需要应付 move semantic。所以自 C++11 起, C++ 标准库宣称 make_pair() 声明如下:

namespace std
{
    template <typename T1, typename T2>
    pair<V1, V2> make_pair(T1&& x1, T2&& x2);
}


其中返回值的细节和它们的类型 V1 和 V2, 取决于 x 和 y 的类型。无须深入细节, C++ standard 明确指出, 如果可能的话 make_pair() 使用 move 
语义, 否则就使用 copy 语义。


当我们必须对一个"接受 pair 为实参"的函数传递两个 value 时, make_pair() 尤显方便, 请看下例:

void f(std::pair<int,char *>);
void g(std::pair<const int, std::string>);

...

void foo()
{
    f(std::make_pair(12,"jello"));
    g(std::make_pair(111,"jello"));
}


从本例可以看出, make_pair() 即使在类型并不准确吻合的情况下也能借由 template 构造函数提供的支持顺利运作。当你使用 map 和 multimap 时, 经常
需要这样的能力。

注意,自 C++11 开始, 你也可以使用初值列表(initializer list):

f({42, "jello"});
g({42, "jello"});

然而一个表达式如果明白指出类型, 便带有一个优势: 产生出来的 pair 将有绝对明确的类型。例如:

std::pair<int , float> p1(42,21.43);

所得结果不同于:

std::make_pair(42,21.43);

后者所生成的 pair 的第二元素的类型是 double (因为"无任何限定符的浮点字面常量"的类型被视为 double)。当我们使用重载函数(overloaded function) 
或 template 时, 确切的类型非常重要。

例如, 为了提高效能, 程序员可能同时提供分别针对 float 和 double 的重载函数或 template, 这时候确切的类型就非常重要了。

面对 C++11 新语义, 你可以借由强迫使用 move semantic 或 reference semantic 来影响 make_pair() 的产出类型。如果你的选择是 move semantic, 
只需使用 std::move() 声明被传递的实参不再使用:

std::string s, t;
auto p = std::make_pair(std::move(s), std::move(t));
// s, t are no longer used


// !! pair 之间的比较

为了比较两个 pair 对象, C++ 标准库提供了大家惯用的操作符。两个 pair 对象内的所有元素都相等, 这两个 pair 对象才被视为相等(equal):

namespace std
{
    template<typename T1, typename T2>
    bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    }
}

两个 pair 互相比较时, 第一元素具有较高的优先级。所以如果两个 pair 的第一元素不相等, 其比较结果就成为整个比较的结果。如果 first 相等, 才继续比较
second, 并把比较结果当作整体结果:

namespace std
{
    template <typename T1, typename T2>
    bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }
}


// !! pair 运用实例

C++ 标准库大量使用 pair。例如(unordered) map 和 multimap 容器的元素类型便是 pair, 也就是一对 key/value。


C++ 标准库中凡"必须返回两个 value"的函数也都使用 pair 对象。


// !! Tuple（不定数的值组）

'Tuple 是 TR1 引入的东西, 它扩展了 pair 的概念, 拥有任意数量的元素'。也就是说, tuple 呈现出一个异质元素列(heterogeneous list of elements)
, '其中每个类型都可以被指定, 或来自编译期推导'。


然而, 由于 TR1 用的是 C++98 语言特性, 也就不可能定义出一个"参数个数不定"的 template。基于这个原因, 实现必须具体指明"一个 tuple 可拥有的"所有
可能的元素个数。TR1 对此的建议是至少 10 个实参, 这意味着 tuple 往往被定义如下, 甚至某些实现会提供更多的 template 参数:

template <typename T0 = ..., typename T1 = ..., typename T2 = ..., typename T3 = ..., typename T4 = ...,
 typename T5 = ..., typename T6 = ..., typename T7 = ..., typename T8 = ..., typename T9 = ...> 
 
class tuple;


这显示, class tuple 拥有至少 10 个类型各异的 template 参数, 每个都带有实现赋予的默认类型。未用到的 tuple 元素也有个默认类型, 但没有作用。
这实际上就是 variadic template 的仿效品, 只不过又累赘又有限制。


来到 C++11, variadic template 被引入进来, 使 template 得以接受任何数量的 template 实参。于是, 出现在 <tuple> 中的 class tuple
声明式现在就被简化如下:

namespace std
{
template <typename ...Types>
class tuple;
}


// !! Tuple 的操作

原则上, tuple 接口十分直观:

1. 通过明白的声明, 或使用便捷函数 make_tuple(), 你可以创建一个 tuple

2. 通过 get<>() function template, 你可以访问 tuple 的元素


Tuple 不是寻常的容器, 不允许迭代元素。对于 tuple 可以使用其成员函数来处理元素, 因此必须在编译期知道你打算处理的元素的索引值。例如你可以这样处
理 tuple t1 的第一元素:

get<0>(t1) 


运行期才传入一个索引值是不被允许的:

int i;
get<i>(t1);// compile-error: i is no compile value 


好消息是, 万一传入无效索引, 编译器会报错:


get<32>(t1);// compile-error: if t1 only has three elements


此外, tuple 还提供惯常会有的拷贝、赋值和比较(copy, assignment, and comparison) 操作。它们身上都允许发生隐式类型转换(因为采用 member 
template), 但元素个数必须绝对吻合。如果两个 tuple 的所有元素都相等, 它们就整体相等。检查某个 tuple 是否小于另一个tuple, 采用的是字典编纂式的
比较法则。


// !! 便捷函数 make_tuple() 和 tie()

便捷函数 make_tuple() 会根据 value 建立 tuple, 不需要明确指出元素的类型。例如:

make_tuple(21,23,"jello");

建立并初始化了一个 tuple, 其相应的三个元素类型是 int、int 和 const char*。


借由特别的函数对象 reference_wrapper<> 及便捷函数 ref() 和 cref() (都是自 C++11 被定义于<functional>, 你可以影响 make_tuple() 
产生的类型, 例如以下表达式产出的 tuple 带有一个 reference 指向变量或对象 s:


string s;
make_tuple(12,23.32,ref(s));

如果你打算改动 tuple 内的一个既有值, 上述就很重要:

string s;
auto x = make_tuple(s);
get<0>(x) = "hello";// modify x, not s


auto y = make_tuple(ref(s));// y is type of tuple<string&>, y ref to s
get<0>(y) = "hello";// modify y

运用 reference 搭配 make_tuple() 就可以提取 tuple 的元素值, 将某些变量值设给它们, 例如以下例子:

std::tuple<int, float, std::string> t(77, 12.32, "hello");
int i;
float f;
std::string s;

std::make_tuple(std::ref(i), std::ref(f), std::ref(s)) = t;

如果想最方便地在 tuple 中使用 reference, 可选择 tie(), 它可以建立一个内含 reference 的 tuple:

std::tuple<int, float, std::string> t(77, 12.32, "hello");
int i;
float f;
std::string s;
std::tie(i,f,s) = t;

这里的 std::tie(i, f, s) 会以 i、f 和 s 的 reference 建立起一个 tuple, 因此上述赋值操作其实就是将 t 内的元素分别赋值给 i、f 和 s。
i, f, s 分别 refers to t 中的元素


// !! Tuple 和初值列表(Initializer List)

各个构造函数中, "接受不定个数的实参"的版本被声明为 explicit:


namespace std
{
    template<typename ...Types>
    class tuple
    {
        explicit tuple(const Types...);
        template <typename ...UTypes> explicit tuple(UTypes&&...);
    };
}

'这是为了避免单一值被隐式转换为"带着一个元素"的 tuple'

template<typename ...Args>
foo(std::tuple<Args...> t);

foo(1);// Error, explicit convention to tuple require
foo(std::make_tuple(1));// okay


// !! Tuple 的输入/输出

tuple class 最初公开于 Boost 程序库。在那儿, tuple 可以将其元素写至 output stream, 但 C++ 标准库并不支持这个性质。如果你拥有以下头文
件, 就可以使用标准输出操作符 << 打印任何 tuple:




这段代码大量运用 template metaprogramming, 在编译期递归迭代(recursively iterate)tuple 的所有元素。每次调用 PRINT_TUPLE<>::print() 
就打印出一个元素,然后调用相同函数打印下一个元素。

一个偏特化(partial specialization)版本(其"当前索引 IDX"和 "tuple 内的元素个数 MAX"相等)用来终结递归调用。

举个例子, 下面这个程序:

#include "printtuple.h"

#include <tuple>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    tuple<int, float, string> t(77, 12.21, "hello world");
    cout << "io: " << t << endl;
}

// !! Smart Pointer (智能指针)

'C 语言让我们知道, pointer 很重要, 却是麻烦的来源'。使用 pointer 的理由之一是在惯常的作用域边界之外拥有 reference 语义。

然而, 确保 "pointer 的寿命" 和 "其所指向的对象的寿命" 一致, 却是件棘手的事, '特别是当多个 pointer 指向同一对象时'。

例如, 为了让多个集合拥有同一对象, 你必须把指向该对象的 pointer 放进那些集合内, 而且当其中一个 pointer 被销毁时不该出现问题, 也就是不该出现所
谓的 dangling pointer(空悬指针)或多次删除被指向对象; 最后一个 pointer 被销毁时也不该出现问题(不该造成资源泄漏 resource leak)

避免上述问题的一个通常做法是使用 smart pointer (智能指针)。它们被称为 smart 是因为它们对于上述问题提供了解决方案。举个例子, smart pointer 
有可能如此 smart 以至于能"知道"它自己是不是"指向某物"的最后一个 pointer, 并运用这样的知识, 在它的确是该对象的最后一个拥有者而且它被删除时, 销
毁它所指向的对象。


然而请注意, 只提供一个 smart pointer class 是不够的。Smart pointer 可以在很多方面发挥其智能, 并满足不同重点, 但你可能会为它的 smartness
付出代价。注意, 对于一个独特的 smart pointer, 还是有可能误用 pointer 或写出容易出错的行为。


自 C++11 起, C++ 标准库提供两大类型的 smart pointer:

1. class shared_ptr 实现共享式拥有 (shared ownership) 概念。多个 smart pointer 可以指向相同对象, 该对象和其相关资源会在"最后一个 
   reference 被销毁" 时被释放。


2. class unique_ptr 实现独占式拥有(exclusive ownership) 或严格拥有(strict ownership) 概念, 保证同一时间内只有一个 smart pointer 
   可以指向该对象。你可以移交拥有权。它对于避免资源泄漏(resource leak)——例如"以 new 创建对象后因为发生异常而忘记调用 delete"——特别有用。


C++98 只让 C++ 标准库提供一个 smart pointer class:auto_ptr<>, 其设计是为了执行现今的 unique_ptr 所提供的服务。然而由于当时缺乏语言特性
如"针对构造和赋值"的 move 语义, 以及其他瑕疵, 这个 class 不易被理解且容易出错。因此在 TR1 引入 class shared_ptr, C++11 引入 class 
unique_ptr 之后, class auto_ptr 成为 C++11 中被正式反对(deprecated)的成分, 意味着你不该再使用它, 除非你手上还有一些老旧代码需要编译。


所有 smart pointer class 都被定义于头文件 <memory> 内。


// !! Class shared_ptr

几乎每一个稍有分量的程序都需要 "在相同时间的多处地点处理或使用对象" 的能力。为此, 你必须在程序的多个地点指向(refer to)同一对象。虽然 C++ 语言
提供 reference 和 pointer, 还是不够, 因为你往往必须确保当"指向对象"的最末一个 reference 被删除时该对象本身也被删除, 毕竟对象被删除时析构函数
可以要求某些操作, 例如释放内存或归还资源等等。

所以我们需要"当对象再也不被使用时就被清理"的语义。Class shared_ptr 提供了这样的共享式拥有语义。

也就是说, 多个 shared_ptr 可以共享(或说拥有)同一对象。'对象的最末一个拥有者有责任销毁对象, 并清理与该对象相关的所有资源'。


如果对象以 new 产生, 默认情况下清理工作就由 delete 完成。但你可以(并且往往必须)定义其他清理办法。你可以定义你自己的析构策略。举个例子, 如果你的对
象是个以 new[] 分配而得的 array, 你必须定义你自己的 delete[] 加以清理。其他例子还包括删除相应资源, 如 handle、lock、associated temporary 
file(相关临时文件)等。

'总而言之, shared_ptr 的目标就是, 在其所指向的对象不再被需要之后, 自动释放与对象相关的资源'。


// !! 使用 shared_ptr

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int main()
{

    shared_ptr<string> ps1(new string("world"));
    shared_ptr<string> ps2(new string("hello"));

    (*ps1)[0] = 'M';

    ps2->replace(0, 1, 'Y');


    vector<shared_ptr<string> > vec;

    vec.push_back(ps2);
    vec.push_back(ps1);
    vec.push_back(ps2);
    vec.push_back(ps1);
    vec.push_back(ps2);

    for(auto v : vec)
    {
        cout << (*v) << endl;
    }
    cout << endl;

    *ps1 = "FUCK";

    for(auto v : vec)
    {
        cout << (*v) << endl;
    }

    cout << endl;

    return 0;
}

注意, 由于"接受单一 pointer 作为唯一实参"的构造函数是 explicit, 所以这里你不能够使用赋值符, 因为那样的话会被视为需要一个隐式转换。

shared_ptr<string> ps1 = new string("Hello World");// Error

shared_ptr<string> ps1{new string("hello world")};// okay

也可以使用便捷函数 make_shared():

shared_ptr<string> ps1 = make_shared<string>("hello world");

这种建立方式比较快, 也比较安全, 因为它使用一次而不是二次分配: 一次针对对象, 另一次针对"shared pointer 用以控制对象"的 shared data

另一种写法是, 你可以先声明 shared pointer, 然后对它赋值一个 new pointer。然而你不可以使用 assignment 操作符, 必须改用 reset():

shared_ptr<string> ps1;
ps1 = new string("Hello World");// Error

ps1.reset(new string("Hello World"));// okay

接下来两行示范 shared pointer 的用法, 就像使用寻常的 pointer:

(*ps1)[0] = 'X';
ps1->replace(0, 1, "X");


运用 operator*, 你取得了 ps1 指向的对象, 然后将一个大写的 'X' 指派为其第一字符。运用 operator->, 你得以取用 ps2 所指向的对象内的一个成员, 
而此处成员函数 replace() 允许你替换 substring。

程序终点处, 当 string 的最末一个拥有者被销毁, shared pointer 对其所指向的对象调用 delete。这样的删除动作并非一定发生在作用域终点。例如,
将 nullptr 赋值给 ps1, 或调整 vector 的大小使其只含前两个元素, 都会 delete "当初以 nico 为初值"的 string 的最末一个拥有者。


// !! 定义一个 Deleter

我们可以声明属于自己的 deleter, 例如让它在"删除被指向对象"之前先打印一条信息:

shared_ptr<string> ps1(new string("Hello World"), [](string *p){
  cout << "delete " << *p << endl;
  delete p;
})

这里传递一个 lambda 作为 shared_ptr 构造函数的第二实参。如果令 ps1 以这种方式声明, 当其最末一个拥有者被销毁时, 会调用这个 lambda 函数。



// !! 对付 Array

请注意, shared_ptr 提供的 default deleter 调用的是 delete, 不是 delete[]。这意味着只有当 shared pointer 拥有"由 new 建立起来的单一对象", 
default deleter 方能适才适所。很不幸, 为 array 建立一个 shared_ptr 是可能的, 却是错误的:

std::shared_ptr<int> ps1(new int[10]); error, but compiles successfully

所以, 如果你使用 new[] 建立一个 array of object, 你必须定义你自己的 deleter。这很简单, 你可以传递一个函数、函数对象或 lambda, 让它们针对传入
的寻常指针调用 delete[]。例如:

std::shared_ptr<int> ps1(new int[10], [](int *p){
    delete[] p;
});


也可以使用为 unique_ptr 而提供的辅助函数作为 deleter, 其内调用 delete[]:

std::shared_ptr<int> ps2(new int[10], sdd::default_delete<int[]>());



// !! 其他析构策略

最末一个拥有者——亦即 shared pointer——结束生命时, '如果清理理工作不仅仅是删除内存, 你必须明确给出自己的 deleter'。你可以指定属于自己的析构
策略。

第一个例子: 假设我们想确保"指向某临时文件"之最末一个 reference 被销毁时, 该文件即被移除。可以这么做:

#include <memory>
#include <fstream>
#include <string>
#include <cstdio>// for remove

using namespace std;


class FileDeleter
{
private:
    string filename;

public:
    FileDeleter(const string& fn):filename(fn)
    {

    }

    void operator()(ofstream& fp)
    {
        fp.close();// close file
        remove(filename.c_str());// delete file
    }
};

int main()
{
    std::shared_ptr<ofstream> fp(new ofstream("hello.txt"), FileDeleter("hello.txt"));
    ...
    return 0;
}

传进去的 FileDeleter 负责确保一件事: 当此 shared pointer 的最末一个拷贝失去此输出文件的拥有权时, 该文件将被关闭并被<cstdio> 提供的 C 标准
函数 remove() 移除。由于 remove() 需要文件名, 所以我们以文件名为实参传给 FileDeleter 的构造函数。


第二个例子展示了'如何使用 shared_ptr 处理共享内存(shared memory)':

#include <fcntl.h>
#include <sys/mman.h>  // for shared memory
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class ShareMemoryDetacher {
 public:

  void operator()(int* p) {
    std::cout << "unlink/tmp1234" << std::endl;
    if (shm_unlink("\tmp1234") != 0) {
  std::cerr << "OOPS, shm_unlink failed" << std::endl;
    }
}

  shared_ptr<int> getShareMemory(int num) {
    void* mem;
    int shmfd = shm_open("/tmp1234", 0_CREATE | 0_RDWR, S_TRWXU | S_IRWXU);
    if (shmfd < 0) {
      throw std::string(strerror(errno));
    }
    if (ftruncate(shmfd, num * sizeof(int)) == -1) {
      throw std::string(strerror(errno));
    }
    mem = mmap(nullptr, num * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (mem == MAP_FAILED) {
      throw std::string(strerror(errno));
    }
    return std::shared_ptr<int>(static_cast<int*>(mem), ShareMemoryDetacher());
  }
};

int main()
{
    std::shared_ptr<int> smp(getShareMemory(1024));

    for(int i = 0; i < 100 ; i++)
    {
        smp.get()[i] = i * 1024;
    }
    ...
    cout << "return " << endl;
    cin.get();
    smp.reset();

    return 0;
}


首先定义一个 deleter SharedMemoryDetacher, 用来卸除 (detach) shared memory。这个 deleter 会释放被 getSharedIntMemory() 取得并附
着(attach) 的 shared memory。为确保这个 deleter 会在 shared memory 最末一次被使用后被调用, 我们在"getSharedIntMemory() 为已附着内存
建立起一个 shared_ptr" 时把它当作第二实参传递。

注意, shared_ptr 只提供  operator* 和 operator->, 指针运算和 operator[] 都未提供。因此, 如果想访问内存, 你必须使用 get() 获得被 shared_ptr
包覆(wrapped)的内部指针m, 提供完全的指针语义:

smp.get()[i] = 42;

上述结果等同于以下调用:

(&*smp)[i] = 42;

对于上述两个例子, 另一个实现技术也许更干净利落: 只建立一个 new class X, 让其构造函数执行初始工作, 让其析构函数执行清理工作。然后你就只是使用
shared_ptr 管理以 new 建立的 class X 对象。这样的好处是, 你可定义一个更直观的接口, 例如为一个表现 shared memory 的对象定义一个 operator[]。
然而随后你应该谨慎地想想 copy 和 assignment 操作, 如果不能肯定, 就禁用(disable)它们。


// !!  误用 Shared Pointer

你必须确保某对象只被一组(one group of) shared pointer 拥有。下面的代码是错的:

int *p = new int[10];
shared_ptr<int> sp1(p);
shared_ptr<int> sp2(p);// Error, two shared pointer manager allocate int


问题出在 sp1 和 sp2 都会在丢失 p 的拥有权时释放相应资源(亦即调用 delete)。一般而言, "两组拥有权" 意味着, 相应资源的释放会被执行两次——每当每一
组的最末一个拥有者"丢失其拥有权"或"被销毁"就会执行一次。因此, 你应该总是在创建对象和其相应资源的那一刻直接设立 smart pointer:


shared_ptr<int> ps1(new int);
shared_ptr<int> ps2(ps1);// okay

这个问题也可能间接发生。在先前介绍过的例子中, 假设我们打算为 Person 引入一个成员函数, 用来建立"从 kid 指向 parent "的 reference 及其反向
reference:


shared_ptr<Person> mom(new Person(name + " mom"));
shared_ptr<Person> dad(new Person(name + " dad"));
shared_ptr<Person> kid(new Person(name + " kid"));

kid.setParentAndTheirKids(mom, dad);

下面是一份朴素直观的 setParentsAndTheirKids() 版本:                          0

class Person
{
public:
    ...
    void setParentAndTheirKids(shared_ptr<Person> m = nullptr, shared_ptr<Person> d = nullptr)
    {
        mother = m;
        dad = d;
        if(m != nullptr)
        {
            m->kids.push_back(shared_ptr<Person>(this));
        }
        if(d != nullptr)
        {
            d->kids.push_back(shared_ptr<Person>(this));
        }
    }
    ...
};


问题出在"得自 this 的那个 shared pointer "的建立。之所以那么做是因为, 我们想要设置 mother 和 father 两成员的 kids。但为了那么做, 我们需要一
个 shared pointer 指向 kid, 而那是我们手上没有的。然而, '根据 this 建立起一个新的 shared pointer 并不能解决事情, 因为这么一来就是开启了一个
新的拥有者团队(a new group of owners)'。


对付这个问题的办法之一是, 将指向 kid 的那个 shared pointer 传递为第三实参。





// !! Class unique_ptr


unique_ptr 是 C++ 标准库自 C++11 起开始提供的类型。它是一种在异常发生时可帮助避免资源泄漏的 smart pointer。'一般而言, 这个 smart pointer
实现了独占式拥有概念, 意味着它可确保一个对象和其相应资源同一时间只被一个 pointer 拥有'。

Class unique_ptr 继承 class auto_ptr, 后者由 C++98 引入但已不再被认可。Class unique_ptr 提供了一个更简明干净的接口, 比 auto_pointer 
更不易出错。

函数往往以下列方式运作:

1.获得某些资源

2.执行某些操作

3.将取得的资源释放掉


如果限定 local 对象, 那么函数进入点获得的资源会在函数结束前被自动释放, 因为那些 local 对象的析构函数会被调用。但如果资源是显式获得, 不与任何对
象捆绑, 它们就必须被明确释放掉。'程序使用 pointer 时, 资源往往被显式管理(managed explicitly)'。


以此方式使用 pointer 的典型例子是, 以 new 和 delete 创建和销毁对象:


void f()
{
    ClassA *p = new ClassA();
    ...
    ....
    ...
    delete p;
}

这个函数将成为麻烦制造者。一个明显的问题是, 有可能忘记 delete 对象, 特别是如果你在函数中有个 return 语句。另一个较不明显的危险是它可能抛出异常, 
那将立刻退离(exit)函数, 末尾的 delete 语句也就没机会被调用, 导致内存泄漏, 或更一般性地说,资源泄漏。


为了避免如此的资源泄漏, 通常函数会捕捉所有异常, 例如:


void f()
{
    ClassA * p = new ClassA();
    try {

    }catch(...)
    {
        delete p;
        throw;
    }
    delete p;
}

'为了在异常发生时能够适当处理好对象的删除,代码变得比较复杂,而而且累赘'。如果第二个对象也以此方式处理, 或需要一个以上的 catch 子句, 情况会变得更
糟。'这是一种不好的编程风格, 应该避免, 因为它复杂而又容易出错'。


对此, smart pointer 可以带来帮助。Smart pointer 可以在它自身被销毁时释放其所指向的数据。而且, 由于它是个 local 变量, 所以会在函数结束时被自动
销毁——不论是正常结束或异常结束。Class unique_ptr 就是这样的一个smart pointer。


用 unique_ptr 改写先前的例子如下:

#include <memory>

void f()
{
    std::unique_ptr<ClassA> pa(new ClassA());
    ...
    ...

}

这就够了, 再也不需要 delete 语句和 catch 子句。



// !! 使用 unique_ptr

unique_ptr 有着与寻常 pointer 非常相似的接口, 操作符 * 用来 dereference 对象, 操作符 -> 用来访问成员——如果被指向的对象来自 class 或
struct:


std::unique_ptr<string> ps(new string("Hello World"));
(*ps)[0] = 'Y';
ps->append("Nio");

然而它不提供 pointer 算术如 ++ 等, 这被视为优点, 因为 pointer 算术运算往往是麻烦的来源。

注意, class unique_ptr<> 不允许你以赋值语法将一个寻常的 pointer 当作初值, 因此你必须直接初始化 unique_ptr, 像下面这样:

std::unique_ptr<int> pi = new int();//Error
std::unique_ptr<int> pi(new int());// okay


unique_ptr 不必一定拥有对象, 它也可以是empty。例如当它被 default 构造函数创建出来:

std::unique_ptr<int> pi;


你也可以对它赋予 nullptr 或调用 reset():

pi = nullptr;
pi.reset();


此外, 你可以调用 release(), 获得 unique_ptr 拥有的对象并放弃拥有权, 于是调用者现在对该对象有了责任:

std::unique_ptr<std::string> ps(new string("Hello World"));
...
std::string *sp1 = ps.release();

你可以调用操作符 bool() 用以检查是否 unique pointer 拥有(任何)对象:

if(ps)// if ps is not empty
{

}


// !! 移转 unique_ptr 的拥有权

unique_ptr 提供的语义是"独占式拥有"。然而其实责任在程序员, 由他/她确保"没有任何两个 unique pointer 以同一个 pointer 作为初值":


std::unique_ptr<ClassA> up1(new ClassA());
std::unique_ptr<ClassA> up2;// create another unique_ptr

up2 = up1;// Error

up2 = std::move(up1);// ok, transform ownership from up1 to up2

'这里的 move assignment 将拥有权由 up1 移交给 up2。于是 up2 拥有了先前被 up1 拥有的对象'。

如果上述赋值动作之前 up2 原本拥有对象, 会有一个 delete 动作被调用, 删除该对象:

std::unique_ptr<ClassA> up1(new ClassA());
std::unique_ptr<ClassA> up2(new ClassA());

up2 = std::move(up1);


失去对象拥有权的 unique_ptr 并不会获得一个"指向无物"(refer to no object) 的新拥有权。


如果想要指派新值给 unique_ptr, 新值必须也是个 unique_ptr, 不可以是寻常 pointer:


std::unique_ptr<ClassA> ptr;// create a unique pointer

ptr = new ClassA();// error
ptr = std::unique_ptr<ClassA>(new ClassA());// okay, delete old object and own new

赋值 nullptr 也是可以的, 和调用 reset() 效果相同:

ptr = nullptr;// delete associate object. if any


// !! 源头和去处（Source and Sink）

拥有权的移转暗暗指出了 unique_ptr 的一种用途: 函数可利用它们将拥有权转移给其他函数。这会发生在两种情况下:

1.函数是接收端。如果我们将一个由 std::move() 建立起来的 unique_ptr 以 rvalue reference 身份当作函数实参, 那么被调用函数的参数将会取得
  unique_ptr 的拥有权。因此, 如果该函数不再转移拥有权, 对象会在函数结束时被 deleted:

  vod sink(std::unique_ptr<ClassA> up)// get ownership
  {

  }

  std::unique_ptr<ClassA> up(new ClassA());
  ...
  sink(std::move(up));// up lose ownership
  ...

2. 函数是供应端。当函数返回一个 unique_ptr, 其拥有权会转移至调用端场景(calling context)内。下面的例子展示了这项技术:

std::unique_ptr<ClassA> source()
{
    std::unique_ptr<ClassA> up(new ClassA());
    ...
    return up;// transform ownership to calling function
}

void g()
{
    std::unique_ptr<ClassA> p;
    for(int i = 0; i < 10 ; i++)
    {
        p = source();// p get ownership from return object
    }
}

每当 source() 被调用, 就会以 new 创建对象并返回给调用者, 夹带着其拥有权。返回值被赋值给 p, 于是拥有权也被移转给 p。在循环的第二次迭代中, 对 p 
赋值导致 p 先前拥有的对象会被删除。一旦 g() 结束, p 被销毁, 导致最后一个由 p 拥有的对象被析构。无论如何都不会发生资源泄漏。即使抛出异常, 任何拥
有数据的 unique_ptr 也能确保数据被删除。

在这里, source() 的 return 语句不需要 std::move() 的原因是, C++11 语言规定, 编译器应该自动尝试加上 move。

// !! unique_ptr 被当作成员

'在 class 内使用 unique_ptr 可避免资源泄漏'。如果你使用 unique_ptr 取代寻常 pointer, 就不再需要析构函数, 因为对象被删除会连带使所有成员被删
除。此外 unique_ptr 也可协助避免"对象初始化期间因抛出异常而造造成资源泄漏"。

注意, '只有当一切构造动作都完成了, 析构函数才有可能被调用'。因此一旦构造期间发生异常, 只有那些已完全构造好的对象, 其析构函数才会被调用。所以, 对于
"拥有多个 raw pointer "的 class, 如果构造期间第一个 new 成功而第二个失败, 就可能导致资源泄漏。例如:

class ClassB
{
private:
    ClassA* ptr1;
    ClassA* ptr2;
public:
    ClassB(int val1, int val2) : ptr1(val1), ptr2(val2)
    {

    }

    ClassB(const ClassB& x) :ptr1(new ClassA(*x.ptr1)), ptr2(new ClassA(*x.ptr2))
    {

    }

    const ClassB& operator=(const ClassB& x)
    {
        *ptr1 = *x.ptr1;
        *ptr2 = *x.ptr2;
        return *this;
    }

    ~ClassB()
    {
        delete ptr1;
        delete ptr2;
    }
    ....
};

只需使用 unique_ptr, 就可以避免上述可能的资源泄漏:

class ClassB
{
private:

    std::unique_ptr<ClassA> ptr1;
    std::unique_ptr<ClassA> ptr2;

public:

    ClassB(int val1, int val2): ptr1(new ClassA(val1)), ptr2(new ClassA(val2)){}

    ClassB(const ClassB &x) : ptr1(new ClassA(x.ptr1)), ptr2(new ClassA(x.ptr2)){}

    const ClassB& operator=(const ClassB& x)
    {
        *ptr1 = *x.ptr1;
        *ptr2 = *x.ptr2;
        return *this;
    }
};







