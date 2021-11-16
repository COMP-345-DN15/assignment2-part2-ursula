#include "GameEngine.h"
#include <iomanip>
#include <algorithm>
// Final names of other .h files TBD
// #include "Player.h"
// #include "Cards.h"

int main()
{
	//game Map1
	vector <Territory*> Map1;
	Territory a1("Canada", "NA", "Player1", 0);
	Territory a2("USA", "NA", "Player1", 0);
	Territory a3("Maxico", "NA", "Player1", 0);
	Territory a4("Europe", "EU", "Player2", 0);
	Territory a5("Africa", "AF", "Player2", 0);
	Territory a6("SouthAmerica", "SA", "Player2", 0);
	Territory a7("Russia", "AS", "Player2", 0);
	Territory a8("China", "AS", "Player3", 0);
	Territory a9("Japan", "AS", "Player3", 0);
	Territory a10("Australia", "AU", "Player3", 0);
	Map1.push_back(&a1);
	Map1.push_back(&a2);
	Map1.push_back(&a3);
	Map1.push_back(&a4);
	Map1.push_back(&a5);
	Map1.push_back(&a6);
	Map1.push_back(&a7);
	Map1.push_back(&a8);
	Map1.push_back(&a9);
	Map1.push_back(&a10);

	vector<Cards*> card1;
	vector<Cards*> card2;
	vector<Cards*> card3;

	vector<Order*> Orderlist1;
	vector<Order*> Orderlist2;
	vector<Order*> Orderlist3;

	vector<Player*> playerList;
	playerList.push_back(new Player(10, "Player1", Map1, card1, Orderlist1));
	playerList.push_back(new Player(20, "Player2", Map1, card1, Orderlist1));
	playerList.push_back(new Player(40, "Player3", Map1, card1, Orderlist1));
	GameEngine game(playerList);



	bool check = true;

	while (check)
	{
		game.reinforcmentPhase();
		game.issueOrdersPhase();
		game.excuteOrderPhase();

		for (size_t i = 0; i < playerList.size(); i++)
		{
			if (playerList[i]->toDefend().size() == 10 || playerList.size() == 1)
			{
				cout << "Winner is " << playerList[i]->getName() << endl;
				check = false;
			}
			if (playerList[i]->toDefend().size() == 0)
			{
				cout << playerList[i]->getName() << " lost the game." << endl;
				playerList.erase(playerList.begin() + i);
			}
		}
	}
	return 0;
}
