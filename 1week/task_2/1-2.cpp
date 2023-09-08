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
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < str[i].length(); ++j) {
			// 띄어쓰기마다 단어 하나로
			if (str[i][j] == ' ') {
				word++;
				if (j != 0) {	// -1 인덱스 방지
					// 이전에 연속으로 띄어쓰기가 더 있거나 숫자면 다시 마이너스
					if (str[i][j - 1] == ' ' || (str[i][j - 1] >= '0' && str[i][j - 1] <= '9')) word--;
				}
			}
			// 한 줄에 단어만 있는 경우 방지
			if (str[i].find(" ") != string::npos) {
				// 마지막 단어가 숫자가 아니면 word 추가
				if (j == str[i].length() - 1) {
					if (!(str[i][j - 1] >= '0' && str[i][j - 1] <= '9')) word++;
				}
			}
		}
	}

	cout << word << endl;

	// 파일 닫기
	file.close();
}