#include <iostream>
//template<typename T>
class Stack {

public:
    Stack(int capacity):size(capacity)
    {
        //create buffer in heap memory
        buffer = new int[capacity];
        mTop = buffer;
    }

    void push(int element)
    {
        if(!isFull())
        {
            *mTop = element;
             mTop++;
        }
    }
    T pop()
    {
        if(!isEmpty())
        {
            mTop--;
        }
        return *mTop;
    }
    bool isEmpty()
    {
        if(mTop == NULL)
        {
            return true;
        }
        return false;
    }
    bool isFull()
    {
        //check if reached max size
    }
    private:
    int size;
    T *buffer;
    T *mTop;
};

int main()
{
    Stack<double> s1(5);
    Stack<uint32_t> s2
    return 0;
}