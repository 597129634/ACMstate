第四章 函数和递归
要点
多参数，单返回值的函数定义和使用
用 typedef 定义结构体
理解函数调用时用实参给形参赋值的过程
理解调用栈和栈帧，学会用 gdb 查看调用栈并选择栈帧
理解地址和指针
递归定义与递归函数
理解可执行文件总的正文段，数据段和 BSS 段
熟悉堆栈段，了解栈溢出的常见原因

4.1 自定义函数和结构体
函数定义形式
返回类型 函数名（参数列表）{
	函数体
}
例如 double dist(double x1, double y1, double x2, double y2);
NOTE main() 是有返回值的 通常是 0 （代表程序正常结束）
定义结构
struct name {
	/**定义的数据类型**/
};
typedef struct name NAME; //把NAME作为一个新的变量类型的名字


p4-1 组合数
注意防止溢出，例如
long long factorlia(int n)
{
	long long m = 1;
	for (int i = 1; i < n; i++)
	{
		m *= i;
	}
	return m;
}

long long C(int n, int m)
{
	return factorial(n) / (factorial(m)*factorlial(n - m));
}
//该代码有溢出的可能
NOTE 即使最终答案在所选择数据类型范围之内，计算的中间结果也可能溢出
//解决方法之一：对复杂的式子约分 如 n!/m! = (m+1)*(m+2)*.....*(n-1)*n 如下
long long C(int n, int m)
{
	if (m < n - m) //思考为什么 m < n-m 时把 m 变成 n-m
		m = n - m;
	long long ans = 1;
	for (int i = m + 1; i <= n; i++)
		ans *= i;
	for (int i = 1; i <= n - m; i++)
		ans /= i;
	return ans;
}



p4-3 素数判定（有问题）
//n = 1 或者 n 很大时请勿调用
int is_prime(int n)
{
	for (int i = 2; i*i < n; i++) //只判断不超过 sqrt（x）的整数 i（牵扯到素数定理）
		if (n%i == 0)
			return 0;
	return 1;
}
n = 1 时不调用是因为该函数会对 n = 1 产生误判
n 太大时不调用是防止溢出（i*i > int（max))
p4-4 素数判断（改进）
int is_prime(int n)
{
	if (n <= 1)
		return 0;
	int m = floor(sqrt(n) + 0.5); //防止本应是整数的地方变成了小数
	for (int i = 2; i <= m; i++)
		if (n%i == 0)
			return 0;
	return 1;
}
//sqrt(x) 开平方函数
//floor(x) 向下取整函数



4.2 函数调用与参数传递
4.2.1 形参与实参
p4-5 用函数交换变量（error)
#include<stdio.h>
void swap(int a, int b)
{
	int t = a;
	a = b;
	b = t;
}

int main(void)
{
	int a = 3, b = 4;
	swap(a, b);
	printf("%d %d", a, b);
	return 0;
}
//依然输出 3 4 变量并未交换
NOTE 局部变量的储存空间是临时分配的，函数结束后，变量的空间也会被释放
NOTE 即子函数与主函数的同名变量并不冲突

4.2.2 调用栈 （Call Stack)
NOTE 多演示程序的执行过程，把注意力集中在“当前代码行”的转移和变量值的变化上
调用栈描述的是函数之间的调用关系，由多个栈帧 (Stack Frame) 组成，每个栈帧对应着一个未运行完的函数
栈帧中保存了该函数的返回地址和局部变量，因此，能在执行完毕后找到正确的返回地址，
还能保证不同函数见的局部变量互不相干---不同函数对应不同栈帧
NOTE C语言用调用栈来描述函数之间的调用关系，调用栈由栈帧组成，
NOTE 每个栈帧对应一个未运行完的函数
NOTE 在 gdb 中可以用 backtrace（简称 bt）命令打印所有栈帧信息。
NOTE 若要用 p 命令打印一个非当前栈帧的局部变量，可以用 frame 命令选择另一个栈帧
学习如何使用 gdb

4.2.3 用指针作参数
p4-6 用函数交换变量（right)
#include<stdio.h>
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int main(void)
{
	int a = 3, b = 4;
	swap(&a, &b);
	printf("%d %d", a, b);
	return 0;
}

4.2.5 数组作为参数和返回值
problem：如何把数组作为参数传递给函数？
p4-7 计算数组元素和（error）
int sum(int a[])
{
	int ans = 0;
	for (int i = 0; i < sizeof(a); i++)
		ans += a[i];
	return ans;
}
//error sizeof(a) 无法得到数组的大小--数组作参数传递时，仅传递了首地址
//定义中的 int a[] 等价于 int *a；
//正确做法--加一个参数，表示数组的元素个数
p4-8 计算数组元素和（right）
int sum(int *a,int n)
{
	int ans = 0;
	for (int i = 0; i < n; i++)
		ans += a[i];
	return ans;
}
NOTE 在函数调用时，a 不一定必须要传递一个数组，如下
int main(void)
{
	int a[] = { 1,2,3,4 };
	printf("%d\n", sum(a + 1, 3));
	return 0;
}
//指针 a+1 指向 a[1] ，因此 sum 的到的是 2，3，4 ，故函数返回 9
//一般地，若 p 是指针，k 是正整数，p+k 就是指针 p 后面第 k 个元素，p-k 是 p 前面第 k 个元素
//如果 p1 和 p2 是相同类型的指针，则 p1-p2 是从 p1 到 p2 的元素个数（不含 p2）
NOTE 以数组为参数调用函数时，实际只有数组首地址传递给了函数，需要另加一个参数表示元素个数
NOTE 除了传递首地址，也可以通过指针加减法传递其他元素首地址
p4-9 计算左闭右开的区间内元素和
法一
int sum(int *begin, int *end)
{
	int n = end - begin;
	int ans = 0;
	for (int i = 0; i < n; i++)
		ans += begin[i];
	return ans;
}
法二
int sum(int *begin, int *end)
{
	//int *p = begin;
	int ans = 0;
	for (int *p = begin; p != end; p++)
		ans += *p;
	return ans;
}
//除了传递数组长度，也可以想上面两例，传递数组的尾指针表示数组结束的位置
NOTE 把数组作指针传递给函数时，数组的内容是可修改的

4.2.6 把函数作为函数的参数
例题 4 - 1 古老的密码（UVa 1339）
C语言的stdlib.h中有一个qsort的库函数，实现了快速排序。声明如下
void qsort(void *base, size_t num, size_t size, int(*comparator)(const void *, const void *));
void *base //待排序数组的其实地址
size_t num //带排序数组的元素个数
size_t size //每个元素大小
int(*comparator)(const *void, const *void); //指向函数的指针
//最后一个参数应当有如下形式:
int cmp(const void *,const void *) {......}
指向常数的万能指针 const void *,可以通过强制类型转化成任意类型指针
//本例为整型数组，写成如下形式
int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}
//一般地，需要先把参数 a 和 b 转化成真实的类型，然后让 cmp 函数当
// a<b,a>b,a==b 时返回负数，整数和 0

4.3 递归


//假期学习如何查看栈，栈帧