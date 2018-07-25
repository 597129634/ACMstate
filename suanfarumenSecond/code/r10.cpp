//移动小球
#include<stdio.h>
#include<stdlib.h>

typedef struct node {        //链表结构 
	int data;
	struct node *next;
}NODE, *LINKLIST;

LINKLIST creatList(int n);   //创建链表 
void destroyList(void);
void printList(LINKLIST list);
void move(LINKLIST list, int m);  //移动小球 

/*
void move(LINKLIST list, int m)    //这个是按照小球排序做出的移动  即是小球的相对顺序决定的移动，与小球自己的序号无关 
{
	int i = 0;
	while (i < m)
	{
		printf("i = %d\n", i);
		char a;
		int p, q;
		a = getchar();   //处理上次输入的 \n 否则会循环错误 
		scanf("%c%d%d", &a, &p, &q);
		printf("%c %d %d\n", a, p, q);
		NODE *f = list;

		int count = 1;
		if (a == 'A')
		{

			//int count = 1;
			NODE *temp1, *temp2, *temp3;
			while (f != NULL)
			{
				printf("count = %d  f->data = %d\n", count, f->data);

				if (count == p)   //正好取到目标结点的前一个结点（需要操作的结点） 
				{
					temp1 = f;
					//printf("temp1->data = %d\n",temp1->data);
				}

				if (count == q)
				{
					temp2 = f;
					//printf("temp2->data = %d\n",temp2->data);
					break;
				}
				f = f->next;
				count++;
			}
			temp3 = temp1->next;//需要移动的结点;
								//printf("temp3->data = %d\n",temp3->data);
			temp1->next = temp3->next;
			//printf("temp1->data = %d\n",temp1->data);
			temp3->next = temp2->next;
			temp2->next = temp3;
		}
		else if (a == 'B')
		{

			NODE *temp1, *temp2, *temp3;
			while (f != NULL)
			{
				printf("count = %d  f->data = %d\n", count, f->data);
				if (count == p)
				{
					temp1 = f;
					printf("temp1->data = %d\n", temp1->data);
				}

				if (count - 1 == q)
				{
					temp2 = f;
					printf("temp2->data = %d\n", temp2->data);
					break;
				}

				f = f->next;
				count++;
			}
			temp3 = temp1->next;
			printf("temp3->data = %d\n", temp3->data);
			temp1->next = temp3->next;
			temp3->next = temp2->next;
			temp2->next = temp3;
		}
		i++;
		printList(list);
		printf("\n");
	}
}
*/


void move(LINKLIST list, int m)
{
	int i = 0;
	while (i<m)    //当 i 小于指令数时循环 
	{
		char a;
		int p, q;
		a = getchar();   //处理每次输入后剩余的换行符 
		scanf("%c%d%d", &a, &p, &q);

		NODE *f = list;
		if (a == 'A')
		{
			NODE *temp1 = f->next, *temp2 = f->next;
			while (temp1 != NULL)
			{
				if (temp1->data == p)   //找到要移动的结点 
					break;
				temp1 = temp1->next;
				f = f->next;
			}
			NODE *temp3 = f;  //temp3 指向要移动结点的前一个结点，用来接续链表 
			f = list;  //重置 f 

			while (temp2 != NULL)
			{
				if (temp2->data == q)
					break;
				temp2 = temp2->next;
				f = f->next;
			}
			NODE *temp4 = f;   //temp4 和 temp3 类似 

			temp3->next = temp1->next;    //摘除前一个结点后接续链表 
			temp1->next = temp4->next;    //左接目标结点 
			temp4->next = temp1;          //接续链表 
		}
		else if (a == 'B')    //基本和 a == ‘A’相同，只是 temp2 是目标结点的同时，不需要找其前一个结点 
		{
			NODE *temp1 = f->next, *temp2 = f->next;
			while (temp1 != NULL)
			{
				if (temp1->data == p)
					break;
				temp1 = temp1->next;
				f = f->next;
			}
			NODE *temp3 = f;

			while (temp2 != NULL)
			{
				if (temp2->data == q)
					break;
				temp2 = temp2->next;
			}

			temp3->next = temp1->next;
			temp1->next = temp2->next;
			temp2->next = temp1;
		}
		i++;
		//printList(list);
		//printf("\n");
	}
}

LINKLIST creatList(int n)
{
	LINKLIST list = (LINKLIST)malloc(sizeof(NODE));
	list->next = NULL;

	NODE *current, *last;
	int i = 1;
	while (i <= n)
	{
		current = (NODE *)malloc(sizeof(NODE));
		if (current != NULL)
		{
			current->data = i;
			i++;
			current->next = NULL;
			if (list->next == NULL)
			{
				list->next = current;
				last = current;
			}
			else
			{
				last->next = current;
				last = current;
			}
		}
		else
			break;
	}
	if (last)
		last->next == NULL;

	return list;
}


void destroyList(LINKLIST list)
{
	NODE *p = list->next;
	while (p != NULL)
	{
		list->next = p->next;
		free(p);
		p = list->next;
	}
	free(list);
}


void printList(LINKLIST list)
{
	NODE *p = list->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}

int main(void)
{
	int n, m;
	scanf("%d%d", &n, &m);

	LINKLIST list = creatList(n);

	//printList(list);
	//printf("\n/**************************/\n");
	move(list, m);  //移动小球 

	printList(list);

	destroyList(list); //释放空间 

	return 0;
}