// !! 对象和类

'面向对象编程(OOP) 是一种特殊的、设计程序的概念性方法'，C++ 通过一些特性改进了 C 语言，使得应用这种方法更容易。

下面是最重要的 OOP 特性:

1. 抽象

2. 封装和数据隐藏

3. 多态

5. 继承

6. 代码的可重用性

为了实现这些特性并将它们组合在一起，C++ 所做的最重要的改进是提供了类。

// !! 过程性编程和面向对象编程

1. 采用过程性编程方法时，首先考虑要遵循的步骤，然后考虑如何表示这些数据

2. 采用 OOP 方法时，首先从用户的角度考虑对象——描述对象所需的数据以及描述用户与数据交互所需的操作。完成对接口的描述后，需要确定如何实现接口和数据存储。
   最后，使用新的设计方案创建出程序。


// !! 抽象和类

'将问题的本质特征抽象出来，并根据特征来描述解决方案'。抽象是通往用户定义类型的捷径，在 C++ 中，用户定义类型指的是实现抽象接口的类设计。

// !! 类型是什么

我们来看看是什么构成了类型。

首先，倾向于根据数据的外观(在内存中如何存储)来考虑数据类型。例如，char 占用 1 个字节的内存，而 double 通常占用 8 个字节的内存。但是稍加思索就会发现，
也可以'根据要对它执行的操作来定义数据类型'。

例如，int 类型可以使用所有的算术运算，可对整数执行加、减、乘、除运算，还可以对它们使用求模运算符（%）

而指针需要的内存数量很可能与 int 相同，甚至可能在内部被表示为整数。但不能对指针执行与整数相同的运算。例如，不能将两个指针相乘，这种运算没有意义的，因此 
C++ 没有实现这种运算。因此，'将变量声明为 int 或 float 指针时，不仅仅是分配内存，还规定了可对变量执行的操作'。


总之，指定基本类型完成了三项工作:

1. 决定数据对象需要的内存数量

2. 决定如何解释内存中的位(long 和 float 在内存中占用的位数相同，但将它们转换为数值的方法不同)

3. 决定可使用数据对象执行的操作或方法。

对于内置类型来说，有关操作的信息被内置到编译器中。但'在 C++ 中定义用户自定义的类型时，必须自己提供这些信息'。

付出这些劳动换来了根据实际需要定制新数据类型的强大功能和灵活性。

// !! C++ 中的类

'类是一种将抽象转换为用户定义类型的 C++ 工具'，它将数据表示和操纵数据的方法组合成一个整洁的包。

一般来说，类规范由两个部分组成:

1. 类声明: 以数据成员的方式描述数据部分，以成员函数(被称为方法)的方式描述公有接口

2. 类方法定义: 描述如何实现类成员函数



'什么是接口?'

接口是一个共享框架，供两个系统(如在计算机和打印机之间或者用户或计算机程序之间)交互时使用。

为开发一个类并编写一个使用它的程序，需要完成多个步骤。这里将开发过程分成多个阶段，而不是一次性完成。通常，C++ 程序员将接口(类定义)放在头文件中，并将实现(
类方法的代码)放在源代码文件中。这里采用这种典型做法。

Stock00.h 是第一个阶段的代码，它是 Stock 类的类声明。
#ifndef E14C33FD_BE4B_4C8A_BC23_01FEB92F5BA4
#define E14C33FD_BE4B_4C8A_BC23_01FEB92F5BA4

#include<string>

