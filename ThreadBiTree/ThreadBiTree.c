#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef char Elemtype;
typedef enum {Link,Thread} PointerTag;  //枚举Link = 0表示有左右孩子,
                                        //    Thread=1表示指向先驱或后继

typedef struct BiTNode
{
    Elemtype data;
    struct BiTNode* lchild,*rchild;
    PointerTag LTag;
    PointerTag RTag;

}BiTNode,*BiTree;

Status CreateBiThrTree(BiTree* T)
{
    Elemtype ch;
    scanf("%c",&ch);

    if(ch == '#')
     *T = NULL;
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));           //创建头节点
        if(!*T)                                          //如申请不成功
            exit(_OVERFLOW);
        (*T)->data = ch;                                //创建根节点
        CreateBiThrTree(&(*T)->lchild);                 //递归进行创建左子树
        if((*T)->lchild)                                //递归回归后判断是否有左孩子
            (*T)->LTag = Link;                          //有表示有孩子已链接
        CreateBiThrTree(&(*T)->rchild);                 //递归回归后判断是否有又孩子
        if((*T)->rchild)                                //有表示有孩子已链接                        
            (*T)->RTag = Link;    
    }
    return OK;
}

BiTree pre;  //访问的节点

void InThreading(BiTree T)
{
    if(T)
    {
        InThreading(T->lchild);             //递归遍历左树
        if(!T->lchild)                      //如果没有该节点没有左树
        {                                   //指向前驱的位置
            T->LTag = Thread;
            T->lchild = pre;
        }
        if(!pre->rchild)                    //判断该节点的前驱是否有右子树
        {
            pre->RTag = Thread;             //后继线索/同步链接
            pre->rchild = T;                //前驱右孩子指向当前后继
        }
        pre = T;                //保持pre指向p的前驱
        InThreading(T->rchild);         //递归遍历右树
    }
}

Status InOrderThreading(BiTree *Thr,BiTree T)
{
    *Thr = (BiTree)malloc(sizeof(BiTNode));  //创建头节点
    if(!*Thr)
        exit(_OVERFLOW);
    (*Thr)->LTag = Link;            //左节点指向T的根节点
    (*Thr)->RTag = Thread;        
    (*Thr)->rchild = *Thr;          //右指针回指
    if(!T)       //若树为空，则左指针回指
        (*Thr)->lchild = *Thr;
    else
    {
        (*Thr)->lchild = T;         //头指针左孩子指向根节点
        pre = *Thr;                 //per前驱从节点开始
        InThreading(T);             //中序遍历进行中序线索化
        pre->rchild = *Thr;         //遍历最后的右节点指向头指针
        pre->RTag = Thread;         //后继线索/同步链接
        (*Thr)->rchild = pre;       //头节点右孩子指向最后一个节点的位置
    }
    

    return OK;
}

void visit(Elemtype e)
{
    printf("%c ",e);
}

Status InOderTraverse_Thr(BiTree T)
{
    BiTree p;
    p= T->lchild;      //头指针指向根节点
    
    while(p != T)           //如果T为空树,或者p == T结束
    {
        while(p->LTag == Link)        //判断左节点的标志,遍历左数最后一个节点 
            p = p->lchild;
        visit(p->data);             //访问左子树为空的节点，已链接
        while(p->RTag == Thread && p->rchild != T)      //p->rchild的情况是只有一个根节点
        {                                               //这时左右孩子都是头节点无须在打印
            p = p->rchild;                              //右边为线索，且不为右边指向不为根节点
            visit(p->data);                             //访问
        }
        p = p->rchild;                                  //线索访问前驱
    }
    return OK;
}

int main()
{
    BiTree H,T;
    printf("请按前序输入二叉树(如:'AB##CD##E###')");
    CreateBiThrTree(&T);
    InOrderThreading(&H,T);
    printf("中序遍历(输出)二叉线索树:\n");
    InOderTraverse_Thr(H);
    printf("\n");

    return 0;
}