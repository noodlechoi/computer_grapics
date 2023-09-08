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
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < str[i].length(); ++j) {
			// ���⸶�� �ܾ� �ϳ���
			if (str[i][j] == ' ') {
				word++;
				if (j != 0) {	// -1 �ε��� ����
					// ������ �������� ���Ⱑ �� �ְų� ���ڸ� �ٽ� ���̳ʽ�
					if (str[i][j - 1] == ' ' || (str[i][j - 1] >= '0' && str[i][j - 1] <= '9')) word--;
				}
			}
			// �� �ٿ� �ܾ �ִ� ��� ����
			if (str[i].find(" ") != string::npos) {
				// ������ �ܾ ���ڰ� �ƴϸ� word �߰�
				if (j == str[i].length() - 1) {
					if (!(str[i][j - 1] >= '0' && str[i][j - 1] <= '9')) word++;
				}
			}
		}
	}

	cout << word << endl;

	// ���� �ݱ�
	file.close();
}