class Stock
{
private:
    long shares;
    double share_val;
    double total_val;
    void set_tot() { total_val - share_val *shares; }

public:
    void acquire(const std::string &co, long n, double pr);
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif /* E14C33FD_BE4B_4C8A_BC23_01FEB92F5BA4 */


首先，C++ 关键字 class 指出这些代码定义了一个类设计。这种语法指出，Stock 是这个新类的类型名。该声明让我们能够声明 Stock 类型的变量——称为对象或实例。
每个对象都表示一支股票。例如，下面的声明创建两个 Stock 对象，它们分别名为 sally 和 solly:

Stock sally;
Stock solly;

例如，sally对 象可以表示 Sally 持有的某公司股票。

接下来，要存储的数据以类数据成员(如 company 和 shares) 的形式出现。

例如，sally 的 company 成员存储了公司名称，share 成员存储了 Sally 持有的股票数量，share_val 成员存储了每股的价格，total_val 成员存储了股票总价格。
同样，要执行的操作以类函数成员(方法，如 sell()和 update())的形式出现。成员函数可以就地定义(如 set_tot())，也可以用原型表示。

'将数据和方法组合成一个单元是类最吸引人的特性'

istream 和 ostream 类有成员函数，如 get() 和 getline()，而 Stock 类声明中的函数原型说明了成员函数是如何建立的。例如，头文件 iostream 将 getline() 
的原型放在 istream 类的声明中。

1. 访问控制

关键字 private 和 public 也是新的，它们描述了对类成员的访问控制。使用类对象的程序都可以直接访问公有部分，但只能通过公有成员函数(或友元函数)来访问对
象的私有成员。因此，'公有成员函数是程序和对象的私有成员之间的桥梁，提供了对象和程序之间的接口。防止程序直接访问数据被称为数据隐藏'。'类设计尽可能将公有接口
与实现细节分开。公有接口表示设计的抽象组件。将实现细节放在一起并将它们与抽象分开被称为封装'。

OOP 和 C++

OOP 是一种编程风格，从某种程度说，它用于任何一种语言中。当然，可以将 OOP 思想融合到常规的 C 语言程序中。

数据隐藏不仅可以防止直接访问数据，还让开发者(类的用户)无需了解数据是如何被表示的。例如，show() 成员将显示某支股票的总价格(还有其他内容），这个值可以存储在对象
中，也可以在需要时通过计算得到。从使用类的角度看，使用哪种方法没有什么区别。所需要知道的只是各种成员函数的功能；也就是说，'需要知道成员函数接受什么样的参数以及返
回什么类型的值'。原则是将实现细节从接口设计中分离出来。如果以后找到了更好的、实现数据表示或成员函数细节的方法，可以对这些细节进行修改，而无需修改程序接口，这使
程序维护起来更容易。

2. 控制对成员的访问:公有还是私有

无论类成员是数据成员还是成员函数, 都可以在类的公有部分或私有部分中声明它。但'由于隐藏数据是 OOP 主要的目标之一，因此数据项通常放在私有部分，组成类接口的成员\
函数放在公有部分'；否则，就无法从程序中调用这些函数。

不必在类声明中使用关键字 private，因为这是类对象的默认访问控制:

class World
{
    float mass;// private by default
    char name[20];

public:
    void tellall() const;
}

'然而，为强调数据隐藏的概念，本书显式地使用了 private'。

'类和结构'

 类描述看上去很像是包含成员函数以及 public 和 private 可见性标签的结构声明。实际上，C++ 对结构进行了扩展，使之具有与类相同的特性。'它们之间唯一的区别是，
 结构的默认访问类型是 public，而类为 private'。'C++ 程序员通常使用类来实现类描述，而把结构限制为只表示纯粹的数据对象'(常被称为普通老式数据
 (POD，Plain Old Data)结构)。


3. 实现类成员函数

还需要创建类描述的第二部分: 为那些由类声明中的原型表示的成员函数提供代码。成员函数定义与常规函数定义非常相似，它们有函数头和函数体，也可以有返回类型和参数。
但是它们还有两个特殊的特征:'定义成员函数时，使用作用域解析运算符(::)来标识函数所属的类; 类方法可以访问类的 private 组件'。


'其定义位于类声明中的函数都将自动成为内联函数'，因此 Stock::set_tot() 是一个内联函数。类声明常将短小的成员函数作为内联函数，set_tot() 符合这样的要求。


4. 使用类

知道如何定义类及其方法后，来创建一个程序，它创建并使用类对象。'C++ 的目标是使得使用类与使用基本的内置类型(如 int 和 char)尽可能相同'。要创建类对象，可以
声明类变量，也可以使用 new 为类对象分配存储空间。可以将对象作为函数的参数和返回值，也可以将一个对象赋给另一个。

C++ 提供了一些工具，可用于初始化对象、让 cin 和 cout 识别对象，甚至在相似的类对象之间进行自动类型转换。虽然要做到这些工作还需要一段时间，但可以先从比较简单
的属性着手。

usestock0.cpp 提供了一个使用上述接口和实现文件的程序，它创建了一个名为 fluffy_the_cat 的 Stock 对象。该程序非常简单，但确实测试了这个类的特性。

#include<iostream>
#include "Stock00.h"

int main()
{
    Stock fluffy_the_cat;
    fluffy_the_cat.acquire("hello",20,12.32);
    fluffy_the_cat.show();
    fluffy_the_cat.buy(15,21.32);
    fluffy_the_cat.show();
    fluffy_the_cat.sell(10,21.32);
    fluffy_the_cat.show();
    return 0;
}

main() 只是用来测试 Stock 类的设计。当 Stock 类的运行情况与预期的相同后，便可以在其他程序中将 Stock 类作为用户定义的类型使用。'要使用新类型，最关键的是
要了解成员函数的功能，而不必考虑其实现细节'。


5. 修改实现

ostream 类包含一些可用于控制格式的成员函数。

std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);

这设置了 cout 对象的一个标记，'命令 cout 使用定点表示法'。同样，下面的语句导致 cout 在使用定点表示法时，显示三位小数:

