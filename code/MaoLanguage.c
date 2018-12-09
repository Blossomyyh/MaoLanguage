#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "MFunction.h"

int main(int argc, char *argv[]) {
  g_fp = fopen(argv[1], "r");
  if (!g_fp) {
	printf("Error: Can't find the file.");
	exit(1);
  }

  Variable *current = NULL;
  Variable *previous = NULL;
  /*curline will be used repeatedly*/
  char *curline = (char *)calloc(MAX_LINE_LEN, sizeof(char));

  int var_type = 0;
  int cur_add = 0;
  ReadLine(&curline);
  /*declaration part*/
  while (var_type = IsDclar(curline)) {
	do {
	  current = (Variable *)calloc(1, sizeof(Variable));
	  if (!g_First)
		g_First = current;
	  if (previous != NULL)
		previous->nextVar = current;
	  cur_add = DclarVar(var_type, curline, cur_add, current);
	  current->nextVar = NULL;
	  previous = current;
	} while (cur_add != 0);
	ReadLine(&curline);
  };
  /*execute part*/
  Variable *seekVar = (Variable *)calloc(1, sizeof(Variable));
  do {
	if (IsPrintLine(curline))
	  Print(curline, seekVar);
	else {
	  cur_add = 0;
	  CalcuEquation(curline, &cur_add);
	}
	ReadLine(&curline);
  } while (1);
}