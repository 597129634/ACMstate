第 5 章 C++与 STL 入门
目标 
理解变量引用
掌握 string与stringstream
掌握 C++ 如何定义使用结构体，包括构造函数和静态成员变量
了解常见可重载运算符，包括四则运算，赋值，流式输入输出，() 和 []
了解模板函数和模板类
掌握STL中的排序和检索的相关函数
掌握STL中 vector set map 这3个容器
了解STL中的集合相关函数
理解栈，队列，优先队列，能使用STL实现
掌握随机数生成方法，能结合assert宏进行测试
能编写大整数类BigInteger

5.1.1 C++版框架
C++版 a+b
#include<cstdio>
int main()
{
	int a, b;
	while (scanf("%d%d", &a, &b) == 2)
		printf("%d\n", a + b);
	return 0;
}
//stdio.h变成了cstdio,类似的 string.h 变成了 cstring , math.h -- cmath , ctype.h--cctype
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 100 + 10;
int A[maxn];
int main()
{
	long long a, b;
	while (cin >> a >> b)
	{
		cout << min(a, b) << "\n";
	}
	return 0;
}
//iostream 提供输入输出流，algorithm 提供一些常用算法

5.1.2 引用
#include<iostream>
using namespace std;
void swap(&a, &b)
{
	int t = a;
	a = b;
	b = t;
}

int main(void)
{
	int a = 3, b = 4;
	swap(a, b);
	cout << a << b << endl;
	return 0;
}
//swap 按照传引用的方式传递参数，同样可以改变主函数中对应变量的值（与 C 按值传递不同）
//引用就是这个变量的别名

5.1.3 字符串
C中字符串即为字符数组，不能直接进行相关的操作，如写一个把两个字符串拼接的函数
NOTE 不能在函数中定义一个数组然后返回首地址，因为函数结束后，定义在其中的局部变量的地址便失效了
NOTE 正确的做法是需要动态申请内存，最后再释放
//C++ 提供了 string 类，可以用来实现变长字符串的相关操作
problem ：输入数组的每行包括若干以空格隔开的整数，输出每行所有整数之和
使用字符与字符数组一般有两种方案
1 使用 getchar 边读边算
2 每次读一行再计算
//使用 C++
#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int main(void)
{
	string line;
	while (getline(cin, line))
	{
		int sum = 0;
		int x;
		stringstream ss(line);
		while (ss >> x)
			sum += x;
		cout << sum << endl;
	}
	return 0;
}
//getline 在 string 头文件中
//stringstream 在 sstream 头文件中
//string 很慢，sstream 更慢

5.1.4 结构体
C++ 中的结构体除了可以拥有成员变量（用 a.x方式访问)之外还可以有成员函数(用 a.add(1, 2)的方式访问)
#include<iostream>
using namespace std;
struct Point {
	int x, y;
	Point(int x = 0, int y = 0):x(x),y(y){} //结构体中定义了一个没有返回值的 Point 函数
};
//Point 称构造函数，在声明变量时调用，两个参数有 =0，表示若未指明参数值，就按 0 处理
//:x(x),y(y) 表示把成员变量x初始化为参数x，成员变量y初始化为参数y,也可以写成如下形式
//Point(int x = 0,int y = 0){ this->x = x ; this->y = y;}
//这里的 this 是指向当前对象的指针，this->x 指的是当前对象的成员变量x，即 (*this).x

Point operator + (const Point &A, const Point &B) //定义了加法操作
{
	return Point(A.x + B.x, A.y + B.y);
}

ostream &operator << (ostream &out, const Point &p) //定义结构体流的输出方式
{
	out << "(" << p.x << "," << p.y << ")";
	return out;
}

int main(void)
{
	Point a, b(1, 2); //定义了两个Point对象
	a.x = 3;
	cout << a + b << endl; //实现两者相加的操作（a.x+b.x,a.y+b.Y);
	return 0;
}

