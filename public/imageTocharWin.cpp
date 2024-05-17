#include "pch.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
//#include <ranges> 当前租用的Linux服务器C++版本不支持
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& out, vector<int> nums) {
    out << '[';
    for (int i = 0; i < nums.size(); i++) {
        out << nums[i] << ((i == nums.size() - 1) ? "" : ", ");
    }
    out << ']' << endl;
    return out;
}

vector<int> convert_array_to_vector(int arr[], int n) {
    // 使用数组的开始和结束地址初始化 vector
    std::vector<int> vec(arr, arr + n);
    return vec;
}

int Partition(vector<int>& nums, int l, int r) {
    int i = l - 1;
    int x = nums[r];
    for (int j = l; j < r; j++) {
        if (nums[j] < x) {
            i++;
            swap(nums[j], nums[i]);
        }
    }
    swap(nums[i + 1], nums[r]);
    return i + 1;
}

vector<int>& QuickSort(vector<int>& nums, int l, int r) {
    if (l < r) {
        int p = Partition(nums, l, r);
        QuickSort(nums, l, p - 1);
        QuickSort(nums, p + 1, r);
    }
    return nums;
}

vector<int>& CountSort(vector<int>& nums) {
    int n = nums.size(), mx = *max_element(nums.begin(), nums.end());
    vector<int> cnt(mx + 1, 0);
    vector<int> ans(n, 0);
    for (int& num : nums) cnt[num]++;
    int sums = 0;
    for (int i = 0; i < mx;i++) {
        if (!cnt[i]) continue;
        fill(ans.begin() + sums, ans.begin() + sums + cnt[i], i);
        sums += cnt[i];
    }
    return ans;
}

vector<char> char_set = {' ', '`', '.', '^', ',', ':', '~', '"', '<', '!', 'c', 't', '+', '{', 'i', '7', '?', 'u', '3', '0', 'p', 'w', '4', 'A', '8', 'D', 'X', '%', '#', 'H', 'W', 'M'};


extern "C" _declspec(dllexport) char* func(int*** nums, int rows, int cols)
{   
    int n = char_set.size();
    char* s = (char*)malloc(sizeof(char) * rows * (cols + 1));
    if (s == NULL) {
        cout << "Memory allocation failed" << endl;
        return (char*)"malloc failed";
    }
    int p = 0;
    vector<int> cnt(n);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sums = 0;
            for (int k = 0; k < 3; k++) {
                sums += nums[i][j][k];
            }
            int index = sums * (n - 1) / 765;
            cnt[index]++;
            cout << "p: " << p << endl;
            s[p++] = char_set[index];
        }
        s[p++] = '\n';
    }
    cout << cnt << endl;
    cout << "end and p value: " << p << endl;
    cout << "malloc: " << rows * (cols + 1) << endl;
    //char* str = (char*)"Hello, World!";
    s[p] = '\0';
    return s;
}

extern "C" _declspec(dllexport) void free_memory(char* ptr) {
    free(ptr);
}