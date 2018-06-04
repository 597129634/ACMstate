/*
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct node {
	int data;
	struct node *nextPtr;
};

typedef struct node LISTNODE;
typedef LISTNODE *LISTNODEPTR;

LISTNODEPTR creatList(LISTNODEPTR *ptr,int n)
{
    (*ptr) = (LISTNODEPTR *)malloc(sizeof(LISTNODE));
	(*ptr)->nextPtr = NULL;

	LISTNODEPTR currentPtr = NULL, lastPtr = NULL;
	int temp = 0;
	while (scanf("%d", &temp) == 1)
	{
		currentPtr = (LISTNODEPTR)malloc(sizeof(LISTNODE));
		if (currentPtr)
		{
			currentPtr->data = temp;
			if ((*ptr)->nextPtr == NULL)
			{
				(*ptr)->nextPtr = currentPtr;
				lastPtr = currentPtr;
			}
			else
			{
				lastPtr->nextPtr = currentPtr;
				lastPtr = currentPtr;
			}
		}
	}
	if (lastPtr)
	{
		lastPtr->nextPtr = (*ptr)->nextPtr;
		return lastPtr;
	}
		
}

void fun(LISTNODEPTR ptr, int k, int m,LISTNODEPTR lastPtr)
{
	LISTNODEPTR A = ptr->nextPtr, B = lastPtr;
	int countA = 1, countB = 1;
	while (1)
	{
		if (countA < k)
		{
			A = A->nextPtr;
			count++;
		}
		else if (countA == k)
		{
			printf("%3d ", A->data);	
		}


		if (countB < m)
		{
			B = B->nextPtr;
			countB++;
		}
		else if (countB == m)
		{
			if (B->data != A->data)
			{
				printf("%3d ", B->data);
				LISTNODEPTR temp = A->nextPtr;
				free(A);
				A = temp;
				temp = B->nextPtr;
				free(B);
				B = temp;
			}
			else
			{
				LISTNODEPTR temp = B->nextPtr;
				free(B);
				B = temp;
			}
		}

		if ((*ptr)->nextPtr == lastPtr)
			break;
	}

}

int main(void)
{
	freopen("UVA133.txt", "r", stdin);
	int n, k, m;
	scanf("%d%d%d", &n, &k, &m);

	LISTNODEPTR list;
	LISTNODEPTR lastPtr = creatList(&list, n);

	fun(list, k, m, lastPtr);

	return 0;
}
*/

/******示例代码******/
#include<cstdio>
#define maxn 25
int n, k, m, a[maxn];

//逆时针走t步，步长是d(-1表示顺时针走），返回新位置
int go(int p, int d, int t);


int go(int p, int d, int t)
{
	while (t--)
	{
		do
		{
			p = (p + d + n - 1) % n + 1;
		} while (a[p] == 0); //

		return p;

	}
}


int main(void)
{
	while (scanf("%d%d%d", &n, &k, &m) == 3 && n)
	{
		for (int i = 1; i <= n; i++)
			a[i] = i;
		int left = n;
		int p1 = n, p2 = 1;

		while (left)
		{
			p1 = go(p1, 1, k);
			p2 = go(p2, -1, m);
			printf("%3d", p1);
			left--;
			if (p2 != p1)
			{
				printf("%3d", p2);
				left--;
			}
			a[p1] = a[p2] = 0;
			if (left)
				printf(",");
		}

		printf("\n");
	}

	return 0;
}