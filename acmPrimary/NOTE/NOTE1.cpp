第三章 数组和字符串 
要点 
一维数组的声明与使用
二维数组的声明与使用
字符串的声明，赋值，比较，连接等方法
熟悉字符ASCII码和ctype.h 中的字符函数
正确认识'++','+=' 等运算符
掌握fgetc 和 getchar 的使用
掌握fgets的使用方法，了解gets的缓冲区溢出漏洞
学会用常量表简化代码

3.1 数组
p3-1 逆序输出
#include<stdio.h>
#define maxn 105
int a[maxn]; //大数组要设成全局变量 
int main(void)
{
	int x,n = 0;
	while(scanf("%d",&x) == 1)
	    a[n++] = x;//先 a[i] = x,在 n++ 
	
	for(int i = n-1;i >= 1;i--)
	{
		printf("%d ",a[i]);
	}
	printf("%d",a[0]);
	return 0;
} 
NOTE n++ : 先用 n 再 ++ 
NOTE ++n : 先 ++ 再用 n
NOTE 比较大的数组要放在 main 函数外，否则可能无法运行
NOTE 数组不能直接赋值，可以采用 memcpy 来赋值，如下 
int a[maxn],b[maxn]; 
memcpy(b,a,sizeof(int)*k); //从数组 a 赋值 k 个元素到数组 b
如果 a b 为浮点型，要写成 memcpy(b,a,sizeof(double)*k);
memcpy() 包含在头文件 string.h 中
如果把 a 全部复制给 b 写成 memcpy(b,a,sizeof(a));

p3 - 2 开灯问题
n 盏灯，编号 1--n。第一个人打开所有灯，第二个按下所有编号为 2 的
倍数的灯，第3个人按下所有倍数为3的灯开关......
一共k人，问最后有那些灯开着？
输入n和k，输出开灯编号
#include<stdio.h>
#include<string.h>
#define maxn 1010
int a[maxn];
int main(void)
{
	int n, k, first = 1;
	memset(a, 0, sizeof(a)); //把数组清 0 ，定义在 string.h 中
	scanf("%d%d", &n, &k);
	
	for (int i = 1; i <= k; i++) //k 个人的循环   i 即第 i 个人
	{
		for (int j = 1; j <= n; j++) // n 盏灯
			if (j%i == 0) //如果当前灯的编号是 i 的倍数
				a[j] = !a[j]; //反转开关
	}

	for(int i = 1;i <= n;i++)
		if (a[i])
		{
			if (first) //避免输出多余空格，设置标志变量 first
				first = 0;
			else
				printf(" ");
			printf("%d", i);
		}

	printf("\n");
	return 0;
}

p3 - 3 蛇形填数
在 n*n 的方阵里填入 1，2，...，要求填入蛇形，如 n = 4 时
10 11 12 1
9  16 13 2
8  15 14 3
7  6  5  4
#include<stdio.h>
#include<string.h>
#define maxn 20
int a[maxn][maxn];
int main(void)
{
	int n, x, y, tot = 0;
	scanf("%d", &n);
	memset(a, 0, sizeof(a));
	tot = a[x = 0][y = n - 1] = 1;
	while (tot < n*n)
	{
		while (x + 1 < n && !a[x + 1][y])
			a[++x][y] = ++tot;
		while (y - 1 >= 0 && !a[x][y - 1])
			a[x][--y] = ++tot;
		while (x - 1 >= 0 && !a[x - 1][y])
			a[--x][y] = ++tot;
		while (y + 1 < n && !a[x][y + 1])
			a[x][++y] = ++tot;
	}

	for (x = 0; x < n; x++)
	{
		for (y = 0; y < n; y++)
			printf("%3d", a[x][y]);
		printf("\n");
	}
		

	return 0;
}
//基本思路，设置一个坐标，通过改变坐标来实现操作
NOTE ！ 是逻辑运算符 “逻辑非”

3.2 字符数组
p3-4 竖式问题
找出所有形如 abc*de（三位数*两位数）的算式，使得在完整的竖式中，所有数字都属于一个特定的
数字集合。
输入数字集合（相邻数字之间没有空格），输出所有竖式。
每个竖式前要有编号，之后有一个空行。
最后输出解的总数
#include<stdio.h>
#include<string.h>
int main(void)
{
	int count = 0;
	char s[20], buf[99];
	scanf("%s", s); //读入一个不含空格，TAB,回车符的字符串
	for (int abc = 111; abc <= 999; abc++)
		for (int de = 11; de <= 99; de++)
		{
			int x = abc*(de % 10), y = abc*(de / 10), z = abc*de;
			sprintf(buf, "%d%d%d%d%d", abc, de, x, y, z); //将后面的数据输入进前面的字符串
			int ok = 1;
			for (int i = 0; i < strlen(buf); i++)
				if (strchr(s, buf[i]) == NULL) //strchr 在字符串中查找单个字符
					ok = 0;
			if (ok)
			{
				printf("<%d>\n", ++count);
				printf("%5d\nX%4d\n-----\n%5d\n%4d\n-----\n%5d\n\n", abc, de, x, y, z);
			}
		}

	printf("The numberof solution = %d\n", count);
	return 0;
}
NOTE 字符数组char s[N1][N2]
NOTE sacnf("%s", a[i]); 表示读取第 i 个字符串，前面没有 &
NOTE printf("%5d"); %5d 表示以5字符宽打印，不足在前面补空格
NOTE strlen(s) 获取字符串 s 的实际长度
NOTE 注意 sizeof 与 strlen 的区别
strlen 从某个字符开始，得到直到字符串结束标志'\0'的长度(不包含'\0')(原型 strlen(char *))
siezof()返回的是变量声明后所占的内存数，不是实际长度
例如
char a[10];
for (int i = 0; i<5; i++)
	a[i] = 'a';