5.1.5 模板
int sum(int *begin, int *end)
{
	int *p = begin;
	int ans = 0;
	for (int *p = begin; p != end; p++)
		ans += *p;
	return ans;
}
//该函数只能计算整型数组的元素和
template<typename T>
T sum(T *begin, T *end)
{
	T *p = begin;
	T ans = 0;
	for (T *p = begin; p != end; p++)
		ans = ans + *p; //思考为什么从 ans += *p ，变成 ans = ans + *p;
	return ans;
}
//可以用sum函数计算 double 数组和 Point 数组求和
int main()
{
	double a[] = { 1.1,2.2,3.3,4.4 };
	cout << sum(a, a + 4) << endl;
	Point b[] = { Point(1,2),Point(3,4),Point(5,6),Point(7,8) };
	cout << sum(b, b + 4) << endl;
	return 0;
}
//ans += *p ，变成 ans = ans + *p; 是因为 Point 结构体中只定义了“+”运算符，没有定义+=
结构体和类(class)也是可以带模板的，如下
template <typename T>
struct Point {
	T x, y;
	Point(T x = 0,T y = 0) : x(x),y(y){}
};
把 + 和 << 稍加改变
template <typename T>
Point<T> operator + (const Point<T> &A, const Point<T> &B)
{
	return Point<T>(A.x + B.x, A.y + B.y);
}
template <typename T>
ostream &opeartor << (ostream &out, const Point<T> &B)
{
	out << "(" << p.x << "," << p.y << ")";
	return out;
}
//可以使用同时使用 int 和 double 类型的 Point
int main()
{
	Point<int>a(1, 2), b(3, 4);
	Point<double>c(1.1, 2.2), d<3.3, 4.4>;
	cout << a + b << " " << c + d << endl;
	return 0;
}

5.2 STL 初步
STL 指的是C++的标准模板库
5.2.1 排序与检索
例题 5 - 1
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1000;
int main(void)
{
	int n, q, x, a[maxn], kase = 0;
	while (scanf("%d%d", &n, &q) == 2 && n)
	{
		printf("CASE# %d\n", ++kase);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		sort(a, a + n); 
		while (q--)
		{
			scanf("%d", &x);
			int p = lower_bound(a, a + n, x) - a; //以排序数组 a 中寻找 x
			if (a[p] == x)
				printf("%d found at %d\n", x, p + 1);
			else
				printf("%d not found\n", x);
		}
	}
	return 0;
}
//sort 使用数组元素默认的大小比较运算符进行排序
//按照特殊依据进行排序时才需要传入额外的比较函数
//sort也可以对vector对象进行排序，调用如下 sort(v.begin(),v.end());
//lower_bound 查找大于或等于 x 的第一个位置
//unique 可以删除有序数组中的重复元素

5.2.2 不定长数组 vector
vector 是一个不定长数组，同时封装了一些常用操作
如 a.size()读取它的大小  a.resize()改变大小, a.push_back()向尾部添加元素, a.pop_back()删除最后一个元素
vector 是一个模板类，需要用 vector<int>a 这样的方式来声明一个 vector
例题 5 - 2 木块问题 （UVA 101）
#include<cstdio>
#include<string>
#include<vector>
#include<iiostream>
using namespace std;

const int maxn = 30;
int n;
vector<int>pile[maxn]; //每一个pile[i] 是一个 vector   pile 是一个二维数组
//pile 第一维固定为 maxn，第二维长度不定

//找木块 a 所在的 pile 和 heigh，以引用的形式返回调用者
void find_block(int a, int &p, int &h)
{
	for (p = 0; p < n; p++)
		for (h == 0; h < pile[p].size; h++)
			if (pile[p][h] == a)
				return;

}

//把第 p 堆高度为 h 的木块上方的所有木块移回原位
void clear_above(int p,int h)
{
	for (int i = h + 1; i < pile[p].size(); i++)
	{
		int b = pile[p][i];
		pile[b].push_back(b);
	}
	pile[p].resize(h + 1);
}

//把第 p 堆高度为 h 及其上方的木块整体移动到 p2 堆的顶部
void pile_onto(int p, int h, int p2)
{
	for (int i = h; i < pile[p].size(); i++)
		pile[p2].push_back(pile[p][i]);
	pile[p].resize(h);
}

void print()
{
	for (int i = 0; i < n; i++)
	{
		printf("%d:", i);
		for (int j = 0; j < pile[i].size(); j++)
			printf(" %d", pile[i][j]);
		printf("\n");
	}
}

int main(void)
{
	int a, b;
	cin >> n;  //输入木块个数
	string s1, s2; //定义两个空串
	for (int i = 0; i < n; i++)
		pile[i].push_back(i);  //向数组中存入元素（木块编号）
	while (cin >> s1 >> a >> s2 >> b)
	{
		int pa, pb, ha, hb;
		find_block(a, pa, ha);
		find_block(b, pb, hb);
		if (pa == pb)
			continue;
		if (s2 == "onto")
			clear_above(pb, hb);
		if (s2 == "move")
			clear_above(pa, ha);
		pile_onto(pa, ha, pb);
	}
	print();
	return 0;
}

5.2.3 集合 set