std::cout.precision(3);


6. 小结

指定类设计的第一步是提供类声明。类声明类似结构声明，可以包括数据成员和函数成员。声明有私有部分，在其中声明的成员只能通过成员函数进行访问；声明还具有公有部分，
在其中声明的成员可被使用类对象的程序直接访问。


// !! 类的构造函数和析构函数

对于 Stock 类，还有其他一些工作要做。'应为类提供被称为构造函数和析构函数的标准函数'。下面来看一看为什么需要这些函数以及如何使用这些函数。

'C++ 的目标之一是让使用类对象就像使用标准类型一样'，然而，到现在为止，本章提供的代码还不能让您像初始化 int 或结构那样来初始化 Stock 对象。也就是说，
常规的初始化语法不适用于类型 Stock:

int year = 2021;

struct thing 
{
    char *pn;
    int m;
};
thing amabob = {"widget", 20};

Stock hot = {"nio",2000,121.21};// NO! compile error

不能像上面这样初始化 Stock 对象的原因在于, 数据部分的访问状态是私有的，这意味着程序不能直接访问数据成员。

您已经看到，程序只能通过成员函数来访问数据成员，因此需要设计合适的成员函数，才能成功地将对象初始化(如果使数据成员成为公有，而不是私有，就可以按刚才介绍的方法
初始化类对象，但使数据成为公有的违背了类的一个主要初衷：数据隐藏)。

一般来说，最好是在创建对象时对它进行初始化。例如，请看下面的代码:

Stock gift;
gift.buy("nio",12,21.32);

就 Stock 类当前的实现而言，gift 对象的 company 成员是没有值的。'类设计假设用户在调用任何其他成员函数之前调用 acquire()，但无法强加这种假设'。避开这种问
题的方法之一是在创建对象时, 自动对它进行初始化。'为此，C++ 提供了一个特殊的成员函数——类构造函数，专门用于构造新对象、将值赋给它们的数据成员'。

1. 声明和定义构造函数

现在需要创建 Stock 的构造函数。由于需要为 Stock 对象提供 3 个值，因此应为构造函数提供 3 个参数。程序员可能只想设置 company 成员，而将其他值设置为 0；这可
以使用默认参数来完成。因此，原型如下所示：

Stock(const std::string &co, long n = 0, double pr = 0);

下面是构造函数的一种可能定义:

Stock::Stock(const std::string &co, long n, double pr)
{
    company = co;
    if(n < 0)
    {
        std::cerr << "Number of shares cannot be negative\n";
        share = 0;
    }
    else
    {
        share = n;
    }
    share_val = pr; 
    set_tot();
}

上述代码和本章前面的函数 acquire() 相同。区别在于: '程序声明对象时，将自动调用构造函数'。

C++ 提供了两种使用构造函数来初始化对象的方式:

1. 第一种方式是显式地调用构造函数

Stock food = Stock("world food",250,1.25);

这将 food 对象的 company 成员设置为字符串 "world food", 将 share 成员设置为 250，依此类推。

2. 另一种方式是隐式地调用构造函数

Stock garment("nio",234,32.21);

这种格式更紧凑，它与下面的显式调用等价

Stock garment = Stock("nio",234,32.21);

每次创建类对象(甚至使用 new 动态分配内存)时，C++ 都使用类构造函数。下面是将构造函数与 new 一起使用的方法

Stock *pstock = new Stock("nio",234,32.21);

这条语句创建一个 Stock 对象，将其初始化为参数提供的值，并将该对象的地址赋给 pstock 指针。'在这种情况下，对象没有名称，但可以使用指针来管理该对象'。

构造函数的使用方式不同于其他类方法。一般来说，使用对象来调用方法:

stock1.show();// stock1 object invokes show() method

无法使用对象来调用构造函数, 因为在构造函数构造出对象之前,对象是不存在的。'因此构造函数被用来创建对象，而不能通过对象来调用'。

// !!默认构造函数

'默认构造函数是在未提供显式初始值时, 用来创建对象的构造函数'。也就是说，它是用于下面这种声明的构造函数:

Stock fluffy_the_cat;

'这条语句管用的原因在于，如果没有提供任何构造函数，则 C++ 将自动提供默认构造函数'。它是默认构造函数的隐式版本，不做任何工作。对于 Stock 类来说，默认构
造函数可能如下:

Stock::Stock()
{
    ...
}

因此将创建 fluffy_the_cat 对象，但不初始化其成员，这和下面的语句创建 x，但没有提供值给它一样:

int x;

默认构造函数没有参数, 因为声明中不包含值。

奇怪的是，当且仅当没有定义任何构造函数时，编译器才会提供默认构造函数。'为类定义了构造函数后，程序员就必须为它提供默认构造函数'。

