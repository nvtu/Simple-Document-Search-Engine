#include "TRIE.h"
int main(){
    Trie Engine;
    Engine.Init();
    string s,t,u;
    bool ok, isFilter;
    cout<<"************Welcome to Group 3 search engine!!!************"<<endl<<"************Please decide the searching style************"<<endl;
    cout<<"1) Do you want to distinguish uppercase letter? (YES/NO) ";
    getline(cin,s);
    cout<<"2) Do you want to turn on stop word filter? (YES/NO) ";
    getline(cin,t);
    cout<<"3) Which output do you want to execute? Console output or File Output? (C/F) ";
    getline(cin,u);
    cout<<"Let's begin!!!..."<<endl;
    if (s=="YES"){
        ok=true;
    }
    else{
        ok=false;
    }
    if (t=="YES"){
        isFilter=true;
    }
    else{
        isFilter=false;
    }
    Engine.QueryExecution(ok, isFilter, u);
    Engine.Free();
    cout<<"Thanks for using our search engine!!!"<<endl;
    return 0;
}
