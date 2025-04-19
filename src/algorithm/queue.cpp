//
// Created by MechaFan on 2025/4/18.
//

//======队列的特征：先进先出，后进后出，只能操作队列头部和尾部的元素，不是新的数据结构底层基于数组或者链表
//======环形队列：
//======链式队列：
#include <iostream>


//==========================环形队列

class circleQueue{
public:
    circleQueue(int size = 10) : mCap_(size), size_(0), front_(0), back_(0){
        mPtr_ = new int[mCap_];
    } 
    ~circleQueue(){
        delete []mPtr_;
        mPtr_ = nullptr;
    }
public:
    //队尾入队
    void push(int val){
        if((back_+1) % mCap_ == front_){
            expand(2*mCap_);
        }
        mPtr_[back_] = val;
        back_ = (back_ + 1) % mCap_;
        size_++;
    }
    //队头出队
    void pop(){
        if(front_ == back_){
            throw "queue is empty!";
        }
        front_ = (front_ + 1) % mCap_;
        size_--;
    }
    //队头元素
    int front() const{
        if(front_ == back_){
            throw "queue is empty!";
        }
        return mPtr_[front_];
    }
    //队尾元素
    int back() const{
        if(front_ == back_){
            throw "queue is empty!";
        }
        //队尾元素指向的是数组的前一个
        return mPtr_[(back_-1+mCap_)%mCap_];
    }
    //判断队列是否为空
    bool empty(){
        return front_ == back_ ? true : false;
    }
    //队列元素的个数
    int size(){
        return size_;
    }
private:
    void expand(int size){
        //环形拷贝要注意
        int *p = new int[size];
        int i = 0; //用于遍历新内存
        int j = front_; //用于遍历老内存
        for(; j != back_; i++, j=(j+1)%mCap_){
            p[i] = mPtr_[j];
        }
        delete []mPtr_;
        mPtr_ = p;
        mCap_ = size;
        front_ = 0;
        back_ = i;
    }   
private:
    int *mPtr_; //数组指针
    int mCap_;  //容量
    int front_; //队头
    int back_;  //队尾
    int size_;  //队列元素的个数
};

int main(){
    int arr[] = {12,4,56,7,89,31,53,75,100,200,300};
    circleQueue c;
    for (int i = 0; i < 11; i++){
        c.push(arr[i]);
    }
    std::cout << c.front() << " "<< c.back() <<std::endl;
    while( !c.empty()){
        std::cout << c.front() << " "<< c.back() <<std::endl;
        c.pop();
    }
    return 0;
}

