#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

/*
• m: 행렬의 곱셈
• a: 행렬의 덧셈
• d: 행렬의 뺄셈
• 숫자 (1~9): 입력한 숫자를 행렬에 곱한다.
• r: 행렬식의 값 (Determinant)  입력한 2개의 행렬의 행렬식 값을 모두 출력한다.
• t: 전치 행렬(Transposed matrix1)과 그 행렬식의 값  입력한 2개의 행렬에 모두 적용한다.
• h: 3X3 행렬을 4X4 행렬로 변환하고 행렬식의 값 (4행4열 행렬식 값) 출력
(단위 행렬의 값, 즉, 4행에 0을, 4열에 0을, 4행 4열의 위치에는 1을 추가한다)
• s: 행렬의 값을 새로 랜덤하게 설정한다.
• q: 프로그램 종료
*/
class Matrix
{
private:
	int** m;
	int size;
public:
	Matrix(const int& _size);
	~Matrix();

	// 행렬 출력
	void PrintMatrix();
	// 행렬 값 설정 함수
	void ResetMatrix();
	// 3X3 행렬식 반환 함수
	int ReturnDeterminant();
	// 전치 행렬 전환 함수
	void TransMatrix();
	// 4X4 행렬로 변환
	void TransFourMatrix();
	// 4X4 행렬식 함수
	int ReturnFourDet();

	// 주소 확인 함수
	// void MM();

	// 행렬 곱하기 연산자
	Matrix operator*(const Matrix& another);
	// 계수 곱하기 연산자
	void operator*(const int num);
	// 덧셈 연산자
	Matrix operator+(const Matrix& another);
	// 뺄셈 연산자
	Matrix operator-(const Matrix& another);
	// 대입 연산자
	Matrix& operator=(const Matrix& another);
};

Matrix::Matrix(const int& _size)
{
	// 동적할당
	size = _size;
	m = new int* [size];
	for (int i = 0; i < size; ++i)
		m[i] = new int[size];
}

Matrix::~Matrix()
{
	// 동적할당 해제
	if (!m) {
		for (int i = 0; i < size; ++i)
			delete[] m[i];
		delete[] m;
	}
}

void Matrix::ResetMatrix()
{
	// 행렬 랜덤 값 입력
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			m[i][j] = rand() % 3;
		}
	}
}

void Matrix::PrintMatrix()
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Matrix::TransMatrix()
{
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 1; j < size; ++j) {
			int tmp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = tmp;
		}
	}
}

int Matrix::ReturnDeterminant()
{
	// 4X4 예외처리
	try {
		if (size != 3) throw size;
	}
	catch (const std::exception& e) {
		cout << "3X3 행렬이 아닙니다. -1를 반환합니다." << endl;
		return -1;
	}

	return (m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - (m[0][0] * m[1][2] * m[2][1] + m[0][1] * m[1][0] * m[2][2] + m[0][2] * m[1][1] * m[2][0]));
}

void Matrix::TransFourMatrix()
{
	Matrix copy_m(size);
	copy_m = *this;

	// 동적할당 해제
	if (!m) {
		for (int i = 0; i < size; ++i)
			delete[] m[i];
		delete[] m;
	}

	// 크기 4만큼 동적할당
	if (m) {
		size = 4;
		m = new int* [size];
		for (int i = 0; i < size; ++i)
			m[i] = new int[size];
	}

	// 원소 다시 복사
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (j == size - 1 || i == size - 1)	m[i][j] = 0;
			else
				m[i][j] = copy_m.m[i][j];
		}
	}
	m[3][3] = 1;


}

int Matrix::ReturnFourDet()
{
	Matrix tmp(3);
	int result = 0;

	for (int k = 0; k < size; ++k) {

		int cnt = 0;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				// 행이나 열이 같은 행이나 열에 있을 때 제외
				if (j == k || i == 0) continue;
				tmp.m[cnt / tmp.size][cnt % tmp.size] = m[i][j];
				cnt++;
			}
		}

		//tmp.PrintMatrix();

		// 짝수면 -
		if (k % 2 == 0) {
			tmp * m[0][k];
			
		}
		// 홀수면 +
		else {
			tmp * (-m[0][k]);
		}
		result += tmp.ReturnDeterminant();

	}

	return result;
}

