//
//  main.cpp
//  Comp345-A2
//
//  Created by J'vlyn d’Ark on 11/3/21.
//

#include "GameEngineDriver.h"
#include "GameEngine.h"
#include "OrdersDriver.h"
#include "PlayerDriver.h"
#include "CardsDriver.h"
#include "MapDriver.h"

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    testGameEngine(); // uncomment to run GameEngine class
//    OrdersTest(); // uncomment to run Orders class
    testPlayer(); // uncomment to run Player class
    //testCards(); // uncommment to run Cards class
//    testMap(); // uncomment to run Map class
    
    cout << "completed program." << endl;
    return 0;
}
