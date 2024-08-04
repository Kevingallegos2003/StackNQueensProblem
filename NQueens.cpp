#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
int col;
int row;
int B = 4;//board size


int Qspace(vector<vector<int>>& board, int x, int y, int B){
  for(int i=0;i < B; i++){//check column for queens 
    if(board[i][y] == 1){return 2;}
  }
  for(int i = 0; i<B; i++){
    if(board[x][i] == 1){return 0;}//check rows
  }
  for(int i = x, j=y; i>=0 && j>= 0; --i,--j){//check left diag towards 0,0 UPDATE changed from && -> ||
    if(board[i][j]==1){return 0;}
  }
  for(int i =x,j=y; i<B && j<B; i++,j++){
    if(board[i][j]==1){return 0;}
  }
  for(int i =x,j =y;i>=0&&j>=0;--i,++j){//check up right diag
    if(board[i][j]==1){return 0;}
  }
  for(int i=x,j=y;i<B && j>=0;++i,--j){//check lower left diag
    if(board[i][j]==1){return 0;}
  }
  return 1;
}


int main(int argc, char* argv[]){
  //-------------INPUT/OUTPUT SETUP----------------
  ifstream in;
  ofstream out;
  
  if(argc != 3){
    cerr<<"Error, invalid amount of arguments"<<endl;
  }
  in.open(argv[1]);
  if(!in.is_open()){
    cerr<<"Unable to open: "<<argv[1]<<endl;
  }
  out.open(argv[2]);
  if(!out.is_open()){
    cerr<<"Unable to open: "<<argv[2]<<endl;
  }
  //------Variables---------
  int NUM;//input size
  string LINE;//input line
  int None;//input row
  int Ntwo;//input column
  int INVALID;
  int numqueens = 0;
  //----Data structures-------
  stack<pair<int,int>> INQ;
  stack<pair<int,int>> Q;
  vector<vector<int>> board(B,vector<int>(B,0));
  //-----Loop-----------------
  while(!in.eof()){
    INVALID = 0;
    getline(in,LINE);
    if(LINE.size() != 0){
      NUM = atoi((LINE.substr(0,LINE.find(' '))).c_str());
      //----set board size with NUM----------------
      if(B != NUM){
        B = NUM;
        board.resize(B);
        for(int i = 0; i<B;i++){
          board[i].resize(B);
        }
      }
      //----grab cords from line-----
      LINE = LINE.substr(LINE.find(' ')+1,-1);
      while(LINE.size() != 1){
        None = atoi((LINE.substr(0,LINE.find(' ')+1)).c_str());
        LINE = LINE.substr(LINE.find(' ')+1,-1);
        Ntwo = atoi((LINE.substr(0,LINE.find(' '))).c_str());
        LINE = LINE.substr(LINE.find(' ')+1,-1);
        if(LINE.size() <= 2){LINE = " ";}
        None--;
        Ntwo--;
        if(Qspace(board,Ntwo,None,B)==1){//Can these cords be placed?
          board[Ntwo][None]=1;
          INQ.push(make_pair(Ntwo,None));
          numqueens++;
        }
        else{
          INVALID = 1;
          out<<"No solution"<<endl;
          break;
        }
      }
    }
    //---debug-----------------------
    /*
    cout<<"Board Size: "<<B<<endl;
    cout<<LINE.size()<<endl;
    for(unsigned int i = 0; i<board.size();i++){
      for(unsigned int x = 0; x<board.size(); x++){
        cout<< board[i][x]<<" ";
      }
      cout<<endl;
    }
    cout<<"----Board W/ INPUTS----"<<endl;
    */
    //-----IF INPUT VALID START NQUEENS-----------
    if(INVALID == 0 && LINE.size() != 0){
      row = 0;
      col = 0;
      while(numqueens != B){
        while(row<B){
          if(Qspace(board,row,col,B)==1){
            board[row][col]=1;
            numqueens++;
            Q.push(make_pair(row,col));
            row = 0;
            col++;
          }
          else if(Qspace(board,row,col,B)==2){
            row = 0;
            col++;
          }
          else{
            row++;
          }
        }
        if(numqueens == B){break;}
        if(row == B){
          if(Q.empty() == false){
            auto last = Q.top();
            Q.pop();
            board[last.first][last.second] = 0;
            numqueens--;
            row = last.first;
            col = last.second;
            row++;
          }
          else{
            out<<"No solution"<<endl;
            break;
          } 
        }
      }
      //-----printing cords only if solution possible----
      string s1;
      while(INQ.empty() == false){
        Q.push(INQ.top());
        INQ.pop();
      }
      while(Q.empty() == false){
        pair<int,int> temp = Q.top();
        Q.pop();
        while(!INQ.empty() && INQ.top().second < temp.second){
          Q.push(INQ.top());
          INQ.pop();
        }
        INQ.push(temp);
      }
      while(INQ.empty() == false){
        auto qi = INQ.top();
        s1 = s1 + to_string(qi.second+1) +" "+ to_string(qi.first+1) + " ";
        INQ.pop();
      }
      if(numqueens == B){
        out<<s1<<endl;
      }
    }
    //---reset for next use------
    numqueens = 0;
    while(!Q.empty()){Q.pop();}
    while(!INQ.empty()){INQ.pop();}
    for(unsigned int i = 0; i<board.size();i++){
      for(unsigned int x = 0; x<board.size(); x++){
        board[i][x] = 0;
      }
    }
  }
  in.close();
  out.close();
}