//
// Created by MechaFan on 2025/4/9.
//

//======数组特征：内存连续，下标访问快
//======数组的优点(内存连续)
//1.数组的下标访问(随机访问)的时间复杂度为O(1)
//2.末尾位置增加或删除元素的时间复杂度为O(1)
//3.访问元素前后相邻位置的元素方便
//======数组的缺点
//1.非末尾位置增加或删除元素需要进行大量的数据移动
//2.对于无序数组用线性搜索，其时间复杂度为O(n)
//3.对于有序数组用二分搜索，其时间复杂度为O(logn)

#include <iostream>
#include <time.h>
#include <stdlib.h>

class array{
public:
    array(int size = 10):mCur_(0),mCap_(size){
        mPtr_ = new int[mCap_](); 
    }
private:
    void expand(int size){
        int *p = new int[size];
        memcpy(p, mPtr_, sizeof(int)*mCur_);
        //这里虽然删除了指针指向的内存，即指针不指向任何内存，但是指针本身还是存在的
        delete []mPtr_;
        mPtr_ = p;
        mCap_ = size;
    }
public:
    //在数组尾部插入元素
    void push_back(int val){
        if(mCur_ == mCap_){
            expand(2*mCap_);
        }
        mPtr_[mCur_] = val;
        mCur_++;
    }
    //删除数组尾部元素
    void pop_back(){
        if(mCur_ == 0){
            return;
        }
        //这里并没有真的删除最后一个元素,而是直接将元素的个数减1,这样打印时就认为数组里没有最后一个数据了
        mCur_--;
    }
    //在数组指定位置插入元素
    void insert(int pos, int val){
        if(pos < 0 || pos > mCur_){
            return;
        }
        if(mCur_ == mCap_){
            expand(2*mCap_);
        }
        for(int i = mCur_; i > pos; i--){
            mPtr_[i] = mPtr_[i-1];
        }
        mPtr_[pos] = val;
        mCur_++;
    }
    //删除数组指定位置元素
    void erase(int pos){
        if(pos < 0 || pos > mCur_){
            return;
        }
        for(int i = pos; i <= mCur_; i++){
            mPtr_[i] = mPtr_[i+1];
        }
        mCur_--;
    }
    //查找元素
    int find(int val){
        for (int i = 0; i< mCur_; i++){
            if(mPtr_[i] == val){
                return i;
            }
        }
        return -1;
    }
    //===============双指针解决数组问题案例==============
    //数组逆序
    void reverse(){
        int *p = mPtr_;
        int *q = p + mCur_ - 1;
        while(p < q){
            int tmp = *p;
            *p = *q;
            *q = tmp;
            p++;
            q--;
        }
    }
    //数组奇数放左边,偶数放右边
    void adjustArray(){
        int *p = mPtr_;
        int *q = p + mCur_ - 1;
        while(p < q){
            //找偶数
            while(p < q){
                if(*p % 2 == 0){
                    break;
                }
                p++;
            }
            //找奇数
            while(p < q){
                if(*q % 2 == 1){
                    break;
                }
                q--;
            }
            if(p < q){
                int tmp = *p;
                *p = *q;
                *q = tmp;
                p++;
                q--;
            }
        }
    }
    //打印数组
    void showArray(){
        for(int i = 0; i< mCur_; i++){
            std::cout << mPtr_[i]<<" ";
        }
        std::cout <<std::endl;
    }
private:
    int *mPtr_; //数组的地址
    int mCur_; //数组元素的个数
    int mCap_; //数组的容量
};
int main(){
    //末尾增加元素测试
    array arr;
    for (int i = 0; i < 10; i++){
        int val = rand() % 100;
        arr.push_back(val);
    }
    arr.showArray();

    //末尾删除元素测试
    arr.pop_back();
    arr.showArray();

    //指定位置插入元素测试
    arr.insert(3,10000);
    arr.showArray();

    //指定位置删除元素测试
    int pos = arr.find(10000);
    arr.erase(pos);
    arr.showArray();

    //数组逆序测试
    arr.reverse();
    arr.showArray();

    //奇偶数测试
    arr.adjustArray();
    arr.showArray();

    return 0;
}