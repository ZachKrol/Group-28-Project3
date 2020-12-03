#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>
using namespace std;

class Title
{
//private:
public:
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

//public:
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

map<string, Title> movieMap;
map<string, Title>::iterator iter;

int main() {
    //ifstream myfile;
    //myfile.open("data2.tsv");
	ifstream myfile("data2.tsv");
    if (!myfile.is_open()) {
        cout << "uh oh file could not be opened" << endl;
    }
    string str = "";
    //skip first line bc those are all titles?
    getline(myfile, str);

    while (getline(myfile, str)) {
		Title obj;
		istringstream iss(str);
		string token; //when getlining, converts to string; use this convert back to int if needed

		getline(iss, obj.titleID, '\t'); //reads until tab character
		
		getline(iss, obj.titleType, '\t');

		getline(iss, obj.primaryTitle, '\t');

		getline(iss, obj.originalTitle, '\t');

		getline(iss, token, '\t'); //this token will be converted to int then to bool
		obj.isAdult = stoi(token);

		getline(iss, token, '\t');
		if (token != "\N") {
			obj.startYear = stoi(token);
		}
		

		getline(iss, token, '\t');
		if (token != "\N") {
			obj.endYear = stoi(token);
		}
		
		getline(iss, token, '\t');
		if (token != "\N") {
			obj.minutes = stoi(token);
		}

		movieMap.emplace(obj.primaryTitle, obj);
    }

	auto iter = movieMap.begin();
	for (; iter != movieMap.end(); iter++) {
		cout << iter->first << endl; //movie name
		cout << "titleID: " << iter->second.titleID << endl;
		cout << "titleType: " << iter->second.titleType << endl;
		cout << "primaryTitle: " << iter->second.primaryTitle << endl;
		cout << "originalTitle: " << iter->second.originalTitle << endl;
		cout << "isAdult: " << iter->second.isAdult << endl;
		cout << "startYear: " << iter->second.startYear << endl;
		cout << "endYear: " << iter->second.endYear << endl;
		cout << "minutes: " << iter->second.minutes << endl;
		cout << endl;
	}

    myfile.close();
    return 0;
}