#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

struct Node {
    int distanceToNextPick;
    int pos;
};

int pick_apples(int m, vector<bool> fruits) {
  int appleCount = 0;
  for (size_t i = m-1; i < fruits.size(); i += m) {
    if (fruits[i] == 1) {
      appleCount++;
    }
  }
  return appleCount;
}

int pick_apples_value(int m, vector<bool> fruits, int index) {
  int appleCount = 0;
  fruits.insert(fruits.begin() + index, 1);
  for (size_t i = m-1; i < fruits.size(); i += m) {
    if (fruits[i] == 1) {
      appleCount++;
    }
  }

  return appleCount;
}

pair<vector<int>, int> solve(int n, int k, int m, vector<bool>& fruits) {
  vector<int> insertedIndices;
  int appleCount = 0;
  bool stop = false;
  bool check = true;
  int check_value = fruits[0];   
  for (int i = 1; i < n; i++) {
    if (fruits[i] != check_value) {
      check = false;
      break;
    }
  }

  if (check || m == 1) {
    appleCount = pick_apples(m, fruits);
    return {insertedIndices, appleCount};
  }

  while (!stop) {
    stop = true;
    for (int i = m-1; i < n && k != 0; i += m) {
      int value1 = 0;
      int value2 = 0;

      if (fruits[i] == 1 && fruits[i-1] == 0) {
        for (int j = i; j < n; j += m) {
          value1 += fruits[j];
        }
        for (int j = i-1; j < n; j += m) {
          value2 += fruits[j];
        }

        if (value2 <= value1) {
          fruits.insert(fruits.begin() + i-1, 1);
          insertedIndices.emplace_back(i);
          stop = false;
          k--;
        }
      }
    }
  }

  appleCount = pick_apples(m, fruits);

  return {insertedIndices, appleCount};
}

vector<bool> stringToVector(const string& str) {
  vector<bool> boolVec;
  for (char c : str) {
      boolVec.push_back(c == '1');
  }
  return boolVec;
}

void printResult(pair<vector<int>, int> result) {
    cout << result.second << endl;
    cout << result.first.size() << ' ';
    for (size_t i = 0; i < result.first.size(); i++) {
        cout << result.first[i] << " ";
    }
    cout << endl;
}

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

  cout << "n: " << n << ", k: " << k << ", m: " << m << endl;
  //cout << fruit << endl;

  vector<bool> fruits = stringToVector(fruit);
  pair<vector<int>, int> result = solve(n, k, m, fruits);
  printResult(result);
  
  auto end = high_resolution_clock::now();
  duration<double> duration_seconds = end - start;
  cout << "Elapsed time: " << duration_seconds.count() << " seconds" << endl;
  return 0;
}