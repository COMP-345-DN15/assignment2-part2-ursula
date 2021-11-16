#include "GameEngine.h"
#include <iomanip>
#include <algorithm>
// Final names of other .h files TBD
// #include "Player.h"
// #include "Cards.h"

// Game engine class

 //constructor
GameEngine::GameEngine(vector<Player*> t)
{
    this->playerList = t;
}

//destructor
GameEngine::~GameEngine() {
    for (auto p : playerList)
    {
        delete p;
    }
    playerList.clear();
}

bool LessSort(Order* a, Order* b)
{
    return(a->get_type_id() < b->get_type_id());
}

//Calculate player's reinforcement
void GameEngine::reinforcmentPhase()
{
    bool check = false;
    int temp = 0;
    double count = 0;

    for (size_t i = 0; i < (playerList.size()); i++)
    {   //check the player's terriotries
        temp = playerList[i]->getReinforcementPool();
        vector<Territory*> c1 = playerList[i]->toDefend();


        //count the terriorties number

        count = c1.size();
        int s1 = (int)round(count / 3);

        //calcuate the contient bouns
        check = playerList[i]->playerContientBouns();
        cout << temp << endl;

        if (check == true)
        {
            temp += 2 * s1;
        }
        else
        {
            temp = temp + s1;
            cout << temp << endl;


        }
        temp = temp + 3;

        cout << temp << endl;
        playerList[i]->setReinforcementPool(temp);
        check = false;
        temp = 0;
        count = 0;

    }
}
void GameEngine::issueOrdersPhase()
{
    for (size_t i = 0; i < (playerList.size()); i++)
    {
        playerList[i]->issueOrder();

    }

}

void GameEngine::excuteOrderPhase()
{
    vector<Order*> sortOrder;

    for (size_t i = 0; i < (playerList.size()); i++)
    {

        sort(playerList[i]->getOrderList().begin(), playerList[i]->getOrderList().end(), LessSort);
        for (int j = 0; i < playerList[i]->getOrderList().size(); j++)
        {
            playerList[i]->getOrderList()[j]->execute();
        }
    }
}

