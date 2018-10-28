//ListTable.h
#pragma once
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<malloc.h>

typedef struct HumanInfo
{
    char name[20];
    char sex[10];
    char phonen[15];
    char site[40];
}HumanInfo;

//用双链表来管理底层的空间
typedef struct Node
{
    HumanInfo _human;
    struct Node* _next;
    struct Node* _pre;
}Node,*PNode;

PNode BuyNewNode(HumanInfo data);
void TableInit(PNode *head);
_Bool TablePop(PNode head, PNode pos);
_Bool TablePushBack(PNode head, HumanInfo data);
_Bool TablePopBack(PNode head);
PNode TableFind(PNode head, char* name);
_Bool TableIsEmpty(PNode head);
void Print(PNode pos);

//------------------------------------------

//申请节点
PNode BuyNewNode(HumanInfo data)
{
    PNode new_node = (PNode)malloc(sizeof(Node));
    new_node->_human = data;
    new_node->_pre = NULL;
    new_node->_next = NULL;
    return new_node;
}

//链表初始化
void TableInit(PNode *head)
{
    assert(head);
    HumanInfo temp = { "","","",""};
    *head = BuyNewNode(temp);
    (*head)->_pre = *head;
    (*head)->_next = *head;
}

//在链表的指定位置删除操作
_Bool TablePop(PNode head, PNode pos)
{
    assert(head);
    assert(pos);
    if (head->_next == head){
        return 0;
    }
    PNode str = head;
    while (str->_next != str)
    {
        if (str->_next == pos)
        {
            str->_next->_next->_pre = str;
            str->_next = str->_next->_next;
            free(str->_next);
            return 1;
        }
    }
    return 0;
}

//链表的尾插操作
_Bool TablePushBack(PNode head, HumanInfo data)
{
    assert(head);
    if (head->_next == head)
    {
        PNode new_node = BuyNewNode(data);
        new_node->_pre = head;
        new_node->_next = head;
        head->_next = new_node;
        head->_pre = new_node;
    }
    else
    {
        PNode new_node = BuyNewNode(data);
        new_node->_next = head;
        new_node->_pre = head->_pre;
        head->_pre->_next = new_node;
        head->_pre = new_node;
    }
    return 1;
}

//链表的尾删操作
_Bool TablePopBack(PNode head)
{
    assert(head);
    if (head->_next == head){
        return 1;
    }
    PNode temp = head->_pre;
    head->_pre = head->_pre->_pre;
    head->_pre->_pre->_next = head;
    free(temp);
    return 1;
}

//链表的节点查找操作
PNode TableFind(PNode head, char *name)
{
    assert(head);
    PNode str = head->_next;
    while ((str != head) && strcmp(str->_human.name, name) != 0)
    {
        str = str->_next;
    }
    if (head == str){
        return NULL;
    }
    else{
        return str;
    }
}

//判断链表是否为空的操作
_Bool TableIsEmpty(PNode head)
{
    return head->_pre == head;
}

//链表的节点数据打印操作
void Print(PNode pos)
{
    printf("姓名：%s\n", pos->_human.name);
    printf("性别：%s\n", pos->_human.sex);
    printf("电话：%s\n", pos->_human.phonen);
    printf("住址：%s\n",pos->_human.site );
}
