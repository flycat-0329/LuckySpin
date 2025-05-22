#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "TokenDoubleLinkedList.h"
#define TokenNode struct TokenNode


Token* createToken(int id) {
	FILE* tokenDataFile = fopen("TokenData.txt", "r");
	Token* t = (Token*)malloc(sizeof(Token));
	char line[1024];

	if (tokenDataFile == NULL) {
		return NULL;
	}

	while (fgets(line, sizeof(line), tokenDataFile)) {
		int temp_id = atoi(strtok(line, ","));
		if (id == temp_id) {
			t->id = temp_id;
			strcpy(t->name, strtok(NULL, ","));
			t->value = atoi(strtok(NULL, ","));
			t->grade = atoi(strtok(NULL, ","));
			strcpy(t->description, strtok(NULL, ","));
			strcpy(t->category, strtok(NULL, ",\n"));
		}
	}

	return t;
}

int getTokenValue(int id) {
	FILE* tokenDataFile = fopen("TokenData.txt", "r");
	Token* t = (Token*)malloc(sizeof(Token));
	char line[1024];

	if (tokenDataFile == NULL) {
		return NULL;
	}

	while (fgets(line, sizeof(line), tokenDataFile)) {
		int temp_id = atoi(strtok(line, ","));
		if (id == temp_id) {
			t->id = temp_id;
			strcpy(t->name, strtok(NULL, ","));
			t->value = atoi(strtok(NULL, ","));
			t->grade = atoi(strtok(NULL, ","));
			strcpy(t->description, strtok(NULL, ","));
			strcpy(t->category, strtok(NULL, ",\n"));
		}
	}

	int temp = t->value;
	free(t);
	fclose(tokenDataFile);
	return temp;
}

int createTokenGrade(int grade) {
	FILE* tokenDataFile = fopen("TokenData.txt", "r");
	char line[1024];
	int gradeToken[10];
	int count = 0;

	if (tokenDataFile == NULL) {
		return NULL;
	}

	while (fgets(line, sizeof(line), tokenDataFile)) {
		int id = atoi(strtok(line, ","));
		strtok(NULL, ",");
		strtok(NULL, ",");
		int g = atoi(strtok(NULL, ","));

		if (g == grade) {
			gradeToken[count] = id;
			count++;
		}
	}

	fclose(tokenDataFile);

	return gradeToken[rand() % count];
}

void tokenListInit(TokenNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

void printTokenList(TokenNode* phead) {
	TokenNode* t;
	for (t = phead->rlink; t != phead->llink; t = t->rlink) {
		printf("%s, ", t->token->name);
	}
	printf("%s", t->token->name);
	printf("\n\n");
}

TokenNode* searchList(TokenNode* phead, int id) {
	TokenNode* t;
	for (t = phead->rlink; t != phead->llink; t = t->rlink) {
		if (t->token->id == id) {
			return t;
		}
	}

	return NULL;
}

int countToken(TokenNode* head) {
	int count = 0;
	for (TokenNode* temp = head; temp != head->llink; temp = temp->rlink) {
		count++;
	}

	return count;
}

void insertLastToken(TokenNode* head, int id) {
	TokenNode* token = (TokenNode*)malloc(sizeof(TokenNode));
	TokenNode* lastToken = head->llink;
	token->token = createToken(id);
	token->llink = lastToken;
	token->rlink = head;
	lastToken->rlink = token;
	head->llink = token;
}

void deleteToken(TokenNode* head, int id) {
	TokenNode* removed = searchList(head, id);
	if (removed == NULL) {
		printf("삭제할 토큰이 존재하지 않음");
		return;
	}
	if (head == removed) {
		free(removed);
		return;
	}

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed->token);
	free(removed);
}
