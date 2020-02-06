#include <iostream>
#include <stack>
using namespace std;
bool corr(string str){
    for(int i = 0; i < str.length(); i++){
        if(str[i] != '(' && str[i] != ')'){
            return false;
        }
    }
    return true;
}
bool valid(string str){
    stack<char> st;
    st.push('?');//end symbol
    if(corr(str) == false){
        return false;
    }else{
        if(str[0] != '('){
            return false;
        }else{
            st.push(str[0]);
        }
    }
    for(int i = 1; i <= str.length(); i++){
        if(st.top() == '?' && str[i] == '('){
            st.push(str[i]);
        }else if(st.top() == '?' && str[i] == ')'){
            return false;
        }else if(st.top() == '(' && str[i] == '('){
            st.push(str[i]);
        }else if(st.top() == '(' && str[i] == ')'){
            st.pop();
        }
    }
    if(st.top() != '?'){
        return false;
    }else{
        return true;
    }
}
int main(){
    string str;   
    cout<<"Enter string: ";
    cin>>str;
    if(valid(str) == true){
        cout<<"True"<<endl;
    }else{
        cout<<"False"<<endl;
    }
    return 0; 
}
