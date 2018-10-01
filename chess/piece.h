#include <string>
#include <vector>
using namespace std;

class Piece {
	char type;
	std::string pos;
	bool white_black(char c);
	void helper_possible_move(std::vector<std::string>* ori, std::vector<std::vector<char> > board, int varx, int vary);
	public:
	std::string get_prom_string();
	int row_to_num(char c);
	int col_to_num(char c);
	bool valid_pos(std::string new_pos);
	void set_pos(std::string new_pos);
	std::string get_pos();
	char get_type();
	void set_type(char type);
	Piece(char type, std::string pos);
	bool white_black();
	std::vector<std::string> possible_move_pos(std::vector<std::vector<char> > board);
};

