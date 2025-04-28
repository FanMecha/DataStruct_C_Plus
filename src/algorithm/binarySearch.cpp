//
// Created by MechaFan on 2025/4/27.
//

//======二分搜索(对于连续序列的搜索时间复杂度为logN)

#include <iostream>

int binarySearch(int arr[], int size, int val){
    // int size = sizeof arr / sizeof(int);
    // 这行代码是错的:当数组作为函数形参时,本质上是数组退化为一个指针,所以这里其实是指针的大小
    int first = 0;
    int last = size - 1;
    while (first <= last)
    {
        int mid = (first + last) / 2;
        if (arr[mid] == val){
            return mid;
        }else if(arr[mid] < val){
            first = mid + 1;
        }else{
            last = mid - 1;
        }
    }
    return -1;
}

//==============递归回顾
//1.不管是什么规模的数据,求解问题的方式一定是一样的
//2.不同规模的数据，其计算结果是有因果关系的
//3.一定要有递归结束的条件
int factorial(int N){
    if (N == 0 || N == 1){
        return 1;
    }else{
        return factorial(N-1)*N;
    }
}

//==============递归二分搜索
int binarySearch(int arr[],int i, int j, int val){
    if (i > j){
        return -1;
    }
    int mid = (i + j) / 2;
    if(arr[mid] == val){
        return mid;
    }else if(arr[mid] > val){
        return binarySearch(arr, i, mid - 1, val);
    }else{
        return binarySearch(arr,mid + 1, j, val);
    }
}

int main(){
    //二分搜索测试
    std::cout << "二分搜索测试:";
    int array[] = {9,12,22,36,47,51,68,74,88,91,100};
    int size  = sizeof(array) / sizeof(int);
    std::cout <<  binarySearch(array, size, 88) <<std::endl;

    //递归回顾测试
    std::cout << "递归回顾测试:";
    std::cout << factorial(10) << std::endl;

    //递归二分搜索测试
    std::cout << "递归二分搜索测试:";
    std::cout << binarySearch(array, 0, size - 1, 91) << std::endl;
    return 0;
}