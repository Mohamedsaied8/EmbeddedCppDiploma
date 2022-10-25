/*
    CreateNode
    InsertNode
    DeleteNode
    Append
    Traverse
*/
#include <iostream>

using namespace std;

struct Record
{
   string name;
   string address; 
};

struct Node
{
    Record record;
    Node *Next;
};

void print(Node *Head)
{
    while(Head)
    {
         cout << Head->record.name << endl;        
         Head = Head->Next;
    }
}

int main()
{

    Node *Head = new Node; //in heap
    Node *FirstNode = new Node;

    Head->record.name = "Mohamed";
    Head->record.address = "Maadi";

    Head->Next = FirstNode;
    FirstNode->record.name = "Robotics";
    FirstNode->record.address = "Corner";
    FirstNode->Next = nullptr;
    print(Head);

    return 0;
}