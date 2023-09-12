#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#define BOARDSIZE 30

class Point
{
private:
	int x, y;
public:
	Point();
	void InputPoint();
	int GetX();
	int GetY();
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

class Rec
{
private:
	Point p1, p2;
public:
	void InputPoint();
	void PrintBoard();
	void Move();
};

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
	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			cout << "    ";
			// p1 이상 p2 이하일때
			if ((i >= p1.GetX() && j >= p1.GetX()) && (i <= p2.GetX() && j <= p2.GetX())) {
				cout << "0";
			}
			else {
				cout << ".";
			}
		}
		cout << endl;
	}
}

void Rec::Move()
{
	
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
			break;
		case 's':
			break;
		case 'a':
			break;
		case 'd':
			break;
		case 'e':
			break;
		case 'E':
			break;
		case 'i':
			break;
		case 'j':
			break;
		case 'k':
			break;
		case 'l':
			break;
		case 'q':
			cout << "프로그램을 종료합니다." << endl;
			return 0;
		default:
			break;
		}
	}
}