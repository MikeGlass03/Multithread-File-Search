#include <iostream>
#include <filesystem>
#include <string>

#include "ThreadedFileSearch.hpp"

int main() {
    std::string file_name;
    std::string directory;

    std::cout << "Input the drive or directory to begin search (for the whole drive, use C:\\ or D:\\): ";
    std::getline(std::cin, directory);

    if (directory.empty()) {
        directory = "C:\\";
    }

    std::cout << "Input the file name, (with or without its extension, but case sensitive): ";
    std::getline(std::cin, file_name);

    std::filesystem::path root_path = directory;

    if (!std::filesystem::exists(root_path) || !std::filesystem::is_directory(root_path)) {
        std::cout << "The directory does not exist.\n";
        return 1;
    }

    vector<filesystem::path> matches = search_files_threaded(root_path, file_name);

    if (matches.empty()) {
        std::cout << "Could not find the file you entered in " << root_path << "\n";
        return 1;
    }

    for (const filesystem::path& p : matches) {
        std::cout << "Success, Here is the full path: " << p << "\n";
    }

    return 0;
}
