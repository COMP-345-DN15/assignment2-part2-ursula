
#include <iostream>
#include <vector>
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;

//struct Army {
//    int armyNumber;
//    Army(int armyNumber);
//};

class Player {

public:
	
	string name;
	// vectors that contain a list of Territory objects
	vector<Territory*> listOfTerritoriesOwned;
	vector<Territory*> listOfTerritoriesToAttack;
	vector<Territory*> listOfTerritoriesToDefend;
    // vector that contains a list of Order objects
    vector<Order*> listOfOrders;

	Player();
	Player(string pname);
	~Player();
	// methods that return corresponding list
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();

	// methods that create and add an order to list of orders.
	void issueOrder();
	void print();
//    vector<Hand> cards;

//    vector<Hand> cardsHandVector;
    Hand playerHand;
    
//    vector<Army> reinforcementPool;
    vector<int> reinforcementPool;

private:

	// vector that contains a list of Card objects
//	Hand* cards;
    

};

