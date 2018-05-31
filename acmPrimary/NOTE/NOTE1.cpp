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