如果提供了非默认构造函数(如 Stock(const char * co, int n, double pr))，但没有提供默认构造函数, 则下面的声明将出错:

Stock stock1;// not possible for current constructor

'这样做的原因可能是想禁止创建未初始化的对象'。然而，如果要创建对象，而不显式地初始化，则必须定义一个不接受任何参数的默认构造函数。

定义默认构造函数的方式有两种:

1. 给已有构造函数的所有参数提供默认值

Stock(const char * co = "Error", int n = 0, double pr = 0));

2. 通过函数重载来定义另一个构造函数---一个没有参数的构造函数

Stock()

由于只能有一个默认构造函数，因此不要同时采用这两种方式。'实际上，通常应初始化所有的对象，以确保所有成员一开始就有已知的合理值'。
因此，用户定义的默认构造函数通常给所有成员提供隐式初始值。例如，下面是为 Stock 类定义的一个默认构造函数：

Stock::Stock()
{
    company = "no name";
    share = 0;
    share_val = 0;
    total_val = 0;
}

使用上述任何一种方式(没有参数或所有参数都有默认值) 创建了默认构造函数后，便可以声明对象变量，而不对它们进行显式初始化:

Stock first;
Stock second = Stock();
Stock *pthird = new Stock();

然而，不要被非默认构造函数的隐式形式所误导：

Stock first("hello world");// calls constructor
Stock second();// declares function
Stock third; // call default constructor


// !! 析构函数

用构造函数创建对象后，程序负责跟踪该对象，直到其过期为止。'对象过期时,程序将自动调用一个特殊的成员函数，该函数的名称令人生畏——析构函数'。
析构函数完成清理工作，因此实际上很有用。

例如，如果构造函数使用 new 来分配内存，则析构函数将使用 delete 来释放这些内存。Stock 的构造函数没有使用 new，因此析构函数实际上没有需要完成的任务。
在这种情况下，只需让编译器生成一个什么都不做的隐式析构函数即可，Stock 类第一版正是这样做的。然而，了解如何声明和定义析构函数是绝对必要的，下面为 Stock 
类提供一个析构函数。

和构造函数一样，析构函数的名称也很特殊：在类名前加上 ~。因此，Stock 类的析构函数为 ~Stock( )。另外，和构造函数一样，析构函数也可以没有返回值和声明类型。
与构造函数不同的是，析构函数没有参数，因此 Stock 析构函数的原型必须是这样的：

~Stock()；

由于 Stock 的析构函数不承担任何重要的工作，因此可以将它编写为不执行任何操作的函数：

Stock::Stock()
{
    ...
}

然而，为让您能看出析构函数何时被调用，这样编写其代码:

Stock::Stock() 
{
    cout << "Bye~, " << company << '\n';
}

什么时候应调用析构函数呢？ '这由编译器决定，通常不应在代码中显式地调用析构函数'。


1. 如果创建的是静态存储类对象，则其析构函数将在程序结束时自动被调用

2. 如果创建的是自动存储类对象，则其析构函数将在程序执行完代码块时(该对象是在其中定义的)自动被调用

3. 如果对象是通过 new 创建的，则它将驻留在栈内存或自由存储区中，当使用 delete 来释放内存时，其析构函数将自动被调用

最后，程序可以创建临时对象来完成特定的操作，在这种情况下，程序将在结束对该对象的使用时自动调用其析构函数。


由于在类对象过期时析构函数将自动被调用，因此必须有一个析构函数。如果程序员没有提供析构函数，编译器将隐式地声明一个默认析构函数，并在发现导致对象被删除的代
码后，提供默认析构函数的定义。

// !! 改进 Stock 类

下面将构造函数和析构函数加入到类和方法的定义中。'鉴于添加构造函数的重大意义，这里将名称从 stock00.h 改为 stock10.h'。类方法放在文件 stock10.cpp 中。最
后，将使用这些资源的程序放在第三个文件中，这个文件名为 usestock2.cpp 。


1．头文件

stock10.h 它将构造函数和析构函数的原型加入到原来的类声明中。另外，它还删除了 acquire() 函数——现在已经不再需要它了，因为有构造函数。该文件还'使用 
#ifndef 技术来防止多重包含'。

#ifndef CAB47F49_65A5_461D_8B44_16C4476D2470
#define CAB47F49_65A5_461D_8B44_16C4476D2470

#include <string>
class Stock
{
    private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot(){total_val = share_val * shares;};

