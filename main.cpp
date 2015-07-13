#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <functional>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <map>
#include <cmath>

using namespace std;

vector<pair<int, map <int, int>>> primefactors;

vector<vector<int>> gcdmatrix;

int gcd(int a1, int b1)
{
	int gcf = 1;
	// std::cout << (a1 == b1) << std::endl;
	if (gcdmatrix[a1][b1] != 0) {
		gcf = gcdmatrix[a1][b1];
	}
	else if (gcdmatrix[b1][a1] != 0) {
		gcf = gcdmatrix[b1][a1];
	}
	else {
		map<int,int> a = primefactors[a1].second;
		map<int,int> b = primefactors[b1].second;

		for (auto it : a) {
			auto c = b.find(it.first);
			if (c != b.end())
			{
				gcf *= pow(it.first, min(it.second, c->second));
			}
		}
	}

	gcdmatrix[a1][b1] = gcf;
	return gcf;
}

int lcm(int a, int b)
{
	int c = gcd(a,b);
	cout << c << endl;
	return (primefactors[a].first*primefactors[b].first)/c;
}

void printTable(function<int(int,int)> f, string filename) {
	ofstream outFile;
	outFile.open(filename);

	outFile << filename.substr(0, filename.find(".")) << "\t";

	for (int i = 0; i < primefactors.size(); i++){
		outFile << primefactors[i].first << "\t";
	}

	outFile << "\n";

	for (int i = 0; i < primefactors.size(); i++){
		outFile << primefactors[i].first << "\t";
		for(int j = 0; j < primefactors.size(); j++) {
			outFile << f(i, j) << "\t";
		}
		outFile << "\n";
	}

	outFile.close();
}

int main (){
	string line;
	ifstream infile;
	infile.open("primefactor.res");
	while(getline(infile, line)) {
		stringstream liness(line);

		string factorization;
		getline(liness, factorization, '=');
		stringstream factorss(factorization.substr(0, factorization.length() - 1));

		string number;
		getline(liness, number, '=');
		number = number.substr(1);

		pair<int, map<int, int>> entry;
		entry.first = stoi(number);

		string cur;
		while (getline(factorss, cur, '*'))
		{
			// Process factors here
			int val = stoi(cur);
			if (entry.second.find(val) != entry.second.end()) {
				entry.second[val]++;
			}
			else {
				entry.second[val] = 1;
			}
		}
		primefactors.push_back(entry);
	}

	for (int i = 0; i < primefactors.size(); i++) {
		vector<int> vec;
		for (int j = 0; j < primefactors.size(); j++) {
			vec.push_back(0);
		}
		gcdmatrix.push_back(vec);
	}

	printTable(lcm, "LCM.res");
	printTable(gcd, "GCD.res");
}