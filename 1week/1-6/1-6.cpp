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
	cout << "�Է� (x1, y1, x2, y2) : ";
	p1.InputPoint();
	p2.InputPoint();
}



void Menu()
{
	cout << "w / s : ��, �Ʒ��� �̵�" << endl;
	cout << "a / d : ����, ���������� �̵�" << endl;
	cout << "e / E : x�� y ��� �� ĭ ���/Ȯ��" << endl;
	cout << "i / j : x�� �� ĭ Ȯ��/���" << endl;
	cout << "k / l : y�� �� ĭ Ȯ��/���" << endl;
	cout << "q : ����" << endl;
}

void Rec::PrintBoard()
{
	for (int i = 0; i < BOARDSIZE; ++i) {
		for (int j = 0; j < BOARDSIZE; ++j) {
			cout << "    ";
			// p1 �̻� p2 �����϶�
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
			cout << "���α׷��� �����մϴ�." << endl;
			return 0;
		default:
			break;
		}
	}
}