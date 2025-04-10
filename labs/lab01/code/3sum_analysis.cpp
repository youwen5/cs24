#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;

bool vectorContains(vector<vector<int>> &vec, vector<int> &test) {
  for (unsigned i = 0; i < vec.size(); i++) {
    if (vec[i] == test)
      return true;
  }
  return false;
}

vector<vector<int>> threeSum(vector<int> &nums) {
  sort(nums.begin(), nums.end());
  vector<vector<int>> result;
  for (unsigned i = 0; i < nums.size(); i++) {
    for (unsigned j = i + 1; j < nums.size(); j++) {
      for (unsigned k = j + 1; k < nums.size(); k++) {
        if (nums[i] + nums[j] + nums[k] == 0) {
          vector<int> newVec;
          newVec.push_back(nums[i]);
          newVec.push_back(nums[j]);
          newVec.push_back(nums[k]);
          if (!vectorContains(result, newVec)) {
            result.push_back(newVec);
          }
        }
      }
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  vector<int> nums;
  nums.push_back(4);
  nums.push_back(-5);
  nums.push_back(4);
  nums.push_back(-2);
  nums.push_back(-8);
  auto start = chrono::high_resolution_clock::now();
  vector<vector<int>> result = threeSum(nums);
  auto end = chrono::high_resolution_clock::now();
  double time_ms =
      chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0;
  for (auto c : result) {
    for (auto b : c) {
      cout << b << " ";
    }
    cout << endl;
  }

  cout << "time taken: " << time_ms << endl;

  return 0;
}
