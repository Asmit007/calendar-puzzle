#include<bits/stdc++.h>
#include<iostream>
#include <fstream>
#include<map>
#include<set>
using namespace std;

#define RESET "\033[0m"
#define RED "\033[38;5;197m"
#define YELLOW "\033[33m"
#define ORANGE "\033[38;5;208m"  
#define DARKPINK "\033[38;5;205m"  
#define LIGHTBLUE "\033[38;5;153m"
#define DARKBLUE "\033[34m"
#define GREEN "\033[32m"
#define VIOLET "\033[38;5;129m" 
#define BLACK "\033[30m"

class Piece {
    private: 
        vector< vector<string> > allVariation;
        vector< vector<string> > allInvertedVariation;

        vector<string> getInvertedPiece(vector<string> &piece){
            vector<string> invertedPiece = piece ;
            for(int i=0; i<invertedPiece.size(); i++){
                reverse(invertedPiece[i].begin(), invertedPiece[i].end());
            }
            return invertedPiece;
        }

        vector<string> rotatePieceClockwise(vector<string> piece, int numberOfRotations){
            while(numberOfRotations--){
                for(int i=0; i<piece.size(); i++){
                    for(int j=0; j<i; j++){
                        swap(piece[i][j], piece[j][i]) ;
                    }
                }

                for(int i=0; i<piece.size(); i++){
                    reverse(piece[i].begin(), piece[i].end());
                }
            }
            return piece;
        }

    public:
        Piece(vector<string> &piece) {
            for(int rotateCount=0; rotateCount<=3; rotateCount++){
                allVariation.push_back(rotatePieceClockwise(piece, rotateCount));
            }
            vector<string> invertedPiece = getInvertedPiece(piece);

            for(int rotateCount=0; rotateCount<=3; rotateCount++){
                allInvertedVariation.push_back(rotatePieceClockwise(invertedPiece, rotateCount));
            }
        }

        vector<string> getPiece(int index){
            if (index >= allVariation.size()) return {};
            return allVariation[index];
        }

        vector<string> getInvertedPiece(int index){
            if (index >= allInvertedVariation.size()) return {};
            return allInvertedVariation[index];
        }

        void printPiece() {
            for(int i=0; i<4; i++){
                vector<string> temp = this->getPiece(i);
                for(auto x: temp) {
                    for(auto z:x) cout<<z<<" " ;
                    cout<<endl; 
                }
                cout<<endl<<endl; 
            }

            for(int i=0; i<4; i++){
                vector<string> temp = this->getInvertedPiece(i);
                for(auto x: temp) {
                    for(auto z:x) cout<<z<<" " ;
                    cout<<endl; 
                }
                cout<<endl<<endl;  
            }
        }

};

class Board {
    private:
        map<string, pair<int,int> > valueToSquareMap; 
        vector<Piece*> pieces;
        string month;
        string date;
        char NOT_ALLOWED_SQUARE = '*';
        char ALLOWED_SQUARE = '.';
        int MASK;
        bool soultionFound = false;

        vector<string> board = {
            "****************",
            "****......******",
            "****......******",
            "****.......*****",
            "****.......*****",
            "****.......*****",
            "****.......*****",
            "****...*********",
            "****************",
        };
        
        void markRequiredDates(string month, string date, char ch) {
            pair<int,int> monthIndex = valueToSquareMap[month];
            pair<int,int> dateIndex = valueToSquareMap[date];
            board[monthIndex.first][monthIndex.second] = ch;
            board[dateIndex.first][dateIndex.second] = ch;
        }

