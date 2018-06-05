#include<cstdio>
#include<string> //使用 memset

int readchar();  //读取编码
int readint(int c); //读取 c 位二进制字符，并转化为十进制整数

int code[8][1 << 8];
int readcodes();

int main(void)
{
	while (readcodes()) //无法读取更多编码头时退出
	{
		//printcodes();
		for (;;)
		{
			int len = readint(3);
			if (len == 0)
				break;
			//printf("len = %d\n",len);
			for (;;)
			{
				int v = readint(len);
				//printf("v = %d\n", v);
				if (v == (1 << len) - 1)
					break;
				putchar(code[len][v]);
			}
		}

		putchar('\n');
	}

	return 0;
}

int readchar()
{
	for (;;)
	{
		int ch = getchar();
		if (ch != '\n'&&ch != '\r')
			return ch;
	}
}

int readint(int c)
{
	int v = 0;
	while (c--)
		v = v * 2 + readchar() - '0';
	return v;
}

int readcodes()
{
	memset(code, 0, sizeof(code));
	code[1][0] = readchar();
	for (int len = 2; len <= 7; len++)
	{
		for (int i = 0; i < (1 << len) - 1; i++)
		{
			int ch = getchar();
			if (ch == EOF)
				return 0;
			if (ch == '\n' || ch == '\r')
				return 1;
			code[len][i] = ch;
		}
	}

	return 1;
}

void printcodes()
{
	for (int len = 1; len <= 7; len++)
	{
		for (int i = 0; i < (1 << len) - 1; i++)
		{
			if (code[len][i] == 0)
				return;
			printf("code[%d][%d] = %c\n", len, i, code[len][i]);
		}
	}
}