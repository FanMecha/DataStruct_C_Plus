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

//<========================单向链表======================>
class list{
public:
    list(){
        head_ = new Node();
    }
    ~list(){
        Node *p = head_;
        while(p != nullptr){
            head_ = head_->next_;
            //循环时,删除p之后,p就成野指针了,所以要再赋值到下一个
            delete p;
            p = head_;
        }
    }
private:
    struct Node
    {
    public:
        Node(int data = 0) : data_(data), next_(nullptr){
        }
        int data_;
        Node *next_;
    };
    Node *head_;
public:
    //尾插
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
    //头插
    void insertHead(int val)
    {
        //生成新的节点
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }
    //删除指定元素的第一个节点
    void remove(int val){
        Node *q = head_;
        Node *p = head_->next_;
        while(p != nullptr){
            if(p->data_ == val){
                q->next_ = p->next_;
                delete p;
                return;
            }else{
                q = q->next_;
                p = p->next_;
            }
        }
    }
    //删除指定元素的所有节点
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
    //查找
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
public:
    //========================单向链表问题案例======================
    //链表逆序
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
    int findKNode(int size){
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
    // 删除倒数第K个节点
    void removeKNode(int size){
        Node *p = head_;
        Node *q = head_;
        if (size < 1){
            throw "size is small";
        }
        for (int i = 0; i < size + 1; i++){
            p = p->next_;
        }
        if(p->next_ == nullptr){
            throw "";
        }
        while(p != nullptr){
            q = q->next_;
            p = p->next_;
        }
        q->next_ = q->next_->next_;
    }
    //合并两个有序链表
    void mergeList(list &l){
        Node *p = head_->next_;
        Node *q = l.head_->next_;
        Node *last = head_;
        l.head_->next_ = nullptr;
        while(p != nullptr && q != nullptr){
            if(p->data_ < q->data_){
                last->next_ = p;
                p = p->next_;
                last = last->next_;
            }else{
                last->next_ = q;
                q = q->next_;
                last = last->next_;
            }
            if(p != nullptr){
                last->next_ = p;
            }else{
                last->next_ = q;
            }
        }
    }
    //判断两个链表是否相交
    bool isMerge(list &l){
        Node *p = head_->next_;
        Node *q = l.head_->next_;
        int num1 = 0, num2 = 0;
        while(p != nullptr){
            num1++;
            p = p->next_;
        }
        while(q != nullptr){
            num2++;
            q = q->next_;
        }
        p = head_;
        q = l.head_;
        if (num1 > num2){
            int offset = num1 - num2;
            for(int i = 0; i < offset; i++){
                p = p->next_;
            }
        }
        if (num1 < num2){
            int offset = num2 - num1;
            for(int i = 0; i < offset; i++){
                q = q->next_;
            }
        }
        while(p != nullptr){
            if(p->data_ == q->data_){
                return true;
            }
            p = p->next_;
            q = q->next_;
        }
        return false;
    }
    //链表环
    bool isCircle(){
        Node *fast = head_;
        Node *slow = head_;
        while(fast != nullptr && fast->next_ != nullptr){
            slow = slow->next_;
            fast = fast->next_->next_;
            //这里表示快指针和满指针相遇
            if(slow == fast){
                fast = head_;
                while(fast != slow){
                    fast = fast->next_;
                    slow = slow->next_;
                }
                return true;
            }
        }
        return false;
    }
};

//<========================单向循环链表======================>
class circleList{
public:
    circleList(){
        head_ = new Node();
        head_->next_ = head_;
    }
    ~circleList(){
        Node *p = head_;
        while(p != head_){
           head_ = head_->next_;
           delete p;
           p = head_;
        }
        delete head_;
    }
public:
    //头插
    void insertHead(int val){
        Node *p = new Node(val);
        p->next_ = head_->next_;
        head_->next_ = p;
    }
    //尾插
    void insertTail(int val){
        Node *node = new Node(val);
        Node *p = head_;
        while(p->next_ != head_){
            p = p->next_;
        }
        p->next_ = node;
        node->next_ = head_;
    }
    //删除第一个指定节点
    void remove(int val){
        Node *p = head_->next_;
        Node *q = head_;
        while(p != head_){
            if(p->data_ == val){
                q->next_ = p->next_;
                delete p;
                break;
            }
            p = p->next_;
            q = q->next_;
        }
    }
    //查找
    bool find(int val){
        Node *p = head_;
        while(p->next_ != head_){
            if(p->data_ == val){
                return true;
            }else{
                p = p->next_;
            }
        }
        return false;
    }
    //打印
    void showNode(){
        Node *p = head_->next_;
        while (p != head_){
            std::cout << p->data_ << " ";
            p = p->next_;
        }
        std::cout << std::endl;
    }
private:
    struct Node
    {
    public:
        Node(int data = 0) : data_(data), next_(nullptr){}
        int data_;
        Node *next_;
    };
    Node *head_;
};

int main(){
    std::cout <<"===============单向链表测试================" <<std::endl;
    //头插测试
    list l;
    std::cout << "头插测试:";
    l.insertHead(10000);
    l.insertHead(1221);
    l.insertHead(518);
    l.insertHead(304);
    l.insertHead(286);
    l.showNode();

    //尾插测试
    std::cout << "尾插测试:";
    l.insertTail(227);
    l.insertTail(10000);
    l.showNode();

    //删除第一个指定节点测试
    std::cout << "删除第一个指定节点测试:";
    l.remove(227);
    l.showNode();

    //删除所有指定节点测试
    std::cout << "删除所有指定节点测试:";
    l.removeAll(10000);
    l.showNode();
    
    //查找节点测试
    std::cout << "查找指定节点测试: ";
    l.find(1221) ? std::cout << "true" <<std::endl : std::cout << "false" <<std::endl;

    //单链表逆序测试
    std::cout << "单链表逆序测试:";
    l.reverse();
    l.showNode();

    //查找倒数第K个节点测试
    std::cout << "查找倒数第3个节点测试: " << l.findKNode(3) <<std::endl;
    
    //删除倒数第K个节点测试
    std::cout << "删除倒数第2个节点测试:";
    l.removeKNode(2);
    l.showNode();

    //有序链表合并测试
    std::cout << "有序链表合并测试:\n";
    list l1;
    std::cout << "list1:";
    l.reverse();
    l.showNode();
    l1.insertTail(227);
    l1.insertTail(334);
    l1.insertTail(10000);
    std::cout << "list2:";
    l1.showNode();
    
    l.mergeList(l1);
    l.showNode();

    //链表相交测试
    std::cout << "链表相交测试:";
    l.isMerge(l1) ? std::cout << "true"<<std::endl : std::cout << "false" <<std::endl;

    //链表环测试
    std::cout << "链表环测试:";
    l.isCircle() ? std::cout << "true"<<std::endl : std::cout << "false" <<std::endl;

    std::cout <<"===============单向循环链表测试================" <<std::endl;
    //头插测试
    std::cout << "头插测试:";
    circleList cl;
    cl.insertHead(100);
    cl.insertHead(200);
    cl.insertHead(300);
    cl.insertHead(400);
    cl.showNode();

    //尾插测试
    std::cout << "尾插测试:";
    cl.insertTail(500);
    cl.insertTail(600);
    cl.insertTail(700);
    cl.insertTail(800);
    cl.showNode();
    
    //删除第一个节点测试
    std::cout << "删除第一个节点测试:";
    cl.remove(800);
    cl.showNode();

    //查找测试
    std::cout << "查找测试:";
    cl.find(100) ? std::cout << "true"<<std::endl : std::cout << "false" <<std::endl;

    return 0;
}