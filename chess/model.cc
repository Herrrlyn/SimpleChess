#include "model.h"
#include <time.h>
#include <algorithm>
#include <iostream>

using namespace std;

void Model::newgame(int a, int b) {
	if(a<0||a>4||b<0||b>4) cout<< "player/AI out of range"<<endl;
	p1=a;
	p2=b;
	srand(time(nullptr));
}

void Model::resign() {}

bool Model::check_win(bool side) {
	string type_str=(!side)?"RNBQKP":"rnbqkp";
	vector<Piece> old_board=board_piece;
	for(Piece piece:board_piece) {
		if(type_str.find(piece.get_type())!=string::npos) {
		vector<string> all_moves=piece.possible_move_pos(get_board());
		for(string single_move:all_moves) {
			if(move(piece.get_pos(),single_move)) {
			board_piece=old_board;
			return false;
			}
		}
		}
	}
	return true;
}

bool Model::get_current_player() {
	return current_player;
}

void Model::set_current_player(bool new_current_player) {
	current_player=new_current_player;
}

void Model::ai_move(int lvl) {
	string type_str=get_current_player()?"RNBQKP":"rnbqkp";
	vector<string> all_moves;
	for(Piece piece:board_piece) {
	if(type_str.find(piece.get_type())!=string::npos) {
	vector<string> piece_all_move=piece.possible_move_pos(get_board());
	for(string move:piece_all_move) all_moves.push_back(piece.get_pos()+move);
	}
	}
	if(lvl==1) {
	random_shuffle(all_moves.begin(),all_moves.end());
	for(string single_move:all_moves) {
		if(move(single_move.substr(0,2),single_move.substr(2,2))) {ai_prom_helper();return;}
	}
	} else if(lvl==2) {
	vector<string> pro_check_moves,pro_normal_moves,normal_check_moves,normal_normal_moves;
	for(string single_move:all_moves) {
	vector<Piece> old_board=board_piece;
	if(move(single_move.substr(0,2),single_move.substr(2,2))) {
		if(board_piece.size()<old_board.size()) 
		{ if(check(!get_current_player())) pro_check_moves.push_back(single_move);
		else pro_normal_moves.push_back(single_move);
		}
		else  {
		if(check(!get_current_player())) normal_check_moves.push_back(single_move);
		else normal_normal_moves.push_back(single_move);
		}
		board_piece=old_board;
	}
	}
	random_shuffle(pro_check_moves.begin(),pro_check_moves.end());
	random_shuffle(normal_check_moves.begin(),normal_check_moves.end());
	random_shuffle(normal_normal_moves.begin(),normal_normal_moves.end());
	random_shuffle(pro_normal_moves.begin(),pro_normal_moves.end());
	for(string single_move:pro_check_moves) {
		move(single_move.substr(0,2),single_move.substr(2,2));
		ai_prom_helper();
		return;
	}
	for(string single_move:normal_check_moves) {
                move(single_move.substr(0,2),single_move.substr(2,2));
                ai_prom_helper();
		return;
        }
	for(string single_move:pro_normal_moves) {
                move(single_move.substr(0,2),single_move.substr(2,2));
                ai_prom_helper();
		return;
        }
	for(string single_move:normal_normal_moves) {
		move(single_move.substr(0,2),single_move.substr(2,2));
		ai_prom_helper();
		return;
	}		
	} else {
		vector<string> all_moves_p;
		vector<Piece> old_board=board_piece;
		for(string sm:all_moves) {
		if(move(sm.substr(0,2),sm.substr(2,2))) {
		int score=0;
		score+=ai_prom_helper()?8:0;
		if(old_board.size()!=board_piece.size()) score+=ai3_score_help(erased_type);
		bool checking=check(!get_current_player());
		set_current_player(!get_current_player());
		vector<string> all_op_moves=ai3_all_moves_help();
		vector<Piece> mid_board=board_piece;
		int deduct=0;
		for(string second_move:all_op_moves) {
		if(move(second_move.substr(0,2),second_move.substr(2,2))) {
		int cur_deduct=0;
		if(mid_board.size()!=board_piece.size()) cur_deduct=ai3_score_help(erased_type);
		if(cur_deduct>deduct) deduct=cur_deduct;
		board_piece=mid_board;
		}
		}
		score-=deduct;
		all_moves_p.push_back(sm+(char)(score+48)+(checking?'1':'0'));
		board_piece=old_board;
		set_current_player(!get_current_player());
		}
	}
		random_shuffle(all_moves_p.begin(),all_moves_p.end());
		vector<string> ranked_moves;
		for(string sm:all_moves_p) {
		bool added=false;
		for(int i=0;i<ranked_moves.size();i++) {
		if(sm[4]>ranked_moves[i][4]||(sm[4]==ranked_moves[i][4]&&sm[5]>ranked_moves[i][5])) {
		ranked_moves.insert(ranked_moves.begin()+i,sm);
		added=true;
		break;
		}
		}
		if(!added) ranked_moves.push_back(sm);
		}
		board_piece=old_board;
		if(ranked_moves.size()==0) return;
		move(ranked_moves[0].substr(0,2),ranked_moves[0].substr(2,2));
		ai_prom_helper();
		return;
	}
}
vector<string> Model::ai3_all_moves_help() {
string type_str=get_current_player()?"RNBQKP":"rnbqkp";
vector<string> all_moves;
for(Piece piece:board_piece) {
        if(type_str.find(piece.get_type())!=string::npos) {
        vector<string> piece_all_move=piece.possible_move_pos(get_board());
        for(string move:piece_all_move) all_moves.push_back(piece.get_pos()+move);
        }
        }
return all_moves;
}

