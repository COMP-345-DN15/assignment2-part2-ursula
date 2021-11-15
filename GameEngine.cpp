// Final names of other .h files TBD
#include "GameEngine.h"
#include "CommandProcessor.h"


using namespace std;

// Final names of other .h files TBD
// #include "Player.h"
// #include "Cards.h"

// Game engine class


GameEngine::GameEngine()
{
    // default constructor

    currentState = start;
    commandProcessor = CommandProcessor();
}

GameEngine::GameEngine(const GameEngine& other) {
    cout << "Copy constructor called" << endl;
    currentState = other.currentState;
} // copy constructor for GameEngine

//GameEngine::GameEngine(const GameEngine& gameEngine) {
    // copy constructor
   // currentState = start;
  //  cout << "Game engine copied" << endl;
//}

GameEngine::~GameEngine()
{
    // something here will be a nullptr
    //destructor

}

//GameEngine& GameEngine::operator = (const GameEngine& gameEngine) {
    // stuff to put here
  //  return *this;
//}

/*ostream& operator << (ostream& out, const GameEngine& gameEngine) {

     stream insertion operator
     out << all things

}*/

void GameEngine::startGame()
{
    while (true)
    {
        /* Get the next command to act on. */
        Command nextCommand = commandProcessor.getCommand();

        /* Acts on the command. */
        receiveCommand(nextCommand);
    }
}

