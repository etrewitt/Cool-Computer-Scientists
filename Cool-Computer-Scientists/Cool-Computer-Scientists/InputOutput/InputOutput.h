#ifndef INPUTOUTPUT_H           // avoid repeated expansion
#define INPUTOUTPUT_H

using namespace std;

class Team {
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

public:
	// constructor
	Team(const string& name, const int Pld, const int W, const int D, const int L, const int GF, const int GA, const int GD, const int Pts, char *Grp);
	~Team();

};

#endif
