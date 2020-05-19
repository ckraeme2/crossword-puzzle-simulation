// Charles Kraemer
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <fstream>
using namespace std;

#include "board.h"

Board::Board() {
	for(int i=0; i<SIZE; ++i) {
		for(int j=0; j<SIZE; ++j) {
			board[i][j]= solNoWord;
		}
	}
}

Board::Board(vector<string> a) {
	for(int i=0; i<SIZE; ++i) {
		for(int j=0; j<SIZE; ++j) {
			board[i][j]= solNoWord;
		}
	}

	for(auto it=a.begin(); it<a.end(); ++it) {
		set.push_back(*it);
	}
}

void Board::display() {
	cout << "+";
	for(int i=0; i<SIZE; ++i) cout << "-";
	cout << "+" << endl;

	for(int i=0; i<SIZE; ++i) {
		cout << "|";
		for(int j=0;j<SIZE;++j) cout << board[i][j];
		cout << "|" << endl;
	}

	cout << "+";
	for(int i=0; i<SIZE; ++i) cout << "-";
	cout << "+" << endl;

}

void Board::solCreate() {
	string word= set[0];
	float  mid;
	int  l= word.length();
	char word_array[l+1];
	strcpy(word_array, word.c_str());
	float length= (float)l;
	float two= 2;
	type.push_back("Across");
	if(l % 2 != 0) {
		mid= (length/two)+0.5;
		int middle= (int)mid;
		int j=0;
		for(int i=middle; i>-1; i=i-1) {
			board[7][7-j]= word_array[i];
			++j;
		}
		coordinates.push_back(7);
		coordinates.push_back(7-j);
		j= 1;
		for(int i=middle+1; i<=length-1; ++i) {
			board[7][7+j]= word_array[i];
			++j;
		}
	}
	else {
		mid= length/two;
		int middle= (int)mid;
		int j= 0;
		for(int i=middle; i>-1; --i) {
			board[7][7-j]= word_array[i];
			++j;
		}
		coordinates.push_back(7);
		coordinates.push_back(7-j);
		j=1;
		for(int i=middle+1; i<=length-1; ++i) {
			board[7][7+j]= word_array[i];
			++j;
		}
	}
	
	int orientIndex= 0;	
	for(auto it=set.begin()+1; it<set.end(); ++it) {
		orient(*it, orientIndex);
		++ orientIndex;
	}
}

void Board::gameCreate() {
	for(int i=0; i<SIZE; ++i) {
		for(int j=0; j<SIZE; ++j) {
			if(board[i][j]==solNoWord) {
				board[i][j]= noWord;
			}
			else {
				board[i][j]= ' ';
			}
		}
	}
}

bool Board::inBounds(int x, int y) {
	if((x>=0)&&(x<SIZE)&&(y>=0)&&(y<SIZE)) {
		return true;
	}
	else {
		return false;
	}
}

char Board::valid(int a, int b, int c, int d) {
	int count=0;
	for(int i=a+1; i<=(a+(d-c)-1); ++i) {
		if((board[i][b]!=solNoWord) || (!inBounds(i,b))) {
			++ count;
		}
		if((board[i+1][b]!=solNoWord)&&(inBounds(i+1,b))) {
			++ count;
		}
		if((board[i][b+1]!=solNoWord)&&(inBounds(i,b+1))) {
			++ count;
		}
		if((board[i][b-1]!=solNoWord)&&(inBounds(i,b-1))) {
			++ count;
		}
	}
	if((board[a-1][b]!=solNoWord)&&(inBounds(a-1,b))) {
		++ count;
	}
	for(int i=a-1; i>=(a-c); --i) {
		if((board[i][b]!=solNoWord) || (!inBounds(i,b))) {
			++ count;
		}
		if((board[i-1][b]!=solNoWord)&&(inBounds(i-1,b))) {
			++ count;
		}
		if((board[i][b-1]!=solNoWord)&&(inBounds(i,b-1))) {
			++ count;
		}
		if((board[i][b+1]!=solNoWord)&&(inBounds(i,b+1))) {
			++ count;
		}
	}
	if(count==0) {
		return 'y';
	}
	else {
		count =0;
		for(int i=b+1; i<=(b+(d-c)-1); ++i) {
			if((board[a][i]!=solNoWord) || (!inBounds(a,i))) {
				++ count;
			}
			if((board[a+1][i]!=solNoWord)&&(inBounds(a+1,i))) {
				++ count;
			}
			if((board[a][i+1]!=solNoWord)&&(inBounds(a,i+1))) {
				++ count;
			}
			if((board[a-1][i]!=solNoWord)&&(inBounds(a-1,i))) {
				++ count;
			}
		}
		if((board[a][b-1]!=solNoWord)&&(inBounds(a,b-1))) {
			++ count;
		}
		for(int i=b-1; i>=(b-c); --i) {
			if((board[a][i]!=solNoWord) || (!inBounds(a,i))) {
				++ count;
			}
			if((board[a-1][i]!=solNoWord)&&(inBounds(a-1,i))) {
				++ count;
			}
			if((board[a][i-1]!=solNoWord)&&(inBounds(a,i-1))) {
				++ count;
			}
			if((board[a+1][i]!=solNoWord)&&(inBounds(a+1,i))) {
				++ count;
			}
		}
	}
	if(count==0) {
		return 'x';
	}
	else {
		return 'n';
	}
}


