#include<stdio.h>
#include<string.h>
#include<stdbool.h>


// Set up DFA Table
int dfaTable[10][130];
enum states{q0, q1, q2, q3, q4, q5, q6, q7, q8, q9};
char stateMessage[10][100] = {"Invalid Token", "Invalid Token", "Identifier", "Constant", "Invalid Token", "Operator", "Identifier", "Identifier", "Keyword", "Keyword"};

char seperators[100] = {',', ' ', '\n', '{', '}', '[', ']', ';', '(', ')'};
int seperatorCount = 10;

// Initialize DFA Table
void initDfa() {
  memset(dfaTable, 0, sizeof(dfaTable));

  int idenStates[] = {q2, q6, q7, q8, q9};
  int i, j;
  for(i = 0; i < 5; i++){
    for(j = 48; j < 58; j++) {
      dfaTable[idenStates[i]][j] = q2;
    }

    for(j = 65; j < 91; j++) {
      dfaTable[idenStates[i]][j] = q2;
    }

    for(j = 97; j < 123; j++) {
      dfaTable[idenStates[i]][j] = q2;
    }

    dfaTable[idenStates[i]]['_'] = q2;
  }

  for(j = 65; j < 91; j++) {
    dfaTable[q1][j] = q2;
  }

  for(j = 97; j < 123; j++) {
    dfaTable[q1][j] = q2;
  }

  dfaTable[q1]['_'] = q2;

  for(j = 48; j < 58; j++) {
    dfaTable[q1][j] = q3;
    dfaTable[q3][j] = q3;
    dfaTable[q5][j] = q3;
    dfaTable[q4][j] = q3;
  }

  dfaTable[q3]['.'] = q4;
  dfaTable[q1]['+'] = q5;
  dfaTable[q1]['-'] = q5;

  dfaTable[q1]['i'] = q6;
  dfaTable[q6]['n'] = q7;
  dfaTable[q7]['t'] = q8;
  dfaTable[q6]['f'] = q9;
}

bool isSeperator(char x) {
  int i;
  for(i = 0; i < seperatorCount; i++) {
    if(x == seperators[i])
      return true;
  }
  return false;
}

int main() {

  initDfa();

  char code[1000], x;
  int i = 0;

  // Scan code from input file.
  while(scanf("%c", &x) != EOF) {
    code[i] = x;
    i++;
  }

  int codeLength = i;
 
  char token[100];
  memset(token, 0, sizeof(token));
  int tokenIndex = 0;

  int currentState = q1;
  int codeIndex;
  
  printf("\tCurrent Token\tType\n");

  for(codeIndex = 0; codeIndex < codeLength; codeIndex++) {
    if (isSeperator(code[codeIndex])) {
      if (strlen(token) != 0) {
	printf("\t%s\t\t%s\n", token, stateMessage[currentState]);
	currentState = q1;
	memset(token, 0, sizeof(token));
	tokenIndex = 0;
      }
    }
    else {
      token[tokenIndex] = code[codeIndex];
      tokenIndex++;
      currentState = dfaTable[currentState][code[codeIndex]];
    }
  }

  return 0;
}
