#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "include/data.h"
bool alignmentFlag = false;

int main(){
    data myData;
    std::string str;
    std::string path = "20170922_Cessna172_200Hz_Ref.txt";
    std::ifstream Fin;
    Fin.open(path);
    
    while (std::getline(Fin, str)){
        std::istringstream iss(str);
        int tokenCount = 0;
        std:: string token;
        while(iss >> token){
            switch(tokenCount){
                case 1: double time = myData.readTime(token);
                case 2: double gyroX = myData.readGyroX(token);
                case 3: double gyroY = myData.readGyroY(token);
                case 4: double gyroZ = myData.readGyroZ(token);
                case 5: double accelX = myData.readAccelX(token);
                case 6: double accelY = myData.readAccelY(token);
                case 7: double accelZ = myData.readAccelZ(token);
                case 8: double roll_0 = myData.readRoll_0(token);
                case 9: double pitch_0 = myData.readPitch_0(token);
                case 10: double yaw_0 = myData.readYaw_0(token);
                case 13: double fi_0 = myData.readFi_0(token);
                case 14: double lambda_0 = myData.readLambda_0(token);
                case 15: double height = myData.readHeight(token);
            }
        }
    }

    if(!alignmentFlag){
        
    }
}