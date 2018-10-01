#include <iostream>
#include <vector>

#include "View.h"
#include "window.h"

using namespace std;

void help() {
	cout << "Avaliable commands:" << endl<< endl;
        cout << "game white-player black-player" << endl;
        cout << "This starts a new game. The parameters white-player and black-player can be either human or computer[1-4]" << endl << endl;
        cout << "resign" << endl;
        cout << "Concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game." << endl << endl;
        cout << "move pos pos" << endl;
        cout << "A move consists of the command move, followed by the starting and ending positions of the piece to be moved. For example: move e2 e4. Castling would specified by the two- square move for the king: move e1 g1 or move e1 c1 for white. Pawn promotion would additionally specify the piece type to which the pawn is promoted: move e7 e8 Q. In the case of a computer player, the command move (without arguments) makes the computer player make a move." << endl << endl;
        cout << "setup" << endl;
        cout << "setup enters setup mode, within which you can set up your own initial board configurations. This can only be done when a game is not currently running." << endl;
}

View::View():w{(450,450)}{
	for (int i=0;i<8;i++){
	w.drawBigString(12,(i+1)*50-12,string()+(char)((int)'8'-i));
	w.drawBigString((i+1)*50+12,450,string()+(char)((int)'A'+i));
		vector<char> temp;
		for (int j=0;j<8;j++){
			temp.push_back('/');
			if((i+j)%2==0) {
			w.fillRectangle((i+1)*50,j*50,50,50,Xwindow::White);
			} else w.fillRectangle((i+1)*50,j*50,50,50,Xwindow::Black);
		}
		old_board.push_back(temp);
	}
}

void View::current_turn(bool b){
	if (b){
		cout << "White " ;
	}else{
		cout << "Black ";
	}
	cout << "turn to move." << endl;
}

void View::update_board(std::vector<std::vector<char>> board){
	for (int i=board.size();i>0;i--) {
		cout << i << " ";
		for (int j=0;j<board.size();j++){
			if (board[j][i-1]!=' '){
				cout << board[j][i-1];
			}else{
				if (i%2==0){
					if (j%2==0){
						cout << ' ';
					}else{
						cout << '_';
					}
				}else{
					 if (j%2==0){
                                                cout << '_';
                                        }else{
                                                cout << ' ';
                                        }
				}
			}
		}
		cout <<endl;
	}
	cout << endl;
	cout << " abcdefgh" <<endl;
        for (int i=0;i<8;i++){
		for(int j=0;j<8;j++) board[i].push_back('P');
        }
        for (int i=1;i<9;i++){
                for (int j=0;j<8;j++){
			if (board[i-1][j]!=old_board[i-1][j]){
                        	if  (i%2==0){
                                	if (j%2==0){
                                        	        w.fillRectangle(i*50,(7-j)*50,50,50,Xwindow::White);
                                        	}else{
                                                	w.fillRectangle(i*50,(7-j)*50,50,50,Xwindow::Black);
                                     		}
                              	        }else{
						if (j%2==0){
                                                	w.fillRectangle(i*50,(7-j)*50,50,50,Xwindow::Black);
                                                }else{
                                                	w.fillRectangle(i*50,(7-j)*50,50,50,Xwindow::White);
                                        	}
                                	}
					string white_pieces="RNBQKP";
					int color=white_pieces.find(board[i-1][j])==string::npos?Xwindow::Red:Xwindow::Blue;
					w.drawBigString(i*50+12,(7-j)*50+38,std::string()+board[i-1][j],color);
                		}
        		}
		}
		old_board=board;
}

void View::invalid_command(){
	cout << "Invalid Command. Please type command again."<<endl;
	help();
}
      
void View::check(bool b){
	if (!b){	
		cout << "White ";
	}else{
		cout << "Black ";
	}
	cout << "is in check."<<endl;
}
       
void View::checkwin(bool state){
	cout << "Checkmate! ";
	if (state){
		cout << "White wins!"<<endl;
	}else{
		cout << "Black wins!"<<endl;
	}
}

void View::score(int a,int b){
	cout << "Final score:"<<endl;
	cout <<"White: "<<a<<endl;
	cout <<"Black: "<<b<<endl;
}
