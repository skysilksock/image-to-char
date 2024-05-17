#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
//#include <ranges> 当前租用的Linux服务器C++版本不支持
#include <algorithm>

using namespace std;

vector<char> char_set = {' ', '`', '.', '^', ',', ':', '~', '"', '<', '!', 'c', 't', '+', '{', 'i', '7', '?', 'u', '3', '0', 'p', 'w', '4', 'A', '8', 'D', 'X', '%', '#', 'H', 'W', 'M'};


extern "C" char* func(int*** nums, int rows, int cols)
{  
	cout << "start" << endl;
	int n = char_set.size();
    // cout << rows << '-' << cols << endl;
    char* s = (char*)malloc(sizeof(char) * rows * (cols + 1));
	if (s == NULL) {
		cout << "Memory allocation failed" << endl;
		return (char*)"Memory allocation failed";
	}
    int p = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sums = 0;
            for (int k = 0; k < 3; k++) {
                sums += nums[i][j][k];
            }
            int index = sums * (n - 1) / 765;
			cout << "p: " << p << endl;
            s[p++] = char_set[index];
        }
		s[p++] = '\n';
    }
    //char* str = (char*)"Hello, World!";
    s[p] = '\0';
	cout << "end: " << p << " malloc: " << rows * (cols + 1)  << endl;
    return s;
}
