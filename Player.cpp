#include <iostream>
#include <ostream>
#include <typeinfo>
#include <cstring>
#include <algorithm>
#include "Player.h"
using namespace std;


//Default constructor
Player::Player()
{
	name = "default";
	int reinforcementPool = 0;
	vector<Territory*> territory;
	vector<Cards*> handCard;
	vector<Order*> listOfOrders;
}


//Parametric construtor 
Player::Player(string pname)
{
	name = pname;
}

//Copy constructor (Deep copy)
Player::Player(const Player& p)
{
	this->reinforcementPool = p.reinforcementPool;
	this->name = p.name;
	this->territory = p.territory;
	this->handCard = p.handCard;
	this->listOfOrders = p.listOfOrders;

}

//Four parmeter constructor
Player::Player(int reinforcementPool, string name, vector<Territory*> t, vector<Cards*> h, vector<Order*> o)
{
	this->reinforcementPool = reinforcementPool;
	this->name = name;
	this->territory = t;
	this->handCard = h;
	this->listOfOrders = o;
}

//added assignment operator
Player& Player::operator=(const Player& player)
{
	this->name = player.name;
	this->reinforcementPool = player.reinforcementPool;
	this->territory = player.territory;
	this->handCard = player.handCard;
	this->listOfOrders = player.listOfOrders;
	return *this;
}

// Player destructor
Player::~Player()
{
	for (auto p : handCard)
	{
		delete p;
	}
	handCard.clear();

	for (auto p : territory)
	{
		delete p;
	}
	territory.clear();

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
		delete p;
	}
	listOfOrders.clear();

	for (auto p : handCard)
	{
		delete p;
	}
	handCard.clear();
}

string Player::getName() {
	return this->name;
}

void Player::setName(string s) {
	this->name = s;
}

int Player::getReinforcementPool() {
	return this->reinforcementPool;
}

void Player::setReinforcementPool(int i) {
	this->reinforcementPool = i;
}

void Player::setTerritory(Territory t)
{

	this->territory.push_back(&t);
}

vector<Territory*> Player::getTerritory()
{
	return territory;

}

vector<Territory*> Player::get_neighbour_territories(vector<Territory*> Map)
{
	vector<Territory*> neighbouring_terrritories;
	for (size_t i = 0; i < territory.size(); i++)
	{
		for (size_t j = 0; j < Map.size(); j++)
		{
			if (!territory[i]->getTerritoryOwner().compare(Map[j]->getTerritoryOwner()))
			{
				for (int k = 0; k < neighbouring_terrritories.size(); k++)
				{
					if (!neighbouring_terrritories[k]->getTerritoryOwner().compare(Map[j]->getTerritoryOwner()) || neighbouring_terrritories.empty())
					{
						neighbouring_terrritories.push_back(Map[j]);
					}
				}

			}
		}

	}

	return neighbouring_terrritories;

}


vector<Cards*> Player::getCard()
{
	return handCard;
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
{
	//Display territories that can be attack or defend
	vector<Territory*> AttackList;
	AttackList = toAttack();
	vector<Territory*> DefendList;
	DefendList = toDefend();

	//Deploy order until no armies left	
	while (getReinforcementPool() != 0)
	{
		int army = getReinforcementPool();

		for (size_t i = 0; i < DefendList.size(); i++)
		{

			int temp = rand() % (army + 1);
			cout << temp << endl;
			temp += DefendList[i]->getArmyAmount();
			DefendList[i]->setArmyAmount(temp);
			army = temp - army;
			setReinforcementPool(army);
			if (army == 1)
			{
				temp = 1;
				temp += DefendList[i]->getArmyAmount();
				DefendList[i]->setArmyAmount(temp);
				setReinforcementPool(0);
			}
		}
	}
	//Advance order
	srand((unsigned int)time(NULL));
	int actionNumber = rand() % AttackList.size();

	int Enemy = AttackList[actionNumber]->getArmyAmount();
}

bool Player::playerContientBouns()
{
	string a = "NA";
	string b = "AS";
	string c = "SA";
	string d = "AU";
	string e = "EU";
	string f = "AF";

	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0;
	for (size_t i = 0; i < territory.size(); i++)
	{
		string temp = (*territory[i]).getContinent();
		if (temp.compare(a) == 0)
		{
			c1++;
		}
		if (temp.compare(b) == 0)
		{
			c2++;
		}
		if (temp.compare(c) == 0)
		{
			c3++;
		}
		if (temp.compare(d) == 0)
		{
			c4++;
		}
		if (temp.compare(e) == 0)
		{
			c5++;
		}
		if (temp.compare(f) == 0)
		{
			c6++;
		}


	}
	if (c1 == 3) { return true; }//NA 
	if (c2 == 3) { return true; }//AS
	if (c3 == 1) { return true; }//SA
	if (c4 == 1) { return true; }//AU
	if (c5 == 1) { return true; }//EU
	if (c6 == 1) { return true; }//EU



	return false;
}

vector<Order*> Player::getOrderList()
{

	return listOfOrders;
}


void Player::printOrder()
{

	for (size_t i = 0; i < listOfOrders.size(); i++) {
		cout << "<" << listOfOrders.at(i)->getResult() << "> ";
	}
	cout << endl;
}

void  Player::print()
{
	cout << "this is player:"<<name<<endl;
}


