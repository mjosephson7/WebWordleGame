//Author: Matthew Josephson
//Description: Stats the program in main
//Oct 4, 2023

#include <Wt/WApplication.h>
#include "wordle.h"

int main(int argc, char **argv) 
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        
        return std::make_unique<wordle>(env);
        
        
    });
}


