
#include <iostream>
#include <ostream>
#include <typeinfo>
#include <cstring>
#include <algorithm>
#include "Player.h"
using namespace std;


//Default constructor
Player::Player(){}

//Parametric construtor 
Player::Player(string pname)
{
    cout << "creating player " << pname << endl;
	name = pname;
//	playerHand = new Hand();
}


// Player destructor
Player::~Player()
{
//	delete cards;
//	cards = nullptr;
	for (auto p : listOfTerritoriesOwned)
	{
        // TODO: This causes a SIGABRT Error on my machine - deleting unassigned memory
//		delete p;
	}
	listOfTerritoriesOwned.clear();

	for (auto p : listOfTerritoriesToDefend)
	{
		delete p;
	}
	listOfTerritoriesToDefend.clear();

	for (auto p : listOfTerritoriesToAttack)
	{
		delete p;
	}
	listOfTerritoriesToAttack.clear();

	for (auto p : listOfOrders)
	{
        cout << "now deleting p: " << *p << endl;
		delete p;
	}
	listOfOrders.clear();
}


//ToAttack() method return a list of territories
vector<Territory*> Player::toAttack() {
	// for now only empty territory list returned
	vector<Territory*> listOfTerritoriesToAttack;
	for (vector<Territory*>::iterator it = listOfTerritoriesToAttack.begin(); it != listOfTerritoriesToAttack.end(); ++it) {
		listOfTerritoriesToAttack.push_back(*it);
		std::cout << *it << std::endl;
	}
	
	return listOfTerritoriesToAttack;
}

//ToDefend() method return a list of territories
vector<Territory*> Player::toDefend() {
	// for now only empty territory list returned
	vector<Territory*> listOfTerritoriesToDefend;
	for (vector<Territory*>::iterator it = listOfTerritoriesToDefend.begin(); it != listOfTerritoriesToDefend.end(); ++it) {
		listOfTerritoriesToDefend.push_back(*it);
		std::cout << *it << std::endl;
	}
	return listOfTerritoriesToDefend;
}

//IssueOrder() will creat a order obj and add it to player's order list
void Player::issueOrder()
{	//every time make a new order obj there will be a printout to show it works
    vector<Order*> listOfOrders;
	Order* ord = new Bomb();
	listOfOrders.push_back(ord);
	std::cout << *ord << std::endl;
}
void  Player::print()
{
	cout << "this is player:"<<name<<endl;
}

//Army::Army(int armyNumber) {
//    this->armyNumber = armyNumber;
//}