void GameEngine::receiveCommand(Command command)
{
    //commands are only valid depending on the state I am in

    switch (currentState)
    {
    case start:
        if (command.name.compare("loadMap") == 0)
        {
            
            cout << "Please select a Map from the list by typing the number and pressing enter: " << endl;
            getMapNames();
            int userMapChoice = 0;
            cin >> userMapChoice;
            // call to loadMap transition
             loadMap(userMapChoice);
            // transition states and update currentState
            currentState = mapLoaded;
            cout << "Current game state is: Map Loaded" << endl;
        }
        else {
            //invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case mapLoaded:
        if (command.name.compare("validateMap") == 0)
        {
            // call to validateMap transition
             validateMap();
            // transition states and update currentState
            currentState = mapValidated;
            cout << "Current game state is: Map Validated" << endl;
        }
        else if (command.name.compare("loadMap") == 0)
        {
            // call to issueOrder transition
            // loadMap();
            // transition states and update currentState
            currentState = mapLoaded;
            cout << "Current game state is: Map Loaded" << endl;
        }
        else {
           // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case mapValidated:
        // Part 2.3
        // enter players in the game
        if (command.name.compare("addPlayer") == 0)
        {
            numberOfPlayers = 0;
            int desiredPlayers = 0;
            bool validPlayers = false;
            while(!validPlayers) {
                cout << "How many players would you like to add? Please enter between 2-6 players: " << endl;
                cin >> desiredPlayers;
                if(desiredPlayers > 6 || desiredPlayers < 2) {
                    cout << "You must select between 2-6 players." << endl;
                } else {
                    validPlayers = true;
                }
            }
//            playersVector.resize(desiredPlayers);
            int i = 0;
            while(numberOfPlayers < desiredPlayers) {
                // call to validateMap transition
                string playerName = "";
                cout << "Please enter player" << i+1 << " name: " << endl;
                
                cin >> playerName;
    //             addPlayer();
                Player* player = new Player(playerName);
                numberOfPlayers++;
                playersVector.push_back(*player);
                cout << "player at " << i << " = " << player->name << endl;
                i++;
            }
            
            // transition states and update currentState
            currentState = playersAdded;
            cout << "Current game state is: Players Added" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case playersAdded:
        // Part 2.4
        // gamestart command
        if (command.name.compare("assignCountries") == 0)
        {
            // Part 2.4a
            // Distribute countries to players
            cout << "Now assigning countries..." << endl;
            cout << "here are the number of countries: " << mapLoaderObject->mapObject->territoryCount << endl;
            int countriesPerPlayer = mapLoaderObject->mapObject->territoryCount / numberOfPlayers;
            cout << "each player will be assigned " << countriesPerPlayer << endl;
            
            cout << "here are the current players and their countries: " << endl;
            
            for(int i = 0; i < playersVector.size(); i++) {
                cout << "playerVector at " <<i << " = " << playersVector.at(i).name << endl;
            }
            
            for(int i = 0; i < numberOfPlayers; i++) {
                cout << "i = " << i << endl;
                playersVector.at(i).listOfTerritoriesOwned.resize(countriesPerPlayer);
                cout << playersVector.at(i).name << " will receive countries: "<< endl;
                for(int j = 0; j < countriesPerPlayer; j++) {
                    cout << j+(countriesPerPlayer*i) << endl;
                    playersVector.at(i).listOfTerritoriesOwned.at(j) = &mapLoaderObject->mapObject->terrVector.at(j+(countriesPerPlayer*i));
                    cout << playersVector.at(i).listOfTerritoriesOwned.at(j)->territoryName << endl;
                    
                }
                    
            }
            cout << "here are the number of countries: " << mapLoaderObject->mapObject->territoryCount << endl;
            
            // Part 2.4b
            // Randomly determine order of players
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

            shuffle(playersVector.begin(), playersVector.end(), default_random_engine(seed));
            cout << "The order of players will be: " << endl;
            for(int i = 0; i < playersVector.size(); i++) {
                cout << playersVector.at(i).name << endl;
            }
            
            // Part 2.4c
            // Give 50 initial armies to the players
            
            for(int i = 0; i < numberOfPlayers; i++) {
                playersVector.at(i).reinforcementPool.resize(50);

                for(int j = 0; j < 50; j++) {
//                    Army army(j);
//                    playersVector.at(i).reinforcementPool.at(j) = army;
                    playersVector.at(i).reinforcementPool.at(j) = j+1;

                    
                }
            }
            
            // test the reinforcement pool
            for(int i = 0; i < numberOfPlayers; i++) {
                cout << "Player " << playersVector.at(i).name << " has " << endl;
                 for(int j = 0; j < 50; j++) {
//                     cout << playersVector.at(i).reinforcementPool.at(j).armyNumber;
                     cout << playersVector.at(i).reinforcementPool.at(j);

                }
                cout << "armies" << endl;
            }
            
            
            // Part 2.4d
            // Players draw 2 cards from deck and cards are added to player's hand
            Deck* deck = new Deck();
            Cards card;
            
            for(int i = 0; i < (numberOfPlayers); i++) {
                playersVector.at(i).playerHand.cardsHandVector.resize(2);
//                Hand* hand = new Hand();
//                playersVector.at(i).playerHand = hand;
                for(int j = 0; j < 2; j++) {
                    card = deck->draw();
                    
                    playersVector.at(i).playerHand.cardsHandVector.at(j) = card;
                    cout << "player " << playersVector.at(i).name << " receives card: " << card.display_card() << endl;
                }
            }
            
            
            // TODO: switch to "gamestart" phase -> "play" phase
            // transition states and update currentState
            currentState = assignReinforcement;
            cout << "Current game state is: Assign Reinforcements" << endl;
        }
        else if (command.name.compare("addPlayer") == 0)
        {
            // call to issueOrder transition
            // addPlayer();
            // transition states and update currentState
            currentState = playersAdded;
            cout << "Current game state is: Players Added " << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case assignReinforcement:
        if (command.name.compare("issueOrder") == 0)
        {
            // call to assignCountries transition
            // assignCountries();
            // transition states and update currentState
            currentState = issueOrders;
            cout << "Current game state is: Issue Orders" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case issueOrders:
        if (command.name.compare("endIssueOrders") == 0)
        {
            // call to issueOrder transition
            // issueOrder();
            // transition states and update currentState
            currentState = executeOrders;
            cout << "Current game state is: Execute Orders" << endl;
        }
        else if (command.name.compare("issueOrder") == 0)
        {
            // call to issueOrder transition
            // issueOrder();
            // transition states and update currentState
            currentState = issueOrders;
            cout << "Current game state is: Issue Orders" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case executeOrders:
        if (command.name.compare("endExecOrders") == 0)
        {
            // call to endIssueOrders transition
            // endIssueOrders();
            // transition states and update currentState
            currentState = assignReinforcement;
            cout << "Current game state is: Assign Reinforcements" << endl;
        }
        else if (command.name.compare("execOrder") == 0)
        {
                // call to execOrder transition
                // execOrder();
                // transition states and update currentState
                currentState = executeOrders;
                cout << "Current game state is: Execute Orders" << endl;
        }
        else if (command.name.compare("winGame") == 0)
        {
            // call to endExecOrders transition
            // endExecOrders();
            // transition states and update currentState
            currentState = win;
            cout << "Current game state is: Win" << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    case win:
        if (command.name.compare("endGame") == 0)
        {
            // call to exit game
            // transition states and update currentState
            cout << "You have ended the game" << endl;
        }
        else if (command.name.compare("playGame") == 0)
        {
            // call to playGame transition
            // start();
            // transition states and update currentState
            currentState = start;
            cout << "Current game state is: Start " << endl;
        }
        else {
            // invalid state transition for current state
            cout << "A state transition could not be made because the command from this state is invalid." << endl;
        }
        break;

    //case exitGame:
        //if (command == GameEngineCommand::endGame)
        //{
            // call to endGame transition
            // endGame();
            // transition states and update currentStat
            //currentState = exitGame;
            //cout << "Current game state is: " << enumStateStr[GameEngineCommand::endGame] << endl;
        //}
        //else {
            // invalid state transition for current state
            //cout << "A state transition could not be made because the command from this state is invalid." << endl;
        //}
        //break;
     
    default:
        // The command received was not part of valid commands, print error message
        cout << "The command entered is invalid." << endl;
        break;

    }
}

void GameEngine::loadMap(int index) {
    
    string mapPath = "";
    string path = "/Users/jvlyndark/Documents/School/COMP 345/Assignments/Assignment 2/Comp345-A2/Comp345-A2/maps/";
    
    int i = 0;
    for(const auto &entry : std::filesystem::directory_iterator(path)) {
        i++;
        if(i == index) {
            mapPath = entry.path();
            mapName = mapPath.substr(path.length(), 100);
            mapName = mapName.substr(0, (mapName.length() - 4));
        }
    }
    
    
    this->mapLoaderObject = new MapLoader(mapPath);

    //maybe add the map to my map array?
    //set the current map to this?
}

void GameEngine::validateMap() {
    // validate map selected by user
    cout << "Now validating " << mapName << " map" << endl;
    mapLoaderObject->mapObject->validate();
}