    public:
    Stock();// default constructor
    Stock(std::string &co, long n = 0, double pr = 0);
    ~Stock();// destructor
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif /* CAB47F49_65A5_461D_8B44_16C4476D2470 */


2．实现文件

stock10.cpp 提供了方法的定义。它包含了文件 stock10.h，以提供类声明(将文件名放在双引号而不是方括号中意味着编译器将源文件所在的目录中搜索它)。另外，程序
stock10.cpp 还包含了头文件 iostream，以提供 I/O 支持。该程序清单还使用 using 声明和限定名称(如 std::string)来访问头文件中的各种声明。该文件将构造
函数和析构函数的方法定义添加到以前的方法定义中。为让您知道这些方法何时被调用，它们都显示一条消息。这并不是构造函数和析构函数的常规功能，但有助于您更好地了
解类是如何使用它们的。

3．客户文件

usestock2.cpp 提供了一个测试这些新方法的小程序；由于它只是使用 Stock 类，因此是 Stock 类的客户。和 stock10.cpp 一样，它也包含了文件 stock10.h 
以提供类声明。

#include<iostream>
#include "stock10.h"

int main()
{
    using std::cout;
    cout << "Using constructor to create new object\n";
    Stock stock1("Nio",2111,12.32);
    stock1.show();
    Stock stock2 = Stock("NIO",21,23.32);
    stock2.show();

    cout << "Assigning stock1 to stock2\n";
    // 与给结构赋值一样，在默认情况下，给类对象赋值时，将把一个对象的成员复制给另一个
    stock2 = stock1;

    cout << "Listing stock1 and stock2\n";
    stock1.show();
    stock2.show();

    cout << "Using a constructor to reset a object\n";
    // 构造函数不仅仅可用于初始化新对象
    // stock1 对象已经存在，因此这条语句不是对 stock1 进行初始化，而是将新值赋给它
    // 这是通过让构造程序创建一个新的、临时的对象，然后将其内容复制给 stock1 来实现的
    // 随后程序调用析构函数，以删除该临时对象
    stock1 = Stock("XV",21,21.23);// temp object
    cout << "Revised stock1\n";
    stock1.show();
    cout << "Done\n";
    return 0;
}

函数 main() 结束时，其局部变量(stock1 和 stock2)将消失。'由于这种自动变量被放在栈中，因此最后创建的对象将最先被删除，最先创建的对象将最后被删除'。


// !! C++11 列表初始化

在 C++11 中，可将列表初始化语法用于类吗？ 可以，'只要提供与某个构造函数的参数列表匹配的内容'，并用大括号将它们括起:

Stock hot_tip = {"NIO",123,32.32};

Stock stock{"APPLE"};

Stock temp{};

在前两个声明中，用大括号括起的列表与下面的构造函数匹配:

Stock(const char * co = "Error", int n = 0, double pr = 0));

因此，将使用该构造函数来创建这两个对象。创建对象 stock 时，第二和第三个参数将为默认值 0 和 0.0。第三个声明与默认构造函数匹配，因此将使用该构造函数创建对象
temp。

另外，C++11 还提供了名为 std::initialize_list 的类，可将其用作函数参数或方法参数的类型。'这个类可表示任意长度的列表，只要所有列表项的类型都相同或可转换
为相同的类型'。

// !! const 成员函数

请看下面的代码片段:

const Stock land = Stock("NIO",123,32.23);
land.show()

对于当前的 C++ 来说，编译器将拒绝第二行。这是什么原因呢？因为 show() 的代码无法确保调用对象不被修改——调用对象和 const 一样，不应被修改。

我们以前通过将函数参数声明为 const 引用或指向 const 的指针来解决这种问题。但这里存在语法问题：show() 方法没有任何参数。相反，它所使用的对象是由方法调用隐
式地提供的。需要一种新的语法——保证函数不会修改调用对象。'C++ 的解决方法是将 const 关键字放在函数的括号后面'。也就是说，show() 声明应像这样:

void show() const;

同样，函数定义的开头应像这样：

Stock::show() const
{

}

'以这种方式声明和定义的类函数被称为 const 成员函数'

// !! 构造函数和析构函数小结

构造函数是一种特殊的类成员函数，在创建类对象时被调用。构造函数的名称和类名相同，但通过函数重载，可以创建多个同名的构造函数，条件是每个函数的特征标(参数列表)
都不同。另外，构造函数没有声明类型。'通常，构造函数用于初始化类对象的成员'，初始化应与构造函数的参数列表匹配。

默认构造函数没有参数，因此如果创建对象时没有进行显式地初始化，则将调用默认构造函数。如果程序中没有提供任何构造函数，则编译器会为程序定义一个默认构造函数；否
则，必须自己提供默认构造函数。

就像对象被创建时程序将调用构造函数一样，当对象被删除时，程序将调用析构函数。每个类都只能有一个析构函数。析构函数没有返回类型(连void都没有)，也没有参数，
其名称为类名称前加上~。

'如果构造函数使用了 new，则必须提供使用 delete 的析构函数'。


// !! this 指针

const Stock & topval(const Stock & s) const;

