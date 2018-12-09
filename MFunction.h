/*****************************************************************************/
/*
*Copyright 2015 Yuhan Yin.
*All Rights Reserved.
*File Name: MFunction.h
*Functions used in Mao language are declared and defined here
*
*Version: 1.0
*Completed Date: 2015.12.27
*/
/*****************************************************************************/
#pragma once

Variable *g_First = NULL;
FILE *g_fp = NULL;
/*���ļ��ж���һ�У�����*line��*/
void ReadLine(char **line) {
  int cur_add = 0;
  for (cur_add = 0; cur_add < MAX_LINE_LEN; cur_add++)
	*(*line + cur_add) = 0;
  char cur_char;
  cur_add = 0;
  cur_char = fgetc(g_fp);
  do {
	/*����EOF���ر��ļ�����������*/
	if (cur_char == EOF) {
	  fclose(g_fp);
	  exit(0);
	}
	/*�ж��Ƿ�����������������ǣ�������ͷ�ַ��Ա��*/
	if (cur_char == ' ' || cur_char == '\t')
	  if (!strcmp(*line, "int") || !strcmp(*line, "double"))
		**line = '#';
	/*����space*/
	if (!isspace(cur_char)) {
	  *(*line + cur_add) = cur_char;
	  cur_add++;
	}
	if (cur_char == ';')
	  break;
	cur_char = fgetc(g_fp);
  } while (1);
 }
