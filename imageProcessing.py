import ctypes
from ctypes import POINTER, c_int
import numpy as np
import cv2

# c func
"""
extern "C" _declspec(dllexport) char* func(int*** nums, int rows, int cols)
{   
    char* s = (char*)malloc(sizeof(char) * (rows + 1) * cols);
    int p = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sums = 0;
            for (int k = 0; k < 3; k++) {
                sums += nums[i][j][k];
            }
            int index = sums * (int)char_set.size() / 766;
            s[p++] = char_set[index];
        }
        s[p++] = '\n';
    }
    //char* str = (char*)"Hello, World!";
    s[p] = '\0';
    return s;
}
"""

# 一维数组转化为ctypes数组
def c_array(ctype, values): 
    arr = (ctype*len(values))()
    arr[:] = values
    return arr

# 二维数组转化为ctypes数组
def c_2d_array(ctype, values):
    arr = (POINTER(ctype)*len(values))()
    for i in range(len(values)):
        arr[i] = c_array(ctype, values[i])
    return arr

# 三维数组转化为ctypes数组
def c_3d_array(ctype, values):
    arr = (POINTER(POINTER(ctype))*len(values))()
    for i in range(len(values)):
        arr[i] = c_2d_array(ctype, values[i])
    return arr

# Load the shared library
so = ctypes.cdll.LoadLibrary
dll = so("D:/demo/Dll2.dll")

# Define the function signature
func = dll.func
func.argtypes = [POINTER(POINTER(POINTER(c_int))), ctypes.c_int, ctypes.c_int]
func.restype = ctypes.c_char_p

"""
Example to Create a numpy array
nums = [
    [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],
    [[11, 12, 13], [14, 15, 16], [17, 18, 19], [20, 21, 22]],
    [[23, 24, 25], [26, 27, 28], [29, 30, 31], [32, 33, 34]],
    [[35, 36, 37], [38, 39, 40], [41, 42, 43], [44, 45, 46]]
]
np_array = np.array(nums, dtype=np.int32)
ctypes_array = c_3d_array(c_int, np_array)
[28998, 35409, 40912, 41742, 36642, 30551, 31907, 38480, 40351, 35448, 38725, 34763, 28201, 25633, 26085, 22888, 25496, 28767, 27862, 22408, 20841, 22236, 17827, 21271, 14546, 5726, 4070, 2249, 2174, 1460, 3691, 22029]
[22029, 3691, 1460, 2174, 2249, 4070, 5726, 14546, 21271, 17827, 22236, 20841, 22408, 27862, 28767, 25496, 22888, 26085, 25633, 28201, 34763, 38725, 35448, 40351, 38480, 31907, 30551, 36642, 41742, 40912, 35409, 28998]

"""

# Call the function
def get_char_from_image(image):
    try:
        fx, fy = 0.5, 0.5
        init_size = image.shape[0] * image.shape[1]
        while init_size * fx * fy > 371_250:
            fx -= 0.05
            fy -= 0.05
        image = cv2.resize(image, (0, 0), fx=fx, fy=fy)
        height, width, _ = image.shape
        print("height: ", height, "width: ", width)
        image = np.array(image, dtype=np.int32)
        ctypes_array = c_3d_array(c_int, image)
        print("C++ func called")
        ans = func(ctypes_array, height, width)
        print("C++ func returned")
        return ans.decode("utf-8")
    except Exception as e:
        print(e)
        return ""





