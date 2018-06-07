#include<cstdio>
#include<cstring> //使用 memset

int readchar() {    //跨行读字符
	for (;;) {
		int ch = getchar(); //思考为什么使用 getchar 读取？
							//因为输入数据可能有空格，使用scanf会导致空格不能存入，使用getchar可以
		if (ch != '\n' && ch != '\r') return ch;   //一直读到非换行符为止
	}
}

//读取 c 位二进制字符，并转化为十进制整数
//十进制与二进制的转化
int readint(int c) {
	int v = 0;
	while (c--) v = v * 2 + readchar() - '0'; //因为是二进制读取，需要转化成十进制
	return v;
}
//思考为什么 readchar() - '0'
//字符型减 '0' 可以得到相应的整数如以 char 类型输入 1 时，想让其输出 1 但是以 %d 形式却输出 49（ '1' 的ASCII码值）
//对应的，只需要用ASCII码减去48即可，即减去 '0'
//类似的大小写字母的转换：
//先看ASCII码：a~z是97~122的二进制，而A~Z是65~90的二进制编码，于是我们就得出：大写字母=小写字母-32 ；
//这个公式了。当然这里的32我也可以这么写‘Z’=‘z’-‘空格’。因为空格的ASCII码是32对应的二进制编码。


//储存编码信息的二维数组
int code[8][1 << 8];   // 1 << 8, 把 1 转化成二进制左移八位再换成十进制
					   //1 << n ，1 先转成二进制  在左移 n 位  然后补 0
					   //比如 1 << 2     1的二进制为 0000 0001   左移2位  0000 0100. 如果再转成10进制就是4

int readcodes() {
	memset(code, 0, sizeof(code));  //清空数组
	code[1][0] = readchar();        //单度读取编码头
	for (int len = 2; len <= 7; len++) {
		for (int i = 0; i < (1 << len) - 1; i++) {
			int ch = getchar();
			if (ch == EOF) return 0;
			if (ch == '\n' || ch == '\r') return 1;
			code[len][i] = ch;
		}
	}
	return 1;
}

//调试用打印
void printcodes() {
	for (int len = 1; len <= 3; len++)
		for (int i = 0; i < (1 << len) - 1; i++) {
			if (code[len][i] == 0) return;
			printf("code[%d][%d] = %c\n", len, i, code[len][i]);
		}
}

int main() {
	while (readcodes()) {   //不能再读取更多编码时结束循环
							//printcodes();
		for (;;) {
			int len = readint(3);  //读取每小节头三位（每小节头三位代表每个编码长度）
			if (len == 0) break;   //长度为 0，代表结束
								   //printf("len=%d\n", len);
			for (;;) {
				int v = readint(len); //v存取每小节字符数
									  //printf("v=%d\n", v);
				if (v == (1 << len) - 1) break;
				putchar(code[len][v]);
			}
		}
		putchar('\n');
	}
	return 0;
}



//NOTE getchar
//即使是 int 类型的变量，用 getchar 来读，依然是一个字符，以 %c 形式输出再和输入保持一样，
//否则可以用上面的 - '0' 的方式的到对应整数
//以 %d 形式则是输出其 ASCII 码
//如下
#include<cstdio>
int main(void)
{
	int a = getchar();
	printf("'a' %%d = *%d* \n", a); //输出了 ASCII
	printf("'a' %%c = *%c* \n", a); //按其字符形式输出
	printf("'a' - '0' %%d = *%d* \n", a - '0');  //如果是整数，则输出整数
	printf("'a'- '0' %%c = *%c*\n", a - '0');

	return 0;
}
/*
输入
1
输出
'a' %d = *49*
'a' %c = *1*
'a' - '0' %d = *1*
'a'- '0' %c = **
*/

/*输入
a
输出
'a' %d = *97*
'a' %c = *a*
'a' - '0' %d = *49*
'a'- '0' %c = *1*
*/