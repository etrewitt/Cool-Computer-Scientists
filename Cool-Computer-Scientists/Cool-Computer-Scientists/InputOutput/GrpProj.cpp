/*
Mike Strain
DeAnza College
CIS 22C Winter 2015
Group Project
Microsoft Visual Studio 2013 Ultimate

Complete implementing the template based Linked List from Chapter 3.
The linked list source code is listed under SLinkedList.* files (there are 5 files).
Read the CreditCard.csv file from lab0 and store it in the linked list.
After storing it in the linked list, output the data.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "InputOutput.h"				// provides CreditCard

using namespace std;

// Function prototypes
void readCsvFile(vector<string> &, string);
void buildObjArray(vector<string> &, vector<Team> &);

// Standard constructor for CreditCard class
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

Team::~Team(){

}

string getInputFile()
{
	//local variable declaration
	string inputFile;

	//Prompt user to enter an input file name
	cout << "Enter input filename: ";
	getline(cin, inputFile);		//get input filename as a line (it may have spaces)
	cout << endl;

	return inputFile;
}//end getInputFile

void readCsvFile(vector<string> &input_values, string inputFile)
{
	string line;
	string line1;
	string line2;

	ifstream inFile;
	inFile.open(inputFile);

	if (inFile.is_open())
	{
		getline(inFile, line1);
		getline(inFile, line2);
		while (getline(inFile, line))
		{
			stringstream parseLine;
			string value = "";
			parseLine << line;

			while (getline(parseLine, value, ','))
			{
				input_values.push_back(value);
			}
		}
		inFile.close();
	}
	else
	{
		cout << "Unable to open input file: " << endl;
	}
}//end readCsvFile

void buildObjArray(vector<string> &input_values, vector<Team> &objTeamArray)
{
	//variable declarations
	string teamName;
	int played, teamWins, teamDraws, teamLoses, teamGoalsFor, teamGoalsAgainst, teamGoalDifference, teamPoints;
	char *Group;
	int count = 0;

	// loop through input_values vector array and add CreditCard objects to the 
	// objCardArray vector of CreditCard objects.
	for (unsigned i = 0; i < input_values.size(); i++)
	{
		if (count == 0)
		{
			teamName = input_values.at(i);
			++count;
		}
		else if (count == 1)
		{
			played = atoi(input_values.at(i).c_str());
			++count;
		}
		else if (count == 2)
		{
			teamWins = atoi(input_values.at(i).c_str());
			++count;
		}
		else if (count == 3)
		{
			teamDraws = atoi(input_values.at(i).c_str());
			++count;
		}
		else if (count == 4)
		{
			teamLoses = atoi(input_values.at(i).c_str());
			++count;
		}
		else if (count == 5)
		{
			teamGoalsFor = atoi(input_values.at(i).c_str());
			++count;
		}
		else if (count == 6)
		{
			teamGoalsAgainst = atoi(input_values.at(i).c_str());
			++count;
		}
		else if (count == 7)
		{
			teamGoalDifference = atoi(input_values.at(i).c_str());
			++count;
		}
		else if (count == 8)
		{
			teamPoints = atoi(input_values.at(i).c_str());
			++count;
		}
		else if (count == 9)
		{
			Group = _strdup(input_values.at(i).c_str());
			count = 0;
			//call CreditCard constructor to create CreditCard object
			objTeamArray.push_back(Team(teamName, played, teamWins, teamDraws, teamLoses, teamGoalsFor, teamGoalsAgainst, teamGoalDifference, teamPoints, Group));
		}
	}
}//end buildObjArray

int main()
{
	string inputFile;
	//vector variable declarations
	vector<string> input_values;
	vector<Team> objTeamArray;
	inputFile = getInputFile();

	//function call to open the CrediCard.csv file and create the vector input_values.
	readCsvFile(input_values, inputFile);
	//function call to create the vector of CreditCard objects.
	buildObjArray(input_values, objTeamArray);	

		
	//clear memory of both vectors and linked list
	input_values.clear();
	objTeamArray.clear();
	
	system("pause");
	return 0;
}// end main