Matrix Matrix::operator*(const Matrix& another)
{
	Matrix rm(size);

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			/*
			첫 번째 행렬은 행이 바뀌고 두 번째 행렬은 열이 바뀜
			 result matrix[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0]
			 result matrix[0][1] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] ...
			*/
			rm.m[j][i] = this->m[j][0] * another.m[0][i] + this->m[j][1] * another.m[1][i] + this->m[j][2] * another.m[2][i];
		}
	}

	return rm;
}

void Matrix::operator*(const int num)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			m[i][j] *= num;
		}
	}
}

Matrix  Matrix::operator+(const Matrix& another)
{
	Matrix rm(size);

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			rm.m[i][j] = this->m[i][j] + another.m[i][j];
		}
	}

	return rm;
}

Matrix  Matrix::operator-(const Matrix& another)
{
	Matrix rm(size);

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			rm.m[i][j] = this->m[i][j] - another.m[i][j];
		}
	}

	return rm;
}

Matrix& Matrix::operator=(const Matrix& another)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			m[i][j] = another.m[i][j];
		}
	}

	return *this;
}

// q면 0 그 외 1리턴
int CommandCheck(char c, Matrix& m1, Matrix& m2)
{
	switch (c) {
	case 'p':
	case 'P':
		cout << "행렬 1" << endl;
		m1.PrintMatrix();
		cout << "행렬 2" << endl;
		m2.PrintMatrix();
		break;
	case 'm':
	case 'M':
		(m1 * m2).PrintMatrix();
		break;
	case 'a':
	case 'A':
		(m1 + m2).PrintMatrix();
		break;
	case 'd':
	case 'D':
		(m1 - m2).PrintMatrix();
		break;
	case 'r':
	case 'R':
		cout << "행렬 1 행렬식 : " << m1.ReturnDeterminant() << endl;
		cout << "행렬 2 행렬식 : " << m2.ReturnDeterminant() << endl;
		break;
	case 't':
	case 'T':
		m1.TransMatrix();
		m2.TransMatrix();
		cout << endl;
		cout << "전치행렬로 전환 완료" << endl;

		cout << "행렬 1" << endl;
		m1.PrintMatrix();
		cout << "행렬 2" << endl;
		m2.PrintMatrix();
		cout << "행렬 1 행렬식 : " << m1.ReturnDeterminant() << endl;
		cout << "행렬 2 행렬식 : " << m2.ReturnDeterminant() << endl;
		break;
	case 'h':
	case 'H':
		m1.TransFourMatrix();
		m2.TransFourMatrix();

		cout << "행렬 1" << endl;
		m1.PrintMatrix();
		cout << "행렬 2" << endl;
		m2.PrintMatrix();

		cout << "행렬 1 행렬식 : " << m1.ReturnFourDet() << endl;
		cout << "행렬 2 행렬식 : " << m2.ReturnFourDet() << endl;
		break;
	case 's':
	case 'S':
		m1.ResetMatrix();
		m2.ResetMatrix();
		break;
	case 'q':
	case 'Q':
		cout << "프로그램이 종료됩니다." << endl;
		return 0;
	default:
		cout << "잘못 입력하셨습니다. 다시 입력해주세요" << endl << endl;
		break;
	}
	
	return 1;
}


//void Matrix::MM()
//{
//	Matrix mm;
//
//	cout << &mm.m[0][0] << endl;
//	cout << &(this->m[0][0]) << endl;
//
//	mm = *this;
//
//	cout << &mm.m[0][0] << endl;
//	cout << &(this->m[0][0]) << endl;
//
//}

int main()
{
	// 랜덤 시드
	srand((unsigned int)time(NULL));
	Matrix m1(3), m2(3);
	m1.ResetMatrix();
	m2.ResetMatrix();

	// 행렬 출력
	cout << "행렬 1" << endl;
	m1.PrintMatrix();
	cout << "행렬 2" << endl;
	m2.PrintMatrix();

	while (1) {

		// 명령어 입력
		cout << "(행렬 확인 : p)" << endl;
		cout << "명령어 : ";
		char command;	cin >> command;

		// 숫자일 때
		if (command >= '1' && command <= '9') {
			int num = command - '0';
			m1* num;
			m2* num;
		}
		// 그 외
		else {
			// 0이 리턴되면 반복문 종료
			if (!CommandCheck(command, m1, m2)) break;

			
		}
	}
}