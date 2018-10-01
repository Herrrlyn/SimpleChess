#ifndef _CHESS_MODEL_
#define _CHESS_MODEL_

#include "piece.h"
#include <vector>
using namespace std;

class Model {
	std::vector<Piece> board_piece;
	int p1=2, p2=2;
	bool current_player=true;
	void set_default_board();
	void ai_move(int lvl);
	bool ai_prom_helper();
	char erased_type=' ';
	int ai3_score_help(char c);
	vector<string> ai3_all_moves_help();
	public:
	Model();
	bool get_current_player();
	void set_current_player(bool new_current_player);
	void newgame(int a, int b);
	bool move(std::string start="", std::string end="", std::string prom="");
	bool valid_board();
	void setup_add(char c, std::string place);
	void setup_remove(std::string place);
	bool check(bool wb);
	std::vector<std::vector<char>> get_board();
	void reset_board();
	void resign();
	bool check_win(bool side);
};

#endif
