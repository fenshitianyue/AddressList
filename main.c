#include <stdio.h>
#include <stdlib.h>
#include"head.h"//第二层的头文件

int main()
{
    char option; //用char来接收选项比int型更省空间
    while (1)
    {
        Menu();//打印通讯录的菜单
        Init();//初始化通讯录
        printf("\n请选择要进行的操作：>");
        scanf("%c", &option);
        switch (option)
        {
        case '1':
            FindHuman();//查找指定联系人
            break;
        case '2':
            ChangeHuman();//修改指定联系人
            break;
        case '3':
            DeleteHuman();//删除指定联系人
            break;
        case '4':
            AddHuman();//添加指定联系人
            break;
        case '5':
            PrintHuman();//打印所有联系人
            break;
        case '6':
            Destroy();//清空通讯录
            break;
        case '7':
            return 0;//退出通讯录
        default:
            printf("输入错误，请重新选择！\n");
            break;
        }
        system("cls");//结束一次操作后清屏
    }

    return 0;
}