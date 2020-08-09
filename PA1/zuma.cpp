
#include <iostream>
#include <string>
using namespace std;

class Node{
    public:
    char data_;
    Node *next;
    Node *pre;
    //constructor
    Node(){}
    Node(char e,Node *p=nullptr,Node *n=nullptr):data_(e),pre(p),next(n){}
    Node *insertAsPrevious(char data);
    Node *insertAsNext(char data);
    
};
class ZumaList{
    protected:
        int size_;
        Node *head_;
        Node *trailer_;
        void copyfrom(char*A);
        void init();
    public:
    ZumaList(){init();}
    ZumaList(char *A){copyfrom(A);}
   // ~ZumaList();
    
    Node* insert(int key,char data);
    //Node* find(int key);

    void boomCheck(Node *cur);
    Node *vanish(Node *start,Node *end,int num);
    void getElem();
    
};

Node * Node::insertAsPrevious(char data){
    Node *cur=new Node(data);
    this->pre=cur;
    cur->next=this;
    cur->pre=nullptr;
    return cur;
}

Node * Node::insertAsNext(char data){
    Node *cur=new Node(data);
    this->next=cur;
    cur->pre=this;
    cur->next=nullptr;
    return cur;
}

void ZumaList::getElem(){
    if(size_==0){
        cout<<"-";
    }
    else{
        Node *tmp=head_;
        while((tmp=tmp->next)!=trailer_)
            cout<<tmp->data_;
    }
    cout<<endl;
}
void ZumaList::init(){
    head_=new Node;
    trailer_=new Node;
    size_=0;
    head_->next=trailer_;
    head_->pre=nullptr;
    trailer_->pre=head_;
    trailer_->next=nullptr;
    head_->data_='-';
    trailer_->data_='-';
}

void ZumaList::copyfrom(char *A){
    init();
    if(A[0]=='-')
        return;
    Node *cur=head_;
    while(A[size_]){
        cur=cur->insertAsNext(A[size_]);
        size_++;
    }
    cur->next=trailer_;
    trailer_->pre=cur;
}

Node* ZumaList::insert(int key,char data){
    if(key<size_>>1){
        Node *cur=head_->next;
        while((0<key--)&&(cur!=trailer_)){
            cur=cur->next;
        }
        Node *tmp=cur->pre;
        Node *new_node=cur->insertAsPrevious(data);
        new_node->pre=tmp;
        tmp->next=new_node;
        size_++;
        return new_node;
    }
    else{
        Node *cur=trailer_->pre;
        int i=size_;
        while((key<i--)&&(cur!=head_)){
            cur=cur->pre;
        }
        Node *tmp=cur->next;
        Node *new_node=cur->insertAsNext(data);
        new_node->next=tmp;
        tmp->pre=new_node;
        size_++;
        return new_node;
    }
    
}


Node *ZumaList::vanish(Node *start, Node* end,int num){
    //Node *p=start;
    /*while(p!=end){
        p->pre->next=p->next;
        p->next->pre=p->pre;
        Node *tmp=p;
        p=p->next;
        delete tmp;
        size_--;
    }*/
    start->pre->next=end;
    end->pre=start->pre;
    size_=size_-num+1;
    return end;
}

void ZumaList::boomCheck(Node* cur){
    
    if((size_<3)||(cur==head_)||(cur==trailer_))
        return;
    Node *start=cur;
    Node *end=cur;
    int p=0;
    int n=0;
    int num=0;
    char c=cur->data_;
    do{
        n++;
        end=end->next;
    }while(end->data_==c);
    do{
        p++;
        start=start->pre;
    }while(start->data_==c);

    if((num=p+n)>3){
        Node *n=vanish(start->next,end,num);
        if(start->data_==end->data_){
            boomCheck(n);
        }
    }

    return;
}



int main(){
    char origin[10000];
    cin>>origin;
    ZumaList zuma(origin);
    //zuma.getElem();
    int num;
    cin>>num;
    for(int i=0;i<num;i++){
        int rank;
        char new_elem;
        cin>>rank>>new_elem;
        Node *n=zuma.insert(rank,new_elem);
        zuma.boomCheck(n);
        zuma.getElem();
    }
    
    return 0;
}