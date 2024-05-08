#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <climits>

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
    } else {
        cout << "Wrong format" << endl;
        return 1;
    }

    if (getline(file, line)) {
        stringstream ss(line);
        ss >> fruit;
    }

    file.close();

    // Data structures for DP
    vector<int> apples_before(n, 0);
    for (int i = 0; i < n; ++i) {
        apples_before[i] = (i > 0 ? apples_before[i-1] : 0) + (fruit[i] == '1');
    }

    // We need to consider n+k positions for insertion points
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX));
    vector<vector<int>> path(n + 1, vector<int>(k + 1, -1)); // To reconstruct insertion decisions

    dp[0][0] = 0; // No apples picked if no fruit is considered
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            // Do not insert an apple
            if (i < n && dp[i][j] != INT_MAX) {
                int next_pick = (i + j) % m == (m - 1) ? (fruit[i] == '1') : 0;
                if (dp[i+1][j] > dp[i][j] + next_pick) {
                    dp[i+1][j] = dp[i][j] + next_pick;
                    path[i+1][j] = j;
                }
            }

            // Try to insert an apple
            if (j < k && dp[i][j] != INT_MAX) {
                int next_pick = (i + j) % m == (m - 1) ? 1 : 0;
                if (dp[i][j+1] > dp[i][j] + next_pick) {
                    dp[i][j+1] = dp[i][j] + next_pick;
                    path[i][j+1] = j;
                }
            }
        }
    }

    // Find minimum apples picked by Ivo
    int min_apples = INT_MAX, best_j = 0;
    for (int j = 0; j <= k; ++j) {
        if (dp[n][j] < min_apples) {
            min_apples = dp[n][j];
            best_j = j;
        }
    }

    // Reconstruct the solution
    vector<int> insertions;
    int current = n, current_j = best_j;
    while (current > 0) {
        int prev_j = path[current][current_j];
        if (prev_j != current_j) {
            insertions.push_back(current);
        }
        current_j = prev_j;
        current--;
    }

    reverse(insertions.begin(), insertions.end());
    cout << min_apples << endl;
    cout << insertions.size() << " ";
    for (int pos : insertions) {
        cout << pos + 1 << " ";  // Convert to 1-based index
    }
    cout << endl;

    auto end = high_resolution_clock::now();
    duration<double> duration_seconds = end - start;
    cout << "Elapsed time: " << duration_seconds.count() << " seconds" << endl;
    return 0;
}