'该函数隐式地访问一个对象，而显式地访问另一个对象，并返回其中一个对象的引用'。括号中的 const 表明，该函数不会修改被显式地访问的对象；而括号后的 const 
表明，该函数不会修改被隐式地访问的对象。由于该函数返回了两个 const 对象之一的引用，因此返回类型也应为 const 引用。

假设要对 Stock 对象 stock1 和 stock2 进行比较，并将其中股价总值较高的那一个赋给 top 对象，则可以使用下面两条语句之一:

top = stock1.topval(stock2);
top = stock2.topval(stock1);

第一种格式隐式地访问 stock1，而显式地访问 stock2； 第二种格式显式地访问 stock1，而隐式地访问 stock2。无论使用哪一种方式，都将对这两个对象进行比较，并
返回股价总值较高的那一个对象。

实际上，这种表示法有些混乱。'如果可以使用关系运算符 > 来比较这两个对象，将更为清晰'。可以使用运算符重载完成这项工作。

同时，还要注意的是 topval() 的实现，它将引发一个小问题。下面的部分实现强调了这个问题:

const Stock & topval(const Stock & s) const
{
    if(s.total_val > total_val)
    {
        return s;
    }
    else
    {
        return ???;
    }
}

其中 s.total_val 是作为参数传递的对象的总值，total_val 是用来调用该方法的对象的总值。如果 s.total_val 大于 toatl_val，则函数将返回指向 s 的引用；
否则，将返回用来调用该方法的对象(在 OOP 中，是 topval 消息要发送给的对象)。

问题在于，如何称呼这个对象？ 

如果调用 stock1.topval(stock2)，则 s 是 stock2 的引用(即 stock2 的别名)，但 stock1 没有别名。

C++ 解决这种问题的方法是: 使用被称为 this 的特殊指针。'this 指针指向用来调用成员函数的对象(this 被作为隐藏参数传递给方法)'。这样，函数调用 
stock1.topval(stock2) '将 this 设置为 stock1 对象的地址'，使得这个指针可用于 topval() 方法。同样，函数调用 stock2.topval（stock1）'将 this 设置
为 stock2 对象的地址'。


'一般来说，所有的类方法都将 this 指针设置为调用它的对象的地址'。


注意:

'每个成员函数(包括构造函数和析构函数)都有一个 this 指针'。this 指针指向调用对象。如果方法需要引用整个调用对象，则可以使用表达式 *this。在函数的括号后面
使用 const 限定符将 this 限定为 const，这样将不能使用 this 来修改对象的值。然而，'要返回的并不是 this，因为 this 是对象的地址，而是对象本身，即 *this'
(将解除引用运算符*用于指针，将得到指针指向的值)。现在，可以将 *this 作为调用对象的别名来完成前面的方法定义。


const Stock & topval(const Stock & s) const
{
    if(s.total_val > total_val)
    {
        return s;
    }
    else
    {
        return *this;
    }
}

返回类型为引用意味着返回的是调用对象本身，而不是其副本。

// !! 对象数组

和 Stock 示例一样，用户通常要创建同一个类的多个对象。可以创建独立对象变量，但创建对象数组将更合适。这似乎是在介绍一个未知领域，但实际上，声明对象数组的方法
与声明标准类型数组相同:

Stock mystuff[4];// create an array with 4 stock object

当程序创建未被显式初始化的类对象时，总是调用默认构造函数。上述声明要求，这个类要么没有显式地定义任何构造函数(在这种情况下，将使用不执行任何操作的隐式默认构造
函数)，要么定义了一个显式默认构造函数。每个元素(mystuff[0]、mystuff[1] 等)都是 Stock 对象，可以使用 Stock 方法:


mystuff[0].update(123.32);
mystuff[1].show();

可以用构造函数来初始化数组元素。在这种情况下，必须为每个元素调用构造函数:

const int STKS = 4;
Stock stock[STKS] = {
    Stock("NIO",121,1111.23),
    Stock("Apple",12,321.3),
    Stock("Alibaba",232,321.3),
    Stock("NIOXF",2222,2222.32)
};

这里的代码使用标准格式对数组进行初始化:用括号括起的、以逗号分隔的值列表。其中，每次构造函数调用表示一个值。如果类包含多个构造函数，则可以对不同的元素使用
不同的构造函数。

'初始化对象数组的方案是，首先使用默认构造函数创建数组元素，然后花括号中的构造函数将创建临时对象，然后将临时对象的内容复制到相应的元素中'。因此，要创建类对
象数组，则这个类必须有默认构造函数。

usestock3.cpp 在一个小程序中使用了这些原理，该程序对 4 个数组元素进行初始化，显示它们的内容，并找出这些元素中总值最高的一个。由于 topval() 每次只检查两个
对象，因此程序使用 for 循环来检查整个数组。另外，它使用 stock 指针来跟踪值最高的元素。

