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
		cout << "���� �̸��� data.txt�� �ƴմϴ�. ���α׷��� �ٽ� �����Ͻÿ�." << endl;

		return 0;
	}

	// ���� �б�
	std::ifstream file;
	file.open(file_name);

	int i = 0;
	while (!file.eof()) {
		// ���ڿ��� ����
		getline(file, str[i]);
		i++;
	}
	
	// ���ڿ� ���
	for (int i = 0; i < 10; ++i) {
		cout << str[i] << endl;
	}

	// �ܾ� �� ���
	int word = 0;
	int number = 0;
	int capital = 0;
	for (int i = 0; i < 10; ++i) {
		bool is_number = false;
		bool is_alpha = false;
		bool is_capital = false;
		for (int j = 0; j < str[i].length(); ++j) {
			// ������ ��
			if (!is_number && (str[i][j] >= '0' && str[i][j] <= '9')) is_number = true;
			// �����϶�
			if (!is_alpha && ((str[i][j] >= 'A' && str[i][j] <= 'Z') || str[i][j] >= 'a' && str[i][j] <= 'z')) is_alpha = true;
			if (!is_capital && (str[i][j] >= 'A' && str[i][j] <= 'Z')) is_capital = true;

			// ���⸶��
			if (str[i][j] == ' ') {
				// �� �ܾ ���� ���� ������ => ���� ���
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
		// ������ �ܾ� �˻�
		if (str[i][str[i].length() - 1]) {
			// �� �ܾ ���� ���� ������ => ���� ���
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

	// ���� �ݱ�
	file.close();
}