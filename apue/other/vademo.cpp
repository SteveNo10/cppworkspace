/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-17
* Descript: 
*
============================================================================*/

#include <stdarg.h>
#include <stdio.h>

//错误，虽然编译运行不会报错，但是需要根据第一个参数地址和类型，以及其它参数类型，来获取各个参数地址
//否则拿不到参数信息，实际函数体跟无参一样
void Func0(...)
{
    printf("Func0 err func!\n");
}

void Func1(int n, ...)
{
    printf("Func1:\n");

    va_list va;
    va_start(va, n);

    for(int i = 0; i < n; ++i)
    {
        int a = va_arg(va, int);
        printf("%d\n", a);
    }

    va_end(va);
}

void Func11(int tmp, ...)
{
    printf("Func11:\n");

    va_list va;
    va_start(va, tmp);

    int val = 0;
    while(true)
    {
        val = va_arg(va, int);
        if(-1 == val)
        {
            break;
        }
        else
        {
            printf("%d\n", val);
        }
    }

    va_end(va);
}

enum EnumType
{
    TYPE_INT = 0,
    TYPE_DOUBLE
};

void Func2(EnumType type, int n, ...)
{
    printf("Func2:\n");

    va_list va;
    va_start(va, n);

    for(int i = 0; i < n; ++i)
    {
        switch(type)
        {
        case TYPE_INT:
            {
                int x = va_arg(va, int);
                printf("%d\n", x);
                break;
            }
        case TYPE_DOUBLE:
            {
                double d = va_arg(va, double);
                printf("%f\n", d);
                break;
            }
        default:
            {
                printf("err type!\n");
                break;
            }
        }
    }

    va_end(va);
}

void MyPrintf(const char* format, ...)
{
    va_list va;
    va_start(va, format);

    while(*format != '\0')
    {
        if('%' == *format)
        {
            switch(*++format)
            {
                case '%':
                    {
                        putchar('%');
                        break;
                    }
                case 'd':
                    {
                        int i = va_arg(va, int);
                        printf("%d", i);
                        break;
                    }
                case 'f':
                    {
                        double d = va_arg(va, double);
                        printf("%f", d);
                        break;
                    }
                default:
                    {
                        printf("err format\n");
                        va_end(va);
                        return;
                    }
            }
        }
        else
        {
            putchar(*format);
        }

        ++format;
    }

    va_end(va);
}

int main(int, char**)
{
    Func0(1, 2, 3);
    Func1(3, 11, 12, 13);
    Func11(0, 111, 122, 133, -1);
    Func2(TYPE_INT, 3, 21, 22, 23);
    Func2(TYPE_DOUBLE, 3, 21.123, 22.223, 23.323);
    MyPrintf("123abc:%d, %f, %%\n", 333, 1314.151617);

    return 0;
}
