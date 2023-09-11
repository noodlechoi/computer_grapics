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
	void InsertSpecial(string& str);
	void EraseSpecial(string& str);
	void ReverseSpace(string& str);
	void ReplaceStr(const char& changed, const char& changing, string& str);
	void Palindrome(string& str);
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

void ControlStr::InsertSpecial(string& str)
{
	int cnt = 0;
	for (int i = 0; i < str.length(); ++i) {
		// cnt가 3의 배수일 때 넣기
		if (cnt != 0 && cnt % 3 == 0) {
			str.insert(i, "@@");
			i += 2;
		}
		cnt++;
	}
}

void ControlStr::EraseSpecial(string& str)
{
	// @를 못 찾을 때까지 지우기
	while(str.find('@') != -1)
		str.erase(find(str.begin(), str.end(), '@'));
}

void ControlStr::ReverseSpace(string& str)
{
	// 띄어쓰기 기준으로 나눈 뒤 substr로 ReverseStr 함수에 넘겨준다. replace를 사용해 바꾼다.
	int first_idx = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == ' ') {
			string s = str.substr(first_idx, i - first_idx);
			ReverseStr(s);
			str.replace(first_idx, i - first_idx, s);

			// 인덱스를 띄어쓰기 다음으로 바꿈
			first_idx = i + 1;
		}
	}

	// 마지막 단어 처리
	string s = str.substr(first_idx);
	ReverseStr(s);
	str.replace(first_idx, str.length() - first_idx, s);
}

void ControlStr::ReplaceStr(const char& changed, const char& changing, string& str)
{
	for (int i = 0; i < str.length(); ++i) {
		// 바꿀 문자와 같다면
		if (str[i] == changed)	str[i] = changing;
	}
}

void ControlStr::Palindrome(string& str)
{
	// substr로 앞 뒤 문자열을 잘라서 compare로 비교
}

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
		{
			// e 누른 여부를 bool 값으로 판단
			static bool is_input = false;
			for (int i = 0; i < 10; ++i) {
				if (!is_input)
					control.InsertSpecial(str[i]);
				else 
					control.EraseSpecial(str[i]);
			}
			is_input = !is_input;
		}
		break;
	case 'f':
	case 'F':
		for (int i = 0; i < 10; ++i) {
			control.ReverseSpace(str[i]);
		}
		break;
	case 'g':
	case 'G':
		{
			char changed, changing;
			cin >> changed >> changing;
			for (int i = 0; i < 10; ++i) {
				control.ReplaceStr(changed, changing, str[i]);
			}
		}
	break;
	case 'h':
	case 'H':
		for (int i = 0; i < 10; ++i) {
			control.Palindrome(str[i]);
		}
		break;
	case '+':
		
			

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