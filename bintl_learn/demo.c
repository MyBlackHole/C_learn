#include <libintl.h> //gettext库的支持
#include <locale.h> //本地化locale翻译的支持
#include <stdio.h>
#include <stdlib.h>

// 家义翻译包的名字为hello,必须与最后生成的.mo文件一致
#define PACKAGE "dome"

// 定义系统语言环境的目录，该目录下存放着国际化的语言
#define LOCALEDIR "/media/black/Data/Documents/C/bintl_learn/"

int demo_demo_main()
{
	// 设置使用环境变量(系统当前的值)
	setlocale(LC_ALL, "");
	// 关联翻译包名称及其对应的国际化翻译语言所在路径
	bindtextdomain(PACKAGE, LOCALEDIR);
	// 定义.mo文件的名字，最终我们生成的为hello.mo
	textdomain(PACKAGE);
	// 国际化字符串的支持，这里我们只展示对中文的支持，其他的类似！
	printf(gettext("Hello, World!\n"));
	return 0;
}
