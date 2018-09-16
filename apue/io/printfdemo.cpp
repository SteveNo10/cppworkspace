/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-11
* Descript: 
* printf format %[flags][width][.prec][length]type
*
*   type:
*       d,i         int,i是老式写法
*       o,u,x,X     unsigned int,o八进制,x时16进制abcdef小写,X时16进制ABCDEF大写
*       e,E         double,[-]dd.dddddde±dd,e时e小写,E时E大写,默认小数点后6位,不够后补0
*       f,F         double,[-]dd.dddddd,默认小数点后6位,不够后补0,f时inf/infinity小写,F时INF/INFINITY大写
*       g,G         double,根据数值长度,选择最短方式输出,默认6位数字,指数≤4或者≥精度时使用e/E格式.g对应e/f,G对应E/F,但是不够位数不补0
*       a,A         double,[-]0xh.hhhhp±,十六进制p计数法输出浮点数,a时xabcdef小写,A时XABCDEF大写
*       c           int,输入数字对应ASCII码字符输出
*       C           跟lc同意,不推荐使用
*       s           const char*,输出字符串直至'\0'结尾
*       S           跟ls同意,不推荐使用
*       p           void*,16进制输出指针,%#x和%#lx等同
*       n           int*,将%n前面输出的字符总数存储到对应位置
*       m           打印errno对应出错内容,等同于strerror(errno)
*       %           输出%本身
*
*   length:
*       hh  d,i                 signed char
*           u,o,x,X             unsigned char
*           n                   signed char*
*       h   d,i                 short
*           u,o,x,X             unsigned short
*           n                   short*
*       l   d,i                 long
*           u,o,x,X             unsigned long
*           a,A,e,E,f,F,g,G     double 跟不加一样
*           c                   wint_t
*           s                   wchar_t*
*           n                   long*
*       ll  d,i                 long long
*           u,o,x,X             unsigned long long
*           n                   long long*
*       L   d,i                 long long
*           u,o,x,X             unsigned long long
*           a,A,e,E,f,F,g,G     long double
*       j   d,i                 intmax_t
*           u,o,x,X             uintmax_t
*           n                   intmax_t*
*       z   d,i,u,o,x,X         size_t / ssize_t 
*           n                   size_t* / ssize_t*
*       t   d,i,u,o,x,X         ptrdiff_t
*           n                   ptrdiff_t*
*
*   .prec:   .开头,后跟十进制整数
*       .数值   整数(d/i/o/u/x/X),表示最小数字个数,不足前补0,超过不截断
*               浮点(a/A/e/E/f),表示小数点后位数,默认六位,不足后补0,超过截断
*               (g/G),可输出的最大有效数字
*               字符串(s),表示最大可输出字符数,不足正常输出,超过则截断
*       .*      参数列表给出精度
*
*   width:   十进制表示最小输出位数，实际少则补0或空格，多则按实际输出
*       数值    输出位数
*       *       参数列表给出最小宽度
*
*   flags:
*       -    字段内左对齐
*       +    输出正负号
*    (space) 正数输出空格,负数输出负号 
*       #    type为 o/x/X时,增加前缀0/0x/0X
*            type为 a/A/e/E/f/g/G时,一定使用小数点。如果用.0控制不输出小数部分，则不输出小数点
*            type为 g/G时,尾部的0保留
*       0    前面补0,直至占满列宽(如果有-,0被忽略)
*
============================================================================*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <map>
#include <math.h>

using namespace std;

void PrintCode(FILE* pFile)
{
    char buf[BUFSIZ] = {0};
    while(fgets(buf, BUFSIZ, pFile) != NULL)
    {
        if(NULL == strstr(buf, "PrintCode"))
        {
            continue;
        }

        char* substr = strstr(buf, "printf");
        if(NULL == substr)
        {
            continue;
        }
        else
        {
            char* semicolon = rindex(substr, ';');
            *semicolon = 0;
            printf("%s : ", substr);
            break;
        }
    }
}

