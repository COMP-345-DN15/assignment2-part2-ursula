
#include <iostream>
#include <vector>
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#pragma once
using namespace std;


class Player {

public:
	
	string name;
	// vectors that contain a list of Territory objects
	vector<Territory*> territory;
	vector<Territory*> listOfTerritoriesToAttack;
	vector<Territory*> listOfTerritoriesToDefend;

	Player();// Default constructor
	Player(string pname);
	Player(const Player& p); //Copy constructor
	Player(int, string, vector<Territory*> territories, vector<Cards*> handCard, vector<Order*> order); //Constructor
	~Player();
	Player& operator = (const Player&);

	// methods that return corresponding list
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	vector<Order*> getOrderList();
	vector<Cards*> getCard();
	vector<Territory*> getTerritory();
	vector<Territory*> get_neighbour_territories(vector<Territory*>);

	// methods that create and add an order to list of orders.
	void issueOrder();
	string getName();
	void setName(string);
	int getReinforcementPool();
	void setReinforcementPool(int);
	void setTerritory(Territory);
	void setOrder(Order*);	
	void printOrder();
	bool playerContientBouns();
	void print();

private:

	int reinforcementPool;
	// vector that contains a list of Order objects
	vector<Order*> listOfOrders;

	// vector that contains a list of Card objects
	vector<Cards*> handCard;

	//friend classes
	friend class Cards;
	friend class GameEngine;
	friend class Map;
};