void Board::orient(string w, int q) {
	int index=0;
	int coordIndex= 2;
	int length= w.length();
	char word_array[length+1];
	strcpy(word_array, w.c_str());
	bool look= true;
	while(look) {
		for(int i=0; i<length; ++i) {
			for(int j=0; j<SIZE; ++j) {
				for(int z=0; z<SIZE; ++z) {
					if(w[i]==board[j][z]) {
						char o= valid(j,z,i,length);
						if(o=='x') {
							coordinates.push_back(j);
							coordinates.push_back(z-i);
							type.push_back("Across");
							for(int it= (z-i); it<=z-1; ++it) {
								board[j][it]= word_array[index];
								++index;
							}
							++ index;
							for(int it=z+1; it<=(z+(length-i-1)); ++it) {
								board[j][it]= word_array[index];
								++index;
							}
							i=length;
							look= false;
						}
						else if(o=='y') {
							coordinates.push_back(j-i);
							coordinates.push_back(z);
							type.push_back("Down");
							for(int it= (j-i); it<=j-1; ++it) {
								board[it][z]= word_array[index];
								++index;
							}
							++index;
							for(int it=j+1; it<=(j+(length-i-1)); ++it) {
								board[it][z]= word_array[index];
								++index;
							}
							i=length;
							look= false;
						}
						else {
							cout << "Word " << w << " could not be fit onto the board with the given rules." << endl;
							look= false;
							set.erase(set.begin()+q);
						}
					}
				}
			}
		}
	}
}

void Board::anagram() {
	for(auto it= set.begin(); it<set.end(); ++it) {
		random_shuffle((*it).begin(), (*it).end());
	}
	int x=0;
	int y=1;
	int index= 0;
	for(auto it=set.begin(); it<set.end(); ++it) {
		cout << coordinates[y] << ", " << coordinates[x] << " " << type[index] << " " << (*it) << endl;
		x=x+2;
		y=y+2;
		index= index+1;
	}
}


void Board::writej(ofstream &o) {
	o << "+";
	for(int i=0; i<SIZE; ++i) o << "-";
	o << "+" << endl;

	for(int i=0; i<SIZE; ++i) {
		o << "|";
		for(int j=0; j<SIZE; ++j) o << board[i][j];
		o << "|" << endl;
	}

	o << "+";
	for(int i=0; i<SIZE; ++i) o << "-";
	o << "+" << endl;
}

void Board::anagramWrite(ofstream &o) {
	for(auto it=set.begin(); it<set.end(); ++it) {
		random_shuffle((*it).begin(), (*it).end());
	}
	int x=0;
	int y=1;
	int index=0;
	for(auto it= set.begin(); it<set.end(); ++it) {
		o << coordinates[y] << ", " << coordinates[x] << " " << type[index] << " " << (*it) << endl;
		x=x+2;
		y=y+2;
		index= index+1;
	}
}



								 









	

