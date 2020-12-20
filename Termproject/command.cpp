#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Receiver 클래스
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
				vec.push_back(tmp); // 파일내용을 단어 단위로 쪼개어 vec에 넣음
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
			cout << "파일 열기 실패" << endl;
		}
	}
	

};

class Insert : public Receiver {
public:
	virtual void execute() override {
		void insertData(vector<string> & vec, int& line, int& num, string & word);
};



// Command 인터페이스
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
	cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << "\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
	cout << "(콘솔 메시지)" << "\n";
	cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
	cout << "입력: "; cin >> input;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";

	string inputStart = input.substr(0, 1); //i
	// cout << inputStart << endl;

	string inputParam = input.substr(2, input.length() - 3); //1,10,hello
	//cout << inputParam << endl;

	vector<string> params;
	string delimeter = ",";


	if (inputStart == "t") {
		// 변경 내용 파일 저장 후 종료
	}
	else if (inputStart == "n") {
		// 다음 페이지 출력
	}
	else if (inputStart == "p") {
		// 이전 페이지 출력
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
		cout << "잘못된 입력입니다." << "\n";
	}
	pCommand1.execute();

	return 0;


}