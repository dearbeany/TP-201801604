#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void insert(vector<string>& vec, int& line, int&num, string& word) {
	
	int bytelen = 0;
	int lineCount = 1;
	int wordCount = 0;

	for (int i = 0; i < vec.size(); i++) {
		bytelen += vec[i].length();

		if (bytelen >= 75) { // 바이트 수가 75 이상일 경우
			lineCount++;	// 라인수 증가
			bytelen = 0;
		}

		if (lineCount == line) { // 사용자가 입력하려는 line과 카운트 된 라인수가 동일할 경우
			if (lineCount == 1) { // 첫 번째 라인일때
				wordCount = i;
			}
			else {
				wordCount = i + 1;
			}
			break;

		}
	}
	vec.insert(vec.begin()+wordCount+num, word); // vec에 사용자가 입력한 단어(word)를 삽입한다

}



void deleteWord(vector<string>& vec, int& line, int& num) {

	int bytelen = 0;
	int lineCount = 1;
	int wordCount = 0;


	for (int i = 0; i < vec.size(); i++) {
		bytelen += vec[i].length();

		if (bytelen >= 75) {
			lineCount++;
			bytelen = 0;
		}

		if (lineCount == line) {
			if (lineCount == 1) {
				wordCount = i;
			}
			else {
				wordCount = i+1;
			}
			break;
		}
	}
	vec.erase(vec.begin() + wordCount + num -1); // 사용자가 지정한 위치에 있는 원소를 vec에서 삭제한다
}


void search(vector<string>& vec, string& word) {
	for (int i = 0; i < vec.size(); i++) {
		int index = vec[i].find(word);
	
		if (index != -1) { // input 찾는 문자가 존재할 경우임, find는 문자 찾을 경우에 인덱스 값을 반환함, 없으면 -1 리턴)
			vec.insert(vec.begin(), word);
			break;
		}
	}
}

void change(vector<string>& vec, string& beforeWord, string& afterWord) {
	for (int i = 0; i < vec.size(); i++) {
		int index = vec[i].find(beforeWord);

		if (index != -1) { // input 찾는 문자가 존재할 경우
			vec[i] = afterWord;
		}
	}
}




void openFile(fstream& in, vector<string>& vec) {

	int bytelen = 0; // 글자 바이트수는 0으로 지정한다
	string line;	// 라인에 보여지는 글자
	int lineCount = 1;	// 라인수

	if (in.is_open()) { //파일을 연다
		string tmp;

		while (getline(in, tmp, ' ')) { // 파일을 한 줄씩 공백 기준으로 읽어옴
			vec.push_back(tmp); // 파일내용을 단어 하나씩 vec에 넣음
		}

		for (int i = 0; i < vec.size(); i++) {
			bytelen += vec[i].length();
			line += vec[i] + " ";

			if (bytelen >= 75) {
				if (lineCount<10) { // 1~10줄까지
					cout <<" " <<lineCount << " | " << line << endl;
				}
				else if(lineCount<=20) { // 11~20줄까지
					cout << lineCount << " | " << line << endl;
					
				}
				else {
					break;
				}
				
				lineCount++; // 한 라인이 75바이트가 초과될 때마다 라인수를 +1씩 한다
				bytelen = 0; // 다시 바이트수는 0으로 초기화
				line = "";   // 라인에 있는 글자 초기화
			}
		}
	}
	else { // 파일을 불러오지 못한 경우
		cout << "파일 열기 실패" << endl;
	}
}

// 사용자의 입력 파라미터를 "," 구분자로 split하는 함수
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
	fstream in("test.txt");

	vector<string> vec;
	openFile(in, vec);

	string input;
	string console = "첫 페이지입니다.";

	while (true) {
		cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
		cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << "\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
		cout << console << "\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
		cout << "입력: "; cin >> input;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";

		string inputStart = input.substr(0, 1); //사용자의 입력 중 가장 첫 번째글자

		vector<string> params; //파라미터를 담는 vector, params선언
		string delimeter = ","; //파라미터 구분자는 ","

		//	for (auto& param : params) {
		//		cout << param << endl;
		//	}

		if (inputStart == "t") {
			// 변경 내용 파일 저장 후 종료
			break;

		}
		else if (inputStart == "n") {
			console = "Next page(다음 페이지로 이동)을 입력하였습니다.";
			// 다음 페이지 출력
		}
		else if (inputStart == "p") {
			console = "Previous page(이전 페이지로 이동)을 입력하였습니다.";
			// 이전 페이지 출력
		}

		// 사용자가 단어 삽입(i)을 입력할 경우
		else if (inputStart == "i") {
			string inputParam = input.substr(2, input.length() - 3); //1,5,insert

			split(inputParam, params, delimeter); // 파라미터를 구분자로 쪼갬

			int line = std::stoi(params[0]);
			int num = std::stoi(params[1]);
			string word = params[2];

			insert(vec, line, num, word);
			console = "Insert(삽입)을 입력하였습니다.";
		}

		// 사용자가 단어 삭제(d)을 입력할 경우
		else if (inputStart == "d") {
			string inputParam = input.substr(2, input.length() - 3); 

			split(inputParam, params, delimeter);

			int line = std::stoi(params[0]);
			int num = std::stoi(params[1]);
			deleteWord(vec, line, num);
			console = "Delete(삭제)을 입력하였습니다.";
		}

		// 사용자가 단어 검색(s)을 입력할 경우
		else if (inputStart == "s") {
			string inputParam = input.substr(2, input.length() - 3); 

			string word = inputParam;
			search(vec, word);
			console = "Search(검색)을 입력하였습니다.";
		}

		// 사용자가 단어 변경(c)을 입력할 경우
		else if (inputStart == "c") {
			string inputParam = input.substr(2, input.length() - 3); 

			split(inputParam, params, delimeter);

			string beforeWord = params[0];
			string afterWord = params[1];

			change(vec, beforeWord, afterWord);
			console = "Change(변경)을 입력하였습니다.";
		}

		else {
			console = "잘못된 입력입니다.";
		}
		openFile(in, vec);
	}

	in.close();

	

	return 0;
}