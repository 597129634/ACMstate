/**********************范例代码--铁轨************************/
#include<cstdio>
const int MAXN = 1000 + 10;
int n, target[MAXN];

int main()
{
	while (scanf("%d", &n) == 1)
	{
		int stack[MAXN], top = 0;
		int A = 1, B = 1;
		for (int i = 1; i <= n; i++)
			scanf("%d", &target[i]);

		int ok = 1;
		while (B <= n)
		{
			if (A == target[B])          //车厢按顺序进出栈 1 2 3 4 .... 遍历后结束循环 
			{
				A++;
				B++;
			}
			else if (top && stack[top] == target[B]) //由当前栈中元素逆序出栈来检索目标栈，一致则目标栈也出栈，顺序一致则一直遍历，否则进入最后一个判断条件结束循环 
			{
				top--;
				B++;
			}
			else if (A <= n)     //该循环调整栈的元素顺序 stack[1] = 1, stack[2] = 2，之后循环可以进入第二个判断条件
				stack[++top] = A++;
			else
			{
				ok = 0;
				break;
			}
		}
		printf("%s\n", ok ? "YES" : "NO");
	}

	return 0;
}








/**********************************************/
分析：
1.栈：在中转站C中，车厢符合后进先出的原则，称为栈，即LIFO表；其中LIFO代表Last In First Out。
  由于栈只有一端生长，实现时只需要一个数组stack和栈顶指针（始终指向栈顶元素）。
2.对于第二种输入情况：
B <= n        A <= n       stack[++top] = A++;
1 <= 5        1 <= 5        stack[1] = 1; top = 1; A = 2;
2 <= 5        stack[2] = 2; top = 2; A = 3;
3 <= 5        stack[3] = 3; top = 3; A = 4;
4 <= 5        stack[4] = 4; top = 4; A = 5;
5 <= 5        stack[5] = 5; top = 5; A = 6;
top&&stack[top] == target[B]               top--; B++;
5 && 5 == 5                               　　　top = 4; B = 2;
4 && 4 == 4                              　　　 top = 3; B = 3;
3 && 3 == 1                              　　　 跳出while循环
3.为了方便，数组下标均从1开始。例如：target[1]是指目标序列中第一个车厢的编号，stack[1]是指栈底元素（栈空当且仅当top = 0）。