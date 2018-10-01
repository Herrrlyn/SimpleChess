#ifndef _VIEW_H_
#define _VIEW_H_
#include <iostream>
#include <vector>
#include "window.h"

//class Xwindow;

class View {
	std::vector<std::vector<char>> old_board;
	Xwindow w;
	public:
	View();
	void current_turn(bool b);
	void update_board(std::vector<std::vector<char>> board);
	void invalid_command();
	void check(bool b);
	void checkwin(bool state);
	void score(int a,int b);
};
#endif
