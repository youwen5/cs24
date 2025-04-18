#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <unordered_set>
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

// assume vectors are same length
bool vectorsAreEqual(const vector<int> &vec1, const vector<int> &vec2) {
  for (unsigned i = 0; i < vec1.size(); i++) {
    if (vec1.at(i) != vec2.at(i)) {
      return false;
    }
  }
  return true;
}
vector<vector<int>> threeSumOptimized(vector<int> &nums) {
  vector<vector<int>> result;
  unordered_set<int> set;
  sort(nums.begin(), nums.end());
  if (nums.at(nums.size() - 1) < 0 || nums.at(0) > 0) {
    return result;
  }
  int ptr1;
  int ptr2;

  int sum;

  for (ptr1 = 0; ptr1 < nums.size(); ptr1++) {
    for (ptr2 = ptr1 + 1; ptr2 < nums.size(); ptr2++) {
      if (set.contains(nums.at(ptr2))) {
        vector<int> elem;
        elem.push_back(nums.at(ptr1));
        elem.push_back(nums.at(ptr2));
        elem.push_back(-(nums.at(ptr1) + nums.at(ptr2)));
        result.push_back(elem);
      }
      sum = nums.at(ptr1) + nums.at(ptr2);
      set.insert(-sum);
    }
    set.clear();
    while (ptr1 + 1 < nums.size() && nums.at(ptr1) == nums.at(ptr1 + 1)) {
      ptr1++;
    }
  }
  ptr1 = 0;
  ptr2 = 0;
  while (ptr1 < result.size()) {
    while (ptr2 + 1 < result.size() &&
           vectorsAreEqual(result.at(ptr2 + 1), result.at(ptr2))) {
      result.erase(result.begin() + ptr2 + 1);
    }
    ptr1++;
    ptr2 = ptr1;
  }
  return result;
}

double average(vector<double> vec) {
  double sum = 0;
  for (auto num : vec) {
    sum += num;
  }
  return sum / vec.size();
}

int main(int argc, char *argv[]) {
  mt19937 gen(12345);
  unsigned samplePoints[] = {100, 200, 400, 800, 1600, 3200, 6400, 8000};
  vector<int> *nums;
  vector<vector<int>> *result;
  uniform_int_distribution<> distrib(-100000, 100000);
  unsigned runs = 3;

  map<unsigned, vector<double>> times;

  cout << "doing 3 runs..." << endl;

  for (unsigned i = 0; i < runs; i++) {
    for (auto ct : samplePoints) {
      nums = new vector<int>;
      result = new vector<vector<int>>;
      for (unsigned j = 0; j < ct; j++) {
        nums->push_back(distrib(gen));
      }
      auto start = chrono::high_resolution_clock::now();
      result = new vector<vector<int>>(threeSumOptimized(*nums));
      auto end = chrono::high_resolution_clock::now();
      double time_ms =
          chrono::duration_cast<chrono::microseconds>(end - start).count() /
          1000.0;

      cout << "testing n=" << ct << " samples" << endl;
      cout << "time taken: " << time_ms << endl;

      times.emplace(ct, 0);
      times.at(ct).push_back(time_ms);

      delete nums;
      delete result;
    }
  }

  fstream csv;

  if (argc > 1) {
    cout << "going to write file " << argv[1] << endl;
    csv.open(argv[1]);
    if (!csv.is_open()) {
      cout << "error: could not open file" << endl;
      return 1;
    }
    csv << "samples,ms" << endl;
    for (auto xs : times) {
      csv << xs.first << "," << average(xs.second) << endl;
    }

    csv.close();

    cout << "wrote output to " << argv[1] << endl;
  }

  return 0;
}
