/*
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

const int col = 2;
const int MAXround = 7;
struct round {
	int num;
	vector<char>word[col];
};

void input(struct round *data)
{
	cin >> temp;
	int i = 0;
	while (temp != -1)
	{
		data[i]->num = temp;
		cin >> data[i]->word[0];
		cin >> data[i]->word[1];
		cin >> num;
		i++;
	}
}

void guess(struct round *data)
{
	int count = 1;
	while (count <= MAXround)
	{
		while()
	}
}
*/


/***************example code********************/
//未通过
#include<stdio.h>
#include<string.h>
#define maxn 100
int left, chance;
char s[maxn], s2[maxn];
int win, lose;

void guess(char ch)
{
	int bad = 1;
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] == ch)  //把猜对的字符变成空格
		{
			left--;
			s[i] = ' ';
			bad = 0;
		}
		if (bad)
			--chance;
		if (!chance)
			lose = 1;
		if (!left)
			win = 1;
	}
}

int main(void)
{
	int rnd;//即 round（回合）
	while (scanf("%d%s%s", &rnd, s, s2) == 3 && rnd != -1)
	{
		printf("Round %d\n", rnd); //输出第几回合
		win = lose = 0;  //
		left = strlen(s); //计算出字符串长度
		chance = 7; //开始共七次机会
		for (int i = 0; i < strlen(s2); i++)
		{
			guess(s2[i]); //读取一个字符
			if (win || lose)
				break;
		}

		if (win)
			printf("You win.\n");
		else if (lose)
			printf("You lose.\n");
		else
			printf("You chickened out.\n");
	}

	return 0;
}


///////////////////////////////////
//问题什么时候属于chicked out？
#include<cstdio>
#include<cstring>
#define maxn 30
char s[maxn], s2[maxn];

int guess(int chance);
void deleteSame(void);

int main(void)
{
	int rnd;
	
	while (scanf("%d%s%s", &rnd, s, s2) == 3 && rnd != -1)
	{
		int chance = 7;
		int judge = guess(chance);
		if (judge == 1)
			printf("You win.\n");
		else if (judge == 0)
			printf("You lose.\n");
		else
			printf("You chickened out.\n");
	}

	return 0;
}

int guess(int chance)
{
	int count = 1;
	
	int length = strlen(s2);
	if (length < chance)
		return 2;

	while (count <= chance)
	{
		for (int i = 0; s[i] != '\0'; i++)
		{
			for (int j = 0; s2[j] != '\0'; j++)
				if (s2[j] == s[i])
					s[i] = ' ';
		}
		count++;
	}
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] != ' ')
			return 0;
	}
	return 1;
}