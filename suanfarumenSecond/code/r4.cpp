//6174 问题
#include<stdio.h>
#include<string.h>
#define MAXSIZE 1000
#define OK 1
#define ERROR 0

int sort(int a);    //第一次排序 返回值为几个数组合的最大值 
int reverse(int a); //反转该数，排除开头为 0 的情况 返回值为最小值 
int check(int *a, int x, int n);  //检测差值是否已经出现

int check(int *a, int x, int n)   //*a 以出现数字的数组，x新待检测元素，n 目前数组长度
{
	for (int i = 0; i < n; i++)
		if (a[i] == x)
			return ERROR;      //表示已经重复 

	return OK;    //未重复 
}

int sort(int a)
{
	int result = 0;
	int temp[4];    //存储每位数字
	for (int i = 3; i >= 0; i--)
	{
		temp[i] = a % 10;
		a = a / 10;
		//printf("temp[%d] = %d\n",i,temp[i]);
	}

	//排序  从大到小
	int mid;  
	for (int i = 0; i<4; i++)
	{
		for (int j = i + 1; j<4; j++)
		{
			if (temp[j]>temp[i])
			{
				mid = temp[i];
				temp[i] = temp[j];
				temp[j] = mid;
			}
		}
	}

	//debug
	//for(int i = 0;i<4;i++)
	//    printf("temp[%d] = %d\n",i,temp[i]);

	for (int i = 3; i >= 0; i--)
	{

		int q = 1;
		for (int j = 3 - i; j != 0; j--)
			q = q * 10;

		//还原数字 
		result = result + temp[i] * q;
	}

	return result;
}

int reverse(int a)    //反转
{
	int array[4];     //定义4位数组，分解数字 i 从 0--3 表示 原数位 1-4
	for (int i = 3; i >= 0; i--)
	{
		array[i] = a % 10;
		a = a / 10;
	}

	int result = 0;    //用来还原数字
	for (int i = 3; i >= 0; i--)
	{
		if (array[i] == 0);   //数位为 0 反转后忽略
		else
		{
			int p = 1;
			for (int j = i; j > 0; j--)   //第几位要 × 几个十
				p = p * 10;
			result = result + array[i] * p;
		}
	}

	return result;
}


int main(void)
{
	int n;
	scanf("%d", &n);
	printf("%d->", n);   //打印开头数字
	int array[MAXSIZE];
	array[0] = n;

	int x1 = 0;
	int x2 = 0;
	int temp = 0;
	int count = 0;
	for (int i = 1; i<MAXSIZE; i++)
	{

		if (i == 1)
		{
			x1 = sort(n);
			x2 = reverse(x1);
		}
		else
		{
			x1 = sort(temp);
			x2 = reverse(x1);
		}
		temp = x1 - x2;
		array[i] = temp;    //存储每次运算结果



		int flag = check(array, array[i], i);    //检测是否重复
		if (flag == ERROR)
		{
			count = i;     //储存数组末尾，退出循环
			break;
		}

	}

	for (int i = 1; i<count; i++)
	{
		printf("%d->", array[i]);
	}
	printf("%d\n", array[count]);

	return 0;
}




/***********范例代码********************/
#include<stdio.h>
#include<string.h>
int get_next(int x);

int get_next(int x)
{
	int a, b, n;
	char s[10];
	//转化成字符串
	sprintf(s, "%d", x);

	n = strlen(s);
	//冒泡排序
	for (int i = 0; i<n; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (s[i]>s[j])
			{
				char t = s[i];
				s[i] = s[j];
				s[j] = t;
			}

		}
	}

	sscanf(s, "%d", &b);
	//字符串反转
	for (int i = 0; i<n / 2; i++)
	{
		char t = s[i];
		s[i] = s[n - 1 - i];
		s[n - 1 - i] = t;
	}
	sscanf(s, "%d", &a);
	return a - b;
}

int num[2000], count;
int main()
{
	scanf("%d", &num[0]);
	printf("%d", num[0]);
	count = 1;
	for (;;)
	{
		//生成并输出下一个数
		num[count] = get_next(num[count - 1]);
		printf(" -> %d", num[count]);
		//在数组num中寻找新生成的数
		int found = 0;
		for (int i = 0; i<count; i++)
			if (num[i] == num[count])
			{
				found = 1;
				break;
			}

		//如果找到退出循环
		if (found)
			break;
		count++;
	}
	printf("\n");

	return 0;
}