#include "file_search.hpp"

std::vector<std::filesystem::path> search_files(
    const std::filesystem::path& root,
    const std::string& target) {

    std::vector<std::filesystem::path> matches;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        if (entry.path().filename().string() == target) {
            matches.push_back(entry.path());
        }
    }

    return matches;
}