#pragma once

#include <filesystem>
#include <string>
#include <vector>

using namespace std;

vector<filesystem::path> search_files_threaded(const filesystem::path& root, const string& target);
