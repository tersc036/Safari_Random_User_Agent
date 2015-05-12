//
//  Created by the MoFo
//  Free to edit.
//
//  Random user agent "load" for Safari(OSX)
//  Add more user agents in user.agents.txt
//  defaults write com.apple.Safari CustomUserAgent "\"My user agent string\""
//
// Compile: clang++ anonymizer.cc -std=c++11 -o anonymize_agent
//
// Usage: ./anonymize_agent     (for random User-Agent)
//        ./anonymize_agent bla (delete random User-Agent)
//
// Note: Restart Safari required.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>

void random(std::string & value)
{
    std::string line;
    std::ifstream myfile ("./user.agents.txt");

    std::vector<std::string> agent;
    for (std::string line; std::getline( myfile, line ); /**/ )
        agent.push_back( line );
    myfile.close();
    std::random_device rd;
    std::mt19937 mt(rd());
    int max = agent.size()-1;
    std::uniform_int_distribution<int> dist(1, max);
    value = agent.at(dist(mt));
}

int main(int argc, char* argv[])
{
    std::string value;
    std::string commando;
    if (argc == 1)
        {
            random(value);
            commando = "defaults write com.apple.Safari CustomUserAgent \"\\\"" + value +"\\\"\"";
        }
    else
        commando = "defaults delete com.apple.Safari CustomUserAgent";

  std::system(commando.c_str());
}