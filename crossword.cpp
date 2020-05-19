// Charles Kraemer
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "board.h"

bool validWord(string);
void upper(string &word);
void sortByLength(vector<string> &words);
int main(int argc, char *argv[]) {
	vector<string> words;
	string word;
	if(argc==1) {
		cout << "Enter a word for the puzzle: ";
		getline(cin,word);
		if (validWord(word)) {
			upper(word);
			words.push_back(word);
		}
		else {
			cout << "Error: words must consist of at least two letters, and cannot consist of any non-letters" << endl;
		}
		bool enter= true;
		while(enter) {
			if(words.size()==20) {
				cout << "You have entered the maximum number of words possible for this puzzle" << endl;
				enter= false;
			}
			else {
				cout << "Enter another word or press the enter key: ";
				getline(cin, word);
				if(word=="") {
					enter= false;
				}
				else {
					if(validWord(word)) {
						upper(word);
						words.push_back(word);
					}
					else {
						cout << "Error: words must consist of at least two letters, cannot consist of any non-letters, and can be at most 15 letters" << endl;
					}
				}
			}
		}
		sortByLength(words);
		Board b(words);
		b.solCreate();
		b.display();
		cout << endl;
		b.gameCreate();
		b.display();
		b.anagram();
	}

	else if(argc==2) {
		ifstream ifs;
		string fileName= argv[1];
		ifs.open(fileName);
		if(!ifs.is_open()) {
			cout << "Error: file " << fileName << " could not be found." << endl;
		}
		else {
			bool run = true;
			getline(ifs, word);
			cout << word << endl;
			upper(word);
			words.push_back(word);
			while(run) {
				if(words.size()<=20) {
					getline(ifs, word);
					cout << word << endl;
					if(word!=".") {
						if(validWord(word)) {
							upper(word);
							words.push_back(word);
						}
						else {
							cout << "Error: words must consist of at least two letters, cannot consist of any non-letters, and can be at most 15 letters" << endl;
						}
					}
					else {
						run = false;
					}
				}
				else {
					cout << "Maximum number of words reached" << endl;
					run= false;
				}
			}
			for (int i = 0; i < words.size(); i++)
				cout << words[i] << endl;	
			sortByLength(words);
			Board b(words);	
			b.solCreate();
			b.display();
			cout << endl;
			b.gameCreate();
			b.display();
			b.anagram();
		}
	}
	else if(argc==3) {
		string fileNameOne= argv[1];
		string fileNameTwo= argv[2];
		ifstream ifs;
		ofstream ofs;
		ifs.open(fileNameOne);
		ofs.open(fileNameTwo);
		if(!ifs.is_open()) {
			cout << "Error: file " << fileNameOne << " could not be found." << endl;
		}
		if(!ofs.is_open()) {
			cout << "Error: file " << fileNameTwo << " could not be found." << endl;
		}
		if((ifs.is_open())&&(ofs.is_open())) {
			bool run= true;
			while(run) {
				if(words.size() <=20) {
					getline(ifs, word);
					if(word!=".") {
						if(validWord(word)) {
							upper(word);
							words.push_back(word);
						}
						else {
							cout << "Error: words must consist of at least two letters, cannot consist of any non-letters, and can be at most 15 letters" << endl;
						}
					}
					else {
						run= false;
					}
				}
				else {
					cout << "Maximum number of words reached" << endl;
					run= false;
				}
			}

			sortByLength(words);
			Board b(words);
			b.solCreate();
			b.writej(ofs);
			ofs << endl;
			b.gameCreate();
			b.writej(ofs);
			b.anagramWrite(ofs);
		}
	}
	else {
		cout << "Error: not sure which mode to run in.  Impromper number of arguments at the command line." << endl;
	}
}


bool validWord(string a) {
	int ASCII;
	int check= a.length();
	int count=0;
	for(int i=0; i<a.length(); ++i) {
		ASCII= (int)a[i];
		if(((ASCII>=65)&&(ASCII<=90)) || ((ASCII>=97)&&(ASCII<=122))) {
			++ count;
		}
	}
	
	if(a.length()<=1) {
		 count= check+1;
	}

	if(a.length()>15) {
		count= check+1;
	}

	if(count==check) {
		return true;
	}
	else {
		return false;
	}
}



void upper(string &word) {
	for(int i=0; i<word.length(); ++i) {
		word[i]= toupper(word[i]);
	}
}

void sortByLength(vector<string> &words) {
	string temp;
	for(auto it= words.begin(); it<words.end(); ++it) {
		for(auto ij= words.begin(); ij<words.end(); ++ij) {
			if((*it).length() > (*ij).length()) {
				temp= *it;
				*it= *ij;
				*ij= temp;
			}
		}
	}
}




