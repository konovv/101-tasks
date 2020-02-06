#include <iostream>
#include <string>
#include <queue>
using namespace std;
void eraseSubStr(string & mainStr, const string & toErase)
{
	size_t pos = mainStr.find(toErase);
	if (pos != string::npos)
	{
        mainStr.erase(pos, toErase.length());
	}
}
void start(){
    string coord, table_size, xch, ych, h;
    int row = 0, col = 0, days = 0, count_rotten_apple = 0, x = 0, y = 0, size_queue = 0;
    queue<int> qX, qY;

    cout<<"Enter the size of the box: ";
    cin>>table_size;
    cout<<"Enter the coordinares of the rotten apples: ";
    getline(cin >> ws, coord);
    cout<<"After how many days will you come back: ";
    cin>>days;
    cout<<endl;

    size_t fount1 = table_size.find('x');
    h = table_size.substr(0,fount1);
    col = stoi(h);
    eraseSubStr(table_size, h +'x');
    row = stoi(table_size);
    char arr[row][col];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            arr[i][j] = 'O';
        }
    }
    for(int i = 0; i < coord.length(); i++){
        if(coord[i] == ')'){
            count_rotten_apple++;
        }
    }
    for(int i = 0; i < count_rotten_apple; i++){
        size_t fount = coord.find(')');
        ych = coord.substr(0,fount);
        eraseSubStr(coord,ych+") ");
        eraseSubStr(ych,"(");
        fount = ych.find(',');
        xch = ych.substr(0,fount);
        eraseSubStr(ych,xch+",");
        x = stoi(ych)-1;
        y = stoi(xch)-1;
        qX.push(x);
        qY.push(y);
        arr[x][y] = 'X';
    }
    for(int i = 1; i <= days; i++){
        size_queue = qX.size();
        if(i % 3 == 0){
            for(int i = 0; i < size_queue; i++){
                x = qX.front();
                qX.pop();
                y = qY.front();
                qY.pop();
                if((x-1 >= 0 && y == y) && (arr[x-1][y] != 'X')){
                    arr[x-1][y] = 'X';
                    qX.push(x-1);
                    qY.push(y);
                }
                if((x+1 < row && y == y) && (arr[x+1][y] != 'X')){   
                    arr[x+1][y] = 'X';
                    qX.push(x+1);
                    qY.push(y);
                }
                if((y-1 >=0 && x == x) && (arr[x][y-1] != 'X')){
                    arr[x][y-1] = 'X';
                    qX.push(x);
                    qY.push(y-1);
                }
                if((y+1 < col && x == x) && (arr[x][y+1])){
                    arr[x][y+1] = 'X';
                    qX.push(x);
                    qY.push(y+1);
                }
                if((x-1 >= 0 && y-1 >= 0) && (arr[x-1][y-1] != 'X')){
                    arr[x-1][y-1] = 'X';
                    qX.push(x-1);
                    qY.push(y-1);
                }
                if((x+1 < row && y+1 < col) && (arr[x+1][y+1] != 'X')){
                    arr[x+1][y+1] = 'X';
                    qX.push(x+1);
                    qY.push(y+1);
                }
                if((x+1 < row && y-1 >= 0) && (arr[x+1][y-1] != 'X')){
                    arr[x+1][y-1] = 'X';
                    qX.push(x+1);
                    qY.push(y-1);
                }
                if((x-1 >= 0 && y+1 < col) && (arr[x-1][y+1] != 'X')){
                    arr[x-1][y+1] = 'X';
                    qX.push(x-1);
                    qY.push(y+1);
                }
            }
        }
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main(){
    start();
    return 0;
}
