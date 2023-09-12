#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#define BOARDSIZE 10
int board[BOARDSIZE][BOARDSIZE];

class Point
{
private:
	int x, y;
public:
	Point();
	void InputPoint();
	int GetX();
	int GetY();
	bool SetX(const int& x);
	bool SetY(const int& y);
};

Point::Point() : x{ 0 }, y{ 0 } { }

void Point::InputPoint()
{
	cin >> this->x >> this->y;
}
int Point::GetX()
{
	return x;
}

int Point::GetY()
{
	return y;
}

bool Point::SetX(const int& x)
{
	if (x < 0) {
		return false;
	}

	this->x = x;
	return true;
}

bool Point::SetY(const int& y)
{
	if (y < 0) {
		return false;
	}

	this->y = y;
	return true;
}

class Rec
{
private:
	Point p1, p2;
public:
	void ResetBoard();
	void InputPoint();
	void PrintBoard();
	void UpDownMove(const char& m);
	void LRMove(const char& m);
	void Zoom(const char& m);
	void XZoom(const char& m);
	void YZoom(const char& m);
};

void Rec::ResetBoard()
{
	// 보드 초기화
	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			board[i][j] = 0;
		}
	}

	////// board 넘어갔을 때
	//if (p1.GetX() > p2.GetX()) {
	//	for (int i = 0; i < p2.GetX(); ++i) {
	//		for (int j = p1.GetX(); j < p2.GetY(); ++j) {
	//			board[i][j] = 1;
	//		}
	//	}
	//}
	//if (p1.GetY() > p2.GetY()) {
	//	for (int i = p1.GetX(); i < p1.GetX(); ++i) {
	//		for (int j = 0; j < p2.GetY(); ++j) {
	//			board[i][j] = 1;
	//		}
	//	}
	//}

	// 보드에 표시
	for (int i = p1.GetX(); i < p2.GetX(); ++i) {
		for (int j = p1.GetY(); j < p2.GetY(); ++j) {
			board[i][j] = 1;
		}
	}
}

void Rec::InputPoint()
{
	cout << "입력 (x1, y1, x2, y2) : ";
	p1.InputPoint();
	p2.InputPoint();
}

void Menu()
{
	cout << "w / s : 위, 아래로 이동" << endl;
	cout << "a / d : 왼쪽, 오른쪽으로 이동" << endl;
	cout << "e / E : x와 y 모두 한 칸 축소/확대" << endl;
	cout << "i / j : x축 한 칸 확대/축소" << endl;
	cout << "k / l : y축 한 칸 확대/축소" << endl;
	cout << "q : 종료" << endl;
}

void Rec::PrintBoard()
{
	ResetBoard();

	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			cout << "    ";
			if (board[i][j] != 0) {
				cout << "0";
			}
			else {
				cout << ".";
			}
		}
		cout << endl;
	}
}

void Rec::UpDownMove(const char& m)
{
	if (m == 'w') {
		// 만약 음수면
		if ((p1.GetX() - 1 < 0) || (p2.GetX() - 1 < 0)) {
			if (p1.GetX() - 1 < 0)
				p1.SetX(BOARDSIZE - 1);
			else if(p2.GetX() - 1 < 0)
				p2.SetX(BOARDSIZE - 1);
		}
		else {
			p1.SetX(p1.GetX() - 1);
			p2.SetX(p2.GetX() - 1);
		}
	}
	else if (m == 's') {
		// 만약 보드를 넘으면
		if ((p1.GetX() + 1 > BOARDSIZE) || (p2.GetX() + 1 > BOARDSIZE)) {
			p1.SetX(0);
			p2.SetX(0);
		}
		else {
			p1.SetX(p1.GetX() + 1);
			p2.SetX(p2.GetX() + 1);
		}
	}
}

void Rec::LRMove(const char& m)
{
	if (m == 'a') {
		// 만약 음수면
		if ((p1.GetY() - 1 < 0) || (p2.GetY() - 1 < 0)) {
			if (p1.GetY() - 1 < 0)
				p1.SetY(BOARDSIZE - 1);
			else if (p2.GetY() - 1 < 0)
				p2.SetY(BOARDSIZE - 1);
		}
		else {
			p1.SetY(p1.GetY() - 1);
			p2.SetY(p2.GetY() - 1);
		}
	}
	else if (m == 'd') {
		// 만약 보드를 넘으면
		if ((p1.GetY() + 1 > BOARDSIZE) || (p2.GetY() + 1 > BOARDSIZE)) {
			p1.SetY(0);
			p2.SetY(0);
		}
		else {
			p1.SetY(p1.GetY() + 1);
			p2.SetY(p2.GetY() + 1);
		}
	}
}

void Rec::Zoom(const char& m)
{
	if (m == 'e') {
		if ((p1.GetX() != p2.GetX() - 1) && (p1.GetY() != p2.GetY() - 1)) {
			p2.SetX(p2.GetX() - 1);
			p2.SetY(p2.GetY() - 1);
		}
	}
	else if (m == 'E') {
		if ((BOARDSIZE > p2.GetX()) && (BOARDSIZE > p2.GetY())) {
			p2.SetX(p2.GetX() + 1);
			p2.SetY(p2.GetY() + 1);
		}
	}
}

void Rec::XZoom(const char& m)
{
	if (m == 'j') {
		if ((p1.GetY() != p2.GetY() - 1)) {
			p2.SetY(p2.GetY() - 1);
		}
	}
	else if (m == 'i') {
		if ( (BOARDSIZE > p2.GetY())) {
			p2.SetY(p2.GetY() + 1);
		}
	}
}

void Rec::YZoom(const char& m)
{
	if (m == 'l') {
		if ((p1.GetX() != p2.GetX() - 1)) {
			p2.SetX(p2.GetX() - 1);
		}
	}
	else if (m == 'k') {
		if ((BOARDSIZE > p2.GetX())) {
			p2.SetX(p2.GetX() + 1);
		}
	}
}

int main()
{
	Rec r;
	r.InputPoint();

	while (1) {
		r.PrintBoard();

		char m;	cin >> m;
		switch (m) {
		case 'w':
			r.UpDownMove('w');
			break;
		case 's':
			r.UpDownMove('s');
			break;
		case 'a':
			r.LRMove('a');
			break;
		case 'd':
			r.LRMove('d');
			break;
		case 'e':
			r.Zoom('e');
			break;
		case 'E':
			r.Zoom('E');
			break;
		case 'i':
			r.XZoom('i');
			break;
		case 'j':
			r.XZoom('j');
			break;
		case 'k':
			r.YZoom('k');
			break;
		case 'l':
			r.YZoom('l');
			break;
		case 'q':
			cout << "프로그램을 종료합니다." << endl;
			return 0;
		default:
			break;
		}
	}
}