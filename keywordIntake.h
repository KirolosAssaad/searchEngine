#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

typedef class Keywords{
private:
    string Input;
    vector<string> searchWords;
    bool quotes = false;
    bool  AND   = false;
    bool  OR    = false;

public:
    void setInput();
    int setWords();
    void findQuotes();
    void findAnd();
    void findOr();
    void setall();
    vector<string> getSearchWords(){return searchWords;}
    bool getQuotes(){return quotes;}
    bool getAND(){return AND;}
    bool getOR(){return OR;}
}Keys;

void Keys::setInput(){
    cout<<endl<<"Please enter the string you want to search: "<<endl;
    getchar();
    getline(cin, Input);
}
void Keys::findQuotes(){
    for (int i=0;i<Input.size();i++){
        if (Input[i]=='"'){
            quotes=true;
            Input.erase(remove(Input.begin(), Input.end(), '"'), Input.end());
        }}}

int Keys:: setWords(){
    string x = Input;
    string delimiter = "OR";
    size_t pos = 0;
    string token;
    while ((pos = x.find(delimiter)) != string::npos) {
        return 1;
    }
    delimiter = "AND";
    while ((pos = x.find(delimiter)) != string::npos) {
        return 2;
    }
    return 0;
}

void Keys:: findAnd(){
    string x = Input;
    string delimiter = " AND ";
    size_t pos = 0;
    string token;
    while ((pos = x.find(delimiter)) != string::npos) {
        token = x.substr(0, pos);
        searchWords.push_back(token);
        x.erase(0, pos + delimiter.length());
    }
    searchWords.push_back(x);
}
void Keys:: findOr(){
    string x = Input;
    string delimiter = " OR ";
    size_t pos = 0;
    string token;
    while ((pos = x.find(delimiter)) != string::npos) {
        token = x.substr(0, pos);
        searchWords.push_back(token);
        x.erase(0, pos + delimiter.length());
    }
    searchWords.push_back(x);
}

void Keys::setall(){
    setInput();
    int x= setWords();
    findQuotes();
    if (quotes)
        searchWords.push_back(Input);
    else if (x==2)
    {findAnd();}
    else if (x==1)
    {findOr();}
    else {
        searchWords.push_back(Input);
        string x = Input;
        string delimiter = " ";
        size_t pos = 0;
        string token;
        while ((pos = x.find(delimiter)) != string::npos) {
            token = x.substr(0, pos);
            searchWords.push_back(token);
            x.erase(0, pos + delimiter.length());
        }
        searchWords.push_back(x);
    }

}
