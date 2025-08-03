#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

void printSet(const set<int>& S){
	for(int num :S)
	cout<<num<<" ";
	cout<<endl;
}

int main(){
	set<int> A={1,2,3,4,5};
	set<int> B={3,4,5,6,7};
	set<int> unionSet,intersectionSet,differenceSet;
	 
	set_union(A.begin(),A.end(),B.begin(),B.end(),inserter(unionSet,unionSet.begin()));
	set_intersection(A.begin(),A.end(),B.begin(),B.end(),inserter(intersectionSet,intersectionSet.begin()));
	set_difference(A.begin(),A.end(),B.begin(),B.end(),inserter(differenceSet,differenceSet.begin()));
	
	cout<<"Union: ";
	printSet(unionSet);
	cout<<"Intersertion: ";
	printSet(intersectionSet);
	cout<<"Difference(A-B): ";
	printSet(differenceSet);
	
	return 0;
}