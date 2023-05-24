#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FASLE 0

typedef int Status;

typedef int Elmtype;    //树的元素类型
typedef Elmtype SqBiTree[MAX_SIZE]; //树的最大各数

typedef struct Position
{
    int level,order;
}Position;

Elmtype Nil=0;

//创建一个空树
Status InitBiTree(SqBiTree T)
{
    int i;
    for(i=0; i<MAX_SIZE;i++)
    {
        T[i] = Nil;
    }
    return OK;
}

#define ClearBiTree InitBiTree

//给每个树赋初值
Status CreateBiTree(SqBiTree T)
{
    int i = 0;
    while(i<10)
    {
        T[i] = i+1;
        if(i !=0 && T[(i+1)/2-1] == Nil &&T[i] != 0)//不是根节点且节点没有双亲"(i+1)/2-1得到双亲的位置",且不空
        {                                          
            printf("出现无双亲的非根节点%d\n",T[i]);
            exit(ERROR);
        }
        i++;
    }
    while(i<MAX_SIZE)
    {
        T[i] = Nil;
        i++;
    }
    return OK;
}

Status BiTreeEmpty(SqBiTree T)
{
    if(T[0] == Nil)
        return TRUE;
    else
        return FASLE;
}

//求树的深度
int BiTreeDepth(SqBiTree T)
{
    int i,j=0;
    for(i=MAX_SIZE-1;i>=0;i--)  //i从最后开始计数,每次都--,直到T[i]不为零是，推出循环
    {
        if(T[i] != Nil)
            break;
    }
    do{
        j++;                //由于是二叉树,2的j次幂每次跳过一层,跳到大于或者等于结束
    }while(i>=powl(2,j));   //这是j累加的就是树的深度
    return j;
}

//获取根节点
Status Root(SqBiTree T,Elmtype *e)
{
    if(BiTreeEmpty(T))
        return ERROR;
    else
        *e = T[0];
        return OK;
}

void visit(Elmtype e)
{
    printf("%d ",e);
}

//层序遍历二叉树
Status LevelOrderTaverse(SqBiTree T)
{
    int i=MAX_SIZE-1,j;
    if(BiTreeEmpty(T))
        return ERROR;
    while(T[i] == Nil)  
    {                   /*使用while可增加效率，待确认*/
        i--;            /*找到最后一个非空节点*/
    }        
    for(j=0;j<=i;j++)
    {
        if(T[j] != Nil)
        {
            visit(T[j]);
        }
    }
    printf("\n");
    return OK;
}

//前序遍历
void PerTraverse(SqBiTree T,Elmtype e)
{
    visit(T[e]);
    if(T[e*2+1] != Nil)         //奇数都为该节点的左树,左树不为空
        PerTraverse(T,e*2+1);   //递归进行
    if(T[e*2+2] != Nil)         //偶数都为该节点的右树,不为空
        PerTraverse(T,e*2+2);
}

//前序遍历二叉树
Status PerOrderTraverse(SqBiTree T)
{
    if(!BiTreeEmpty(T))
        PerTraverse(T,0);
    printf("\n");
        return OK;
}

void InTraverse(SqBiTree T,Elmtype e)
{
    if(T[e*2+1] != Nil)         //奇数都为该节点的左树,左树不为空
        InTraverse(T,e*2+1);   //递归进行
        visit(T[e]);
    if(T[e*2+2] != Nil)         //偶数都为该节点的右树,不为空
        InTraverse(T,e*2+2);
}

Status InOrderTraverse(SqBiTree T)
{
        if(!BiTreeEmpty(T))
        InTraverse(T,0);
    printf("\n");
        return OK;
}

void PostTraverse(SqBiTree T,Elmtype e)
{
    if(T[e*2+1] != Nil)         //奇数都为该节点的左树,左树不为空
        PostTraverse(T,e*2+1);   //递归进行
    if(T[e*2+2] != Nil)         //偶数都为该节点的右树,不为空
        PostTraverse(T,e*2+2);
        visit(T[e]);
}

Status PostOrderTraverse(SqBiTree T)
{
        if(!BiTreeEmpty(T))
        PostTraverse(T,0);
    printf("\n");
        return OK;
}

