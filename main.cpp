// Main file for homework 7
#include <fstream>
#include <map>
#include <iostream>
#include <iterator>
#include <cassert>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;

typedef map<string, vector<int> > myMap;

// Declarations of external helper functions 
vector<string> split(string inp, char delim);
map<string, vector<int> > makeMap(string &input, int k);
void search(myMap& genMap, string query, string big, int tolerance, int k);

int main(int argc, char *argv[])
{	
	//first line expected input, opens input stream
	string inp;
	string fileName;
	getline(cin, inp);
	//line starts with "genome", anything after first whitespace is file name
	if(inp[0] == 'g')
	{
		vector<string> words = split(inp, ' ');
		fileName = string(words[1]);
	}
	ifstream istr;
	istr.open(fileName.c_str());
	if(!istr.good())
	{
		cerr << "Error opening file!" << endl;
		exit(1);
	}
	string fl;
	vector<string> fileLines;
	while(!istr.eof())
	{
		getline(istr, fl);
		fl.erase(remove(fl.begin(), fl.end(), '\n'), fl.end()); // removes newline char
		fileLines.push_back(string(fl));
	}
	istr.close();

	//makes one big string out of all input file lines 
	string bigOne;
	for(int i = 0; i < fileLines.size(); i++)
	{
		bigOne = bigOne + fileLines[i];
	}

	//second line where setting of k-length is expected
	int len;
	string temp;
	getline(cin, inp);
	if(inp[0] == 'k')
	{
		vector<string> words = split(inp, ' ');
		temp = words[1];
		len = atoi(temp.c_str());
	}

	//makes map given file lines and k num
	myMap genMap = makeMap(bigOne, len);

	//rest of file until quit command is encountered 
	int misMatch;
	string query;
	while(getline(cin, inp))
	{
		if(string(inp) == string("quit"))
		{
			break;
		}
		vector<string> words = split(inp, ' ');
		assert(words[0] == "query");
		misMatch = atoi(words[1].c_str());
		query = words[2];
		search(genMap, query, bigOne, misMatch, len);
	}
	return 0;
}

//helper function to split whole lines by whitespace into a vector
vector<string> split(string inp, char delim)
{
	vector<string> words;
	stringstream ss(inp);
	string temp;
	while(getline(ss, temp, delim))
	{
		words.push_back(temp);
	}
	return words;
}

// Makes the map that will be later searched 
myMap makeMap(string &bigOne, int k)
{
	//takes string and makes map using k-len
	int size = bigOne.length(); 
	myMap answer;
	pair<myMap::iterator, bool> ifInsert;
	myMap::iterator itr;
	int pos;
	for(pos = 0; pos < size - k; pos++)
	{
		string temp = bigOne.substr(pos, k);
		vector<int> t;
		t.push_back(pos);
		ifInsert = answer.insert(make_pair<string, vector<int> >(temp, t));
		if(ifInsert.second == false) //substring already exists
		{
			itr = ifInsert.first;
			(itr->second).push_back(pos); //add pos to vector of pos's for that substr
		}
	}
	return answer;
}

//finds query and prints position found, or prints no match
void search(myMap& genMap, string query, string big, int tolerance, int k)
{
	string seed = query.substr(0, k);
	int miss = 0;
	int QL = query.length();
	bool matchFound = false;
	myMap::iterator itr;
	itr = genMap.find(seed);
	//seed not found 
	cout << "Query: " << query << endl;
	if(itr == genMap.end())
	{
		cout << "No Match" << endl;
		return;
	}

	//will iterate forward k times from original find testing all possible solutions along the way
	int c = 0;
	while(c < k)
	{
		if(itr == genMap.end())
		{
			break;
		}
		vector<int> data = itr->second;
		for(int i = 0; i < data.size(); i++)
		{
			string toTest = big.substr(data[i], QL);
			for(int j = 0; j < QL; j++)
			{

				if(toTest[j] == query[j])
				{
					continue;
				}
				else
				{
					miss += 1;
				}
				if(miss > tolerance)
				{
					break;
				}
			}
			if(miss > tolerance)//for loop was exited because of too many mismatches
			{	
				miss = 0;
				continue;
			}
			else //for loop was exited because of match
			{
				cout << data[i] << " " << miss << " " << toTest << endl;
				matchFound = true;
				miss = 0;
			}
		}
		++c;
		++itr;
	}
	if(matchFound == false) //seed was found but query with given mis-match allowance was not
	{
		cout << "No Match" << endl;
		return;
	}
}