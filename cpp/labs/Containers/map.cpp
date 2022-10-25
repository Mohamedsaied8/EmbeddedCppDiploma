// CPP Program to demonstrate the implementation in Map

#include <iostream>
#include <iterator>
#include <map>
using namespace std;

int main()
{
	map<string, int> myMap;
	myMap.insert(pair<string, int>("Mohamed", 40)); 

	// empty map container
	map<int, int> quiz;

	// insert elements in random order
	quiz.insert(pair<int, int>(1, 40)); //make_pair(1,40s)
	quiz.insert(pair<int, int>(2, 30));
	quiz.insert(pair<int, int>(3, 50));
	quiz.insert(pair<int, int>(4, 20));
	quiz.insert(pair<int, int>(5, 50));
	quiz.insert(pair<int, int>(6, 50));
	
	quiz[7]=10;	 // another way of inserting a value in a map
	

	// printing map quiz
	map<int, int>::iterator itr;
	cout << "\nThe map quiz is : \n";
	cout << "\tKEY\tELEMENT\n";
	for (itr = quiz.begin(); itr != quiz.end(); ++itr) {
		cout << '\t' << itr->first << '\t' << itr->second << '\n';
	}
	cout << endl;

	// assigning the elements from quiz to quiz2
	map<int, int> quiz2(quiz.begin(), quiz.end());

	// print all elements of the map quiz2
	cout << "\nThe map quiz2 after"
		<< " assign from quiz is : \n";
	cout << "\tKEY\tELEMENT\n";
	for (itr = quiz2.begin(); itr != quiz2.end(); ++itr) {
		cout << '\t' << itr->first << '\t' << itr->second
			<< '\n';
	}
	cout << endl;

	// remove all elements up to
	// element with key=3 in gquiz2
	cout << "\n quiz2 after removal of"
			" elements less than key=3 : \n";
	cout << "\tKEY\tELEMENT\n";
	quiz2.erase(quiz2.begin(), quiz2.find(3));
    
	for (itr = quiz2.begin(); itr != quiz2.end(); ++itr) {
		cout << '\t' << itr->first << '\t' << itr->second
			<< '\n';
	}

	// remove all elements with key = 4
	int num;
	num = quiz2.erase(4);
	cout << "\ngquiz2.erase(4) : ";
	cout << num << " removed \n";
	cout << "\tKEY\tELEMENT\n";
	for (itr = quiz2.begin(); itr != quiz2.end(); ++itr) {
		cout << '\t' << itr->first << '\t' << itr->second
			<< '\n';
	}

	cout << endl;

	// lower bound and upper bound for map gquiz1 key = 5
	cout << "gquiz1.lower_bound(5) : "
		<< "\tKEY = ";
	cout << quiz2.lower_bound(5)->first << '\t';
	cout << "\tELEMENT = " << quiz2.lower_bound(5)->second
		<< endl;
	cout << "gquiz1.upper_bound(5) : "
		<< "\tKEY = ";
	cout << quiz2.upper_bound(5)->first << '\t';
	cout << "\tELEMENT = " << quiz2.upper_bound(5)->second
		<< endl;

	return 0;
}