#include<iostream>
#include "stock20.h"

const int STKS =4;

int main()
{
    Stock stocks[STKS] = {
        Stock("NIO",22,12.21),
        Stock("APPLE",21,12.21),
        Stock("NIOXF",12321,21.234),
        Stock("xforg",12,21.234)
    };

    std::cout << "Stock holdings\n";
    int st;
    for( st =0; st < STKS; st++ )
    {
        stocks[st].show();
    }

    // set pointer to first elements
    const Stock *pStock = &stocks[0];
    for( st = 1; st < STKS; st++ )
    {
        top =  &(top->topval(stocks[st]));
    }

    std::cout << "most valuable holdings:\n";
    top->show();
    return 0;
}

顺便说一句，知道 this 指针就可以更深入了解 C++ 的工作方式。例如，最初的 UNIX 实现使用 C++ 前端 cfront 将 C++ 程序转换为 C 程序。
处理方法的定义时，只需将下面这样的 C++ 方法定义：

void Stock::show() const
{
    cout << "Company is " << Company << "\n";
}

转换为下面这样的 C-风格定义：

void show(const Stock *this) const
{
    cout << "Company is " << Company << "\n";
}

同样，该前端将下面的函数调用:

top.show();

转换为：

show(&top);

这样，将调用对象的地址赋给了 this 指针(实际情况可能更复杂些)。

// !! 类作用域

'在类中定义的名称(如类数据成员名和类成员函数名)的作用域都为整个类，作用域为整个类的名称只在该类中是已知的，在类外是不可知的'。

因此，可以在不同类中使用相同的类成员名而不会引起冲突。例如，Stock 类的 shares 成员不同于 JobRide 类的 shares 成员。另外，类作用域意味着不能从外部直接
访问类的成员，公有成员函数也是如此。也就是说，要调用公有成员函数，必须通过对象。


Stock sleeper = {"NIO",123,32.21};
sleeper.show();

show();// invalid 

同样，在定义成员函数时，必须使用'作用域解析运算符':

void Stock::show() const
{
    ...
}

总之，在类声明或成员函数定义中，可以使用未修饰的成员名称(未限定的名称)，就像 sell() 调用 set_tot() 成员函数时那样。在其他情况下，使用类成员名时，必须根据
上下文使用直接成员运算符(．)、间接成员运算符(->)或作用域解析运算符(::)。下面的代码片段演示了如何访问具有类作用域的标识符:


class TK
{
private:
    int fuss;// fuss has class scope
public:
    TK(int f = 9)
    {
        fuss = f;
    }
    void viewTK() const;// viewTK has class scope
}

void TK::viewTK() const
{
    cout << fuss << endl;
}

int main()
{
    Tk *pTk = new Tk();
    Tk ee = TK(8);
    ee.viewTK();
    pTk->viewTK();
    return 0;
}


// !! 作用域为类的常量

'有时候，使符号常量的作用域为类很有用'。例如，类声明可能使用字面值 30 来指定数组的长度，由于该常量对于所有对象来说都是相同的，因此创建一个由所有对象共享的
常量是个不错的主意。您可能以为这样做可行:

class Bakery
{
private:
    const int Months = 12;// declare a constant ? FAIL
    double costs[Months];
    ...
}

但这是行不通的，'因为声明类只是描述了对象的形式，并没有创建对象'。因此，在创建对象前，将没有用于存储值的空间(实际上，C++11 提供了成员初始化，但不适用于前述
数组声明)。

有两种方式可以实现这个目标，并且效果相同:

1. 在类中声明一个枚举。在类声明中声明的枚举的作用域为整个类，因此可以用枚举为整型常量提供作用域为整个类的符号名称
   也就是说，可以这样开始 Bakery 声明：

class Bakery
{
private:
    enum {Months=12};
    double costs[Months];
    ...
};

'用这种方式声明枚举并不会创建类数据成员'。也就是说，所有对象中都不包含枚举。另外，Months 只是一个符号名称，在作用域为整个类的代码中遇到它时，编译器将用 12 
来替换它。由于这里使用枚举只是为了创建符号常量，并不打算创建枚举类型的变量，因此不需要提供枚举名。顺便说一句，在很多实现中，ios_base 类在其公有部分中完成了
类似的工作，诸如 ios_base::fixed 等标识符就来自这里。其中，fixed 是 ios_base 类中定义的典型的枚举量。

2. C++ 提供了另一种在类中定义常量的方式---使用关键字 static

class Bakery
{
private:
    static const int Months = 12;
    double costs[Months];
    ...
};

'这将创建一个名为 Months 的常量，该常量将与其他静态变量存储在一起，而不是存储在对象中'。因此，只有一个 Months 常量，被所有 Bakery 对象共享。


