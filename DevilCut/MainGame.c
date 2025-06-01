#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <conio.h> 
#include <math.h>
#include <windows.h>
#include "TokenDoubleLinkedList.h"

#define TAX_TURN 5

Token* blankToken;
Token* gameBoard[5][5];
int money = 0;

int calcToken() {
	int tokenMoney = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			tokenMoney += getTokenValue(gameBoard[i][j]->id);
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			switch (gameBoard[i][j]->id)
			{
			case 5:
				if (i > 0) {
					if (gameBoard[i - 1][j]->id == 3) {
						tokenMoney += 7;
						deleteToken(headNode, 3);
					}
					if (gameBoard[i - 1][j]->id == 4) {
						tokenMoney += 10;
						deleteToken(headNode, 4);
					}
				}

				if (i < 4) {
					if (gameBoard[i + 1][j]->id == 3) {
						tokenMoney += 7;
						deleteToken(headNode, 3);
					}
					if (gameBoard[i + 1][j]->id == 4) {
						tokenMoney += 10;
						deleteToken(headNode, 4);
					}
				}

				if (j > 0) {
					if (gameBoard[i][j - 1]->id == 3) {
						tokenMoney += 7;
						deleteToken(headNode, 3);
					}
					if (gameBoard[i][j - 1]->id == 4) {
						tokenMoney += 10;
						deleteToken(headNode, 4);
					}
				}
				if (j < 4) {
					if (gameBoard[i][j + 1]->id == 3) {
						tokenMoney += 7;
						deleteToken(headNode, 3);
					}
					if (gameBoard[i][j + 1]->id == 4) {
						tokenMoney += 10;
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

	int tokenCount = countToken(headNode);

	if (tokenCount <= 25) {
		for (TokenNode* t = headNode->rlink; t != headNode; ) {
			int row = rand() % 5;
			int col = rand() % 5;

			if (gameBoard[row][col]->id == 99) {
				gameBoard[row][col] = t->token;
				t = t->rlink;
			}
		}
	}
	else {
		Token** nodes = malloc(sizeof(Token*) * tokenCount);
		TokenNode* current = headNode->rlink;
		for (int i = 0; i < tokenCount && current; i++) {
			nodes[i] = current->token;
			current = current->rlink;
		}

		for (int i = tokenCount - 1; i > 0; i--) {
			int j = rand() % (i + 1);
			Token* temp = nodes[i];
			nodes[i] = nodes[j];
			nodes[j] = temp;
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				gameBoard[i][j] = nodes[i * 5 + j];
			}
		}

		free(nodes);
	}
	return NULL;
}

void printBoard() {
	printf("\033[1;1H돈: %d\n\n", money);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("\033[0;3%dm %10s \033[0m", gameBoard[i][j]->grade + 1, gameBoard[i][j]->name);
		}
		printf("\n");
	}
}

int selectToken() {
	int trigger = rand() % 10000;

	if (trigger >= 0 && trigger < 8000) {		//레어도 0
		createTokenGrade(0);
	}
	else if (trigger >= 8000 && trigger < 9500) {		//레어도 1
		createTokenGrade(1);
	}
	else if (trigger >= 9500 && trigger < 9900) {		//레어도 2
		createTokenGrade(2);
	}
	else {		//레어도 3
		createTokenGrade(0);
	}
}

int main() {
	headNode = (TokenNode*)malloc(sizeof(TokenNode));
	int turnCount = 0;
	double firstTax = 25.0;
	double growRate = 0.6;

	srand(time(NULL));
	tokenListInit(headNode);

	insertLastToken(headNode, 0);
	insertLastToken(headNode, 0);
	insertLastToken(headNode, 0);
	insertLastToken(headNode, 0);
	insertLastToken(headNode, 5);

	while (1) {
		system("cls");
		printf("\033[1;1H돈: %d\n%d턴 후에 %.0f원 납부 예정\n현재 %d턴\n\n", money, TAX_TURN - (turnCount % TAX_TURN), firstTax * pow(1.0 + growRate, turnCount / TAX_TURN), turnCount);
		printf("1. 게임 진행\n2. 내 토큰 보기\n3. 게임 설명\n4. 종료\n\n");
		int playerSelect = 0;
		while (1) {
			int a = scanf("%d", &playerSelect);
			if (a == 1) {
				break;
			}
			else {
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF);
			}
		}

		switch (playerSelect) {
		case 1: {
			system("cls");
			Token* selectTokenList[3];
			int tokenSelect = 0;

			makeBoard();
			printBoard();
			int turnMoney = calcToken();
			printf("%d원을 벌었다!\n\n", turnMoney);
			money += turnMoney;

			selectTokenList[0] = createToken(selectToken());
			selectTokenList[1] = createToken(selectToken());
			selectTokenList[2] = createToken(selectToken());
			printf("토큰을 하나 선택해주세요. 선택하고 싶지 않다면 0을 입력해주세요.\n");
			printf("1. %s  2. %s  3. %s\n\n", &selectTokenList[0]->name, &selectTokenList[1]->name, &selectTokenList[2]->name);
			
			while (1) {
				if (scanf("%d", &tokenSelect) == 1) {
					break;
				}
				else {
					int ch;
					while ((ch = getchar()) != '\n' && ch != EOF);
				}
			}

			if (tokenSelect != 0) {
				insertLastToken(headNode, selectTokenList[tokenSelect - 1]->id);
				for (int i = 0; i < 3; i++) {
					free(selectTokenList[i]);
				}
			}

			turnCount++;

			if (turnCount % TAX_TURN == 0) {
				system("cls");
				printf("\033[1;1H돈: %d\n\n", money);
				printf("아니 뭐 벌써 세금을 떼가!\n\n");
				_getch();
				if (money > (firstTax * pow(1 + growRate, (turnCount - 1) / TAX_TURN))) {
					printf("휴 다행이다.. 이번엔 어떻게든 넘어갔어..");
					money -= firstTax * pow(1 + growRate, (turnCount - 1) / TAX_TURN);
					_getch();
				}
				else {
					printf("아니 하루만! 진짜 딱 하루만 더 시간을.. 안 돼! 죽기 싫어!! 으아아악!!");
					printf("\nGame Over");
					printf("\n총 %d 턴을 버텼다!", turnCount);
					_getch();
					exit(0);
				}
			}
			break;
		}
		case 2: {
			system("cls");
			printf("\033[1;1H돈: %d\n\n", money);
			printTokenList(headNode);
			printf("토큰들의 정보를 보려면 1번을, 뒤로 가려면 2번을 눌려주세요.");
			int temp = 0;
			while (1) {
				if (scanf("%d", &temp) == 1) {
					break;
				}
				else {
					int ch;
					while ((ch = getchar()) != '\n' && ch != EOF);
				}
			}

			switch (temp) {
			case 1:
				system("cls");
				printTokenInfo();
				_getch();
				break;
			default:
				break;
			}
			break;
		}
		case 3: {
			system("cls");
			printf("\033[1;1H돈: %d\n\n", money);
			printf("이 게임은 룰렛을 돌려 보유한 토큰을 보드 위에 배치한 뒤에 그 결과를 통해 돈을 얻는 것이 목적인 게임입니다.\n");
			printf("토큰은 게임 내에서 다양한 방식으로 얻을 수 있습니다.\n");
			printf("..."); 
			_getch();
			break;
		}
		case 4: {
			exit(0);
		}
		default:
			break;
		}
	}
}