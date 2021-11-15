#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "CommandProcessor.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "MapDriver.h"



using namespace std;

enum GameEngineState { start, mapLoaded, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win, exitGame };
//static const char* enumStateStr[] = { "Start", "Map loaded", "Map validated", "Players added", "Assigned reinforcement", "Issue orders", "Execute orders", "Execute orders", "Assign reinforcement", "Win game", "Exit game", "Start" };

class GameEngine {

private:

    GameEngineState currentState;
    CommandProcessor commandProcessor;
    void loadMap(int index);
    // void addPlayer;
    // void assignCountries;
    // void issueOrder;
    // void endIssueOrders;
    // void execOrder;
    // void endExecOrders;
    // void winGame;
    // void endGame;
    // void playGame;

public:

    // constructors, assignment operator, destructor
    GameEngine(); // constructor for the GameEngine
    GameEngine(const GameEngine& args);
    ~GameEngine(); // destructor for the GameEngine
    GameEngine& operator= (const GameEngine& other) {
        cout << "Assignment operator called" << endl;
        return *this;
    }; // assignment operator for GameEngine
    
    void startGame();

    void receiveCommand(Command command);
    void validateMap();
    string mapName;
    int numberOfPlayers;
    
    Map* mapObject;
    MapLoader* mapLoaderObject;
    
    vector<Player> playersVector;
//    vector<Deck> deckVector;
    Deck deck;

    // stream operator if necessary
    friend ostream& operator<<(ostream& out, const GameEngine& ge);

};
