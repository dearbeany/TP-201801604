#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Receiver Ŭ����
class Receiver {
public:
	virtual void execute() = 0;
};

class OpenFile : public Receiver {
public:
	
	virtual void execute() override {
		ifstream in;
		in.open("test.txt");

		vector<string> vec;

		//string input, console;

		int bytelen = 0;
		string line;
		int lineCount = 1;

		if (in.is_open()) {
			string tmp;

			while (getline(in, tmp, ' ')) {
				vec.push_back(tmp); // ���ϳ����� �ܾ� ������ �ɰ��� vec�� ����
			}

			for (int i = 0; i < vec.size(); i++) {
				bytelen += vec[i].length();
				line += vec[i] + " ";

				if (bytelen >= 75) {
					if (lineCount < 10) {
						cout << " " << lineCount << " | " << line << endl;
					}
					else if (lineCount <= 20) {
						cout << lineCount << " | " << line << endl;

					}
					else {
						break;
					}

					lineCount++;

					bytelen = 0;
					line = "";
				}
			}

		}
		else {
			cout << "���� ���� ����" << endl;
		}
	}
	

};

class Insert : public Receiver {
public:
	virtual void execute() override {
		void insertData(vector<string> & vec, int& line, int& num, string & word);
};



// Command �������̽�
template<typename T>

class Command {
private:
	T* pReceiver;

public:
	Command(T* receiver) :pReceiver(receiver){}
	~Command() { if (pReceiver) delete pReceiver; }
	
	void execute() { pReceiver->execute(); }
};


void split(string str, vector<string>& params, string& delimeter) {
	int pos = 0;
	string token;

	while ((pos = str.find(delimeter)) != string::npos) {
		token = str.substr(0, pos);
		params.push_back(token);
		str.erase(0, pos + delimeter.length());
	}

	params.push_back(str);
}

int main() {
	Command<OpenFile> pCommand1(new OpenFile());
	pCommand1.execute();

	string input, console;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
	cout << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << "\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
	cout << "(�ܼ� �޽���)" << "\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
	cout << "�Է�: "; cin >> input;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";

	string inputStart = input.substr(0, 1); //i
	// cout << inputStart << endl;

	string inputParam = input.substr(2, input.length() - 3); //1,10,hello
	//cout << inputParam << endl;

	vector<string> params;
	string delimeter = ",";


	if (inputStart == "t") {
		// ���� ���� ���� ���� �� ����
	}
	else if (inputStart == "n") {
		// ���� ������ ���
	}
	else if (inputStart == "p") {
		// ���� ������ ���
	}
	else if (inputStart == "i") {

		split(inputParam, params, delimeter);

		int line = std::stoi(params[0]);
		int num = std::stoi(params[1]);
		string word = params[2];

		//insert(vec, line, num, word);
		Command<Insert> pCommandi(new Insert());
		pCommandi.execute();
	}
	else if (inputStart == "d") {
		split(inputParam, params, delimeter);

		int line = std::stoi(params[0]);
		int num = std::stoi(params[1]);
		//deleteWord(vec, line, num);
	}

	else if (inputStart == "s") {
		string word = inputParam;
		//search(vec, word);
	}

	else if (inputStart == "c") {
		split(inputParam, params, delimeter);

		string beforeWord = params[0];
		string afterWord = params[1];

		//change(vec, beforeWord, afterWord);
	}

	else {
		cout << "�߸��� �Է��Դϴ�." << "\n";
	}
	pCommand1.execute();

	return 0;


}