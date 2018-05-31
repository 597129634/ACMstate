#include<stdio.h>
#include<string.h>
#define max 10000
char a[max];
int main(void)
{
	freopen("uva272.txt", "r", stdin);
	gets(a);

	for (int i = 0; i < max&&a[i] != '\0'; i++)
	{
		if (a[i] == '"')
			a[i] = '``';
		else if (a[i] == '"')
			a[i] = '''';
	}
	puts(a);
	return 0;
}


/*
示例
int main()
{
freopen("uva272.txt", "r", stdin);
int c, q = 1;

while((c = getchar()) != EOF)            //输入没有结束
{
if(c == '"'){
printf("%s",q ? "“" : "”" );
q = !q;
}
else
printf("%c", c);
}
return 0;
}
*/

//NOTE
如何输入字符串？
使用sacnf("%s", ); 输入字符串，但是本题不行
scanf（） 碰到空格或者TAB就会停止，解决方法
1 使用 fgetc(fin)；
fgetc(fin)； 读取一个打开的文件 fin，然后读取一个字符，返回一个 int
如果读到文件末尾返回 EOF
读取字符，一般情况下在检查它不是EOF后再将其转换成 char 值
从标准输入读取一个字符可以用 getchar，它等价于 fgetc(stdin);
NOTE 在 sacnf 与 getchar 连用时要特别注意 如
scanf("%d", &a);
getchar();
此时如果输入 12后加一个回车，getchar() 读取的就是回车
2 使用fgets(buf, maxn, fin); 
使用fgets(buf, maxn, fin); 读取完整一行，其中buf声明 char buf[maxn]；
该函数读取不超过 maxn - 1 个字符，在末尾添上结束符'\0'
该函数同样读到换行符就停止
当一个字符都没读到，fgets 返回 NULL

