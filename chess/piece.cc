#include "piece.h"
#include <iostream>
using namespace std;

bool Piece::valid_pos(std::string new_pos) {
	if (new_pos.length()!=2) return false;
	std::string pos1_str="abcdefgh";
	std::string pos2_str="12345678";
	if (pos1_str.find(new_pos[0])==std::string::npos) return false;
	if (pos2_str.find(new_pos[1])==std::string::npos) return false;
	return true;
}

std::string Piece::get_prom_string() {
	if(type=='p') return "rnbq";
	else if(type=='P') return "RNBQ";
	else return "";
}

void Piece::set_pos(std::string new_pos) {
	if (this->valid_pos(new_pos)) pos=new_pos;
	else cout<< "invalid position "<<new_pos<<endl;
}

std::string Piece::get_pos() {
	return pos;
}

char Piece::get_type() {
	return type;
}

void Piece::set_type(char type) {
	std::string type_str="rnbqkbnrpRNBQKBNRP";
	if(type_str.find(type)==std::string::npos) cout<< "wrong piece type"<<endl;
	this->type=type;
}

Piece::Piece (char type, string pos):type{type},pos{pos} {
}

bool Piece::white_black() {
	return (type>=65&&type<=90);
}

int Piece::row_to_num(char c) {
	return (int)(c-49);
}

int Piece::col_to_num(char c) {
	return (int)(c-97);
}

bool Piece::white_black(char c) {
	std::string charset="PRNBQK";
	return !(charset.find(c)==string::npos);
}

void Piece::helper_possible_move(vector<string>* ori, vector<vector<char>> board, int varx, int vary) {
	char i=pos[0]+varx, j=pos[1]+vary;
	while(i>='a'&&i<='h'&&j>='1'&&j<='8'){
			if(board[col_to_num(i)][row_to_num(j)]==' ') 
			{
			ori->push_back(string()+i+j);
			}
			else if(white_black(board[col_to_num(i)][row_to_num(j)])==white_black()) break;
			else {ori->push_back(string()+i+j);break;}
			i+=varx;
			j+=vary;
	}
}

vector<string> Piece::possible_move_pos(vector<vector<char>> board) {
	vector<string> rv;
	if(type=='r'||type=='R') {
		helper_possible_move(&rv, board,0,1);
		helper_possible_move(&rv, board,1,0);
		helper_possible_move(&rv, board,-1,0);
		helper_possible_move(&rv, board,0,-1);
	} else if(type=='B'||type=='b') {
		helper_possible_move(&rv, board,1,1);
		helper_possible_move(&rv, board,1,-1);
		helper_possible_move(&rv, board,-1,1);
		helper_possible_move(&rv, board,-1,-1);
	} else if(type=='q'||type=='Q') {
		for(int i=-1;i<=1;i++) {
			for(int j=-1;j<=1;j++) {
				if(!(i==0&&j==0)) helper_possible_move(&rv, board,i,j);
			}
		}
	} else if(type=='k'||type=='K') {
		for(char i=pos[0]-1;i<=pos[0]+1;i++) {
			for(char j=pos[1]-1;j<=pos[1]+1;j++) {
				if(i==pos[0]&&j==pos[0]) continue;
				else if(i<'a'||i>'h'||j<'1'||j>'8') continue;
				else if(board[col_to_num(i)][row_to_num(j)]!=' '&&(white_black(board[col_to_num(i)][row_to_num(j)])==white_black())) continue;
				else {rv.push_back(string()+i+j);}
			}
		}
	} else if(type=='n'||type=='N') {

		int set[4]={1,-1,2,-2};
		for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
		if(set[i]*set[j]==2||set[i]*set[j]==-2) {
		char x=pos[0]+set[i];
		char y=pos[1]+set[j];
		if(x<'a'||x>'h'||y<'1'||y>'8') continue;
		else if(board[col_to_num(x)][row_to_num(y)]!=' '&&white_black(board[col_to_num(x)][row_to_num(y)])==white_black()){
		continue;
		}
		else {
		rv.push_back(std::string()+x+y);
		}
		}
		}
		}
	} else if(type=='P') {
		int col_num=col_to_num(pos[0]);
		int row_num=row_to_num(pos[1]);
		if(pos[1]!='8'&&board[col_num][row_num+1]==' ') rv.push_back(std::string()+pos[0]+(char)(pos[1]+1));
		if(pos[1]=='2'&&board[col_num][row_num+1]==' '&&board[col_num][row_num+2]==' ') rv.push_back(std::string()+pos[0]+(char)(pos[1]+2));
		if(row_num+1<8) {
		if(col_num-1>=0&&board[col_num-1][row_num+1]!=' '&&white_black(board[col_num-1][row_num+1])!=white_black()) rv.push_back(std::string()+(char)(pos[0]-1)+(char)(pos[1]+1));
		if(col_num+1<8&&board[col_num+1][row_num+1]!=' '&&white_black(board[col_num+1][row_num+1])!=white_black()) rv.push_back(std::string()+(char)(pos[0]+1)+(char)(pos[1]+1));
	}
	}
	else if(type=='p') {
		int col_num=col_to_num(pos[0]);
		int row_num=row_to_num(pos[1]);
		if(pos[1]!='1'&&board[col_num][row_num-1]==' ') rv.push_back(std::string()+pos[0]+(char)(pos[1]-1));
		if(pos[1]=='7'&&board[col_num][row_num-1]==' '&&board[col_num][row_num-2]==' ') rv.push_back(std::string()+pos[0]+(char)(pos[1]-2));
		if(row_num-1>=0) {
		if(col_num-1>0&&board[col_num-1][row_num-1]!=' '&&white_black(board[col_num-1][row_num-1])!=white_black()) rv.push_back(std::string()+(char)(pos[0]-1)+(char)(pos[1]-1));
		if(col_num+1<8&&board[col_num+1][row_num-1]!=' '&&white_black(board[col_num+1][row_num-1])!=white_black()) rv.push_back(std::string()+(char)(pos[0]+1)+(char)(pos[1]-1));
		}
	}
	return rv;
}
