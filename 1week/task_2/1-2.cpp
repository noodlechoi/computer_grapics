#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main()
{
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
	
	// 문자열 출력
	for (int i = 0; i < 10; ++i) {
		cout << str[i] << endl;
	}

	// 단어 수 출력
	int word = 0;
	int number = 0;
	int capital = 0;
	for (int i = 0; i < 10; ++i) {
		bool is_number = false;
		bool is_alpha = false;
		bool is_capital = false;
		for (int j = 0; j < str[i].length(); ++j) {
			// 숫자일 때
			if (!is_number && (str[i][j] >= '0' && str[i][j] <= '9')) is_number = true;
			// 문자일때
			if (!is_alpha && ((str[i][j] >= 'A' && str[i][j] <= 'Z') || str[i][j] >= 'a' && str[i][j] <= 'z')) is_alpha = true;
			if (!is_capital && (str[i][j] >= 'A' && str[i][j] <= 'Z')) is_capital = true;

			// 띄어쓰기마다
			if (str[i][j] == ' ') {
				// 한 단어에 숫자 문자 있으면 => 문자 취급
				if (is_alpha && is_number)
					word++;
				else if (is_alpha)
					word++;
				else if (is_number)
					number++;
				if (is_capital)
					capital++;
				is_number = false;
				is_alpha = false;
				is_capital = false;
			}
		}
		// 마지막 단어 검사
		if (str[i][str[i].length() - 1]) {
			// 한 단어에 숫자 문자 있으면 => 문자 취급
			if (is_alpha && is_number)
				word++;
			else if (is_alpha)
				word++;
			else if (is_number)
				number++;
			if (is_capital)
				capital++;
			is_number = false;
			is_alpha = false;
			is_capital = false;
		}
	}

	cout << "word count : " << word << endl;
	cout << "number count : " << number << endl;
	cout << "capital count : " << capital << endl;

	// 파일 닫기
	file.close();
}