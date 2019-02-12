#ifndef _QUEUE_H__
#define _QUEUE_H__

#include "MyTypedef.h"

typedef uint8 elementype;        //    定义数据类型
/*//    定义节点结构
typedef struct Node {
    Elementype Element;        //    数据域
    struct Node * Next;
}NODE, *PNODE;


*/

//    定义队列结构体
#define QUEUQ_SIZE 100	//队列容量为100

typedef struct MyQueue {
    uint8 front, rear;        //    队列头，尾指针
	elementype elements[QUEUQ_SIZE];
} Queue, *P_Queue;
//为提高效率，将使用数组作为队列缓存空间

//    声明函数体
bool InitQueue(P_Queue  p_Queue);    //创建队列函数
bool IsEmptyQueue(P_Queue p_Queue);    //判断队列是否为空函数
bool IsFullQueue(P_Queue p_Queue);	//判断队列是否满
int8 InsertQueue(P_Queue p_Queue, elementype val);    //入队函数
bool DeleteQueue(P_Queue p_Queue,elementype * val);    //出队函数
void DestroyQueue(P_Queue p_Queue);    //摧毁队列函数
void TraverseQueue(P_Queue p_Queue);    //遍历队列函数
void ClearQueue(P_Queue p_Queue);    //清空队列函数
int LengthQueue(P_Queue p_Queue);    //求队列长度函数

#endif