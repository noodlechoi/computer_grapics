﻿#include <iostream>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

/*
50x50 크기의 2차원 배열을 만든다. 좌측 상단에서 우측 하단으로 가는 한 줄의 경로를 만든 후 화면에 출력한다.

• 0은 길, 1은 벽 (혹은 반대로)으로 표시한다.

• 이때, 경로는 4방향인 좌/우/상/하로 연결되고, 다음의 조건에 맞게 경로를 만든다.
• 조건 1) 경로는 한쪽 방향으로 5칸 이상 계속 이동할 수 없다.
• 조건 2) 경로는 좌우상하로 최소한 1번 이상 방향을 전환한 적이 있어야 한다.
 => cnt로 세어서 하기
 주변 8칸에 2개 이상이면 다시

• enter키: 새로운 경로를 만든다.
• r: 임의의 객체 (문자)가 경로 시작칸에 나타난다. (다른 색상으로 그리기)
• +/-: 나타난 객체를 경로 따라 앞으로/뒤로 이동한다.	=> 인덱스에 위치 저장
• q: 프로그램 종료

*/

#define BOARDSIZE 20

typedef struct way
{
	int cnt;
	bool is_gone;
}WAY;

int board[BOARDSIZE][BOARDSIZE];

void ResetBoard()
{
	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			board[i][j] = 0;
		}
	}
}

void PrintBoard()
{
	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			if (board[i][j] == 0) cout << "." << " ";
			else
				cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

bool IsExist(const int& r, const int& c)
{
	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			if (board[r][c] == board[i][j])	return true;
		}
	}

	return false;
}

bool IsAround(const int& r, const int& c)
{
	// 주변에 2개 이상 있는지 확인
	int cnt = 0;

	if (board[r - 1][c] == 1) cnt++;
	if (board[r][c - 1] == 1) cnt++;
	if (board[r + 1][c] == 1) cnt++;
	if (board[r][c + 1] == 1) cnt++;

	if (cnt > 1)	return false;
	else
		return true;
}

void MakePath()
{
	ResetBoard();

	WAY north = {}, south = {}, west = {}, east = {};

	int i = 0, j = 0;
	while (1) {
		board[i][j] = 1;

		// 방향 랜덤으로 정하기
		int direct = rand() % 4;
		if (direct == 0) {	// north
			// 주변에 길이 하나밖에 없다면
			if (i - 1 >= 0) {
				// 4번 연속 갔다면 다시 랜덤으로
				if (north.cnt >= 4)	continue;

				// 범위가 보드 안이면
				if (IsAround(i - 1, j))	i--;
				else
					continue;

				north.cnt++;
				south.cnt = 0;
				west.cnt = 0;
				east.cnt = 0;

				if (!north.is_gone)
					north.is_gone = true;
			}
		}
		else if (direct == 1) {	// south
			if (i + 1 <= BOARDSIZE) {
				// 4번 연속 갔다면 다시 랜덤으로
				if (south.cnt >= 4)	continue;

				// 범위가 보드 안이면
				if (IsAround(i + 1, j))	i++;
				else
					continue;

				north.cnt = 0;
				south.cnt++;
				west.cnt = 0;
				east.cnt = 0;

				if (!south.is_gone)
					south.is_gone = true;
			}
		}
		else if (direct == 2) {	// west
			if (j - 1 >= 0) {
				// 4번 연속 갔다면 다시 랜덤으로
				if (west.cnt >= 4)	continue;

				// 범위가 보드 안이면
				if (IsAround(i, j - 1))	j--;
				else
					continue;

				north.cnt = 0;
				south.cnt = 0;
				west.cnt++;
				east.cnt = 0;

				if (!west.is_gone)
					west.is_gone = true;
			}
		}
		else if (direct == 3) {	// east
			if (j + 1 <= BOARDSIZE) {
				// 4번 연속 갔다면 다시 랜덤으로
				if (east.cnt >= 4)	continue;

				// 범위가 보드 안이면
				if (IsAround(i, j + 1))	j++;
				else
					continue;

				north.cnt = 0;
				south.cnt = 0;
				west.cnt = 0;
				east.cnt++;

				if (!east.is_gone)
					east.is_gone = true;
			}
		}

		// 맨 오른쪽 끝으로 가면 탈출
		if (j == BOARDSIZE || i == BOARDSIZE || i == 0 || j == 0) {
			if (!north.is_gone || !south.is_gone || !west.is_gone || !east.is_gone)	{}
			else {
				if (i == 0 || j == 0)	board[i][j] == 1;
				break;
			}
		}
	}

}

int main()
{
	srand((unsigned int)time(NULL));

	while (1) {
		PrintBoard();

		// 명령어 입력
		cout << "입력 : ";
		char m;	cin >> m;
		switch (m) {
		case 'e':
			MakePath();
			break;
		case 'r':

			break;
		case '+':

			break;
		case '-':

			break;
		case 'q':
			cout << "프로그램이 종료됩니다." << endl;
			return 0;
		default:
			break;
		}
	}
}