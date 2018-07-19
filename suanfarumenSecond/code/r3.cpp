#include<stdio.h>
#include<string.h>
//#define MAXSIZE 3000
const int maxn = 3000;
int f[maxn];    //用含 3000 个元素的数组足够保存 1000！  其中让 f[0] 为个位 f[1]为十位..... 

				//计算阶乘 ( < 1000! )
				//学习用数组模拟手算按位操作的方法，明白过大数会溢出的情况 
int main(void)
{
	/* 输入规模过大会溢出
	int a[MAXSIZE];
	int n;
	scanf("%d",&n);
	long long int N = 1;
	for(int i = 1;i<=n;i++)
	{
	N = N*i;
	printf("%d is %lld\n",i,N);
	}
	*/

	//为了解决溢出，采用数组来保存结果
	int i, j, n;
	scanf("%d", &n);   //输入问题规模 
	memset(f, 0, sizeof(f));    //初始化数组 
	f[0] = 1;    //置个位为 0 开始计算 
	for (int i = 2; i <= n; i++)
	{
		//乘以 i
		int c = 0;
		for (int j = 0; j< maxn; j++)    //模拟手算，每位都 * i 然后取余为当前位的数字 
		{
			int s = f[j] * i + c;
			f[j] = s % 10;
			c = s / 10;     //进位产生的数字 
		}
	}

	for (j = maxn - 1; j >= 0; j--)
		if (f[j]) break;  //忽略前导 0 

	for (i = j; i >= 0; i--)
		printf("%d", f[i]);

	return 0;
}