int main(int, char**)
{
    FILE* pFile = fopen("./printfdemo.cpp", "r");
    if(NULL == pFile)
    {
        printf("fopen err:%d, msg:%s\n", errno, strerror(errno));
        return -1;
    }

    PrintCode(pFile); printf("%d %i\n", (int)12, (int)12);
    PrintCode(pFile); printf("%hhd\n", (char)'A');
    PrintCode(pFile); printf("%hd\n", (short)12);
    PrintCode(pFile); printf("%ld\n", (long)12);
    PrintCode(pFile); printf("%Ld\n", (long long)12);
    PrintCode(pFile); printf("%lld\n", (long long)12);
    PrintCode(pFile); printf("%jd\n", (intmax_t)12);
    PrintCode(pFile); printf("%zd\n", (size_t)12);
    PrintCode(pFile); printf("%td\n", (ptrdiff_t)12);

    PrintCode(pFile); printf("%.2d\n", 1234);
    PrintCode(pFile); printf("%.6d\n", 1234);
    PrintCode(pFile); printf("%.*d\n", 6, 1234);

    PrintCode(pFile); printf("%2d\n", 1234);
    PrintCode(pFile); printf("%02d\n", 1234);
    PrintCode(pFile); printf("%*d\n", 10, 1234);
    PrintCode(pFile); printf("%0*d\n", 10, 1234);
    PrintCode(pFile); printf("%'d\n", 12345678);

    PrintCode(pFile); printf("%-10d\n", 1234);
    PrintCode(pFile); printf("%+d %+d\n", 1234, -1234);
    PrintCode(pFile); printf("% d % d\n", 1234, -1234);
    PrintCode(pFile); printf("%#o %#x %#X\n", 123, 123, 123);
    PrintCode(pFile); printf("%#a %#A %#e %#E %#f %#F %#g %#G\n", (double)123, (double)123, (double)123, (double)123, (double)123, (double)123, (double)123, (double)123);

    PrintCode(pFile); printf("%o %u %x %X\n", 123, 123, 123, 123);
    PrintCode(pFile); printf("%hho %hhu %hhx %hhX\n", 'A', 'A', 'A', 'A');
    PrintCode(pFile); printf("%ho %hu %hx %hX\n", (unsigned)123, (uint16_t)123, (uint16_t)123, (uint16_t)123);
    PrintCode(pFile); printf("%lo %lu %lx %lX\n", (unsigned long)123, (unsigned long)123, (unsigned long)123, (unsigned long)123);
    PrintCode(pFile); printf("%Lo %Lu %Lx %LX\n", (unsigned long long)123, (unsigned long long)123, (unsigned long long)123, (unsigned long long)123);
    PrintCode(pFile); printf("%llo %llu %llx %llX\n", (unsigned long long)123, (unsigned long long)123, (unsigned long long)123, (unsigned long long)123);
    PrintCode(pFile); printf("%jo %ju %jx %jX\n", (uintmax_t)123, (uintmax_t)123, (uintmax_t)123, (uintmax_t)123);
    PrintCode(pFile); printf("%zo %zu %zx %zX\n", (size_t)123, (size_t)123, (size_t)123, (size_t)123);
    PrintCode(pFile); printf("%to %tu %tx %tX\n", (ptrdiff_t)123, (ptrdiff_t)123, (ptrdiff_t)123, (ptrdiff_t)123);

    PrintCode(pFile); printf("%.2o %.3u %.4x %.5X\n", 123, 123, 123, 123);
    PrintCode(pFile); printf("%.*o %.*u %.*x %.*X\n", 2, 123, 3, 123, 4, 123, 5, 123);

    PrintCode(pFile); printf("%e %e\n", 13.141, 13.14159267);
    PrintCode(pFile); printf("%E %E\n", 13.141, 13.14159267);
    PrintCode(pFile); printf("%f %f %f %f %f %f %f\n", 13.141, 13.14159267, NAN, INFINITY, 0.0/0.0, 1.0/0.0, -1.0/0.0);
    PrintCode(pFile); printf("%F %F %F %F %F %F %F\n", 13.141, 13.14159267, NAN, INFINITY, 0.0/0.0, 1.0/0.0, -1.0/0.0);
    PrintCode(pFile); printf("%g %g %g %g\n", 13.141, 13.14159267, 13141519267.686651, 0.0000012345678);
    PrintCode(pFile); printf("%G %G %G %G\n", 13.141, 13.14159267, 13141519267.686651, 0.0000012345678);
    PrintCode(pFile); printf("%a %a\n", 13.141, 13.14159267);
    PrintCode(pFile); printf("%A %A\n", 13.141, 13.14159267);
    PrintCode(pFile); printf("%le %lE %lf %lF %lg %lG %la %lA\n", 13141519267.68665134, 13141519267.68665134, 13141519267.68665134, 13141519267.68665134, 13141519267.68665134, 13141519267.68665134, 13141519267.68665134, 13141519267.68665134);
    PrintCode(pFile); printf("%Le %LE %Lf %LF %Lg %LG %La %LA\n", (long double)13141519267.68665134, (long double)13141519267.68665134, (long double)13141519267.68665134, (long double)13141519267.68665134, (long double)13141519267.68665134, (long double)13141519267.68665134, (long double)13141519267.68665134, (long double)13141519267.68665134);

    PrintCode(pFile); printf("%.2e %.3E %.4f %.5F %.6g %.7G %.8a %.9A\n", 13.68665134, 13.68665134, 13.68665134, 13.68665134, 13.68665134, 13.68665134, 13.68665134, 131.68665134);
    
    PrintCode(pFile); printf("%c\n", 'A');
    PrintCode(pFile); printf("%c\n", 97);
    PrintCode(pFile); printf("%s\n", "Hello World!");

    PrintCode(pFile); printf("%.3s\n", "Hello World!");


    setlocale(LC_ALL,"zh_CN.UTF-8");
    wchar_t wc[] = L"中文测试";
    PrintCode(pFile); printf("%lc\n", wc[0]);
    PrintCode(pFile); printf("%ls\n", wc);
    setlocale(LC_ALL,"");

    PrintCode(pFile); printf("%p\n", PrintCode);

    int num = 0;
    PrintCode(pFile); printf("abcdefg%n\n", &num);
    PrintCode(pFile); printf("num:%d\n", num);
    signed char sc_num = 0;
    PrintCode(pFile); printf("abcdefg%hhn\n", &sc_num);
    PrintCode(pFile); printf("sc_num:%hhd\n", sc_num);
    short s_num = 0;
    PrintCode(pFile); printf("abcdefg%hn\n", &s_num);
    PrintCode(pFile); printf("s_num:%hd\n", s_num);
    long l_num = 0;
    PrintCode(pFile); printf("abcdefg%ln\n", &l_num);
    PrintCode(pFile); printf("l_num:%ld\n", l_num);
    long long ll_num = 0;
    PrintCode(pFile); printf("abcdefg%lln\n", &ll_num);
    PrintCode(pFile); printf("ll_num:%lld\n", ll_num);
    intmax_t im_num = 0;
    PrintCode(pFile); printf("abcdefg%jn\n", &im_num);
    PrintCode(pFile); printf("im_num:%jd\n", im_num);
    size_t size_num = 0;
    PrintCode(pFile); printf("abcdefg%zn\n", &size_num);
    PrintCode(pFile); printf("im_num:%zd\n", size_num);
    ptrdiff_t pd_num = 0;
    PrintCode(pFile); printf("abcdefg%tn\n", &pd_num);
    PrintCode(pFile); printf("im_num:%td\n", pd_num);

    open("aaabbbccc", 0);
    PrintCode(pFile); printf("errmsg: %m\n");

    PrintCode(pFile); printf("%%\n");

    fclose(pFile);

    return 0;
}
