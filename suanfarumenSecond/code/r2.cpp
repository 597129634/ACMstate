//#include<cstdio>        //得到一个周期串得最小周期 
//#define MAXSIZE 1000

/*思路*/
/*
FALSE
由于要找最小周期，则从开头找第一个最小的完整周期即可
先找到第一个与串第一个字符相同字符的位置，记为 count -- count 可能为最小周期，
此时要进行检测 （由于数组的第一个记为 0）如果从 1 开始则是 count - 1
找到第一个可能周期后，开始匹配第二个元素，第三个元素... 
如果出现了不匹配的情况，说明到此为止不是一个周期，下次再找与第一个字符相同字符的位置，从 count 开始找
重复上述操作，直到 count - 1 位置的元素都与 count 后对应得元素相同，则找到最小周期 -- 只是找了第一个重复的串，可能不是周期
*/
int main()
{
	char s[MAXSIZE];
	char temp;
	for (int i = 0; i<MAXSIZE && (temp = getchar()) != EOF; i++)
		s[i] = temp;          //输入串 

	char head = s[0];
	int count = 1;
	int flag = 1;    //标志变量，用来表示找到结果退出循环 
	while (1)
	{
		int i;
		for (i = count; s[i] != head; i++)
			;
		count = i;         //得到与开头字符相同的位置

		for (int i = 1; i<count; i++)   //检测后面的元素是否匹配 
		{
			if (s[i] != s[count + i])
			{
				flag = 0;
				break;
			}
		}

		if (flag == 1)
			break;

		flag = 1;
	}

	printf("%d", count);
}


/***************************************************/
//范例代码 
//思路
//从小到大枚举各个周期，一旦符号条件就立即输出 
//使用了临时变量，i，j 在退出作用域后不可用 
#include<stdio.h>
#include<string.h>
int main(void)
{
	char word[100];
	scanf("%s", word);
	int len = strlen(word);
	for (int i = 1; i<len; i++)       //用外层循环 i 来列举周期
	{
		if (len % i == 0)
		{
			int ok = 1;
			for (int j = i; j < len; j++)       //判断数组是否以 i 为周期 
			{
				if (word[j] != word[j%i])
				{
					ok = 0;
					break;
				}
			}

			if (ok)
			{
				printf("%d\n", i);
				break;
			}
		}
	}

	return 0;
}