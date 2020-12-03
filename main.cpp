/*
Team 28
Team Members - Elizabeth Gekhtman, Sydney Opyrchal, Zachary Krol
Project Title - Buzzfeed Quiz Knockoff: Movie Recommender

Last Updated: 12/2/2020 9:12pm by ZK
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
tconst (string) - alphanumeric unique identifier of the title
titleType (string) – the type/format of the title (e.g. movie, short, tvseries, tvepisode, video, etc)
primaryTitle (string) – the more popular title / the title used by the filmmakers on promotional materials at the point of release
originalTitle (string) - original title, in the original language
isAdult (boolean) - 0: non-adult title; 1: adult title
startYear (YYYY) – represents the release year of a title. In the case of TV Series, it is the series start year
endYear (YYYY) – TV Series end year. ‘\N’ for all other title types
runtimeMinutes – primary runtime of the title, in minutes
genres (string array) – includes up to three genres associated with the title
*/

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

	// original title, in the original language

	// 0: non-adult title; 1: adult title

	// represents the release year of a title.In the case of TV Series, it is the series start year

	// TV Series end year.‘\N’ for all other title types

	// primary runtime of the title, in minutes

	// includes up to three genres associated with the title

public:
	Title();
	Title(string titleID, string titleType);
};

Title::Title()
{ 
	// default constructor 
}

Title::Title()
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

			// 1. which data structure do you want to use AVL/Map
				/* 
					if "AVL"
						initialize AVL tree (Sydney)<------------------------------------------------------
					else if "Map"
						initialzie Map (Elizabeth)<------------------------------------------------------
					else
						invalid input
				*/
		
			// 2. Ask quiz questions yayyyyyy
				// maybe storing answers in an array(index is question # and value is answer) 
				// or map (key is question number, value is answer)

	// 5. 

	return 0;
}