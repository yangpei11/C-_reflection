//
//  main.cpp
//  function_pointer
//
//  Created by yangpei on 2018/9/19.
//  Copyright © 2018年 yangpei. All rights reserved.
//

#include <iostream>
#include <map>

using namespace std;

typedef void* (*x)(void);

class ClassFactory{
private:
    map<string, x>classMap;
    ClassFactory(){};
    
public:
    void* getClassByName(string name);
    void registClass(string name,x method);
    static ClassFactory& getInstance();
};

void* ClassFactory::getClassByName(string name){
    map<string, x>::iterator it = classMap.find(name);
    if(it ==  classMap.end()){
        return NULL;
    }
    x xx = it->second;
    return xx();
}

void ClassFactory::registClass(string name, x method){
    classMap[name] = method;
}

ClassFactory& ClassFactory::getInstance(){
    static ClassFactory cc;
    return cc;
}

class T{
public:
    void print(){
        cout << "T is built" << endl;
    }
};

void* createT(){
    T* s = new T;
    return s;
}


int main(int argc, const char * argv[]) {
    ClassFactory::getInstance().registClass("T", createT);
    T* s = (T*)ClassFactory::getInstance().getClassByName("T");
    s->print();
    return 0;
}
