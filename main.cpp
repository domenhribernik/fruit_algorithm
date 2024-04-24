#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {
  auto start = high_resolution_clock::now();

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }
  
  string filename = argv[1];
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Failed to open the file." << endl;
    return 1;
  }

  string line;
  int n, k, m;
  string fruit;
  if (getline(file, line)) {
    stringstream ss(line);
    ss >> n >> k >> m;
  }
  else {
    cout << "Wrong format" << endl;
    return 1;
  }

  if (getline(file, line)) {
    stringstream ss(line);
    ss >> fruit; 
  }

  file.close();

  // code

  cout << "n: " << n << ", k: " << k << ", m: " << m << endl;
  cout << "fruits: " << fruit << endl;
  
  auto end = high_resolution_clock::now();
  duration<double> duration_seconds = end - start;
  cout << "Elapsed time: " << duration_seconds.count() << " seconds" << endl;
  return 0;
}