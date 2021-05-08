#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "webGraph.h"
#include "keywordIntake.h"
using namespace std;

#include <unistd.h>
#include <term.h>

void cls()
  {
      for (int i=0;i<10;i++)
      cout<<endl;
  }
bool compareByScore(const websites &a,const websites  &b)
{
    return (a.score > b.score);
}


vector<websites> Search(webGraph fullGraph, Keywords Input){
    vector<string> keywordInputs, results;
    
    if (Input.getAND()){
        for (int i=0;i<fullGraph.returnAllWebs().size();i++){ int count=0;
            for (int j=0;j<fullGraph.returnAllWebs()[i].attributes.size();j++){
                for (int k=0; k<Input.getSearchWords().size();k++){
                    if (fullGraph.returnAllWebs()[i].attributes[j]==Input.getSearchWords()[k]){
                        count++;
                    }
                }
            }
            if(count ==Input.getSearchWords().size()){
                results.push_back(fullGraph.returnAllWebs()[i].page);
            }
            count =0;
        }
    }

    else{
        for (int k=0; k<Input.getSearchWords().size();k++){
            for (int i=0;i<fullGraph.returnAllWebs().size();i++){
                for (int j=0;j<fullGraph.returnAllWebs()[i].attributes.size();j++){
                    if (fullGraph.returnAllWebs()[i].attributes[j]==Input.getSearchWords()[k]){
                        results.push_back(fullGraph.returnAllWebs()[i].page);}}}}}
    
    sort( results.begin(), results.end() );
    results.erase( unique( results.begin(), results.end() ), results.end() );
    vector<websites> resultWebs;
    for (int i=0;i<results.size();i++){
        for (int j=0;j<fullGraph.returnAllWebs().size();j++){
            if(fullGraph.returnAllWebs()[j].page==results[i]){
                websites x =fullGraph.returnAllWebs()[j];
                fullGraph.incImpressions(results[i]);
                fullGraph.updateImpressions();
                resultWebs.push_back(x);
            }
        }
    }
    
    sort(resultWebs.begin(), resultWebs.end(), compareByScore);
    return resultWebs;
}

void searching(){
    webGraph fullGraph;
    vector<websites> results;
    Keywords Input;
    fullGraph.initializeAll();
    int chooseFinal=0;
    int choice=0;
do{
    cout<< "Welcome to my search engine, please choose an option:"<<endl;
    cout<<"1. New Search"<<endl<<"2. Quit"<<endl;
    cout<<"type in your choice: ";
    cin>>choice;
    //getchar();
    while(choice!=1&&choice!=2){
        cout<<"Invalid Entry! Please try again"<<endl;
        cout<<"type in your choice: ";
        cin>>choice;
        //getchar();
    }
    switch (choice) {
        case 2:{
            fullGraph.updateClicks();
            fullGraph.updateImpressions();
            chooseFinal=0;
            exit(1);
            break;}
        case 1:{
            Input.setall();
            break;}
        default:
            break;
    }
    cls();
    results=Search(fullGraph, Input);
    
    if (results.size()==0){
        cout<<endl<<"No results Found"<<endl;
        searching();
    }
    
    do{
    cout<<"Search Results"<<endl;
    int resultcount=0;
    for ( resultcount=0;resultcount<results.size();resultcount++){
        cout<<resultcount+1<<". "<<results[resultcount].page<<endl;
    }
//        <<"please choose the website or new search:"<<endl
        cout<<endl<<"what would you like to do"<<endl<<"1. open a website"<<endl<<"2. New Search"<<endl<<"3. Exit"<<endl;
    int choose=0;
        cout<<endl;
        cout<<"type in your choice: ";
    cin>>choose;
        getchar();
        while (choose!=1 && choose!=2&& choose!=3){
            cout<<endl<<"Invalid Entry Please Try Again"<<endl;
            cout<<"type in your choice: ";
            cin>>choose;
            getchar();
        }
        
   if (choose==1){
       cout<<"Search Results"<<endl;
       int resultcount=0;
       for ( resultcount=0;resultcount<results.size();resultcount++){
           cout<<resultcount+1<<". "<<results[resultcount].page<<endl;
       }
       cout<<"choose website"<<endl;
       cout<<"type in your choice: ";
       cin>>choose;
       getchar();
       fullGraph.incClicks(results[choose-1].page);
       fullGraph.updateClicks();
       cout<<endl<<"You are now viewing website "<<results[choose-1].page<<endl;
       cout<<endl<<"what would you like to do?"<<endl<<"1. Back to search results"<<endl<<"2. New Search"<<endl<<"3. Exit"<<endl;
       cout<<"type in your choice: ";
       cin>>chooseFinal;getchar();
       while (chooseFinal!=1 && chooseFinal!=2&& chooseFinal!=3){
           cout<<endl<<"Invalid Entry Please Try Again"<<endl;
           cin>>chooseFinal;
           getchar();
       }
                if (chooseFinal==1)
                    Search(fullGraph, Input);
                else if (chooseFinal ==2)
                    searching();
                else
                    exit(1);
            
        
   }
    else if (choose==2){
        searching();
    }
    else if (choose ==3){
        fullGraph.updateClicks();
        fullGraph.updateImpressions();
    }
    }
        while(chooseFinal==1);
    chooseFinal=0;}while (choice ==1);
}


void searchings(){
    webGraph fullGraph;
    vector<websites> results;
    Keywords Input;
    fullGraph.initializeAll();
    
    
    
}
