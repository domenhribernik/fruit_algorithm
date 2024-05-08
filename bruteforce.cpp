#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

int scan(const string &bits, int m)
{
  int sum = 0;
  for (int i = m - 1; i < bits.size(); i += m)
  {
    if (bits[i] == '1')
    {
      sum++;
    }
  }
  return sum;
}

pair<int, vector<int>> insertFruit(string bits, int k, int m, int index = 0, int insertions = 0, vector<int> positions = {})
{
  // Base case: if no more apples can be inserted or we've reached the end of the string
  if (insertions == k || index > bits.size())
  {
    return make_pair(scan(bits, m), positions);
  }

  // Try inserting an apple at the current position
  string withApple = bits.substr(0, index) + '1' + bits.substr(index);
  vector<int> withApplePositions = positions;
  withApplePositions.push_back(index + 1);
  pair<int, vector<int>> withAppleScore = insertFruit(withApple, k, m, index + 1, insertions + 1, withApplePositions);

  // Try not inserting an apple at the current position
  pair<int, vector<int>> withoutAppleScore = insertFruit(bits, k, m, index + 1, insertions, positions);

  // Return the pair with the minimum score
  if (withAppleScore.first < withoutAppleScore.first)
  {
    return withAppleScore;
  }
  else
  {
    return withoutAppleScore;
  }
}

int main(int argc, char *argv[])
{
  auto start = high_resolution_clock::now();

  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  string filename = argv[1];
  ifstream file(filename);
  if (!file.is_open())
  {
    cout << "Failed to open the file." << endl;
    return 1;
  }

  string line;
  int n, k, m;
  string fruit;
  if (getline(file, line))
  {
    stringstream ss(line);
    ss >> n >> k >> m;
  }
  else
  {
    cout << "Wrong format" << endl;
    return 1;
  }

  if (getline(file, line))
  {
    stringstream ss(line);
    ss >> fruit;
  }

  file.close();

  pair<int, vector<int>> result = insertFruit(fruit, k, m);
  cout << result.first << endl;
  cout << result.second.size() << " ";
  for (int pos : result.second)
  {
    cout << pos << " ";
  }
  cout << endl;

  auto end = high_resolution_clock::now();
  duration<double> duration_seconds = end - start;
  cout << "Elapsed time: " << duration_seconds.count() << " seconds" << endl;
  return 0;
}
