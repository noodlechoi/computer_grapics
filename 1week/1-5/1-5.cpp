#include <iostream>
#include <ctime>
#include <vector>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;

/*
4x4 크기의 격자 보드를 만든다. 격자 칸을 *로 표시한다. (다른 방법을 적용해도 무방함)
• 8개의 다른 대문자를 각각 2개씩 보드에 무작위로 배치한다.
• 보드 위쪽에 a b c d, 좌측에 1 2 3 4를 표시하여 칸의 위치를 알 수 있게 한다.
• 2개의 격자를 선택한다. 선택된 보드 칸에 o을 그려 선택된 것을 알려준다. 엔터키를 치면 선택된 칸의 문자가 보여진다.
• 두 문자가 같으면 그 칸에는 문자가 계속 그려지고, 문자가 다르면 다시 가려진다. 문자의 색상 변경한다.
• 특정 횟수만큼 진행할 수 있게 하고, 점수를 배점하여 출력한다. (횟수, 점수 배점은 각자 정해보기)
• 명령어: r – 게임을 리셋하고 다시 시작한다.
• 보드칸 선택 방법
• 행렬의 번호를 입력 받아 선택하기
• 1행1열이 기본으로 선택되어 있고, 특정 키보드를 입력 받아 칸을 이동한다

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main()
{
int i;
for (i = 0; i < 16; i++)
{
unsigned short text = i;
SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), text);
printf("setColor (%d)\n", text);
}
return 0;
}
*/

#define TRY 10
#define BOARDSIZE 4

typedef struct board
{
	bool is_open;
	char card;
	unsigned short color;
}BOARD;

// 0이면 빈칸 1이면 맞춘 카드
BOARD board[BOARDSIZE][BOARDSIZE];

void PrintBoard()
{
	cout << "  a b c d" << endl;
	for (int i = 0; i < BOARDSIZE; ++i) {
		cout << i;
		for (int j = 0; j < BOARDSIZE; ++j) {
			cout << " ";
			if (!board[i][j].is_open) {
				cout << "*";
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), board[i][j].color);
				cout << board[i][j].card;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		cout << endl;
	}
}

void ResetCard()
{
	int color = 1;
	int idx[BOARDSIZE * BOARDSIZE] = {};

	int cnt = 0;
	char m = 'A';
	for (int i = 0; i < BOARDSIZE * BOARDSIZE; ++i) {
		// 중복 체크 불 값
		bool is_dup = false;
		// 두번 넣기 위해 cnt 2의 배수일 때 문자랑 색깔 바꾸기
		if (cnt % 2 == 0) {
			m = rand() % 26 + 65;
			color++;
		}
		// 인덱스를 랜덤으로 집어넣기
		idx[i] = rand() % (BOARDSIZE * BOARDSIZE);
		// 행 = idx / BOARDSIZE, 열 = idx % BOARDSIZE
		cnt++;
		// 인덱스 중복 제거
		for (int j = 0; j < i; ++j) {
			if ((idx[i] == idx[j]) || ((m == (board[idx[j] / BOARDSIZE][idx[j] % BOARDSIZE].card)) && cnt % 2 == 1)) {
				i--;
				cnt--;
				is_dup = true;
				break;
			}
		}

		if (!is_dup) {
			board[idx[i] / BOARDSIZE][idx[i] % BOARDSIZE].card = m;
			board[idx[i] / BOARDSIZE][idx[i] % BOARDSIZE].color = color % 15 + 1;
			// cout << board[idx[i] / BOARDSIZE][idx[i] % BOARDSIZE].card << " " << (idx[i] / BOARDSIZE) << " " << (idx[i] % BOARDSIZE) << endl;
		}
		
		
	}
}

void SetCard()
{
	// 초기화
	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			board[i][j] = { false, NULL, 1 };
		}
	}

	ResetCard();
}

int main()
{
	srand((unsigned int)time(NULL));
	SetCard();

	int life = TRY;
	int point = 0;
	while (1) {
		PrintBoard();
		cout << "점수 : " << point << endl;
		cout << "생명 : " << life << endl;

		std::string c1, c2;
		cout << "card 1 : ";	cin >> c1;
		cout << "card 2 : ";	cin >> c2;
		if (board[c1[1] - '0'][c1[0] - 'a'].is_open) {
			cout << "이미 정답인 카드입니다." << endl;
			continue;
		}
		if (board[c2[1] - '0'][c2[0] - 'a'].is_open) {
			cout << "이미 정답인 카드입니다." << endl;
			continue;
		}

		// 카드가 정답인지 확인
		board[c1[1] - '0'][c1[0] - 'a'].is_open = true;
		board[c2[1] - '0'][c2[0] - 'a'].is_open = true;
		

		// 문자가 다르면 false로
		if (board[c1[1] - '0'][c1[0] - 'a'].card != board[c2[1] - '0'][c2[0] - 'a'].card) {
			PrintBoard();
			cout << "점수 : " << point << endl;
			cout << "생명 : " << life << endl;

			board[c1[1] - '0'][c1[0] - 'a'].is_open = false;
			board[c2[1] - '0'][c2[0] - 'a'].is_open = false;
			life--;
		}
		else {
			point++;
			cout << "정답 입니다!" << endl;
		}

		while (life <= 0) {
			cout << "r을 눌러서 리셋하세요" << endl;
			char c;	cin >> c;
			if (c == 'r') {
				SetCard();
				life = TRY;
				point = 0;
			}
			else {
				cout << "잘못된 문자입니다." << endl;
			}
		}
	}
}