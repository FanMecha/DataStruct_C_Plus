//
// Created by MechaFan on 2025/4/11.
//

//======链表的特征：链表的每一个节点都是在堆内存上独立new出来的，节点内存不连续
//======链表的优点
//1.内存利用率高，不需要连续的大块内存
//2.插入和删除元素不需要移动其他元素，时间复杂度为O(1)（这里单单指插入和删除操作，并不考虑插入和删除之前和查找操作的时间复杂度）
//3.不需要专门进行内存扩容
//======数组的缺点
//1.内存占用大，每一个节点不仅存储数据，还需要内存存储下一个节点的地址
//2.节点内存不连续，无法进行随机访问
//3.链表搜索效率不高，只能从头节点开始逐节点遍历

#include <iostream>
#include <stdlib.h>
#include <time.h>

class Node{
public:
    Node(int data = 0):data_(data),next_(nullptr){}
    int data_;
    Node *next_;
};

class Clink{
public:
    Clink(){
        head_ = new Node();
    }
    ~Clink(){
        Node *p = head_;
        while(p != nullptr){
            head_ = head_->next_;
            //循环时,删除p之后,p就成野指针了,所以要再赋值到下一个
            delete p;
            p = head_;
        }
    }
private:
    Node *head_;
public:

    //链表尾部插入节点
    void insertTail(int val){
        //先找到当前链表的末尾节点
        Node *p = head_;
        while(p->next_!=nullptr){
            p = p->next_;
        }
        //生成新的节点
        Node *node = new Node(val);
        //把新节点挂在尾节点的后面
        p->next_ = node;
    }

    //链表头部插入节点
    void insertHead(int val)
    {
        //生成新的节点
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    //删除元素val的第一个节点
    void remove(int val){
        Node *q = head_;
        Node *p = head_->next_;
        while(p != nullptr){
            if(p->data_ == val){
                q->next_ = p->next_;
                delete p;
                return;
            }else{
                q = p;
                p = p->next_;
            }
        }
    }

    //删除元素val的所有节点
    void removeAll(int val){
        Node *q = head_;
        Node *p = head_->next_;
        while (p != nullptr)
        {
            if(p->data_ == val){
                q->next_ = p->next_;
                delete p;
                //对指针p进行重制并指向原来p指向的下一个地址
                p = q->next_;
            }else{
                q = p;
                p = p->next_;
            }
        }
    }

    //查找链表中指定值的节点
    bool find(int val){
        Node *p = head_->next_;
        while(p != nullptr){
            if (p->data_ == val){
                return true;
            }else{
                p = p->next_;
            }
        }
        return false;
    }

    //单链表逆序
    void reverse(){
        Node *p = head_->next_;
        if(p == nullptr){
            return;
        }
        head_->next_ = nullptr;
        while(p != nullptr){
            Node *q = p->next_;
            //这里其实是头插法
            p->next_ = head_->next_;
            head_->next_ = p;
            p = q;
        }
    }

    //求链表倒数第k个节点的值
    int getKValue(int size){
        if (size < 1){
            return -1;
        }
        Node *p = head_;
        Node *q = head_;
        for (int i = 0; i < size; i++){
            p = p->next_;
            if(p->next_ == nullptr){
                return -1;
            }
        }
        //注意这里用节点p本身的地址做判断
        while(p != nullptr){
            q = q->next_;
            p = p->next_;
        }
        return q->data_;
    }

    //生成单链表环
    void generateListCircle(){
        Node *p = head_;
        while(p->next_ != nullptr){
            p = p->next_;
        }
        p->next_ = head_->next_;
    }

    //链表环及环的入口地址
    bool listCircle(){
        Node *fast = head_;
        Node *slow = head_;
        while(fast != nullptr && fast->next_ != nullptr){
            slow = slow->next_;
            fast = fast->next_->next_;
            //这里表示快指针和满指针相遇
            if(slow == fast){
                std::cout << "单链表存在环" <<" ";
                fast = head_;
                while(fast != slow){
                    fast = fast->next_;
                    slow = slow->next_;
                }
                int val = slow->data_;
                std::cout << "环的入口节点的值为: "<< val << std::endl;
                return true;
            }
        }
        return false;
    }

    //打印链表
    void showNode(){
        Node *p = head_->next_;
        while (p != nullptr)
        {
            std::cout << p->data_ << " ";
            p = p->next_;
        }
        std::cout << std::endl;
    }
};

int main(){
    //头插和尾插测试
    Clink clink;
    srand(time(0));
    for (int i = 0; i < 10; i++){
        int val = rand() % 100;
        clink.insertHead(val);
        std::cout << val << " ";
    }
    std::cout << std::endl;
    clink.showNode();
    
    //删除指定元素的节点测试
    clink.insertHead(20000);
    clink.insertTail(10000);
    clink.insertTail(20000);
    clink.insertHead(10000);
    clink.showNode();
    clink.remove(10000);
    clink.showNode();

    //删除指定元素的所有节点测试
    clink.removeAll(20000);
    clink.showNode();

    //查找元素测试
    std::cout << clink.find(10000) << std::endl;

    //单链表逆序测试
    clink.reverse();
    clink.showNode();

    //链表倒数第k个节点的值测试
    std::cout << clink.getKValue(1) <<std::endl;

    //单链表环测试
    clink.generateListCircle();
    bool islistcircle = clink.listCircle();
    
    return 0;
}