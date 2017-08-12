#ifndef HEAP_H
#define HEAP_H
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

template<class ValueType, class Container = vector<ValueType>, class Compare = less<ValueType> >
class Heap
{
public:
  Heap(){};
  ~Heap(){};
  void push_heap(const ValueType& v)
  {
    c.push_back(v);
    heapAdjUp();
  }
  void pop_heap()
  {
    c[0] = c.back();
    c.pop_back();
    heapAdjDown(c.size());
  }
  void sort_heap()
  {
    int size = c.size();
    ValueType tmp;
    for(int i=0; i<size; i++)
    {
      tmp = c[0];
      c[0] = c[size-i-1];
      c[size-i-1] = tmp;
      heapAdjDown(size-i-1);
    }
  }
  void make_heap(const ValueType* begin, const ValueType* end)
  {
    while(begin != end)
    {
      push_heap(*begin);
      begin ++;
    }
    //push_heap(*begin);   //last one;
  }
  void print_heap()
  {
    for(size_t i=0; i<c.size(); i++)
      cout << c[i] << ", ";
    cout << endl;
  }
  const ValueType& top()
  {
    return c[0];
  }
private:
  Container c;
  Compare com;
  void heapAdjUp()  //从最后一个元素开始向上比较，将之放在合适的地方
  {
    ValueType hole = c.back();
    int tmp = c.size()-1;
    while(tmp && ((tmp-1)/2)>=0)   //tmp should>0 if tmp==0 is valid while may will run forever
    {
      if(com(hole,c[(tmp-1)/2]))
      {
        c[tmp] = c[(tmp-1)/2];
        tmp = (tmp-1)/2;
      }
      else
        break;
    }
    c[tmp] = hole;
  }

  void heapAdjDown(int size)  //下溯，size表示下溯的范围，即前size个元素
  {
    ValueType hole = c[0];  //从零开始向下比较，把第一个值放到合适的地方
    int tmp = 0,id = 0;  
    while(tmp*2+2 < size)
    {
      if(com(c[tmp*2+1], c[tmp*2+2]))
        id = tmp*2+1;
      else
        id = tmp*2+2;
      if(com(hole, c[id]))
        break;
      else
      {
        c[tmp] = c[id];
        tmp = id;
      }
    }
    if(tmp*2+1<size)   //last element is left of tree
    {
      if(!com(hole, c[tmp*2+1]))
      {
        c[tmp] = c[tmp*2+1];
        tmp = tmp*2+1;
      }
    }
    c[tmp] = hole;
  }
};

#endif