/*�ж��Ƿ�����������*/
int IsDclar(char *cur_line) {
  int var_type = 0;
  if (!strncmp(cur_line, "#nt", 3))
	var_type = 1;
  else if (!strncmp(cur_line, "#ouble", 6))
	var_type = 2;
  return var_type;
}
/*������������ʼ��Ϊ0*/
int DclarVar(int figr_type, char *cur_line, int initial_add, Variable *curStruct) {
  int i = 0;
  curStruct->var_type = figr_type;
  memset(curStruct->var_name, 0, VAR_NAME_LEN * sizeof(char));
  if (initial_add == 0)
	initial_add = figr_type == 1 ? 3 : 6;
  i = 0;
  do {
	if (isalnum(*(cur_line + initial_add))) {
	  curStruct->var_name[i] = *(cur_line + initial_add);
	  initial_add++;
	  i++;
	}

	if (*(cur_line + initial_add) == ',')
	  return initial_add + 1;
	if (*(cur_line + initial_add) == ';')
	  return 0;
  } while (1);
  /*��������Ϊ������ʱ*/
  if (strcmp("int", curStruct->var_name) == 0
	|| strcmp("double", curStruct->var_name) == 0
	|| strcmp("print", curStruct->var_name) == 0) {
	printf("Reserved Variable Name!");
	exit(2);
  }
}
/*�жϵ�ǰ�ַ��������Ƿ�Ϊ�����������ǣ�����һ��
��<���渺�ţ�<0),>��������(>0)����������ȼ�����:
; -1, = 1, ( 2, +- 3, * / 4, <> 5, ) 60 default 0
����Ϊ�����ʱ����ǰ�ַ�Ϊ��ĸ���ֻ�'.'�����ȼ�Ϊ0
*/
int OprtrPri(char ch) {
	int no = 0;
	switch (ch) {
	case ';':
		no = -1;
		break;
	case '=':
		no = 1;
		break;
	case '(':
		no = 2;
		break;
	case '+':
	case '-':
		no = 3;
		break;
	case '*':
	case '/':
		no =4;
		break;
	case'<':
	case'>':
		no = 5;
		break;
	case ')':
		no = 60;
		break;
	default:
		no = 0;
		break;
	}
	return no;
}
/*��������Ѱ�Ҹñ���*/
Variable *MatchVar(char *var_name) {
  Variable *checker = g_First;
  while (checker->nextVar != NULL) {
	if (!strcmp(checker->var_name, var_name))
	  break;
	checker = checker->nextVar;
  }
  /*δ�ҵ�ƥ��ı�������˵��û�������ñ���*/
  if (!checker) {
	printf("Error:variable undeclared!");
	fclose(g_fp);
	exit(3);
  }
  else
	return checker;
}
/*�ж��Ƿ�Ϊ�����*/
Status IsPrintLine(char *cur_line) {
  int initial_add = 5;
  if (!strncmp(cur_line, "print(", 6))
	return TRUE;
  else
	return FALSE;
}
/*�ж��ַ����д���ı����Ƿ�Ϊdouble����*/
Status IsDouble(char *num) {
  unsigned int i;
  for (i = 0; i < strlen(num); i++)
	if (*(num + i) == '.')
	  return TRUE;
  return FALSE;
}
/*������Ĵ���*/
void Print(char *cur_line, Variable *var_finder) {
  int initial_add;
  int i = 0;
  char *content = (char *)calloc(MAX_FIGURE_BITS, sizeof(char));
  /*�����ǰ6���ַ�Ϊprint(����������ݴӵ�7���ַ���ʼ*/
  initial_add = 6;
  /*�������ʱ��Ҫ��������ݿ���������(ASCII 48 - 57),'.'(46),'-'(45)��'+'(43)
  ����','(44)'/'(47)�������*/
  while (*(cur_line + initial_add) >= '+' && *(cur_line + initial_add) <= '9'
	&& i < MAX_FIGURE_BITS) {
	*(content + i) = *(cur_line + initial_add);
	i++;
	initial_add++;
  }
  /*��*content��Ϊ�գ�˵����print����*/
  if (*content) {
	if (IsDouble(content)) {
	  printf("%lf\n", atof(content));
	  free(content);
	  return;
	}
	else {
	  printf("%d\n", atoi(content));
	  free(content);
	  return;
	}
  }
  while (*(cur_line + initial_add) != ')') {
	*(content + i) = *(cur_line + initial_add);
	i++;
	initial_add++;
  }
  var_finder = MatchVar(content);
  if (var_finder->var_type == 1)
	printf("%d\n", var_finder->var_int_figr);
  else
	printf("%lf\n", var_finder->var_db_figr);
  free(content);
  return;
}
/*����׺���ʽתΪ��׺���ʽʱ������������ջ��ֱ�Ӽ���*/
void CalcuPart(LinkStack *Res, LinkStack *Oprtr, const int maxPri) {
  SElem TempRes1, TempRes2;
  SElem OprtrHolder;
  double factor1, factor2;
  
  while (!StackEmpty(*Oprtr)){
	memset(&TempRes1, 0, sizeof(SElem));
	memset(&TempRes2, 0, sizeof(SElem));
	memset(&OprtrHolder, 0, sizeof(SElem));
	Pop(Oprtr, &OprtrHolder);
	if (OprtrHolder.oprtr == '(')
	  break;
	if (OprtrHolder.oprtr == '<') {
	  Res->top->s_data.db_figr *= -1;
	  Res->top->s_data.int_figr *= -1;
	}
	else if(OprtrHolder.oprtr != '>'){
	  Pop(Res, &TempRes2);
	  Pop(Res, &TempRes1);
	  if (TempRes1.data_type == 1)
		factor1 = TempRes1.int_figr;
	  else
		factor1 = TempRes1.db_figr;
	  if (TempRes2.data_type == 1)
		factor2 = TempRes2.int_figr;
	  else
		factor2 = TempRes2.db_figr;
	  switch (OprtrHolder.oprtr) {
	  case'+':
		factor1 += factor2;
		break;
	  case'-':
		factor1 -= factor2;
		break;
	  case'*':
		factor1 *= factor2;
		break;
	  case'/':
		if (factor2 == 0) {
		  printf("divided by ZERO\n");
		  fclose(g_fp);
		  exit(4);
		}
		else
		  factor1 /= factor2;
		break;
	  default:
		break;
	  }
	  /*judge which type of data should be restored*/
	  if (TempRes1.data_type * TempRes2.data_type == 1)
		TempRes1.int_figr = factor1;
	  else {
		TempRes1.data_type = 2;
		TempRes1.db_figr = factor1;
	  }
	  Push(Res, TempRes1);
	}
	if (maxPri != 60 && OprtrPri(Oprtr->top->s_data.oprtr) < maxPri)
	  break;
  }
}
/*����׺���ʽתΪ��׺��ͬʱ���м���*/
double CalcuEquation(char *line, int *totalAdd) {
  LinkStack Oprtr;
  LinkStack Res;
  InitStack(&Oprtr);
  InitStack(&Res);
  SElem TempElem;
  
  int cur_add = 0;
  int i = 0;
  Variable *seeker = g_First;
  char *content =(char *)calloc(MAX_FIGURE_BITS, sizeof(char));;
  do {
	memset(content, 0, MAX_FIGURE_BITS * sizeof(char));
	memset(&TempElem, 0, sizeof(SElem));
	i = 0;
	if (isalpha(*(line + cur_add))) {
	  do {
		*(content + i) = *(line + cur_add);
		cur_add++;
		i++;
	  } while (!OprtrPri(*(line + cur_add)));
	  seeker = MatchVar(content);
	  TempElem.data_type = seeker->var_type;
	  if (seeker->var_type == 1)
		TempElem.int_figr = seeker->var_int_figr;
	  else
		TempElem.db_figr = seeker->var_db_figr;
	  Push(&Res, TempElem);
	}
	else if (isdigit(*(line + cur_add))) {
	  do {
		*(content + i) = *(line + cur_add);
		cur_add++;
		i++;
	  } while (!OprtrPri(*(line + cur_add)));
	  if (IsDouble(content)) {
		TempElem.data_type = 2;
		TempElem.db_figr = atof(content);
	  }
	  else {
		TempElem.data_type = 1;
		TempElem.int_figr = atoi(content);
	  }
	  Push(&Res, TempElem);
	}
	else if (*(line + cur_add) != '=') {
	  /*�ж��Ƿ�Ϊ�����ţ��������Ϊ-+��ǰһ�ַ�Ϊ�������ǰһ�ַ���Ϊ')'ʱ��
	  -+����������*/
	  if ((OprtrPri(*(line + cur_add)) == 3)
		&& (OprtrPri(*(line + cur_add - 1)) % 10 != 0)) {
		if (*(line + cur_add) == '-')
		  *(line + cur_add) = '<';
		else
		  *(line + cur_add) = '>';
	  }
	  TempElem.oprtr = *(line + cur_add);
	  
	  if (*(line + cur_add) == ')')
		  CalcuPart(&Res, &Oprtr, OprtrPri(*(line + cur_add)));
	  else if (*(line + cur_add) == '(' || OprtrPri(*(line + cur_add)) >
		OprtrPri(Oprtr.top->s_data.oprtr))
		Push(&Oprtr, TempElem);
	  else {
		CalcuPart(&Res, &Oprtr, OprtrPri(*(line + cur_add)));
		Push(&Oprtr, TempElem);
	  }
		
	  cur_add++;
	}
	else {
	  Pop(&Res, &TempElem);
	  if (seeker->var_type == 1) {
		seeker->var_int_figr = CalcuEquation(line + cur_add + 1,
		  &cur_add);
		TempElem.int_figr = seeker->var_int_figr;
	  }
	  else {
		seeker->var_db_figr = CalcuEquation(line + cur_add + 1, &cur_add);
		TempElem.db_figr = seeker->var_db_figr;
	  }
	  Push(&Res, TempElem);
	}
  } while (*(line + cur_add) != ';');
  free(content);
  while (!StackEmpty(Oprtr))
	CalcuPart(&Res, &Oprtr, OprtrPri(Oprtr.top->s_data.oprtr));
  Pop(&Res, &TempElem);
  if (StackEmpty(Oprtr))
	StackClear(&Oprtr);
  if (StackEmpty(Res))
	StackClear(&Res);
  *totalAdd = *totalAdd + cur_add + 1;
  if (TempElem.data_type == 1)
	return (double)TempElem.int_figr;
  else
	return TempElem.db_figr;
}
