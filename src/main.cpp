#include <iostream>
#include <filesystem>
#include <string>

#include "file_search.hpp"

int main() {
    std::string file_name;
    std::string directory;

    std::cout << "Input the drive or directory to begin search (for the whole drive, use C:\\ or D:\\): ";
    std::cin >> directory;

    if (directory.empty()) {
        directory = "C:\\";
    }

    std::cout << "Input the name of the file to search for: ";
    std::cin >> file_name;

    std::filesystem::path root_path = directory;

    if (!std::filesystem::exists(root_path) || !std::filesystem::is_directory(root_path)) {
        std::cout << "The directory does not exist.\n";
        return 1;
    }

    auto matches = search_files(root_path, file_name);

    if (matches.empty()) {
        std::cout << "Could not find the file you entered in " << root_path << "\n";
        return 1;
    }

    for (const auto& p : matches) {
        std::cout << p << "\n";
    }

    return 0;
}
