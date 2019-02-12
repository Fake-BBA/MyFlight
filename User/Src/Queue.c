#include "Queue.h"

//    创建队列函数
bool InitQueue(P_Queue p_Queue)    
{
	p_Queue->front=0;
	p_Queue->rear=0;
	return TRUE;
}

//    判断队列是否为空函数
bool IsEmptyQueue(P_Queue p_Queue)
{
	if(p_Queue->rear==p_Queue->front)
		return TRUE;
	else
		return FALSE;
}

//判断队列是否满
bool IsFullQueue(P_Queue p_Queue)
{
	if(((p_Queue->rear+1)%QUEUQ_SIZE)==p_Queue->front)
		return TRUE;
	else
		return FALSE;
}
//    入队函数
int8 InsertQueue(P_Queue p_Queue, elementype val)
{
	if(IsFullQueue(p_Queue))
		return FALSE;
	else
	{
		p_Queue->elements[p_Queue->rear]=val;
		p_Queue->rear=(p_Queue->rear+1)%QUEUQ_SIZE;
		return TRUE;
	}
	return FALSE;
}

// 出队函数
bool DeleteQueue(P_Queue p_Queue, elementype* val)
{
	if(IsEmptyQueue(p_Queue))
		return FALSE;
	else
	{
		*val=p_Queue->elements[p_Queue->front];
		p_Queue->front=(p_Queue->front+1)%QUEUQ_SIZE;
		return TRUE;
	}
	return FALSE;
}	

void DestroyQueue(P_Queue p_Queue);    //    摧毁队列函数
void TraverseQueue(P_Queue p_Queue);    //    遍历队列函数
void ClearQueue(P_Queue p_Queue);    //    清空队列函数
int LengthQueue(P_Queue p_Queue);    //    求队列长度函数