//cantor 数表
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 1000

int a[MAXSIZE][2] = { 0 };    //用二维数组存储cantor数表,a[][0] 为分子  a[][1] 为分母 
int delZero(void);

int delZero(void)        //除去在存储数表时由于下标产生的 0/0 
{
	for (int i = 0; i<MAXSIZE; i++)
	{
		if (a[i][0] == 0)
		{
			//直接 j < MAXSIZE 的判断条件会把最后的元素都变成一样的 
			for (int j = i; j<MAXSIZE; j++)      //为什么加a[j][1] != '\0' 有问题 
			{
				a[j][0] = a[j + 1][0];
				a[j][1] = a[j + 1][1];
			}
		}
	}


	return 1;
}

 
int main(void)
{
	//int a[MAXSIZE][2] = {0};
	//int **a;
	//a[0] = (int *)malloc(sizeof(int)*MAXSIZE*2);

	int sum = 0;
	int count = 1;
	//思考如何在列表中去除 0/0 
	for (int i = 1; i<50; i++)      //每斜行的标号,第 i 斜行有 i 个元素
	{
		sum = sum + i;
		//printf("sum = %d\n",sum);
		//printf("i = %d\n",i);

		for (int j = 0; j<i; j++)
		{

			if (i % 2 == 0)   //标号为偶数的斜行,开始分母为 1 ,依次累加
			{
				a[j + sum][0] = count;
				a[j + sum][1] = i + 1 - a[j + sum][0];
				count++;
			}
			else
			{
				a[j + sum][0] = i + 1 - count;
				a[j + sum][1] = i + 1 - a[j + sum][0];
				count++;
			}
		}
		count = 1;
	}

	delZero();

	//for(int i = 0;i<MAXSIZE;i++)
	//printf("%d = %d/%d\n",i,a[i][0],a[i][1]);

	freopen("r7.txt", "r", stdin);
	int n;
	int zero = 0;
	while (scanf("%d", &n) != EOF)
	{
		printf("%d/%d\n", a[n - 1][0], a[n - 1][1]);
	}

	//free(a[0]);
	return 0;
}


/*测试数据
3 
14 
7
*/



/*********************示例代码*******************/
#include<stdio.h>

int main(void)
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		int k = 1, s = 0;
		while (1)
		{
			s += k;
			if (s >= n)
			{
				printf("%d/%d\n", s - n + 1, k - s + n);
				break;
			}
			k++;
		}
	}
	return 0;
}
