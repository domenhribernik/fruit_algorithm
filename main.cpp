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

pair<vector<int>, int> solve(int n, int k, int m, vector<bool>& fruits) {
    deque<Node> dq;
    vector<int> insertedIndices;
    // initialize deque
    for (int i = 0; i < n; i++) {
        if (i % m != 0) {
            dq.push_back({min(i % m, m - i % m), i});
        }
    }
    while (k-- > 0) {
        Node front = dq.front();
        dq.pop_front();
        // insert apple
        fruits.insert(fruits.begin() + front.pos, 1);
        insertedIndices.push_back(front.pos);
        // update deque
        for (auto& node : dq) {
            if (node.pos >= front.pos) {
                node.pos++;  // shift positions to the right
            }
        }
        int size = fruits.size();
        if (front.pos + 1 < size && (front.pos + 1) % m != 0) {
            dq.push_back({min((front.pos + 1) % m, m - (front.pos + 1) % m), front.pos + 1});
        }
    }

    for (int f : fruits) {
        cout << f;
    }
    cout << endl;

    int appleCount = 0;
    for (size_t i = 0; i < fruits.size(); i += m) {
        if (fruits[i] == 1) {
            appleCount++;
        }
    }
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
    cout << "Indices where the apples were inserted: ";
    for (size_t i = 0; i < result.first.size(); i++) {
        cout << result.first[i] << " ";
    }
    cout << endl;

    cout << "Number of apples Ivo picked: " << result.second << endl;
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
  cout << fruit << endl;

  vector<bool> fruits = stringToVector(fruit);
  pair<vector<int>, int> result = solve(n, k, m, fruits);
  printResult(result);
  
  auto end = high_resolution_clock::now();
  duration<double> duration_seconds = end - start;
  cout << "Elapsed time: " << duration_seconds.count() << " seconds" << endl;
  return 0;
}