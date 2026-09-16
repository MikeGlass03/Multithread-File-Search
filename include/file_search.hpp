#include <filesystem>
#include <string>
#include <vector>

std::vector<std::filesystem::path> search_files(const std::filesystem::path& root, const std::string& target);