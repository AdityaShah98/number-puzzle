#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename Comparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c = Comparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
    std::vector<T> heapvec; //stores heap
    Comparator comp; //stores given comparator
    int size; //stores order of heap (i.e. binary)

    //heapify functions
    void sendup(int index);
    void senddown(int index);


};

// Add implementation of member functions here

template <typename T, typename Comparator>
Heap<T,Comparator>::Heap(int m, Comparator c){
  size = m; //constructs heap
  comp = c;
}

template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap(){

}

template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const{ //returns true if heap is empty
  return heapvec.empty();
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::senddown(int index){
  //heapify down
  if ((index*size) + 1 >= heapvec.size()) //if index is a leaf node
    return; //stop

  int maxIndex = index;
  int childIndex;

    for (int i = 1; i <= size; i++){ //cycles through children
      childIndex = size*index + i;
      if (childIndex < heapvec.size()){ //if child exists
        if (comp(heapvec[childIndex],heapvec[maxIndex])){ //compare to max child
          maxIndex = childIndex; //find max child
        }
      }
    }

  if (maxIndex != index){ //if the item isn't in the right position yet
    //swap
    T temp = heapvec[maxIndex];
    heapvec[maxIndex] = heapvec[index];
    heapvec[index] = temp;
  }else{
    return;
  }
  senddown(maxIndex);
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::sendup(int index){
//heapify up
  int parentIndex = (index-1)/size;

  while(index >= size-1 && comp(heapvec[index],heapvec[parentIndex])){
    //iteratively sends item to its appropriate place
    T temp = heapvec[parentIndex];
    heapvec[parentIndex] = heapvec[index];
    heapvec[index] = temp;
    index = parentIndex;
    parentIndex = (index-1)/size;
  }
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item){
  heapvec.push_back(item);
  sendup(heapvec.size()-1);
  }


template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // Heap has atleast 1 item...
  return (heapvec[0]); //return the first element of vector (top of tree)

}


template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
//Heap has atleast 1 item...
  heapvec[0] = heapvec[heapvec.size()-1];
  heapvec.pop_back();
  senddown(0);
}

#endif