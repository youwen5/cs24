#import "@youwen/zen:0.5.0": *
#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *

#show: codly-init.with()

#show: zen.with(
  title: "Lab 1 Writeup",
  author: "Youwen Wu",
  subtitle: "CS24, Spring 2025",
)

#codly(languages: codly-languages)

= Code

== Naive solution

```cpp
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        bool aux = false;
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
    bool vectorContains(vector<vector<int>>& vec, vector<int>& test) {
        for (unsigned i = 0; i < vec.size(); i++) {
            if (vec[i] == test)
                return true;
        }
        return false;
    }
};
```
