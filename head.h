#pragma once 
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "ListTable.h"

//用宏来定义文件路径是一个技巧，方便以后修改
#define FILENAME "MailList.data"

PNode header;//将头指针设置为全局变量
FILE *fp;

//接口
void Menu();
void Init();
void FindHuman();
void ChangeHuman();
void DeleteHuman();
void AddHuman();
void PrintHuman();
void Destroy();

//---------------------------------------------
void Menu()
{
    printf("###-----------------------------###\n");
    printf("###      1.>查找指定联系人      ###\n");
    printf("###-----------------------------###\n");
    printf("###      2.>修改指定联系人      ###\n");
    printf("###-----------------------------###\n");
    printf("###      3.>删除指定联系人      ###\n");
    printf("###-----------------------------###\n");
    printf("###      4.>添加指定联系人      ###\n");
    printf("###-----------------------------###\n");
    printf("###      5.>显示所有联系人      ###\n");
    printf("###-----------------------------###\n");
    printf("###      6.>删除所有联系人      ###\n");
    printf("###-----------------------------###\n");
    printf("###      7.>退出通讯录          ###\n");
    printf("###-----------------------------###\n");
}

void Init()
{
    HumanInfo human;
    TableInit(&header);//初始化链表
    if ((fp = fopen(FILENAME, "rb+")) == NULL && (fp = fopen(FILENAME, "wb+")) == NULL){
        printf("Error on open %s file!", FILENAME);//pause
        exit(1);
    }
    if (getFileSize(fp))
    {//如果文件不为空，则将文件内容加载到内存，用链表管理
        while (fread(&human, 1, sizeof(HumanInfo), fp))
        {
            if (TablePushBack(header, human) != 1){
                printf("初始化失败！\n");
                //用getch()接收一个无回显的空格作为暂停，以至于用户可以看见
                //“初始化失败！”这句话，下面的所有getch()用法均为此
                exit(1);
            }
        }
    }
}

//每次写操作后需要更新文件,将链表内容重新写回文件
//否则在程序运行期间进行的更改不会影响文件的实际内容
void UpdataFile()
{
    PNode str;
    freopen(FILENAME, "wb+", fp);
    for (str = header->_next; str != header; str = str->_next)
    {
        fwrite(&(str->_human), sizeof(HumanInfo), 1, fp);
    }
    fflush(fp);
}

void FindHuman()
{
    char name[30];
    printf("\n输入要查找联系人的姓名：");
    scanf("%*[^\n]");scanf("%*c");//每次输入前都要清空输入缓冲区
    //fgets这个函数相比gets要更加安全，推荐实际中使用这个函数
    fgets(name, 30, stdin);
    PNode pos;
    if (pos = TableFind(header, name))
    {
        Print(pos);
    }
    else
    {
        printf("没有找到该联系人的信息！\n");
    }
}

void AddHuman()
{
    HumanInfo dest;
    printf("\n输入需要添加联系人的信息\n");
    printf("姓名：");
    scanf("%*[^\n]");scanf("%*c");//清空输入缓冲区
    fgets(dest.name, 30, stdin);
    printf("性别：");
    scanf("%*[^\n]");scanf("%*c");//清空输入缓冲区
    fgets(dest.sex, 10, stdin);
    printf("手机号码：");
    scanf("%*[^\n]");scanf("%*c");//清空输入缓冲区
    fgets(dest.phonen, 15, stdin);
    printf("住址：");
    scanf("%*[^\n]");scanf("%*c");//清空输入缓冲区
    fgets(dest.site, 40, stdin);
    if (TablePushBack(header, dest) == 1)
    {
        printf("\n添加成功！\n");
        UpdataFile();//每次更改链表内容后，都要将更新写回文件
    }
    else
    {
        printf("\n添加失败！\n");
    }
}

void PrintHuman()
{
    PNode str = header->_next;
    if (str != header){
        //如果通讯录不为空，则清屏。提供更好的显示效果
        system("cls");
    }
    printf("------------------\n");
    for (;str != header;str = str->_next)
    {
        Print(str);
        printf("------------------\n");
    }
}

void ChangeHuman()
{
    char name[30] = { 0 };
    printf("\n输入需要修改的联系人的姓名：");
    scanf("%*[^\n]");scanf("%*c");//清空输入缓冲区
    fgets(name, 30, stdin);
    PNode pos;
    if (pos = TableFind(header, name))
    {
        printf("输入需要修改的联系人的信息\n");
        printf("姓名：");
        scanf("%*[^n]");scanf("%*c");;
        fgets(pos->_human.name, 30, stdin);
        printf("性别：");
        scanf("%*[^n]");scanf("%*c");;
        fgets(pos->_human.sex, 10, stdin);
        printf("手机号码：");
        scanf("%*[^n]");scanf("%*c");;
        fgets(pos->_human.phonen, 15, stdin);
        printf("住址：");
        scanf("%*[^n]");scanf("%*c");;
        fgets(pos->_human.site, 40, stdin);
        UpdataFile();//更新文件
        printf("修改成功！\n");
    }
    else
    {
        printf("未找到该联系人，修改失败！\n");
    }
}

void DeleteHuman()
{
    char name[30];
    printf("\n输入需要删除联系人的姓名：");
    scanf("%*[^n]");scanf("%*c");;
    fgets(name, 30, stdin);
    PNode del;
    if (del = TableFind(header, name))
    {
        del->_pre->_next = del->_next;
        del->_next->_pre = del->_pre;
        free(del);
        UpdataFile();//更新文件
        printf("删除成功！\n");
    }
    else
    {
        printf("未找到该联系人！\n");
    }
}

void Destroy()
{
    if (!TableIsEmpty(header))
    {
        TablePopBack(header);
    }
    UpdataFile();
    printf("销毁成功！\n");
}
