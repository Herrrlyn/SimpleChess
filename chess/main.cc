#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "model.h"
#include "View.h"
using namespace std;

bool check_piece(char piece){
  if (piece <= 122 && piece >= 97){
    return (piece == 98 || piece == 107 || piece == 110 || piece == 112 || piece == 113 || piece == 114);
  } else if (piece <= 90 && piece >= 65){
    return (piece == 66 || piece == 75 || piece == 78 || piece == 80 || piece == 81 || piece == 82);
  } else {
    return false;
  }
}

bool check_pos(string position){
  return ((position[0] >= 97 && position[0] <= 104) && (position[1] >= 49 && position[1] <= 56));
}

int main(){
  Model model;
  View view;
  string command_line, command1, command2, command3;
  string piece;
  int player_1 = 5, player_2 = 5, whiteScore = 0, blackScore = 0, score = 0;
  bool check, turn = true, move, board, running = false, invalid_command;
  while (getline(cin, command_line)){
    istringstream ss {command_line};
    ss >> command1;
    while (command1 == "setup"){
      getline(cin, command_line);
      istringstream ss {command_line};
      if (running) {
	view.invalid_command();
	command1 = "";
      } else {
        ss >> command2;
        if (command2 == "+"){
          ss >> piece;
          ss >> command3;
          if (check_piece(piece[0]) && check_pos(command3)){
            model.setup_add(piece[0], command3);
            view.update_board(model.get_board());
          } else {
            view.invalid_command();
	    command1 = "";
          }
        } else if (command2 == "-"){
          ss >> command3;
          if (check_pos(command3)){
            model.setup_remove(command3);
            view.update_board(model.get_board());
          } else {
            view.invalid_command();
	    command1 = "";
          }
        } else if (command2 == "="){
          ss >> command3;
	  command3 == "white" ? turn = true : turn = false;
          view.update_board(model.get_board());
        } else if (command2 == "done"){
          board = model.valid_board();
	  if (!board){
	    view.invalid_command();
	  }
	  view.update_board(model.get_board());
	  command1 = "";
	  break;
        } else {
	  view.invalid_command();
	  command1 = "";
	}
	command2 = "";
	command3 = "";
	piece = "";
      } 
    }
    
    if (command1 == "game"){
      running = true;
      ss >> command2;
      ss >> command3;
      if (command2 == "human"){
        player_1 = 0;
      } else if (command2 == "computer1" || command2 == "computer2" || command2 == "computer3" || command2 == "computer4"){
        player_1 = command2[8] - '0';
      } else {
	player_1 = 5;
      }
      if (command3 == "human"){
        player_2 = 0;
      } else if (command3 == "computer1" || command3 == "computer2" || command3 == "computer3" || command3 == "computer4"){
        player_2 = command3[8] - '0';
      } else {
	player_2 = 5;
      }
      if (player_1 > 4 || player_2 > 4){
	view.invalid_command();
      } else {
        model.newgame(player_1, player_2);
        view.update_board(model.get_board());
        view.current_turn(turn);
      }
      command1 = "";
      command2 = "";
      command3 = "";
    } else if (command1 == "move") {
      invalid_command = false;
      if ((ss >> command2) && (ss >> command3)) {
        if (!(check_pos(command2) && check_pos(command3))){
          invalid_command = true;
	  view.invalid_command();
        } else {
          if (ss >> piece){
	    model.set_current_player(turn);
            move = model.move(command2, command3, piece);
	    if (move) {
	      view.update_board(model.get_board());
	      turn == true ? turn = false : turn = true;
	    } else {
	      invalid_command = true;
	      view.invalid_command();
	    }
          } else {
	    model.set_current_player(turn);
	    move = model.move(command2, command3);
	    if (move) {
              view.update_board(model.get_board());
              turn == true ? turn = false : turn = true;
            } else {
		invalid_command=true;
              view.invalid_command();
            }
          }
	}
	command1 = "";
	command2 = "";
	command3 = "";
      } else if(!((turn==true&&player_1==0)||(turn==false&&player_2==0))) {
	model.set_current_player(turn);
        move = model.move();
	if (move) {
          view.update_board(model.get_board());
          turn == true ? turn = false : turn = true;
        } else {
	  invalid_command = true;
          view.invalid_command();
        }
      } else {
	invalid_command = true;
	view.invalid_command();
      }
      if(!invalid_command) {
        score = model.check_win(turn);
        if (score == 0){
	  check = model.check(!turn);
          if (check) {
	    view.check(!turn);
	  }
	  view.current_turn(turn);
        } else  {
	  running = false;
          turn ? whiteScore += score : blackScore += score;
          view.checkwin(turn);
	  model.reset_board();
	  turn = true;
        } 
      }
      command1 = "";
    } else if (command1 == "resign") {
      if (running){
        score = 1;
        turn ? blackScore += score : whiteScore += score;
        view.checkwin(!turn);
        model.resign();
        model.reset_board();
        view.update_board(model.get_board());
        turn = true;
	running = false;
      } else {
	view.invalid_command();
      }
      command1 = "";
    } else {
      view.invalid_command();
    }
  }
  view.score(whiteScore, blackScore);
}

