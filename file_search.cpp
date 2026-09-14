#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

void searchFile(const fs::path& path, const std::string& query) {
    ifstream file(path);

    if(!file.is_open()) {
        return;
    }
    
    string line;
    int ln = 1;

    while(std::getline(file, line)) {
            if(line.find(query) != string::npos) {
                cout << path << ": " << linenumber << " " << line << "\n"; 
            }

            ln++;
    }
}