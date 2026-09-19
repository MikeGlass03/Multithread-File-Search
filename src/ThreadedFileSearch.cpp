#include "ThreadedFileSearch.hpp"

#include <algorithm>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <system_error>
#include <thread>
#include <vector>

class FileTaskQueue {
    private:
        static constexpr size_t max_queue_size = 256;
        queue<filesystem::path> tasks;
        mutex queue_mutex;
        condition_variable task_available;
        condition_variable space_available;
        bool finished = false;

    public:
        //Adds file path to queue and wakes up worker
        void push(const filesystem::path& path) {
            unique_lock<mutex> lock(queue_mutex);
            space_available.wait(lock, [this]() {
                return tasks.size() < max_queue_size || finished;
            });

            if (finished) {
                return;
            }

            tasks.push(path);
            task_available.notify_one();
        }
        
        //Removes file path from queue and signals space is available
        bool pop(filesystem::path& path) {
            unique_lock<mutex> lock(queue_mutex);
            task_available.wait(lock, [this]() {
                return !tasks.empty() || finished;
            });

            if (tasks.empty()) {
                return false;
            }

            path = tasks.front();
            tasks.pop();
            space_available.notify_one();
            return true;
        }

        //Signal that tasks are done, wakes dormant workers so queue can complete
        void finish() {
            lock_guard<mutex> lock(queue_mutex);
            finished = true;
            task_available.notify_all();
            space_available.notify_all();
        }
    };

vector<filesystem::path> search_files_threaded(const filesystem::path& root, const string& target) {
    
    vector<filesystem::path> matches;
    filesystem::path target_path = target;
    FileTaskQueue task_queue;
    mutex matches_mutex;
    constexpr unsigned int max_worker_threads = 8;
    unsigned int thread_count = thread::hardware_concurrency();

    //I think I need this in case something goes wrong in hardware_concurrency, no computers have 0 cores
    if (thread_count == 0) {
        thread_count = 4;
    }

    //Finds thread count available to queue, limited to 8 for purposes of this project
    thread_count = min(thread_count, max_worker_threads);

    vector<thread> workers;

    //Runs queue to consume file paths
    for (unsigned int i = 0; i < thread_count; ++i) {
        workers.emplace_back([&]() {
            
			filesystem::path file;
            while (task_queue.pop(file)) {
                if (file.filename() == target_path || file.stem() == target_path) {
                    lock_guard<mutex> lock(matches_mutex);
                    matches.push_back(file);
                }
            }
        });
    }

    //Error handling, essentially stores errors without throwing exceptions due to access issues
    error_code error;
    filesystem::recursive_directory_iterator iterator(root, filesystem::directory_options::skip_permission_denied, error);
    filesystem::recursive_directory_iterator end;

    //Gives tasks to threads and ensures file search doesn't go down paths without access
    while (iterator != end) {
        if (!error && iterator->is_regular_file(error)) {
            task_queue.push(iterator->path());
        }
        error.clear();
        iterator.increment(error);
    }

    task_queue.finish();

    //Waits till all threads to be finished, prevents function from jumping to return statement
    for (thread& worker : workers) {
        worker.join();
    }

    return matches;
}
