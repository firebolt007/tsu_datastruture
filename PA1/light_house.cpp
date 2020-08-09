#include <iostream>
using namespace std;
class Position{
    public:
    int x;int y;
    Position & operator=(const Position &p){
        x=p.x;
        y=p.y;
        return *this;
    }
    Position(int x_in,int y_in){x=x_in;y=y_in;}
    Position(){}
};
class Array {
    private:
    int size_;
    int capacity_;
    
    void merge(int lo, int mi, int hi);
    unsigned long int invOutside(int lo,int mi,int hi);
    void copyfrom(const Position *A,const int len);
    
    public:
    Position *elem_;
    Array & operator=(const Array& a);
    int size() const{return size_;}
    Array(Position *A,int len){copyfrom(A,len);}
    Array(int len);
    void mergeSort(int lo, int hi);
    unsigned long int invInside(int lo,int hi);
    
};
Array::Array(int len){
    elem_=new Position[len];
    size_=0;
    while(size_<len){
        elem_[size_++]=Position(0,0);
    }

}
Array & Array::operator=(const Array & a){
    if(elem_) delete []elem_;
    copyfrom(a.elem_,a.size());
    return *this;
}

void Array::copyfrom(const Position *A,const int len){
    elem_=new Position[capacity_=2*len];
    size_=0;
    int i=0;
    while(i<len){
        elem_[size_++]=A[i++];
    }
}
void Array::merge(int lo, int mi, int hi){
    Position *A=elem_+lo;
    int lb=mi-lo; 
    int lc=hi-mi;
    Position *B=new Position[lb];
    for(int i=0;i<lb;i++){
        B[i]=A[i];
    }
    Position *C=elem_+mi;
    for(int i=0,j=0,k=0;(j<lb)||(k<lc);){
        if((j<lb)&&(!(k<lc)||(B[j].x<=C[k].x))) {A[i++]=B[j++];}
        if((k<lc)&&(!(j<lb)||(C[k].x<B[j].x))) {A[i++]=C[k++];}
    }
}

void Array::mergeSort(int lo,int hi){
    if(hi-lo<2)
        return;
    int mi=(lo+hi)>>1;
    mergeSort(lo,mi);
    mergeSort(mi,hi);
    merge(lo,mi,hi);
}

unsigned long int Array::invOutside(int lo, int mi, int hi){
    unsigned long int num=0;
    Position *A=elem_+lo;
    int lb=mi-lo; 
    int lc=hi-mi;
    Position *B=new Position[lb];
    for(int i=0;i<lb;i++){
        B[i]=A[i];
    }
    Position *C=elem_+mi;
    for(int i=0,j=0,k=0;(j<lb)||(k<lc);){
        if((j<lb)&&(!(k<lc)||(B[j].y<=C[k].y))) {
            A[i++]=B[j++];
            num=num+lc-k;
        }
        if((k<lc)&&(!(j<lb)||(C[k].y<B[j].y))) {
            A[i++]=C[k++];
            //num=num+lb-j;
        }
    }
    delete []B;
    return num;
}

unsigned long int Array::invInside(int lo, int hi){
    if(hi-lo<2)
        return 0;

    int mi=(lo+hi)>>1;
    return invInside(lo, mi)+invInside(mi, hi)+invOutside(lo,mi,hi);
    
}


int main(){
    int num;
    cin>>num;
    //Position *light_input=new Position[num];
    Array light(num);
    for(int i=0;i<num;i++){
        //cin>>light_input[i].x>>light_input[i].y;
        int x_in;int y_in;
        cin>>x_in>>y_in;
        light.elem_[i]=Position(x_in,y_in);
    }
    //Array light(light_input,num);
    //delete [] light_input;
    light.mergeSort(0,num);
    
    cout<<light.invInside(0,num)<<endl;
    
    return 0;
}