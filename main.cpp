/*
Team 28
Team Members - Elizabeth Gekhtman, Sydney Opyrchal, Zachary Krol
Project Title - Buzzfeed Quiz Knockoff: Movie Recommender

Last Updated: 12/2/2020 10:07pm by ZK
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Title is a broad term that includes movies, shorts, tv series, video etc.
class Title
{
private:
	// These variables are the column headers in the data set from title.basics.tsv.gz (https://www.imdb.com/interfaces/)

	// alphanumeric unique identifier of the title
	string titleID;

	// the type/format of the title(e.g.movie, short, tvseries, tvepisode, video, etc)
	string titleType;

	// the more popular title / the title used by the filmmakers on promotional materials at the point of release
	string primaryTitle;

	// original title, in the original language
	string originalTitle;

	// 0: non-adult title; 1: adult title
	bool isAdult;

	// represents the release year of a title.In the case of TV Series, it is the series start year
	int startYear;

	// TV Series end year.‘\N’ for all other title types
	int endYear;

	// primary runtime of the title, in minutes
	int minutes;

	// includes up to three genres associated with the title
	string genre[]; // I'm gonna look into this one because some titles have varying number of genres... I think a string array works

public:
	Title();
	Title(string titleID, string titleType, string primaryTitle, string originalTitle, 
		bool isAdult, int startYear, int endYear, int minutes, string genre[]);
};

Title::Title()
{ 
	// default constructor 
}

Title::Title(string titleID, string titleType, string primaryTitle, string originalTitle,
	bool isAdult, int startYear, int endYear, int minutes, string genre[])
{ 
	// constructor 
}


int main(string titleID, string titleType)
{
	// 1. load file title.basics.tsv.gz (Zach)

	// 2. read through file rows initializing Title objects for each row (Zach)
		/*
		pushback these objects to a vector. 
		This is the vector that will be passed by reference into functions that create the Map and AVL structures
		(stack overflow has an easy way to iterate through vectors using an iterator once inside your functions. lmk if you need help)
		*/ 

	// 3. output welcome screen and selection (Zach)

	// 4. start asking questions and take in input (Zach)
		// begin loop
		
			// start timer 
		
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
