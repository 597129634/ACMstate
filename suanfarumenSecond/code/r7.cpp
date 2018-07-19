//阶乘的素因子分解
#include<stdio.h>
#include<string.h> 
#include<math.h>
#define MAXSIZE 1000

int a[MAXSIZE];   //全局数组 a[] = {1} 不是把所有元素都初始化为 1 

int prime(void);

int prime(void)         //筛选素数  -- 之后用来当除数 
{
	//Eratosthenes筛法 
	for (int i = 0; i<MAXSIZE; i++)
		a[i] = i + 1;
	for (int i = 1; i<MAXSIZE; i++)
	{
		if (a[i] != 0)
		{

			for (int j = 0; j<MAXSIZE; j++)   //加 a[j] != '\0' 就结果错误 
			{
				if (a[j] % a[i] == 0 && a[j] != a[i])
				{
					a[j] = 0;
				}
			}
		}
	}
	//debug 
	//for(int i = 0;i< MAXSIZE;i++)
	//printf("%d ",a[i]);
	//printf("\n**********\n");


	for (int i = 0; i < MAXSIZE; i++)    //去除数组中分散的重复元素 0  仅一次前移遍历不足够  最外层要用两层循环 
	{
		for (int j = 0; j<MAXSIZE; j++)
		{
			if (a[j] == 0)
			{
				for (int p = j; p < MAXSIZE; p++)
				{
					a[p] = a[p + 1];
				}
			}
		}
	}

	//debug 
	//for(int i = 0;i< MAXSIZE;i++)
	//printf("%d ",a[i]);

	return 1;
}

int main(void)
{
	prime();


	//debug 
	/*
	for(int i = 0;i<MAXSIZE;i++)   //判断条件写成 i < MAXSIZE && a[i] != '\0' 就不行
	if(a[i] != 0)
	printf("%d ",a[i]);
	printf("\n");
	*/


	int n;
	int b[MAXSIZE] = { 0 };

	while (scanf("%d", &n) == 1)
	{
		int jiechen = 1;

		for (int i = 1; i <= n; i++)    //计算阶乘,由于是整型,数据过大会溢出 
			jiechen = jiechen*i;


		int i = 0;
		for (i = 1; i<MAXSIZE&&a[i] <= n&&a[i] != 0; i++)
		{

			//printf("temp = %d\n",temp);
			while (1)
			{
				if (jiechen % a[i] == 0)    //如果当前素数是该阶乘的因子,反复除该素数  
				{
					b[i] += 1;   //除一次,指数加 1 
					jiechen = jiechen / a[i];  //缩小阶乘 
											   //printf("b[%d] = %d\n",i,b[i]);
											   //printf("jiechen = %d\n",n);
				}
				else
					break;
			}
		}

		printf("%d! = ", n);
		for (int j = 1; j<i; j++)
		{
			printf("%d ", b[j]);
		}
		printf("\n");

		memset(b, 0, sizeof(int)*MAXSIZE);   //每次存下一个结果后就重新初始化数组 
	}


	return 0;
}

/*测试数据
5
6
*/


/***************示例代码****************/
#include<stdio.h>
#include<string.h>
//素数判定，n 不能太大
int is_prime(int n)
{
	for (int i = 2; i*i <= n; i++)
		if (n % i == 0)
			return 0;
	
	return 1;
}

//素数表
int prime[100], count = 0;
int main()
{
	//n 和各个素数的指数
	int n, p[100];

	//构造素数表
	for (int i = 2; i <= 100; i++)
		if (is_prime(i))
			prime[count++] = i;

	while (scanf("%d", &n) == 1)
	{
		printf("%d! =", n);
		memset(p, 0, sizeof(p));
		int maxp = 0;
		for (int i = 1; i <= n; i++)
		{
			//必须把 i 复制到变量 m 中，而不要在做除法时直接修改他
			int m = i;
			for(int j = 0; j< count;j++)
				while (m%prime[j] == 0) //反复除以prime[j]，并累加p[j]
				{
					m /= prime[j];
					p[j]++;
					if (j > maxp)
						maxp = j; //更新最大素因子下标
				}
		}

		//只循环到最大下标
		for (int i = 0; i <= maxp; i++)
			printf(" %d", p[i]);
		printf("\n");
	}

	return 0;
}