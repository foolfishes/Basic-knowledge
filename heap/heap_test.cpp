#include "heap.h"  
#include <iostream>  
#include <list>

using namespace std;  
void test1();
void test2();

int main()  
{  
    cout << "test1:" << endl;
    test1();

    cout << "test2:" << endl;
    test2(); 
    

    return 0;  
}  

void test1()
{
    const int n = 9;  
    int data[n] = {3,6,12,1,4,11,9,3,2};  
   
    Heap<int> myheap;
    myheap.make_heap(data,data+9);
    myheap.print_heap();

    myheap.push_heap(0);
    myheap.print_heap();

    myheap.pop_heap();
    myheap.print_heap();

    myheap.sort_heap();
    myheap.print_heap();

    int a = myheap.top();
    cout << "top of heap: " << a << endl;

}

class strcom
{
public:
    bool operator()(const string& s1, const string& s2) const
    {
        if((!s1.empty()) && (!s2.empty()))
            return s1[0] < s2[0];
        else
            return false;
    }
};

void test2()
{ 
    Heap<string,vector<string>,strcom>myheap;

    myheap.push_heap("efd");
    myheap.push_heap("fefe");
    myheap.push_heap("hefgafg");
    myheap.push_heap("ghtht");
    myheap.push_heap("bnreg");
    myheap.push_heap("c3hdsa");
    myheap.push_heap("arvb");
    myheap.print_heap();

    myheap.pop_heap();
    myheap.print_heap();

    myheap.sort_heap();
    myheap.print_heap();

    string a = myheap.top();
    cout << "top of heap: " << a << endl;

}