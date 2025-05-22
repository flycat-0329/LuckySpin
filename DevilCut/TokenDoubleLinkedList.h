#pragma once

typedef struct Token {
	int id;
	char name[10];
	int value;
	int grade;
	char description[100];
	char category[10];
} Token;

typedef struct TokenNode {
	Token* token;
	struct TokenNode* llink;
	struct TokenNode* rlink;
} TokenNode;

TokenNode* headNode;

Token* createToken(int id);
int createTokenGrade(int grade);

void tokenListInit(TokenNode* phead);
void printTokenList(TokenNode* phead);
TokenNode* searchList(TokenNode* phead, int id);
int countToken(TokenNode* head);

void insertLastToken(TokenNode* head, int id);
void deleteToken(TokenNode* head, int id);