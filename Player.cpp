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
vector<Territory*> Player::toAttack() 
{
	vector<Territory*> listOfTerritoriesToAttack;
	
	for (int i = 0; i < territory.size(); i++)
	{
		string temp = getName();
		if (!temp.compare(territory[i]->getTerritoryOwner())==0)
			listOfTerritoriesToAttack.push_back(territory[i]);

	}
	cout << "The list of territories that can be Attack by " << getName() << endl;
	for (int i = 0; i <listOfTerritoriesToAttack.size(); i++)
	{
		cout <<"Index "<<i<< " "<<(*listOfTerritoriesToAttack[i]).getTname() << " "<<(*AlistOfTerritoriesToAttack[i]).getContinent()<< endl;
	}
	return listOfTerritoriesToAttack;
}


//ToDefend() method return a list of territories
vector<Territory*> Player::toDefend() 
{
		vector<Territory*> listOfTerritoriesToDefend;
		
		for (int i = 0; i < territory.size(); i++)
		{
			if (getName().compare(territory[i]->getTerritoryOwner())==0)

				listOfTerritoriesToDefend.push_back(territory[i]);
		}

		cout << "The list of territories that can be Defend by "<< getName() << endl;
		for (int i = 0; i < listOfTerritoriesToDefend.size(); i++)
		{
			cout << "Index " << i << " " << (*listOfTerritoriesToDefend[i]).getTname() << " " << (*listOfTerritoriesToDefend[i]).getContinent() << endl;
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
	//Advance order Attack

	int actionNumber1 = rand() % AttackList.size();
	int Enemy = AttackList[actionNumber1]->getArmyAmount();

	int actionNumber2 = rand() % DefendList.size();
	int Attack = DefendList[actionNumber2]->getArmyAmount();

	if (Enemy >= Attack)
	{
		Enemy = Enemy - Attack;
		AttackList[actionNumber1]->setArmyAmount(Enemy);
		DefendList[actionNumber2]->setArmyAmount(0);
	}
	else
	{
		Attack = Attack - Enemy;
		AttackList[actionNumber1]->setArmyAmount(Attack);
		DefendList[actionNumber2]->setArmyAmount(0);
		AttackList[actionNumber1]->setTerritoryOwner(getName());
	}
	//Advance order Defend

	int actionNumber3 = rand() % AttackList.size();
	int Defend1 = DefendList[actionNumber1]->getArmyAmount();

	int actionNumber4 = rand() % DefendList.size();
	int Defend2 = DefendList[actionNumber2]->getArmyAmount();

	if (actionNumber3 != actionNumber4) 
	{
		DefendList[actionNumber3]->setArmyAmount(0);
		DefendList[actionNumber4]->setArmyAmount(Defend2 + Defend1);
	}

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

void Player::setOrder(Order* a) 
{
	orderList.push_back(a);
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


