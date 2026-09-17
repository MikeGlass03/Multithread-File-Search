#include "Threading.hpp"
#include "file_search.hpp"

#include <thread>

vector<filesystem::path> search_files_threaded(const filesystem::path& root, const string& target) {

	vector<filesystem::path> matches;
	vector<filesystem::path> subdirectories;

	for (const filesystem::directory_entry& entry : filesystem::directory_iterator(root)) {
		if (entry.is_directory()) {
			subdirectories.push_back(entry.path());
		} 
        else if (entry.is_regular_file() && entry.path().filename() == target) {
			matches.push_back(entry.path());
		}
	}

	vector<vector<filesystem::path>> per_thread_matches(subdirectories.size());
	vector<thread> workers;

	for (int i = 0; i < subdirectories.size(); ++i) {
		workers.emplace_back([&, i]() {
			per_thread_matches[i] = search_files(subdirectories[i], target);
		});
	}

	for (auto& worker : workers) {
		worker.join();
	}

	for (const auto& thread_matches : per_thread_matches) {
		matches.insert(matches.end(), thread_matches.begin(), thread_matches.end());
	}

	return matches;
}
