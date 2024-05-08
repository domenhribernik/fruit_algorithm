#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

int scan(const string &bits, int m) {
    int sum = 0;
    for (int i = m - 1; i < bits.size(); i += m) {
        if (bits[i] == '1') {
            sum++;
        }
    }
    return sum;
}

pair<int, vector<int>> insertFruit(string bits, int k, int m, int index = 0, int insertions = 0, vector<int> positions = {}) {
    if (k == 0 || index >= bits.size()) {
        // Scan the sequence as it is and return the number of apples picked
        return make_pair(scan(bits, m), positions);
    }

    // Option 1: Do not insert an apple at this position
    auto resultWithoutInsertion = insertFruit(bits, k, m, index + 1, insertions, positions);

    // Option 2: Try inserting an apple at this position if we have any left
    pair<int, vector<int>> resultWithInsertion = {INT_MAX, {}};
    if (k > 0) {
        string newBits = bits.substr(0, index) + "1" + bits.substr(index);
        vector<int> newPositions = positions;
        newPositions.push_back(index + 1); // Use 1-based index for output
        resultWithInsertion = insertFruit(newBits, k - 1, m, index + 1, insertions + 1, newPositions);
    }

    // Return the better option
    if (resultWithoutInsertion.first <= resultWithInsertion.first) {
        return resultWithoutInsertion;
    } else {
        return resultWithInsertion;
    }
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
    } else {
        cout << "Wrong format" << endl;
        return 1;
    }

    if (getline(file, line)) {
        stringstream ss(line);
        ss >> fruit;
    }

    file.close();

    pair<int, vector<int>> result = insertFruit(fruit, k, m);
    cout << result.first << endl;
    cout << result.second.size() << " ";
    for (int pos : result.second) {
        cout << pos << " ";
    }
    cout << endl;

    auto end = high_resolution_clock::now();
    duration<double> duration_seconds = end - start;
    cout << "Elapsed time: " << duration_seconds.count() << " seconds" << endl;
    return 0;
}
