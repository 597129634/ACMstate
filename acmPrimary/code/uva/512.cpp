#include<cstdio>
#include<cstring>
#include<cstdlib>
#define rmax 60
#define cmax 60

int r, c, form[rmax][cmax];
int a[rmax];

int exchange(void);
int deleteR(void);
int deleteC(void);
int addR(void);
int addC(void);
int find();

int deleteR(void)
{
	int sum;
	scanf("%d", &sum);
	for (int i = 0; i < sum; i++)
		scanf("%d", &a[i]);

	for (int i = 0; i < rmax; i++)
	{
		form[a[i]][0] = -1;   //删除 -1
	}

	return 1;
}

int deleteC(void)
{
	int sum;
	scanf("%d", &sum);
	for (int i = 0; i < sum; i++)
		scanf("%d", &a[i]);

	for (int i = 0; i < cmax; i++)
	{
		form[a[i]][0] = -1;
	}

	return 1;
}
int exchange()
{
	int r1, r2, c1, c2;
	scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
	
	int temp;
	temp = form[r1][c1];
	form[r1][c1] = form[r2][c2];
	form[r2][c2] = temp;
	
	return 1;
}