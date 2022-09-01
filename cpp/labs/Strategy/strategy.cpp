#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Record
{
    string name;
    string address;
};

//template function
template <class T>
void sort(T::iterator &first, T::iterator &second,std::function<T> comp)
{
    //

}

int main()
{
    vector<Record> vr(2);
    cout <<"strategy pattern example\n";
    vr[0].name = "Mohamed";
    vr[0].address = "Maadi";

    vr[1].name = "Samir";
    vr[1].address = "aa";

    auto CmpareByName = [](const Record& a, const Record& b)->bool{return a.name > b.name;};
    auto CmpareByAddress = [](const Record& a, const Record& b)->bool{return a.address > b.address;};

    sort(vr.begin(),vr.end(),CmpareByName); //depend on how insertion sort 
    for(auto v : vr)
    {
        cout << "vec.name:" << v.name <<endl;
    }
    
    sort(vr.begin(),vr.end(),CmpareByAddress);

    for(auto v : vr)
    {
        cout << "vec.address:" << v.address <<endl;
    }
    return 0;
}