//
// Created by MechaFan on 2025/4/28.
//

//======冒泡排序

#include <iostream>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int size){
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size - 1 - i; j++){
            if(arr[j] > arr[j+1]){
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main(){
    //冒泡排序测试
    std::cout << "冒泡排序测试:";
    srand(time(NULL));
    int array[15];
    for(int i = 0; i < 15; i++){
        array[i] = rand() % 100;
    }

    int size = sizeof(array) / sizeof(int);
    bubbleSort(array, size);

    for (int i = 0; i < size; i++){
        std::cout << array[i] <<" ";
    }
    std::cout <<std::endl;
    
    return 0;
}