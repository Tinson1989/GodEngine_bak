#include<iostream>
#include"Foundation/Asset.hpp"
#include"Foundation/EngineConfig.hpp"
#include <crtdbg.h>
int main(){
    std::cout << "EngineVersion:" << Engine_Version_Major << "." << Engine_Version_Minor << std::endl;
    std::cout << "EngineBuildType" << BUILD_TYPE << std::endl;
    int a = 1, b = 2;
    GOD_ASSERT(a > b, "XXXXXXXXXXXX");
    std::cout << "X ___________ DEBUG" << std::endl;

    return 0;
}