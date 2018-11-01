/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-01
* Descript: 
* mysql_store_result:一次性将结果返回到客户端，客户端费内存，mysql_fetch_row时直接判断是否非空即可知道是否循环完
* mysql_use_result:结果保存在服务端，需要客户端mysql_fetch_row()逐行获取，不能简单通过判断是否非空来判断是否无数据，因为服务器断开连接也会返回NULL，必须进一步结合mysql_errno或者mysql_error来判断
============================================================================*/

#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

const char ip[] = "192.168.1.32";
const unsigned int port = 4001;
const char username[] = "root";
const char pwd[] = "goome";
const char db[] = "test";
const char sql_select[] = "select * from student";
const char sql_insert[] = "insert into student (name, age, birthday) values('Tom', 23, '1988-01-02')";
const char sql_update[] = "update student set age = 30 where name = 'Tom'";
const char sql_delete[] = "delete from student where name = 'Tom'";

int f_query_1(MYSQL* mysql, const char* sql)
{
    mysql_query(mysql, sql);
    MYSQL_RES* res = mysql_store_result(mysql);
    if(res != NULL)
    {
        int column_num = mysql_num_fields(res);
        int row_num = mysql_num_rows(res);
        printf("query %d column %d row\n", column_num, row_num);

        if(row_num <= 0)
        {
            printf("query result empty!\n");
            mysql_free_result(res);
            return 0;
        }

        MYSQL_FIELD* field = NULL;
        while((field = mysql_fetch_field(res)) != NULL)
        {
            printf("%s\t", field->name);
        }

        printf("\n");

        MYSQL_ROW row = NULL;
        while((row = mysql_fetch_row(res)) != NULL)
        {
            for(int i = 0; i < column_num; ++i)
            {
                printf("%s\t", row[i]);
            }

            printf("\n");
        }
    }
    else
    {
        printf("query err!\n");
        return -1;
    }

    mysql_free_result(res);

    return 0;
}

int f_query_2(MYSQL* mysql, const char* sql)
{
    mysql_query(mysql, sql);
    MYSQL_RES* res = mysql_use_result(mysql);
    if(res != NULL)
    {
        int column_num = mysql_num_fields(res);
        if(column_num <= 0)
        {
            printf("query result empty!\n");
            mysql_free_result(res);
            return 0;
        }

        MYSQL_FIELD* field = NULL;
        while((field = mysql_fetch_field(res)) != NULL)
        {
            printf("%s\t", field->name);
        }

        printf("\n");

        MYSQL_ROW row = NULL;
        int row_num = 0;
        while((row = mysql_fetch_row(res)) != NULL)
        {
            ++row_num;
            for(int i = 0; i < column_num; ++i)
            {
                printf("%s\t", row[i]);
            }

            printf("\n");
        }

        if(0 != mysql_errno(mysql))
        {
            printf("mysql fetch row err:%s\n", mysql_error(mysql));
            return -1;
        }

        printf("query colunm:%d row:%d\n", column_num, row_num);
    }
    else
    {
        printf("query err!\n");
        return -1;
    }

    mysql_free_result(res);

    return 0;
}

int f_exec(MYSQL* mysql, const char* sql)
{
    int flag = mysql_real_query(mysql, sql, strlen(sql));
    if(0 == flag)
    {
        printf("exec success!\n");
    }
    else
    {
        printf("exec failed:%d\n", flag);
        return -1;
    }

    return 0;
}

int main(int, char**)
{
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_real_connect(&mysql, ip, username, pwd, db, port, NULL, CLIENT_FOUND_ROWS);

    f_query_1(&mysql, sql_select);

    f_exec(&mysql, sql_insert);

    f_query_1(&mysql, sql_select);

    f_exec(&mysql, sql_update);

    f_query_2(&mysql, sql_select);

    f_exec(&mysql, sql_delete);

    f_query_2(&mysql, sql_select);

    mysql_close(&mysql);

    return 0;
}