        void printSquare(int size) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    cout << "\u2588";
                }
            }
        }

        void fillValueToSquareMap(){
            map<string, pair<int,int> > M;
            M["jan"] = make_pair(1,4), M["feb"] = make_pair(1,5), M["mar"] = make_pair(1,6), M["apr"] = make_pair(1,7), M["may"] = make_pair(1,8), M["jun"] = make_pair(1,9);
            M["jul"] = make_pair(2,4), M["aug"] = make_pair(2,5), M["sep"] = make_pair(2,6), M["oct"] = make_pair(2,7), M["nov"] = make_pair(2,8); M["dec"] = make_pair(2,9);
            M["1"] = make_pair(3,4), M["2"] = make_pair(3,5), M["3"] = make_pair(3,6), M["4"] = make_pair(3,7), M["5"] = make_pair(3,8), M["6"] = make_pair(3,9), M["7"] = make_pair(3,10);
            M["8"] = make_pair(4,4), M["9"] = make_pair(4,5), M["10"] = make_pair(4,6), M["11"] = make_pair(4,7); M["12"] = make_pair(4,8), M["13"] = make_pair(4,9), M["14"] = make_pair(4,10);
            M["15"] = make_pair(5,4), M["16"] = make_pair(5,5), M["17"] = make_pair(5,6), M["18"] = make_pair(5,7), M["19"] = make_pair(5,8), M["20"] = make_pair(5,9), M["21"] = make_pair(5,10);
            M["22"] = make_pair(6,4), M["23"] = make_pair(6,5), M["24"] = make_pair(6,6), M["25"] = make_pair(6,7), M["26"] = make_pair(6,8), M["27"] = make_pair(6,9), M["28"] = make_pair(6,10);
            M["29"] = make_pair(7,4), M["30"] = make_pair(7,5), M["31"] = make_pair(7,6);

            this->valueToSquareMap = M; 
        }

        bool allPiecesPlaced(int mask){
            return mask == MASK; 
        }

        void putPiece(vector<string> piece, int row, int col){
            for(int i=0; i<piece.size(); i++){
                for(int j=0; j<piece[0].size(); j++){
                    if(piece[i][j] != '.') {
                        this->board[i+row][j+col] = piece[i][j];
                    }
                }
            }
        }

        void removePiece(vector<string> piece, int row, int col){
            for(int i=0; i<piece.size(); i++){
                for(int j=0; j<piece[0].size(); j++){
                    if(piece[i][j] != '.') {
                        this->board[i+row][j+col] = '.';
                    }
                }
            }
        }

        bool canPutPiece(vector<string> piece, int row, int col){
            for(int i=0; i<piece.size(); i++){
                for(int j=0; j<piece[0].size(); j++){
                    if(piece[i][j] != '.') {
                        if(this->board[i+row][j+col] != '.') return false; 
                    }
                }
            }
            return true;
        }

        bool isPieceAvailable(int index, int mask) {
            return (mask & (1<<index)) == 0; 
        }
        
        int takeCurrentPiece(int index, int mask) {
            return mask | (1<<index);
        }

        bool shouldMoveToNextRow(int row) {
            for(int col=0; col<board[0].size(); col++){
                if(this->board[row][col] == '.') return false;
            }
            return true;
        } 

        void Solve(int row, int col, int mask){

            if(soultionFound) return ;

            if(allPiecesPlaced(mask)) {
                cout<<"\n\n\tSOLUTION FOUND !!"<<endl<<endl;
                soultionFound = true;
                printBoard();
                return;
            }

            if(row >= this->board.size()) {
                return;
            }

            if(col >= this->board[0].size()){
                if (shouldMoveToNextRow(row))
                    Solve(row+1, 0, mask);
                return;
            }

            for(int i=0; i<pieces.size(); i++){
                if(isPieceAvailable(i, mask)) {
                    // normal piece
                    for(int rotation=0; rotation <= 0; rotation++){
                        vector<string> p = pieces[i]->getPiece(rotation);
                        if (canPutPiece(p, row, col)){
                            putPiece(p, row, col);
                            Solve(row, col, takeCurrentPiece(i, mask));
                            removePiece(p, row, col);
                        }
                    }

                    // inverted piece
                    for(int rotation=0; rotation <= 3; rotation++){
                        vector<string> p = pieces[i]->getInvertedPiece(rotation);
                        if (canPutPiece(p, row, col)){
                            putPiece(p, row, col);
                            Solve(row, col, takeCurrentPiece(i, mask));
                            removePiece(p, row, col);
                        }
                    }
                }
            }

            Solve(row, col+1, mask) ;
        }

        string getColorForTerminal(char ch) {
            switch (ch) {
                case 'A': return GREEN;
                case 'B': return ORANGE;
                case 'C': return LIGHTBLUE;
                case 'D': return DARKBLUE;
                case 'E': return DARKPINK;
                case 'F': return VIOLET;
                case 'G': return YELLOW;
                case 'H': return RED;
                default: return BLACK;
            }
        }


    public:
        Board(vector<Piece*> pieces) {
            this->pieces = pieces;
            this->MASK = (1<<pieces.size()) - 1 ;
            fillValueToSquareMap();
        }

        void solveBoard(string month, string date){
            transform(month.begin(), month.end(), month.begin(), ::tolower);

            if(valueToSquareMap.count(month) == 0 || valueToSquareMap.count(date) == 0) {
                cout<<"INVALID INPUT !"<<endl;
                return;
            }
            this->month = month;
            this->date = date;
            markRequiredDates(month, date, NOT_ALLOWED_SQUARE);
            Solve(0, 0, 0);
            markRequiredDates(month, date, ALLOWED_SQUARE);

            if (this->soultionFound == false) {
                cout<<"NO SOLUTION FOUND!"<<endl; 
            }
        }   

        void printBoard(){
            pair<int,int> monthIndexes = valueToSquareMap[this->month];
            pair<int,int> dateIndexes = valueToSquareMap[this->date];
            cout<<endl;
            for(int i=1; i<=7; i++){
                cout<<"\t ";
                for(int j=4; j<=10; j++){
                    char ch = this->board[i][j];
                    
                    if(ch != NOT_ALLOWED_SQUARE ){
                        cout<<getColorForTerminal(ch);
                        printSquare(2);
                        cout<<RESET<<" " ;
                    }
                    else if(monthIndexes == make_pair(i,j)) {
                        string upperCaseMonth = this->month;
                        transform(upperCaseMonth.begin(), upperCaseMonth.end(), upperCaseMonth.begin(), ::toupper);
                        cout<<upperCaseMonth<<"  " ;
                    }
                    else if(dateIndexes == make_pair(i,j)){
                        string date = this->date;
                        while(date.size() != 4) date.push_back(' ');
                        cout<<date<<" ";
                    }
                    else {
                        cout<<"XXXX"<<" ";
                    }
                }
                cout<<endl<<endl; 
            }
            cout<<endl<<endl; 
        }
};



