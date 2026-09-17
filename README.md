## Multithreaded File Search
This project is a simple file search that employs a worker queue to search a given directory.
This project was built to practice C++ filesystem operations, multithreading, synchronization, and CMake.

## Installation and use

Requires:
C++17-compatible compiler
CMake

Clone the repository:
git clone https://github.com/MikeGlass03/Multithread-File-Search.git
cd Multithread-File-Search

Configure and build:
cmake -S . -B build
cmake --build build

Example Run: 

Input the drive or directory to begin search: C:\Users 
Input the name of the file to search for: example.txt Success: "C:\Users\Example\Documents\example.txt"
