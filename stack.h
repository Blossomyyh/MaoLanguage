/*****************************************************************************/
/*
*Copyright 2015 Yuhan Yin.
*All Rights Reserved.
*File Name: stack.h
*Functions used in Mao language are declared and defined here
*
*Version: 1.0
*Completed Date: 2015.12.27
*/
/*****************************************************************************/
#pragma once
/*�궨������г��ȣ�Ҳ������������������������ȣ������λ���Լ�һЩ�������
����ɶ��ԵĴ�*/
#define MAX_LINE_LEN 1001
#define VAR_NAME_LEN 21
#define MAX_FIGURE_BITS 330
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

/*������������Variable����������������ë���Ա���*/
typedef struct Variable {
	int var_type;
	char var_name[VAR_NAME_LEN];
	int var_int_figr;
	double var_db_figr;
	struct Variable *nextVar;
}Variable;

/*������������SElemType�����ջ��Ԫ�ص�����*/
typedef struct SElemType {
	int data_type;//oprtr 0, int 1, double 2
	char oprtr;
	int int_figr;
	double db_figr;
} SElem;
/*ջ�Ľڵ�Ķ���*/
typedef struct StackNode {
	SElem s_data;
	struct StackNode *next;
}StackNode, *PLinkStack;
typedef struct {
	PLinkStack top;
	int count;
}LinkStack;

typedef int Status;
/*��ʼ��ջ*/
Status InitStack(LinkStack *NewStack) {
  NewStack->top = (PLinkStack)calloc(1, sizeof(StackNode));
  NewStack->count = 0;
  if (!NewStack)
	return ERROR;
  else
	return OK;
}
/*ѹջ*/
Status Push(LinkStack *Stack, SElem s_elem) {
  PLinkStack newNode = (PLinkStack)calloc(1, sizeof(StackNode));
  newNode->s_data = s_elem;
  newNode->next = Stack->top;
  Stack->top = newNode;
  Stack->count++;
  return OK;
}
/*��ջ*/
Status Pop(LinkStack *Stack, SElem *elem_recver) {
  if (!Stack->top)
	return ERROR;
  *elem_recver = Stack->top->s_data;
  Stack->top = Stack->top->next;
  Stack->count--;
  return OK;
}
/*�ж�ջ�Ƿ�Ϊ��*/
Status StackEmpty(LinkStack SLinker) {
  if (SLinker.count == 0)
	return TRUE;
  else
	return FALSE;
}
/*���ջ*/
Status StackClear(LinkStack *Stack) {
  PLinkStack next_node;
  while (Stack->top->next) {
	next_node = Stack->top->next;
	free(Stack->top);
	Stack->top = next_node;
  }
  Stack->count = 0;
  return OK;
}