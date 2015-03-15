#include <iostream>
#include <cstdlib>
#include <string>
#include "TeamClass.h"
using namespace std;


Team::Team(const string& name, const int Pld, const int W, const int D, const int L, const int GF, const int GA, const int GD, const int Pts, char *Grp) {
	Name = name;
	Played = Pld;
	Wins = W;
	Draws = D;
	Loses = L;
	GoalsFor = GF;
	GoalsAgainst = GA;
	GoalDifference = GD;
	Points = Pts;
	Group = Grp;
}

void Team::operator=(Team& T)
{
	Name = T.Name;
	Played = T.Played;
	Wins = T.Wins;
	Draws = T.Draws;
	Loses = T.Loses;
	GoalsFor = T.GoalsFor;
	GoalsAgainst = T.GoalsAgainst;
	GoalDifference = T.GoalDifference;
	Points = T.Points;
	Group = T.Group;
}

bool Team::operator==(Team&T)
{
	return Name == T.Name;
}
bool Team::operator<(Team& T)
{
	return Name < T.Name;
}
string Team::getName() const
{
	return Name;
}
int Team::getPlayed() const
{
	return Played;
}
int Team::getWins() const
{
	return Wins;
}
int Team::getDraws() const
{
	return Draws;
}
int Team::getLoses() const
{
	return Loses;
}
int Team::getGoalsFor() const
{
	return GoalsFor;
}
int Team::getGoalsAgainst() const
{
	return GoalsAgainst;
}
int Team::getGoalDifference() const
{
	return GoalDifference;
}
int Team::getPoints() const
{
	return Points;
}