// !! 作用域内枚举(C++11)

传统的枚举存在一些问题，其中之一是两个枚举定义中的枚举量可能发生冲突。假设有一个处理鸡蛋和T恤的项目，其中可能包含类似下面这样的代码:

enum egg{Small,Medium,Large};
enum t_shirt{Small,Medium,Large};


这将无法通过编译，因为 egg Small 和 t_shirt Small 位于相同的作用域内，它们将发生冲突。为避免这种问题，C++11 提供了一种新枚举，其枚举量的作用域为类。
这种枚举的声明类似于下面这样：

enum class egg{Small,Medium,Large};
enum class t_shirt{Small,Medium,Large};

无论使用哪种方式，都需要使用枚举名来限定枚举量:

egg choice = egg::Small;
t_shirt flod = t_shirt::Small;

枚举量的作用域为类后，不同枚举定义中的枚举量就不会发生名称冲突了

'C++11 还提高了作用域内枚举的类型安全'。在有些情况下，常规枚举将自动转换为整型，如将其赋给 int 变量或用于比较表达式时，但作用域内枚举不能隐式地转换
为整型:

enum egg_old{Small,Medium,Large};// unscoped
enum class t_shirt{Small,Medium,Large};// scoped

egg_old one = Medium;
t_shirt rolf = t_shirt::Small;

int king = one;// implicit type conversion for unscope
int ring = rolf;// not allowed

但在必要时，可进行显式类型转换：

int ring = int(t_shirt::Small);

枚举用某种底层整型类型表示，在 C++98 中，如何选择取决于实现，因此包含枚举的结构的长度可能随系统而异。'对于作用域内枚举，C++11 消除了这种依赖性。默认情况
下，C++11 作用域内枚举的底层类型为 int'。另外，还提供了一种语法，可用于做出不同的选择：

enum class:short pizza{Small,Medium,Large};

:short 将底层类型指定为 short。


// !!  抽象数据类型

Stock 类非常具体。'然而，程序员常常通过定义类来表示更通用的概念'。例如，就实现计算机专家们所说的抽象数据类型(abstract data type，ADT) 而言，使用类是一
种非常好的方式。

'顾名思义，ADT 以通用的方式描述数据类型，而没有引入语言或实现细节'。例如，通过使用栈，可以以这样的方式存储数据，即总是从堆顶添加或删除数据。例如，C++ 程序
使用栈来管理自动变量。当新的自动变量被生成后，它们被添加到堆顶; 消亡时，从栈中删除它们。

下面简要地介绍一下栈的特征。首先，栈存储了多个数据项(该特征使得栈成为一个容器----一种更为通用的抽象) ；其次，栈由可对它执行的操作来描述。

1. 可创建空栈

2. 可将数据项添加到堆顶(压入)

3. 可从栈顶删除数据项(弹出)

4. 可查看栈否填满

5. 可查看栈是否为空

可以将上述描述转换为一个类声明，其中公有成员函数提供了表示栈操作的接口，而私有数据成员负责存储栈数据。'类概念非常适合于 ADT 方法'


私有部分必须表明数据存储的方式。例如，可以使用常规数组、动态分配数组或更高级的数据结构(如链表)。然而，公有接口应隐藏数据表示，而以通用的术语来表达，如创建
栈、压入等。

#ifndef C0B90B36_16E9_4F12_9009_2C8517AFEA67
#define C0B90B36_16E9_4F12_9009_2C8517AFEA67

typedef unsigned long Item;
class Stack
{
private:
    enum {MAX = 10};
    Item items[MAX];
    int top;
public:
    Stack();
    bool isEmpty() const;
    bool isFull() const;
    bool push(const Item& item);
    bool pop(Item& item);// pop top into items
};

#endif /* C0B90B36_16E9_4F12_9009_2C8517AFEA67 */


stack.h 中 '私有部分表明，栈是使用数组实现的；而公有部分隐藏了这一点'。因此，可以使用动态数组来代替数组，而不会改变类的接口。这意味着修改栈的实现后
，不需要重新编写使用栈的程序，而只需重新编译栈代码，并将其与已有的程序代码链接起来即可。

接口是冗余的，因为 pop() 和 push() 返回有关栈状态的信息(满或空)，而不是 void 类型。在如何处理超出栈限制或者清空栈方面，这为程序员提供了两种选择。他可以
在修改栈前使用 isempty() 和 isfull()  来查看，也可以使用 push() 和 pop() 的返回值来确定操作是否成功。

这个类不是根据特定的类型来定义栈，而是根据通用的 Item 类型来描述。在这个例子中，头文件使用 typedef 用 Item 代替 unsigned long。如果需要 double 栈或
结构类型的栈，则只需修改 typedef 语句，而类声明和方法定义保持不变。