printf("sizeof(a) = %d\nstrlen(a) = %d\n", sizeof(a), strlen(a));
//输出 10 5
因为 a 数组占了十个字节，而实际长度只有 5

查阅
字符串操作函数

补充内容
1 一维数组的声明与使用
初始化数组
int power[N] = { 1,2,3,4... }；
使用逗号分隔，花括号括起来
NOTE 可以省略方括号中的数字，让编译器自动匹配数组大小
int day[] = { 1,2,3,4 };

2 多维数组
二维数组初始化
int day[N1][N2] = {
	{1,2,3,4,5}, //一个数值列表代表一行
	{2,3,4,5},
	{4,5,6,7}
};

指针和数组
数组名是数组首元素的地址
a[n] == *(a + n);
函数，数组和指针
int fun(int *a);//声明
NOTE 声明数组形参，以下 4 种声明等价
int fun(int *a, int n);
int fun(int *, int);
int fun(int a[], int n);
int fun(int[], int);
注意，在函数定义中不能省略参数名，以下两种定义等价
int fun(int *a, int n);
int fun(int a[], int n);

使用指针形参
指针和多维数组
函数和多维数组 （形参最多只能省略第一维的长度）
注意多维数组动态传参要申请内存，具体方法如下
使用malloc动态申请内存（切记最后要释放内存）
方法一：利用二级指针申请一个二维数组
int main()
{
	int **a;  //用二级指针动态申请二维数组    
	int i, j;
	int m, n;
	printf("请输入行数\n");
	scanf("%d", &m);
	printf("请输入列数\n");
	scanf("%d", &n);

	/*************关键部分*********************/
	a = (int**)malloc(sizeof(int*)*m); //先对行申请
	for (i = 0; i<m; i++)
		a[i] = (int*)malloc(sizeof(int)*n); //再对列申请
	/*************申请结束****************************/
	/****************重要提示*************************/
	//不可以使用 a = (int **)malloc(sizeof(int)*m*n); 来申请，这样会失败

	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
		{
			printf("%p\n", &a[i][j]);     //输出每个元素地址，每行的列与列之间的地址时连续的，行与行之间的地址不连续  
		}
	}
	for (i = 0; i<m; i++)
		free(a[i]);

	free(a);
	return 0;
}
//使用此方法，传递参数时使用二级指针即可 如下例，对二维数组每个元素加 3
void sum(int N, int **a)   //函数定义
{
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++)
		{
			a[i][j] += 3;
		}
	}

	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}

}

int main(void)
{
	freopen("array.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	printf("n = %d\n", n);


	//int **a = (int **)malloc(sizeof(int)*n*n); 错误的声明
	/*正确的声明*/
	int **a = (int **)malloc(sizeof(int *)*n);
	for (int i = 0; i<n; i++)
		a[i] = (int *)malloc(sizeof(int)*n);

	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			scanf("%d", &a[i][j]);
	}

	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}

	printf("\nstart function\n");

	sum(n, a);
   /*   //检验是否改变了原数组的内容
	*  for (int i = 0; i<n; i++)
	*   {
	*	    for (int j = 0; j<n; j++)
	*		    printf("%d ", a[i][j]);
	*	    printf("\n");
	*    }
	*/

	free(a); //释放内存
	return 0;
}


方法二：用数组指针形式申请一个二维数组
int main()
{
	int i, j;
	//申请一个3行2列的整型数组    
	int(*a)[2] = (int(*)[2])malloc(sizeof(int) * 3 * 2);
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<2; j++)
		{
			printf("%p\n", &a[i][j]);  //输出数组每个元素地址，每个元素的地址是连续的  
		}
	}

	free(a);
	return 0;
}

方法三：用一个单独的一维数组来模拟二维数组
int main()
{
	int nrows, ncolumns;
	int *Array;
	int i, j;
	printf("please input nrows&ncolumns:\n");
	scanf("%d%d", &nrows, &ncolumns);
	Array = (int *)malloc(nrows*ncolumns * sizeof(int));   //申请内存空间  
	for (i = 0; i<nrows; i++)
	{
		for (j = 0; j<ncolumns; j++)
		{
			Array[i*ncolumns + j] = 1;
			printf("%d ", Array[i*ncolumns + j]);   //用Array[i*ncolumns+j] 访问第i,j个成员  
		}
		printf("\n");
	}
	free(Array);
	return 0;
}



字符串函数（相关定义在 string.h 头文件中）