//获取该层数的某节点的值，2^(k-1)-1获得该层数的节点数,由于数组的下标从0开始因此需要-2
Elmtype Value(SqBiTree T,Position p)
{
   //if(T[(int)powl(2,p.level-1)]+p.order-2 > T[(int)powl(2,p.level-1)])
 //       return ERROR;
 //  else
    return T[(int)powl(2,p.level-1)]+p.order-2;
}

Status Assign(SqBiTree T,Position p,Elmtype value)
{
    int i = (int)powl(2,p.level-1)-2+p.order;

    if(value == Nil && T[2*i+1] != Nil || T[2*i+2] == !Nil) //给某元素赋值,但有双亲
        return ERROR;
    else if(value != Nil && T[(i+1)/2-1] == Nil)    //给叶子赋值但无双亲
        return ERROR;                               //(i+1)用于左叶寻找双亲，如直接i-1会导致左叶找错双亲，对于右叶并没影响
    T[i] = value;
    return OK;
    
}

Elmtype Parent(SqBiTree T, Elmtype value)
{
    int i = 0;
    if(BiTreeEmpty(T))      //判断树是否空
        return Nil;
    for(i=0; i<MAX_SIZE;i++)    //遍历树
    {
        if(T[i] == value)       //如有树的值相等
            return T[(i+1)/2-1];    //返回双亲位置
    }
        return Nil;             //没找到
}

Elmtype LeftChild(SqBiTree T, Elmtype value)
{
    int i =0;
    if(BiTreeEmpty(T))
        return Nil;
    for(i=0;i<MAX_SIZE;i++)
    {
        if(T[i] == value)
            return T[i*2+1];
    }
        return Nil;
}

Elmtype RightChild(SqBiTree T, Elmtype value)
{
    int i =0;
    if(BiTreeEmpty(T))
        return Nil;
    for(i=0;i<MAX_SIZE;i++)
    {
        if(T[i] == value)
            return T[i*2+2];
    }
        return Nil;
}

Elmtype LeftSibling(SqBiTree T,Elmtype value)
{
    int i;
    if(BiTreeEmpty(T))
        return Nil;
    for(i=1;i<=MAX_SIZE-1;i++)         //从第二个节点开始
    {
        if(T[i] == value && i%2 == 0)   //如当中某元素%2等0说明为右,有左兄弟
            return T[i-1];              //i-1得到左兄弟,顺序表中可行，二叉树只有左右兄弟
    }
        return Nil;
}

Elmtype RightSibling(SqBiTree T, Elmtype value)
{
    int i;
    if(BiTreeEmpty(T))
        return Nil;
    for(i=1;i<=MAX_SIZE-1;i++)
    {
        if(T[i] == value && i%2)    //如当中某元素%2等1说明为左,有右兄弟
            return T[i+1];          //i+1得到右兄弟,顺序表中可行,二叉树只有左右兄弟
    }
        return Nil;
}



int main()
{
    Status i;
    Position p;
    Elmtype e;
    SqBiTree T;
    InitBiTree(T);
    CreateBiTree(T);
    printf("建立二叉树后,树空否?%d(1:是 0：否),树的深度=%d",BiTreeEmpty(T),BiTreeDepth(T));
    
    i=Root(T,&e);
    if(i)
        printf("二叉树的根为: %d\n");
    else
        printf("树空,无根\n");
    printf("层序遍历二叉树:\n");
    LevelOrderTaverse(T);
    printf("前序遍历二叉树:\n");
    PerOrderTraverse(T);
    printf("中序遍历二叉树:\n");
    InOrderTraverse(T);
    printf("后序遍历二叉树:\n");
    PostOrderTraverse(T);
    printf("修改节点的层号3序号2。");
    p.level = 3;
    p.order = 2;
    e=Value(T,p);
    printf("待修改的结点的原值为%d输入新值:50\n",e);
    e = 50;
    Assign(T,p,e);
    printf("层序遍历二叉树:\n");
    LevelOrderTaverse(T);
    printf("节点%d的双亲为%d,",e,Parent(T,e));
    printf("左孩子为%d,右孩子为%d,",LeftChild(T,e),RightChild(T,e));
    printf("左兄弟为%d,右兄弟为%d\n",LeftSibling(T,e),RightSibling(T,e));
    ClearBiTree(T);
    printf("清空二叉树后,树是否空%d (1 是 0 否),树的深度%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i = Root(T,&e);
    if(i)
        printf("二叉树的根为%d",e);
    else
        printf("树无根");


    return 0;
}