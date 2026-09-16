#include <iostream>
#include <filesystem>
#include <string>

#include "file_search.hpp"

int main() {
    std::string file_name;
    std::cout << "Input the name of the file to search for: \n";
    std::cin >> file_name;
    
    auto matches = search_files(".", file_name);

    if(matches.empty()) {
        std::cout << "Could not find the file you entered.";
        return 0;
    }

    for(const auto& p : matches) {
        std::cout << p << "\n"; 
    }

    return 0;
}
