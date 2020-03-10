#include "pch.h"
#include "ArgumentManager.h"
#include "Game.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	// Incorrect Arg Handling
    if (argc != 2 && argc !=3) {
        cout << "Usage: ./ga2 input=<file> output=<file>" << endl;
        cout << "Input: Text file with a list of ages" << endl;
        return -1;
    }

    // Get input output info
    ArgumentManager am(argc, argv);
    string infilename = am.get("input");
    string outfilename = am.get("output");

    // Get team and put them on the court/bench
	Team team; Court court; Bench bench;
	team.getPlayersFromFile(infilename);
    getPlayersOnCourt(5,&team,&court);
    getPlayersOnBench(&team, &bench);

    // Game sim
    Game game(&court, &bench);
    game.quarter(12);

    // Console out see if players in properly
    printInfo(&team, &court, &bench);
}