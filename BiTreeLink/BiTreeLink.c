#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAX_SIZE 30

typedef char Elmtype;
typedef int Status;
typedef char String[24];

int Index=1;
String str;
Elmtype Nil = 0;

typedef struct BiTNode
{
    Elmtype data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

//创建空树
Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return OK;
}

#define ClearBiTree InitBiTree

//构建二叉树的初始内容
Status StrAssign(String T,Elmtype *str)
{
    int i;
    //if(strlen(str) > MAX_SIZE)
      //  return ERROR;
    T[0] = strlen(str);         //将输入的字符存储在，str数组中
    for(i=1; i<=T[0];i++)
    {
        T[i] = *(str+i-1);
    }
    return OK;
}

//创建二叉树
Status CreateBiTree(BiTree *T)
{
   Elmtype ch = str[Index++];       //Index为全局变量,从1开始
    //if(!T)
      //  return ERROR;
    if(ch == '#')                   //如果ch为'#'说明没有孩子,为空
        *T = NULL;
    else
    {
        *T =(BiTree)malloc(sizeof(BiTNode));
        (*T)->data = ch;            //生成根节点
        CreateBiTree(&(*T)->lchild);    //生成左子树
        CreateBiTree(&(*T)->rchild);    //生成右子树
    }

}

Status BiTreeEmpty(BiTree T)
{
    if(!T)
        return TRUE;
    else
        return FALSE;
}

int BiTreeDepth(BiTree T)
{
    int i,j;
    if(BiTreeEmpty(T))       //如果为空则深度为零
        return 0;
    if(T->lchild)           //如果T有左孩子
        i=BiTreeDepth(T->lchild);   //递归下一个左孩子
    else
        i=0;                    //最后得出树左的深度
    if(T->rchild)                   //如有右孩子
        j=BiTreeDepth(T->rchild); //递归下一个右孩子
    else                        
        j=0;                    //最后得出右树的深度
                                    //可代数 AB##CD##E###
    return i>j?i+1:j+1;     //最终i跟j比较大小 哪一个大,最后加第一个节点的深度(+1),则是该树的深度
}

Elmtype Root(BiTree T)
{
    if(BiTreeEmpty(T))
        return Nil;
    else
        return T->data;
}

void visit(Elmtype e)
{
    printf("%c ",e);
}

//前序遍历
void PerOrderTraverse(BiTree T)
{
    if(T==NULL)         //如果T空，或递归到最后一个返回当前函数
        return;
    visit(T->data); 
    PerOrderTraverse(T->lchild);
    PerOrderTraverse(T->rchild);
}

void InOrderTraverse(BiTree T)
{
    if(T==NULL)         //如果T空，或递归到最后一个返回当前函数
        return;
    PerOrderTraverse(T->lchild);
    visit(T->data); 
    PerOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTree T)
{
    if(T==NULL)         //如果T空，或递归到最后一个返回当前函数
        return;
    PerOrderTraverse(T->lchild);
    PerOrderTraverse(T->rchild);
    visit(T->data); 
}

int main()
{
    int i;
    BiTree T;
    Elmtype e;

    InitBiTree(&T);

    StrAssign(str,"ABDH#K###E##CFI###G#J##");

    CreateBiTree(&T);

    printf("构造空二叉树后,树空否?%d(1:是  0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    
    e = Root(T);
    printf("二叉树的根为: %c \n",e);

    printf("前序遍历二叉树: \n");
    PerOrderTraverse(T);
    printf("\n中序遍历二叉树: \n");
    InOrderTraverse(T);
    printf("\n后序遍历二叉撒: \n");
    PostOrderTraverse(T);
    ClearBiTree(&T);
    i = Root(T);
    if(!i)
        printf("\n树空,无根\n");

    return 0;
}