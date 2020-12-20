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

		if (bytelen >= 75) { // ����Ʈ ���� 75 �̻��� ���
			lineCount++;	// ���μ� ����
			bytelen = 0;
		}

		if (lineCount == line) { // ����ڰ� �Է��Ϸ��� line�� ī��Ʈ �� ���μ��� ������ ���
			if (lineCount == 1) { // ù ��° �����϶�
				wordCount = i;
			}
			else {
				wordCount = i + 1;
			}
			break;

		}
	}
	vec.insert(vec.begin()+wordCount+num, word); // vec�� ����ڰ� �Է��� �ܾ�(word)�� �����Ѵ�

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
	vec.erase(vec.begin() + wordCount + num -1); // ����ڰ� ������ ��ġ�� �ִ� ���Ҹ� vec���� �����Ѵ�
}


void search(vector<string>& vec, string& word) {
	for (int i = 0; i < vec.size(); i++) {
		int index = vec[i].find(word);
	
		if (index != -1) { // input ã�� ���ڰ� ������ �����, find�� ���� ã�� ��쿡 �ε��� ���� ��ȯ��, ������ -1 ����)
			vec.insert(vec.begin(), word);
			break;
		}
	}
}

void change(vector<string>& vec, string& beforeWord, string& afterWord) {
	for (int i = 0; i < vec.size(); i++) {
		int index = vec[i].find(beforeWord);

		if (index != -1) { // input ã�� ���ڰ� ������ ���
			vec[i] = afterWord;
		}
	}
}




void openFile(fstream& in, vector<string>& vec) {

	int bytelen = 0; // ���� ����Ʈ���� 0���� �����Ѵ�
	string line;	// ���ο� �������� ����
	int lineCount = 1;	// ���μ�

	if (in.is_open()) { //������ ����
		string tmp;

		while (getline(in, tmp, ' ')) { // ������ �� �پ� ���� �������� �о��
			vec.push_back(tmp); // ���ϳ����� �ܾ� �ϳ��� vec�� ����
		}

		for (int i = 0; i < vec.size(); i++) {
			bytelen += vec[i].length();
			line += vec[i] + " ";

			if (bytelen >= 75) {
				if (lineCount<10) { // 1~10�ٱ���
					cout <<" " <<lineCount << " | " << line << endl;
				}
				else if(lineCount<=20) { // 11~20�ٱ���
					cout << lineCount << " | " << line << endl;
					
				}
				else {
					break;
				}
				
				lineCount++; // �� ������ 75����Ʈ�� �ʰ��� ������ ���μ��� +1�� �Ѵ�
				bytelen = 0; // �ٽ� ����Ʈ���� 0���� �ʱ�ȭ
				line = "";   // ���ο� �ִ� ���� �ʱ�ȭ
			}
		}
	}
	else { // ������ �ҷ����� ���� ���
		cout << "���� ���� ����" << endl;
	}
}

// ������� �Է� �Ķ���͸� "," �����ڷ� split�ϴ� �Լ�
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
	string console = "ù �������Դϴ�.";

	while (true) {
		cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
		cout << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << "\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
		cout << console << "\n";
		cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";
		cout << "�Է�: "; cin >> input;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << "\n";

		string inputStart = input.substr(0, 1); //������� �Է� �� ���� ù ��°����

		vector<string> params; //�Ķ���͸� ��� vector, params����
		string delimeter = ","; //�Ķ���� �����ڴ� ","

		//	for (auto& param : params) {
		//		cout << param << endl;
		//	}

		if (inputStart == "t") {
			// ���� ���� ���� ���� �� ����
			break;

		}
		else if (inputStart == "n") {
			console = "Next page(���� �������� �̵�)�� �Է��Ͽ����ϴ�.";
			// ���� ������ ���
		}
		else if (inputStart == "p") {
			console = "Previous page(���� �������� �̵�)�� �Է��Ͽ����ϴ�.";
			// ���� ������ ���
		}

		// ����ڰ� �ܾ� ����(i)�� �Է��� ���
		else if (inputStart == "i") {
			string inputParam = input.substr(2, input.length() - 3); //1,5,insert

			split(inputParam, params, delimeter); // �Ķ���͸� �����ڷ� �ɰ�

			int line = std::stoi(params[0]);
			int num = std::stoi(params[1]);
			string word = params[2];

			insert(vec, line, num, word);
			console = "Insert(����)�� �Է��Ͽ����ϴ�.";
		}

		// ����ڰ� �ܾ� ����(d)�� �Է��� ���
		else if (inputStart == "d") {
			string inputParam = input.substr(2, input.length() - 3); 

			split(inputParam, params, delimeter);

			int line = std::stoi(params[0]);
			int num = std::stoi(params[1]);
			deleteWord(vec, line, num);
			console = "Delete(����)�� �Է��Ͽ����ϴ�.";
		}

		// ����ڰ� �ܾ� �˻�(s)�� �Է��� ���
		else if (inputStart == "s") {
			string inputParam = input.substr(2, input.length() - 3); 

			string word = inputParam;
			search(vec, word);
			console = "Search(�˻�)�� �Է��Ͽ����ϴ�.";
		}

		// ����ڰ� �ܾ� ����(c)�� �Է��� ���
		else if (inputStart == "c") {
			string inputParam = input.substr(2, input.length() - 3); 

			split(inputParam, params, delimeter);

			string beforeWord = params[0];
			string afterWord = params[1];

			change(vec, beforeWord, afterWord);
			console = "Change(����)�� �Է��Ͽ����ϴ�.";
		}

		else {
			console = "�߸��� �Է��Դϴ�.";
		}
		openFile(in, vec);
	}

	in.close();

	

	return 0;
}