#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>

using namespace std;

vector< vector< vector< int > > > primefactors;

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  else
    return gcd(b, a%b);
}

int lcm(int a, int b)
{
  return (a*b)/gcd(a,b);
}

int main (){
	string line;
	ifstream infile;
	infile.open("primefactor.res");
	while(!infile.eof()) {
		getline(infile, line);
		cout << line << endl;
		std::stringstream test(line);
		std::string segment;
		vector < vector < int > > seglist;
		while(std::getline(test, segment, '='))
		{
			vector < int > tempvector;
			string newSegment = segment;
			newSegment.erase(std::remove(newSegment.begin(),newSegment.end(),' '),newSegment.end());
			std::string starsegment;
			std::stringstream newSegmentStream(newSegment);
			while(std::getline(newSegmentStream, starsegment, '*')){
				tempvector.push_back(atoi(starsegment.c_str()));
			}
			seglist.push_back(tempvector);
		}
		primefactors.push_back(seglist);
	}

	for (int i = 0; i < primefactors.size() - 1; ++i){
		for(int um = i + 1; um < primefactors.size() - 1; ++um) {
			cout << primefactors[i][1][0] << " " << primefactors[um][1][0] << " LCM " << lcm(primefactors[i][1][0], primefactors[um][1][0]) << "\n";
		}  

	}

}