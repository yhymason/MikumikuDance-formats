#include "Vmd.h"
#include "Pmd.h"
#include "Pmd.cpp"
#include <iostream>
#include <fstream>
#include <iomanip>

#ifndef __unix__
#define utfcout std::wcout
#else
#define utfcout std::cout
#endif


int main(int argc, char *argv[]) {

    vmd::VmdMotion motion;
    motion.LoadFromFile("Bad Romance.vmd");
    //std::cout << "here" << std::endl;
    //pmd::PmdModel model;
    //model.LoadFromFile("Miku_Hatsune.pmd");
    return 0;
}
