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

class array{
public:
    array(int size = 10) : mCur_(0), mCap_(size){
        mPtr_ = new int[mCap_]();
    }
    ~array(){
        delete []mPtr_;
        mPtr_ = nullptr;
    }
private:
    //内部数组扩容接口
    void expand(int size){
        int *p = new int[size];
        memcpy(p, mPtr_, sizeof(int)*mCur_);//按照字符拷贝
        delete []mPtr_;
        mPtr_ = p;
        mCap_ = size;
    }
public:
    //末尾位置增加元素
    void push_back(int val){
        //如果数组容量已满，先扩容
        if(mCur_ == mCap_){
            expand(2*mCap_);
        }
        mPtr_[mCur_] = val;
        mCur_++;
    }
    //末尾位置删除元素
    void pop_back(){
        if(mCur_ == 0){
            return;
        }
        //这里并没有真的删除最后一个元素,而是直接将元素的个数减1,这样打印时就认为数组里没有最后一个数据了
        mCur_--; 
    }
    //按位置增加元素
    void insert(int pos, int val){
        if(pos < 0 || pos > mCur_){
            return;
        }
        if (mCur_ == mCap_){
            expand(2*mCur_);
        }
        for(int i = mCur_; i > pos; i--){
            mPtr_[i] = mPtr_[i-1];
        }
        mPtr_[pos] = val;
        mCur_++;
    }
    //按位置删除元素
    void erase(int pos){
        if(pos < 0 || pos > mCur_){
            return;
        }
        for(int i = pos; mCur_ >= i; i++){
            mPtr_[i] = mPtr_[i+1];
        }
        mCur_--;
    }
    //查找元素
    int find(int val){
        for(int i = 0; i < mCur_; i++){
            if(mPtr_[i] == val){
                return i;
            }
        }
        return -1;
    }
    void showArray(){
        for(int i =0 ;i < mCur_; i++){
            std::cout << mPtr_[i] << " ";
        }
        std::cout << std::endl;
    }
private:
    int *mPtr_;//指针指向堆内存上开辟的地址
    int mCap_;//当前数组的容量
    int mCur_;//当前数组的元素个数
};

int main(){
    // 末尾增加元素测试
    array array1(10);
    for(int i = 0; i < 10; i++){
        array1.push_back(i);
    }
    array1.showArray();

    //末尾删除元素测试
    array1.pop_back();
    array1.showArray();

    //指定位置增加元素测试
    array1.insert(3,10000);
    array1.showArray();

    //指定位置删除元素测试
    int pos = array1.find(2);
    array1.erase(pos);
    array1.showArray();
    return 0;
}