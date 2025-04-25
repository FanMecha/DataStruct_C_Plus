//
// Created by MechaFan on 2025/4/17.
//

//======栈的特征：先进后出，后进先出，只能操作栈顶元素，不是新的数据结构底层基于数据或者链表
//======顺序栈：入栈出栈的时间复杂度为O(1)，但是顺序栈扩容的时间复杂度为O(n)，
//======链式栈：入栈出栈的时间复杂度为O(1)，但是链式栈不需要扩容
#include <iostream>

//<========================顺序栈======================>
class arrayStack{
public:
    arrayStack(int size = 10): mTop_(0), mCap_(size){
        mPtr_ = new int[mCap_];
    }
    ~arrayStack(){
        delete []mPtr_;
        mPtr_ = nullptr;
    }
private:
    void expand(int size){
        int *p = new int[size];
        memcpy(p, mPtr_, mTop_ * sizeof(int));
        delete []mPtr_;
        mPtr_ = p;
        mCap_ = size;
    }
public:
    //入栈
    void push(int val){
        if(mTop_ == mCap_){
            expand(2 * mCap_);
        }
        mPtr_[mTop_] = val;
        mTop_++;
    }
    //出栈
    void pop(){
        if(mTop_ == 0){
            throw "stack is empty!";
        }
        mTop_--;
    }
    //获取栈顶元素
    int top()const{
        if(mTop_ == 0){
            throw "stack is empty!";
        }
        return mPtr_[mTop_ - 1];
    } 
    //判断栈是否为空
    bool empty(){
        return mTop_ == 0 ? true : false;
    }
    //获取栈的大小
    int size() const{
        return mTop_;
    }
private:
    int *mPtr_; //顺序栈的地址
    int mCap_;  //栈容量
    int mTop_;  //栈元素个数(即代表栈顶元素)
};

//<========================链式栈======================>
class listStack{
public:
    listStack():size_(0){
        head_ = new Node();
    }
    ~listStack(){
        Node *p = head_;
        while(p != nullptr){
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }
public:
    //入栈(头插模拟栈顶)
    void push(int val){
        Node *p = new Node(val);
        p->next_ = head_->next_;
        head_->next_ = p;
        size_++;
    }
    //出栈
    void pop(){
        Node *p = head_->next_;
        if(p == nullptr)
        {
            throw "stack is empty!";
        }
        head_->next_ = p->next_;
        delete p;
        size_--;
    }
    //获取栈顶元素
    int top()const{
        if(head_->next_ == nullptr){
            throw "stack is empty";
        }
        return head_->next_->data_;
    }
    //判断栈是否为空
    bool empty(){
        return head_->next_ == nullptr ? true : false;
    }
    //栈元素大小
    int size() const{
        return size_;
    }
private:
    struct Node
    {
        Node(int data = 0): data_(data),next_(nullptr){}
        int data_;
        Node *next_;
    };
    Node *head_;
    int size_;
};
int main(){
    std::cout <<"================顺序栈测试===============" <<std::endl;
    int arr[7] = {11, 8, 52, 90, 14, 28, 36};
    arrayStack as;
    for (int i = 0; i < 7; i++){
        as.push(arr[i]);
    }
    std::cout << "顺序栈的大小为" << as.size()<< " "<< "并且栈的元素为:" << " ";
    while(!as.empty()){
        std::cout << as.top()<< " ";
        //只能先把栈顶元素pop掉才能访问里面的元素
        as.pop();
    }
    std::cout << std::endl;

    std::cout <<"===============链式栈测试===============" <<std::endl;
    listStack l;
    for (int i = 0; i < 7; i++){
        l.push(arr[i]);
    }
    std::cout << "链式栈的大小为" << l.size()<< " "<< "并且栈的元素为:" << " ";
    while(!l.empty()){
        std::cout << l.top()<< " ";
        l.pop();
    }
    std::cout << std::endl;
    return 0;
}

