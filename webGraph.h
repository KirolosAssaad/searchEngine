#pragma once
#include <iostream>
#include <istream>
#include <cstring>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
const string impressionsFile="/Users/kirolosmorcos/Desktop/lab project/lab project/impression_no.csv";
const string attributesFile="/Users/kirolosmorcos/Desktop/lab project/lab project/keyword_file.csv";
const string clicksFile="/Users/kirolosmorcos/Desktop/lab project/lab project/clicks.csv";
const string webGraphFile="/Users/kirolosmorcos/Desktop/lab project/lab project/web_graph.csv";

using namespace std;


void tokenize(std::string const &str, const char delim,std::vector<std::string> &out)
{
   size_t start;
   size_t end = 0;

   while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
   {
       end = str.find(delim, start);
       out.push_back(str.substr(start, end - start));
   }
}


struct websites{
    string page;
    vector<string> attributes;
    int impressions;
    int clicks;
    float ctr;
    float pageRank;
    float score;
    vector<string> outgoingWebs;
    vector<string> ingoingWebs;

};


class webGraph {
private:
    vector<websites> allWebs;
public:
    
    void setWebsites();
    void setClicks();
    void setattributes();
    void setoutgoing ();
    void setingoing ();
    void incClicks (string x);
    void incImpressions (string x);
    void updateClicks ();
    void pageRankCalc();
    void calcCTR(string x);
    void updateImpressions ();
    void calcScore(string x);
    void calcScores();
    void calcCTRs();
    void initializeAll();
    vector<websites> returnAllWebs(){return allWebs;}
    void resultDisplay(string site);
};

void webGraph::setWebsites(){
    fstream fin;
    fin.open(impressionsFile, ios::in);
    if(!fin){
        cout<<endl<<"Invalid path to impressions file"<<endl;exit(0);
    }
    string line;

    while(getline(fin,line)){
        vector <string> results;
        websites x;
        tokenize(line, ',',results);
        x.page = results[0];
        x.impressions = stoi(results[1]);
        allWebs.push_back(x);
    }
    fin.close();

}

void webGraph::setattributes(){
    
    fstream fin;
    fin.open(attributesFile, ios::in);
    if(!fin){
        cout<<endl<<"Invalid path to attributes file"<<endl;exit(0);
    }
    string line;
    while(getline(fin,line)){
        vector<string> results;
        string webpage;
        tokenize(line, ',',results);
        webpage= results[0];
        results.erase(results.begin());
        for (int i=0;i<allWebs.size();i++){
            if (allWebs[i].page==webpage){
                allWebs[i].attributes=results;
                break;
            }
        }
    }
    fin.close();
}

void webGraph::setClicks(){
    
    fstream fin;
    fin.open(clicksFile, ios::in);
    if(!fin){
        cout<<endl<<"Invalid path to clicks file"<<endl;exit(0);
    }
    string line;
    while(fin>>line){
        vector<string> results;
        string webpage;
        websites x;
        tokenize(line, ',',results);
        webpage= results[0];
        results.erase(results.begin());
        for (int i=0;i<allWebs.size();i++){
            if (allWebs[i].page==webpage){
                allWebs[i].clicks=stoi(results[0]);
            }
        }
    }
    fin.close();
}

void webGraph::setingoing (){
    
    fstream fin;
    fin.open(webGraphFile, ios::in);
    if(!fin){
        cout<<endl<<"Invalid path to web graph file"<<endl;exit(0);
    }
    string line;

    while(fin>>line){

        vector<string> results;
        string webpage;
        tokenize(line, ',',results);
        webpage= results[1];
        results.erase(results.end()-1);
        for (int i=0;i<allWebs.size();i++){
            if (allWebs[i].page==webpage){
                allWebs[i].ingoingWebs.push_back(results[0]);
            }
        }
    }
}

void webGraph::setoutgoing (){
    
    fstream fin;
    fin.open(webGraphFile, ios::in);
    if(!fin){
        cout<<endl<<"Invalid path to web graph file"<<endl;exit(0);
    }
    string line;
    while(fin>>line){
        vector<string> results;
        string webpage;
        tokenize(line, ',',results);
        webpage= results[0];
        results.erase(results.begin());
        for (int i=0;i<allWebs.size();i++){
            if (allWebs[i].page==webpage){
                allWebs[i].outgoingWebs.push_back(results[0]);
            }
        }
    }
}

void webGraph::updateImpressions(){
    
    ofstream myFile(impressionsFile);
    
    for (int i=0;i<allWebs.size();i++){
        myFile<<allWebs[i].page;
        myFile<<",";
        myFile<<allWebs[i].impressions;
        myFile<<endl;
    }
}

void webGraph::updateClicks(){
    
    ofstream myFile(clicksFile);
    
    for (int i=0;i<allWebs.size();i++){
        myFile<<allWebs[i].page;
        myFile<<",";
        myFile<<allWebs[i].clicks;
        myFile<<endl;
    }
}

void webGraph::incImpressions (string x){
    
    for (int i=0;i<allWebs.size();i++){
        if (x==allWebs[i].page)
            allWebs[i].impressions++;
    }
    calcCTR(x);
    calcScore(x);
}

void webGraph::incClicks (string x){
    
    for (int i=0;i<allWebs.size();i++){
        if (x==allWebs[i].page)
            allWebs[i].clicks++;
    }
    calcCTR(x);
    calcScore(x);
}

void webGraph::pageRankCalc(){
    
    for (int i=0; i<allWebs.size();i++){
        allWebs[i].pageRank=(float)1/allWebs.size();
    }
    
        for (int k=0;k<allWebs.size();k++){
        for (int j=0;j<allWebs[k].ingoingWebs.size();j++){
            allWebs[j].pageRank+=(float)(((float)allWebs[j].pageRank)/((float)allWebs[j].outgoingWebs.size()));
        }
    }
}

void webGraph::calcCTR(string x){
    for (int i=0;i<allWebs.size();i++){
        if(allWebs[i].page==x){
            allWebs[i].ctr=allWebs[i].clicks/allWebs[i].impressions;
        }
    }
}

void webGraph::calcScore(string x){
    for (int i=0;i<allWebs.size();i++){
        if (allWebs[i].page==x){
            float PR = allWebs[i].pageRank;
            float imp = allWebs[i].impressions;
            float CTR = allWebs[i].ctr;
            float x= (0.1*imp)/(1+0.1*imp);
            allWebs[i].score=0.4*PR + 0.6*(((1-x)*PR)+(CTR*x));
        }
    }
}

void webGraph::calcScores(){
    for (int i =0;i<allWebs.size();i++){
        calcScore(allWebs[i].page);
    }
}

void webGraph::calcCTRs(){
    for (int i =0;i<allWebs.size();i++){
        calcCTR(allWebs[i].page);
    }
}

void webGraph::initializeAll(){
    
    setWebsites();
    setattributes();
    setClicks();
    setoutgoing();
    setingoing();
    calcCTRs();
    calcScores();
    pageRankCalc();
}

void webGraph::resultDisplay(string site){
    cout<<"You are viewing "<<site<<" "<<endl;
    for (int i=0;i<allWebs.size();i++){
        if (site==allWebs[i].page){
            for(int j=0;j<allWebs[i].attributes.size();j++){
                cout<<allWebs[i].attributes[j]<<endl;
            }break;
        }
    }
}
