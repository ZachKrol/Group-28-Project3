/*
Team 28
Team Members - Elizabeth Gekhtman, Sydney Opyrchal, Zachary Krol
Project Title - Buzzfeed Quiz Knockoff: Movie Recommender

Last Updated: 12/4/2020 9:07pm by ZK
*/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <iterator>
#include <algorithm>
#include <ctype.h>
using namespace std;

// Title is a broad term that includes movies, shorts, tv series, video etc.
struct Title
{
	// These variables are the column headers in the data set from title.basics.tsv.gz (https://www.imdb.com/interfaces/)

	// alphanumeric unique identifier of the title
	int titleID;
	// the type/format of the title(e.g.movie, short, tvseries, tvepisode, video, etc)
	string titleType;
	// the more popular title / the title used by the filmmakers on promotional materials at the point of release
	string primaryTitle;
	// original title, in the original language
	string originalTitle;
	// 0: non-adult title; 1: adult title
	int isAdult;
	// represents the release year of a title.In the case of TV Series, it is the series start year
	int startYear;
	// TV Series end year.‘\N’ for all other title types
	int endYear;
	// primary runtime of the title, in minutes
	int minutes;
	// includes up to three genres associated with the title
	string genre;

	Title();
	Title(int titleID, string titleType, string primaryTitle, string originalTitle,
		int isAdult, int startYear, int endYear, int minutes, string genre);
};

Title::Title()
{
	titleID = 0;
	titleType = "Not Initialized";
	primaryTitle = "Not Initialized";
	originalTitle = "Not Initialized";
	isAdult = 0;
	startYear = 0;
	endYear = 0;
	minutes = 0;
	genre = "";
}

Title::Title(int titleID, string titleType, string primaryTitle, string originalTitle,
	int isAdult, int startYear, int endYear, int minutes, string genre)
{
	this->titleID = titleID;
	this->titleType = titleType;
	this->primaryTitle = primaryTitle;
	this->originalTitle = originalTitle;
	this->isAdult = isAdult;
	this->startYear = startYear;
	this->endYear = endYear;
	this->minutes = minutes;
	this->genre = genre;
}

// Load Data function. returns vector of title objects
vector<Title> LoadData()
{
	ifstream data("data.tsv");

	vector<Title> titleObjects;

	if (data.is_open())
	{
		string line;

		// pass over first line of headers
		getline(data, line);

		// IMPORTANT: adjust for-loop counter to determine number of rows to read
		for (int i = 0; i < 10000; i++)
		{
			// declare variables to capture data
			string _titleID;
			string _titleType;
			string _primaryTitle;
			string _originalTitle;
			string _isAdult;
			string _startYear;
			string _endYear;
			string _minutes;
			string _genre;

			// clear row of header
			getline(data, line);

			// create stringstream
			istringstream streamFromLine(line);

			// get title characteristics
			getline(streamFromLine, _titleID, '\t');

			getline(streamFromLine, _titleType, '\t');

			getline(streamFromLine, _primaryTitle, '\t');

			getline(streamFromLine, _originalTitle, '\t');

			getline(streamFromLine, _isAdult, '\t');

			getline(streamFromLine, _startYear, '\t');

			getline(streamFromLine, _endYear, '\t');

			getline(streamFromLine, _minutes, '\t');

			getline(streamFromLine, _genre, '\t');

			// filter out bad entries and initialize date into objects
			// also pushback valid rows of data into object vector

			// throw out adult films for this project
			if (stoi(_isAdult) == 1)
				continue;

			// throw out all garbage episode titles
			string episodeCheck = "Episode";
			// cout << "TESTTTTTT: Primary title first 7: " << _primaryTitle.substr(0, 7) << endl;
			if (episodeCheck.compare(_primaryTitle.substr(0, 7)) == 0)
				continue;

			// change any value of '/N' that are supposed to be numbers(start date, minutes, etc.) to integer = 0
			// if a string is '/N' we will just leave it
			string nullCheck = "\\N";

			if (_startYear.compare(nullCheck) == 0)
				_startYear = "0";
			if (_endYear.compare(nullCheck) == 0)
				_endYear = "0";
			if (_minutes.compare(nullCheck) == 0)
				_minutes = "0";

			// chop "tt" off _titleID. convert all necessary strings to ints when needed
			_titleID = _titleID.substr(2);
			int titInt = stoi(_titleID);
			int adultInt = stoi(_isAdult);
			int startInt = stoi(_startYear);
			int endInt = stoi(_endYear);
			int minuteInt = stoi(_minutes);

			// initialize title object
			Title t(titInt, _titleType, _primaryTitle, _originalTitle, adultInt, startInt, endInt, minuteInt, _genre);

			// pushback to vector of objects
			titleObjects.push_back(t);
		}
	}

	// print data
	// IMPORTANT: COMMENT THIS OUT IF YOU DON'T WANT IT TO PRINT
	
	for (auto iter = titleObjects.begin(); iter != titleObjects.end(); ++iter)
	{
		Title temp = *iter;
		cout << temp.titleID << " " << temp.titleType << " " <<  temp.primaryTitle << " " << temp.originalTitle << " " << 
			temp.primaryTitle << " " << temp.isAdult << " " << temp.startYear << " " << temp.endYear << " " <<
			temp.minutes << " " << temp.genre << endl;
	}

	data.close();

	return titleObjects;
}

int main()
{
	// 1. load file title.basics.tsv.gz (Zach)
		// DONE
	// 2. read through file rows initializing Title objects for each row (Zach)
		// pushback these objects to a vector. 
		// This is the vector that will be passed by reference into functions that create the Map and AVL structures
		// (stack overflow has an easy way to iterate through vectors using an iterator once inside your functions. lmk if you need help)
		//DONE
	vector<Title> titleObjects = LoadData();

	// 3. output welcome screen and selection (Zach)

	// 4. start asking questions and take in input (Zach)
		// begin loop
		
			// 1. Ask quiz questions yayyyyyy
				// maybe storing answers in an array(index is question # and value is answer) 
				// or map (key is question number, value is answer)

			// 2. which data structure do you want to use AVL/Map
			/*
				get input

				* start timer
			
				if "AVL"
					initialize AVL tree (Sydney)<------------------------------------------------------
					*2a. search function based on answers
						----> we should talk about how to do this because i don
				else if "Map"
					initialzie Map (Elizabeth)<------------------------------------------------------
					*2a. search function based on answers
				else
					invalid input
			*/

			// *2a. Using the answers, search for titles based on "things" (genres, decades, title etc.)
				// if certain set of questions are answered, search for certain genre etc.

				// ------------NOT SURE YET!----------------
					// Zach's Idea: I can figure out which things to search for, add them to a container, and pass that container into your functions
					// It would just be tricky for you all figuring out how to use that container to find titles
					// ALSO: this is a problem we can solve towards the end or over a zoom

				// if more than 1 title satisfies the search, randomly select one of them to recommend to the user
				// or just output a list of the titles
			
			// end timer and display time for data structure to be initialized and searched through

		// ask if they want to take quiz again
		// end loop

	return 0;
}