int main() {

    vector<string> piece1 = {
        ".A..",
        ".A..",
        ".A..",
        ".AA."
    };
    vector<string> piece2 = {
        ".BB.",
        ".BB.",
        ".BB.",
        "...."
    };
    vector<string> piece3 = {
        "....",
        ".CC.", 
        ".CCC",
        "...."
    };
    vector<string> piece4 = {
        "....",
        "..DD", 
        "DDD.",
        "...."
    };
    vector<string> piece5 = {
        "....",
        "...E", 
        ".EEE", 
        ".E.."
    };
    vector<string> piece6 = {
        "....",
        ".FFF", 
        ".F..", 
        ".F.."
    };
    vector<string> piece7 = {   
        "....",
        ".G..", 
        "GGGG",
        "...."
    };
    vector<string> piece8 = {
        "....",
        ".HHH", 
        ".H.H",
        "...."
    };

    Piece *p1 = new Piece(piece1);
    Piece *p2 = new Piece(piece2);
    Piece *p3 = new Piece(piece3);
    Piece *p4 = new Piece(piece4);
    Piece *p5 = new Piece(piece5);
    Piece *p6 = new Piece(piece6);
    Piece *p7 = new Piece(piece7);
    Piece *p8 = new Piece(piece8);
    Board *board = new Board({p1, p2, p3, p4, p5, p6, p7, p8});

    board->solveBoard("Aug", "19");

    return 0 ;
}