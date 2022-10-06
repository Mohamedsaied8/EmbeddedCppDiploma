#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class student {
    public:
    string name;
    string address;
};
int main(){
    vector<student> students(2);
    students[0].name = "Sadeen Alaa";
    students[0].address = "Sheikh Zaid";
    students[1].name = "Alaa Ashraf";
    students[1].address = "six october city";
    sort(students.begin(), students.end(), [](student a, student b){return tolower(a.name[0]) < tolower(b.name[0]); });
    for(auto s: students){
        cout<<"Name : "<<s.name<< "--------- Address: "<< s.address <<endl;
    }
    return 0;
}