#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <fstream>
using namespace std;
void eraseSubStr(string & mainStr, const string & toErase)
{
	size_t pos = mainStr.find(toErase);
	if (pos != string::npos)
	{
        mainStr.erase(pos, toErase.length());
	}
}
bool is_inside_circle(double xc, double yc, double xp, double yp, double R){
    if(xc == xp && yc == yp){
        return false;
    }
    if(pow(xp-xc,2)+pow(yp-yc,2)<=pow(R,2)){
        return true;
    }else{
        return false;
    }
}
class point{
private:
    int x;
    int y;
    int value;
public:
    //point(const int& _x,const int& _y, const int& _value):x(_x),y(_y),value(_value){}
    point(string str){
        string help;
        size_t fount =  str.find(',');
        help = str.substr(0,fount);
        x = stoi(help);
        eraseSubStr(str,help+',');
        fount = str.find(',');
        help = str.substr(0,fount);
        y = stoi(help);
        eraseSubStr(str,help+',');
        value = stoi(str);
    }
    void print(){
        cout<<"("<<x<<","<<y<<")";
    }
    int get_x(){
        return this->x;
    }
    int get_y(){
        return this->y;
    }
    int get_value(){
        return this->value;
    }
};
class points{
private:
    vector<point*> arr_points;
public:
    points(){};
    void print(){
        for(int i=0;i<arr_points.size();i++){
            arr_points[i]->print();
        }
    }
    void add_point(point* p){
        arr_points.push_back(p);
    }
    set<point*> work(int R, int error){
        vector<point*> neighbours;
        stack<point*> neighbour_error_points;
        set<point*> error_points;
        for(int i = 0; i < arr_points.size(); i++){
            neighbours = find_neighbours(R, arr_points[i]);
            if(!neighbours.empty()){
                neighbour_error_points = error_neighbours(error, arr_points[i], neighbours);
                if(!neighbour_error_points.empty()){
                    if(neighbours.size() == neighbour_error_points.size()){
                    error_points.insert(arr_points[i]);
                    }else if(neighbours.size() > neighbour_error_points.size()){
                        while(!neighbour_error_points.empty()){
                            error_points.insert(neighbour_error_points.top());
                            neighbour_error_points.pop();
                        }
                    }
                }
            }
        }
        return error_points;
    }
    vector<point*> find_neighbours(int R, point* p){
        vector<point*> neighbours;
        for(int i = 0; i < arr_points.size(); i++){
            if(is_inside_circle(p->get_x(), p->get_y(), arr_points[i]->get_x(), arr_points[i]->get_y(), R) == true){
                neighbours.push_back(arr_points[i]);
            }
        }
        return neighbours;
    }
    stack<point*> error_neighbours(int error, point* check_point, vector<point*> neighbours){
        stack<point*> neighbour_error_points;
        for(int j = 0; j < neighbours.size(); j++){
            if(abs(check_point->get_value() - neighbours[j]->get_value()) > error){
                neighbour_error_points.push(neighbours[j]);
            }
        }
        return neighbour_error_points;
    }
    friend bool is_inside_circle(double xc, double yc, double xp, double yp, double R);

};
void start(){
    points arr;
    set<point*> s;
    string file_name, str;
    int distance, error;    
    cout<<"Filename: ";
    cin>>file_name;
    cout<<endl;
    cout<<"Neighbours distance: ";
    cin>>distance;
    cout<<endl;
    cout<<"Max error: ";
    cin>>error;
    cout<<endl;
    ifstream in(file_name);
    while (getline(in,str)){
        point* a = new point(str);
        arr.add_point(a);
    }
    s = arr.work(distance, error);
    if(s.empty()!= true){
        cout<<"Please check sensors at: ";
        for(auto& a:s){
            a->print();
            cout<<", ";
        }
    }else{
        cout<<"All sensors are OK.";
    }
}
int main (){
    start();
    return 0;
}