int Model::ai3_score_help(char c) {
	string score_str=get_current_player()?"pnbrq":"PNBRQ";
	int pos=(int)score_str.find(c);
	int rv=0;
	if(pos==0) rv=1;
	else if(pos==1) rv=3;
	else if(pos==2) rv=3;
	else if(pos==3) rv=5;
	else if(pos==4) rv=9;
	return rv;
}

bool Model::ai_prom_helper() {
	for(int i=0;i<board_piece.size();i++) {
                if(board_piece[i].get_type()==(get_current_player()?'P':'p')&&(board_piece[i].get_pos()[1]=='1'||board_piece[i].get_pos()[1]=='8')) {
                board_piece[i].set_type(get_current_player()?'Q':'q');
                return true;
		}
        }
	return false;
}

bool  Model::move(std::string start, std::string end,std::string prom) {
	if(start=="") {ai_move(get_current_player()?p1:p2);return true;}
	for(int i=0;i<board_piece.size();i++) {
		if(board_piece[i].get_pos()==start) {
			if(board_piece[i].white_black()!=get_current_player()) return false;
			vector<string> possible_moves=board_piece[i].possible_move_pos(get_board());
			for(int t=0;t<possible_moves.size();t++) {
				if(possible_moves[t]==end) {
	vector<Piece> old=board_piece;
					if(prom!="") {
	if((board_piece[i].get_type()!='p'&&board_piece[i].get_type()!='P')||prom.length()!=1) 
{
return false;}
	if(board_piece[i].get_prom_string().find(prom[0])==std::string::npos) {
return false;

}
	board_piece[i].set_type(prom[0]);
					}
			board_piece[i].set_pos(end);
			for(int j=0;j<board_piece.size();j++) {
		if(board_piece[j].get_pos()==end&&board_piece[j].get_type()!=board_piece[i].get_type())
		{erased_type=board_piece[j].get_type();
		board_piece.erase(board_piece.begin()+j);
		break;
		}	
		}
			if(check(get_current_player())) {board_piece=old;return false;}
			else {return true;}
				}
			}
			return false;
		}
	}
}

void Model::setup_add(char c, string place) {
	for(int i=0;i<board_piece.size();i++) {
		if (place==board_piece[i].get_pos()) { 
			board_piece[i].set_type(c); 
			return;
			}
	}
	board_piece.push_back({c, place});	
}

void Model::setup_remove(string place) {
	for(int i=0;i<board_piece.size();i++) {
		if(board_piece[i].get_pos()==place) board_piece.erase(board_piece.begin()+i);
	}
}
bool Model::valid_board() {
	int wk=0, bk=0;
	string wkpos="", bkpos="";
	for (int i=0;i<board_piece.size();i++) {
		if(board_piece[i].get_type()=='P'||board_piece[i].get_type()=='p') {
			if (board_piece[i].get_pos()[1]=='1'||board_piece[i].get_pos()[1]=='8')
			return false;
		}
		else if (board_piece[i].get_type()=='K') {wk+=1;}
		else if (board_piece[i].get_type()=='k') {bk+=1;}
	}
	if (wk!=1||bk!=1) return false;
	if(check(true)||check(false)) return false;
	return true;
}

vector<vector<char>> Model::get_board() {
	vector<vector<char>> rv;
	for(int i=0;i<8;i++) {
	vector<char> temp;
	for(int j=0;j<8;j++) {
	temp.push_back(' ');
	}
	rv.push_back(temp);
	}
	for(int i=0;i<board_piece.size();i++) {
		
		int col=board_piece[i].col_to_num((board_piece[i].get_pos())[0]);
		int row=board_piece[i].row_to_num((board_piece[i].get_pos())[1]);

		rv[col][row]=board_piece[i].get_type();
	}
	return rv;
}

Model::Model() {
	set_default_board();
}

void Model::set_default_board() {
	for(char i='a';i<='h';i++) {
		board_piece.push_back(Piece{'P',string()+i+'2'});
		board_piece.push_back(Piece{'p',string()+i+'7'});
	}
	board_piece.push_back(Piece{'R',string{"a1"}});
	board_piece.push_back(Piece{'R',string{"h1"}});
	board_piece.push_back(Piece{'r',string{"a8"}});
	board_piece.push_back(Piece{'r',string{"h8"}});
	
	board_piece.push_back(Piece{'N',string{"b1"}});
	board_piece.push_back(Piece{'N',string{"g1"}});
	board_piece.push_back(Piece{'n',string{"b8"}});
	board_piece.push_back(Piece{'n',string{"g8"}});

	board_piece.push_back(Piece{'B',"c1"});
	board_piece.push_back(Piece{'B',"f1"});
	board_piece.push_back(Piece{'b',"c8"});
	board_piece.push_back(Piece{'b',"f8"});

	board_piece.push_back(Piece{'Q',"d1"});
	board_piece.push_back(Piece{'q',"d8"});

	board_piece.push_back(Piece{'K',"e1"});
	board_piece.push_back(Piece{'k',"e8"});
}

void Model::reset_board() {
	board_piece.clear();
	set_default_board();
}

bool Model::check(bool wb) {
	string kp="";
	for(int i=0;i<board_piece.size();i++) {
		if(wb&&board_piece[i].get_type()=='K') {kp=board_piece[i].get_pos();break;}
		if(!wb&&board_piece[i].get_type()=='k') {kp=board_piece[i].get_pos();break;}
	}
	vector<vector<char>> all_board=get_board();
	for(int t=0;t<board_piece.size();t++) {
		Piece* temp_p=&board_piece[t];
		if(temp_p->white_black()!=wb) {
			vector<string> temp_p_m=temp_p->possible_move_pos(all_board);
			for(int j=0;j<temp_p_m.size();j++) {
			if(temp_p_m[j]==kp) {return true;}
			}
		}
	}
	return false;
}
