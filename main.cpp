#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "include/data.h"

int main(){
    data myData;
    std::string str;
    std::string path = "20170922_Cessna172_200Hz_Ref.txt";
    std::ifstream Fin;
    Fin.open(path);
    std::istringstream iss(str);
    int tokenCount = 0;
    std:: string token;
    while (std::getline(Fin, str)){
        ++tokenCount;
        while(iss >> token)
        switch(tokenCount){
            case 1: int t = myData.readTime(token);
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
        }
    }
}