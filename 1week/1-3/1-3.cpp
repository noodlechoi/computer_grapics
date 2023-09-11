#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
* 실제로는 파일에서 읽은 모든 문장에 각각 적용
* 
다음의 명령어를 실행한다.
• d: 문장 한 줄 전체를 거꾸로 출력하기
• e: 동일한 간격으로 특정 문자를 일정 갯수 삽입하기 (3문자 후 2개의 @ 문자 삽입. 공백도 하나의 문자로 취급하기)
• f: 공백을 기준으로 문자 거꾸로 출력하기
• g: 문자 내부의 특정 문자를 다른 문자로 바꾸기 (바꿀 문자와 새롭게 입력할 문자 입력받음)
• h: 앞에서 읽었을 때, 뒤에서 읽었을 때 어디까지 같은 문자인지 출력하기
• +: 문장에 있는 모든 숫자에 +1을 한다.
• -: 문장에 있는 모든 숫자에 -1을 한다. (최소 숫자는 0, 즉 0에 -1을 해도 0으로 출력)
• q: 프로그램 종료
*/
// string을 다루는 클래스
class ControlStr
{
private:
public:
	void OutputStr(const string& str);
	void ReverseStr(string& str);

	/*void NumberChange(string& str, const char& m);*/
};

void ControlStr::OutputStr(const string& str)
{
	cout << str << endl;
}

void ControlStr::ReverseStr(string& str)
{
	int len = str.length();
	for (int i = 0; i < str.length() / 2; ++i) {
		char tmp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = tmp;

		len--;
	}
}

//
//void ControlStr::NumberChange(string& str, const char& m)
//{
//	std::istringstream iss(str);
//	string buffer;
//
//	// 띄어쓰기 기준으로 str을 buffer에 입력
//	// 맨 마지막 단어는??
//	while (getline(iss, buffer, ' ')) {
//		int num = stoi(buffer);
//		num++;
//		buffer = std::to_string(num);
//
//
//	}
//
//	for (int j = 0; j < str.length(); ++j) {
//		if (str[j] >= '0' && str[j] <= '9') {
//			
//		}
//	}
//}

int CheckCommand(string* str)
{
	char m;
	cout << "command : ";
	cin >> m;

	ControlStr control;

	switch (m) {
	case 'd':
	case 'D':
		for (int i = 0; i < 10; ++i) {
			control.ReverseStr(str[i]);
		}
		break;
	case 'e':
	case 'E':
		break;
	case 'f':
	case 'F':
		break;
	case 'g':
	case 'G':
		break;
	case 'h':
	case 'H':
		break;
	case '+':
		for (int i = 0; i < 10; ++i) {
			
		}
		break;
	case '-':
		break;
	case 'q':
	case 'Q':
		cout << "프로그램이 종료됩니다." << endl;
		return 0;
	default:
		cout << "존재하지 않는 명령어 입니다. 다시 입력해주세요" << endl;
		break;
	}

	return 1;
}

int main()
{
	ControlStr control;
	string str[10];

	string file_name;
	cout << "Input file name : ";
	cin >> file_name;

	try
	{
		if (file_name != "data.txt")	throw file_name;
	}
	catch (const string& e)
	{
		cout << "파일 이름이 data.txt가 아닙니다. 프로그램을 다시 실행하시오." << endl;

		return 0;
	}

	// 파일 읽기
	std::ifstream file;
	file.open(file_name);

	int i = 0;
	while (!file.eof()) {
		// 문자열에 저장
		getline(file, str[i]);
		i++;
	}

	while (1) {
		// 문자열 출력
		for (int i = 0; i < 10; ++i) {
			control.OutputStr(str[i]);
		}

		if (!CheckCommand(str))	break;
	}

	// 파일 닫기
	file.close();
}