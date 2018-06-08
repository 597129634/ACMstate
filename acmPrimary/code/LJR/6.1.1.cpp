//owned
#include<cstdio>
int main(void)
{
	int n;
	scanf("%d", &n);  //输入总数

	int count = n;
	int a[n + 5];
	for (int i = 0; i < n + 5; i++) //初始化牌号
		a[i] = i;

	while (count >= 2)   //还剩两张牌以上
	{
		printf("%d", a[1]);  //打印要丢弃的牌
		for (int i = 1; i <= count; i++) //利用数组前面的空位，每个都前移一位
		{
			a[i - 1] = a[i];
		}
		a[count] = a[1]; //把当前第一个元素放到队尾
		for (int i = 2; i <= count; i++) //再前移所有元素
			a[i - 1] = a[i];
		
		count--; //总牌数减 1
	}
	printf("%d", a[1]); //输出最后一张牌

	return 0;
}




/***********源码 1 *************/
#include<cstdio>
const int maxn = 50;
int queue[maxn];
int main(void)
{
	int n, front, rear;
	scanf("%d", &n);

	for (int i = 0; i<n; i++) //初始化队列
		queue[i] = i + 1;
	front = 0; //队首元素的位置
	rear = n;  //队尾元素的后一个位置
	
	while (front < rear)
	{
		printf("%d ", queue[front++]); //输出并抛弃队首元素
		queue[rear++] = queue[front++]; //队首元素转移到队尾
		//有 bug ，最后打印 rear 的值要比 n 大，说明 queue[rear++] = queue[front++] 读写了非法内存
	}

	return 0;
}


/**********改进***********/
#include<cstdio>
#include<queue>
using namespace std;

queue < int> q;
int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		s.push(i + 1);  //初始化队列 
	
	while (!q.empty()) //当前队列非空
	{
		printf("%d ", q.front()); //打印队首元素
		q.pop(); //抛弃队首元素
		q.push(q.front()); //把队首元素加入队尾
		q.pop(); //抛弃队首元素
	}

	return 0;
}