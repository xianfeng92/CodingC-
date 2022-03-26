
// !! void* 是一种特殊的指针类型, 可用于存放任意对象的地址。

一个 void* 指针存放着一个地址, 这一点和其他指针类似

// !! 如果函数的参数或返回值可以是任意类型指针, 那么应声明其类型为 void*

void 的字面意思是 "无类型", void* 则为 "无类型指针", void 不能代表一个真实的变量, void 体现了一种抽象

// !! 任何类型的指针都可以直接赋值给 void 指针, 且无需进行强制类型转换

double obj = 3.14;
double *pd = &obj;
void *pv = &obj;// 正确, void* 能存放任意类型对象的地址
pv = pd;  // 正确, pv 可以存放任意类型的指针    


// !! void 指针并不能无需类型转换直接赋值给其他类型

如果要把 void 类型的指针赋值给其他类型的指针, 需要进行显式转换。



double obj = 3.14;
void *pv = &obj;

double *pd1 = pv; // 错误, 不可以直接赋值

double *pd2 = (double *)pv;// 必须进行显示类型转换


// !! void 指针可以直接和其他类型的指针进行比较指针存放的地址值是否相同

double obj = 3.14;
double *pd = &obj;

void *pv = &obj;
double * pd1 = (double *)pv;
cout << pd1 == pv << endl;// 1


// !! void 指针只有强制类型转换后才可以正常对其操作

'我们对该地址中到底是个什么类型的对象并不了解, 因此不能直接操作 void* 指针所指的对象', 也就无法确定能在这个对象上做哪些操作。
概括来说, 以 void* 的视角来看内存空间也就是仅仅是内存空间, 没办法访问内存空间中所存的对象, 因此只有对其进行恰当的类型转换之后才可以对其进行相应
的访问。

也就是说一个 void 指针必须要经过强制类型转换以后才有意义。

double obj = 3.14, *pd = &obj;
void *pv = &obj;
	
cout << *(double*)pv << endl;   // 3.14


// !! void 指针变量和普通指针一样可以通过 NULL 或 nullptr 来初始化, 表示一个空指针


// !! 当 void 指针作为函数的输入和输出时, 表示可以接受任意类型的输入指针和输出任意类型的指针



