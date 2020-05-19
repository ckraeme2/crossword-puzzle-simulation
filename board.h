// Charles Kraemer
#include <vector>
#include <string>
#include <fstream>

const int SIZE= 15;
const char noWord= '#';
const char solNoWord= '.';
const char word= ' ';


class Board
{
	public:
	 Board();
	 Board(vector<string>);
	 void display();
	 void solCreate();
	 void gameCreate();
	 void orient(string,int);
	 char valid(int, int, int, int);
	 bool inBounds(int, int);
	 void writej(ofstream&);
	 void anagramWrite(ofstream&);
	 void anagram();
	private: 
	 char board[SIZE][SIZE];
	 vector<string> set;
	 vector<string> type;
	 vector<int> coordinates;
};
