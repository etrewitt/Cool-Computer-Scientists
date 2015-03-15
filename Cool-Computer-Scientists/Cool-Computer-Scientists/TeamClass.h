#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#ifndef TEAM_CLASS
#define TEAM_CLASS
class Team{
public:
	Team(){}
	Team(const string& name, const int Pld, const int W, const int D, const int L, const int GF, const int GA, const int GD, const int Pts, char *Grp);
	void operator=(Team& T);
	bool operator<(Team& T);
	bool operator==(Team&T);
	string getName() const;
	int getPlayed() const;
	int getWins() const;
	int getDraws() const;
	int getLoses() const;
	int getGoalsFor() const;
	int getGoalsAgainst() const;
	int getGoalDifference() const;
	int getPoints() const;
private:
	string Name;
	int Played;
	int Wins;
	int Draws;
	int Loses;
	int GoalsFor;
	int GoalsAgainst;
	int GoalDifference;
	int Points;
	char* Group;
};

#endif
