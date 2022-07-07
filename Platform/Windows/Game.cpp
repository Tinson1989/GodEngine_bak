#include<iostream>
#include"Foundation/Asset.hpp"
#include <crtdbg.h>
int main(){
    std::cout << "EngineVersion:" << "0.0.1" << std::endl;
    std::cout << "EngineBuildType" << BUILD_TYPE << std::endl;
    int a = 1, b = 2;
    GOD_ASSERT(a > b, "XXXXXXXXXXXX");
    std::cout << "X ___________ DEBUG" << std::endl;

    return 0;
}