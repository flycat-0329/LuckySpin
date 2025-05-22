#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <conio.h> 
#include <windows.h>
#include "TokenDoubleLinkedList.h"
#include "Player.h"

Token* blankToken;
Token* gameBoard[5][5];
Player player;

int calcToken() {
	int tokenMoney = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%d ", gameBoard[i][j]->id);

			tokenMoney += getTokenValue(gameBoard[i][j]->id);
			
			switch (gameBoard[i][j]->id)
			{
			case 5:
				if (i > 0) {
					if (gameBoard[i - 1][j]->id == 3) {
						tokenMoney += 10;
						deleteToken(headNode, 3);
					}
					if (gameBoard[i - 1][j]->id == 4) {
						tokenMoney += 15;
						deleteToken(headNode, 4);
					}
				}

				if (i < 4) {
					if (gameBoard[i + 1][j]->id == 3) {
						tokenMoney += 10;
						deleteToken(headNode, 3);
					}
					if (gameBoard[i + 1][j]->id == 4) {
						tokenMoney += 15;
						deleteToken(headNode, 4);
					}
				}

				if (j > 0) {
					if (gameBoard[i][j - 1]->id == 3) {
						tokenMoney += 10;
						deleteToken(headNode, 3);
					}
					if (gameBoard[i][j - 1]->id == 4) {
						tokenMoney += 15;
						deleteToken(headNode, 4);
					}
				}
				if (j < 4) {
					if (gameBoard[i][j + 1]->id == 3) {
						tokenMoney += 10;
						deleteToken(headNode, 3);
					}
					if (gameBoard[i][j + 1]->id == 4) {
						tokenMoney += 15;
						deleteToken(headNode, 4);
					}
				}
				break;
			default:
				break;
			}
		}
	}
	printf("\n\n");
	return tokenMoney;
}

void makeBoard() {
	free(blankToken);
	blankToken = createToken(99);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			gameBoard[i][j] = blankToken;
		}
	}

	for (TokenNode* t = headNode->rlink; t != headNode; ) {
		int row = rand() % 5;
		int col = rand() % 5;

		if (gameBoard[row][col]->id == 99) {
			gameBoard[row][col] = t->token;
			t = t->rlink;
		}
	}

	return NULL;
}

void printBoard() {
	printf("\033[1;1H돈: %d\n\n", player.money);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("\033[0;3%dm %10s \033[0m", gameBoard[i][j]->grade + 1, gameBoard[i][j]->name);
		}
		printf("\n");
	}
	printf("\n");
}

int selectToken() {
	int trigger = rand() % 10000;

	if (trigger >= 0 && trigger < 7000) {		//레어도 0
		createTokenGrade(0);
	}
	else if (trigger >= 7000 && trigger < 9000) {		//레어도 1
		createTokenGrade(1);
	}
	else if (trigger >= 9000 && trigger < 9900) {		//레어도 2
		createTokenGrade(2);
	}
	else {		//레어도 3
		createTokenGrade(0);
	}
}

int main() {
	headNode = (TokenNode*)malloc(sizeof(TokenNode));
	srand(time(NULL));

	tokenListInit(headNode);

	while (1) {
		system("cls");
		printf("\033[1;1H돈: %d\n\n", player.money);
		printf("1. 게임 진행\n2. 내 토큰 보기\n3. 게임 설명\n4. 종료\n\n");
		int playerSelect = 0;
		scanf("%d", &playerSelect);

		switch (playerSelect) {
		case 1: {
			system("cls");
			Token* selectTokenList[3];
			int select = 0;

			makeBoard();
			printBoard();
			int turnMoney = calcToken();
			printf("%d원\n\n", turnMoney);
			player.money += turnMoney;

			selectTokenList[0] = createToken(selectToken());
			selectTokenList[1] = createToken(selectToken());
			selectTokenList[2] = createToken(selectToken());
			printf("토큰을 하나 선택해주세요. 선택하고 싶지 않다면 0을 입력해주세요.\n");
			printf("1. %s  2. %s  3. %s\n\n", &selectTokenList[0]->name, &selectTokenList[1]->name, &selectTokenList[2]->name);

			scanf("%d", &select);

			if (select != 0) {
				insertLastToken(headNode, selectTokenList[select - 1]->id);
				for (int i = 0; i < 3; i++) {
					free(selectTokenList[i]);
				}
			}
			break;
		}
		case 2: {
			system("cls");
			printTokenList(headNode);

			printf("\033[1;1H돈: %d\n\n", player.money);
			printf("토큰들의 정보를 보려면 1번을, 뒤로 가려면 2번을 눌려주세요.");
			int temp = 0;
			scanf("%d", &temp);
			switch (temp) {
			case 1:
				printf("아직 안 만들었슈");
				_getch();
				break;
			default:
				break;
			}
			break;
		}
		case 3: {
			printf("\033[1;1H돈: %d\n\n", player.money);
			printf("이 게임은 룰렛을 돌려 보유한 토큰을 보드 위에 배치한 뒤에 그 결과를 통해 돈을 얻는 것이 목적인 게임입니다.\n");
			printf("토큰은 게임 내에서 다양한 방식으로 얻을 수 있습니다.\n");
			printf("..."); 
			_getch();
			break;
		}
		default:
			break;
		}
	}
}