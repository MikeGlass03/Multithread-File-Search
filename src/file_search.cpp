#include "file_search.hpp"

vector<filesystem::path> search_files(const filesystem::path& root, const string& target) {

    vector<filesystem::path> matches;

    for (const filesystem::directory_entry& entry : filesystem::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        if (entry.path().filename().string() == target) {
            matches.push_back(entry.path());
        }
    }

    return matches;
}