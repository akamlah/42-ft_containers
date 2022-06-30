/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ENDBOSS_main.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fharing <fharing@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:47:05 by julian            #+#    #+#             */
/*   Updated: 2022/05/30 12:24:24 by fharing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
clang++ ENDBOSS_main.cpp -o ft_container
clang++ ENDBOSS_main.cpp -o std_container -DSTD
./ft_container > endboss.ft
./std_container > endboss.std
diff endboss.ft endboss.std
*/

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>

#include "../vector.hpp"
#include "../stack.hpp"
#include "../map.hpp"

#include <sys/time.h>
#include <iomanip>
#include <fstream>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"
#define RED     "\033[0;31m"

#define NAMESPACE ft
#ifdef STD
# undef NAMESPACE
# define NAMESPACE std
#endif

// functions for map & set
bool fncomp (char lhs, char rhs) {return lhs<rhs;}
bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp
{
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

struct classcomp2
{
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};

int main()
{
	struct timespec startVector, endVector;
	struct timespec startStack, endStack;
	struct timespec startMap, endMap;
	struct timespec startSet, endSet;

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startVector);

	std::cout << GREEN << "\n****************************" << std::endl;
	std::cout          <<   "*          VECTOR          *" << std::endl;
	std::cout          <<   "****************************" << RESET << std::endl;

	std::cout << YELLOW << "\nvector::vector\n" << RESET;

	// constructors used in the same order as described above:
	NAMESPACE::vector<int> vfirst;                                // empty vector of ints
	NAMESPACE::vector<int> vsecond (4,100);                       // four ints with value 100
	NAMESPACE::vector<int> vthird (vsecond.begin(),vsecond.end());  // iterating through second
	NAMESPACE::vector<int> vfourth (vthird);                       // a copy of third
	// the iterator constructor can also be used to construct from arrays:
	int vmyints[] = {16,2,77,29};
	NAMESPACE::vector<int> fifth (vmyints, vmyints + sizeof(vmyints) / sizeof(int) );
	std::cout << "The contents of fifth are:";
	for (NAMESPACE::vector<int>::iterator vit = fifth.begin(); vit != fifth.end(); ++vit)
	std::cout << ' ' << *vit;
	std::cout << '\n';

	std::cout << YELLOW << "\niterator comparison\n" << RESET;

	NAMESPACE::vector<int>::iterator 	   compare_it = fifth.begin();
	NAMESPACE::vector<int>::const_iterator compare_cit = fifth.begin();
	if (compare_it == compare_cit)
		std::cout << "Iterator comparison works\n";

	std::cout << YELLOW << "\nvector::operator=\n" << RESET;

	NAMESPACE::vector<int> vfoo0 (3,0);
	NAMESPACE::vector<int> vbar0 (5,0);
	vbar0 = vfoo0;
	vfoo0 = NAMESPACE::vector<int>();
	std::cout << "Size of vfoo0: " << int(vfoo0.size()) << '\n';
	std::cout << "Size of vbar0: " << int(vbar0.size()) << '\n';

	std::cout << YELLOW << "\nvector::begin & vector::end\n" << RESET;

	NAMESPACE::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);
	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::rbegin | vector::rend\n" << RESET;

	NAMESPACE::vector<int> myvector2 (5);  // 5 default-constructed ints
	int i=0;
	NAMESPACE::vector<int>::reverse_iterator rit = myvector2.rbegin();
	for (; rit!= myvector2.rend(); ++rit)
		*rit = ++i;
	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector2.begin(); it != myvector2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::size\n" << RESET;

	NAMESPACE::vector<int> vmyints2;
	std::cout << "0. size: " << vmyints2.size() << '\n';
	for (int i=0; i<10; i++) vmyints2.push_back(i);
		std::cout << "1. size: " << vmyints2.size() << '\n';
	vmyints2.insert (vmyints2.end(),10,100);
	std::cout << "2. size: " << vmyints2.size() << '\n';
	vmyints2.pop_back();
	std::cout << "3. size: " << vmyints2.size() << '\n';

	std::cout << YELLOW << "\nvector::size | vector::capacity | vector::max_size\n" << RESET;

	NAMESPACE::vector<int> myvector3;
	// set some content in the vector:
	for (int i=0; i<100; i++) myvector3.push_back(i);
	std::cout << "size: " << myvector3.size() << "\n";
	std::cout << "capacity: " << myvector3.capacity() << "\n";
	std::cout << "max_size: " << myvector3.max_size() << "\n";

	std::cout << RED << "\nvector::resize\n" << RESET;

	NAMESPACE::vector<int> myvector4;
	for (int i=1;i<10;i++) myvector4.push_back(i);
	myvector4.resize(5);
	myvector4.resize(8,100);
	myvector4.resize(12);
	std::cout << "myvector contains:";
	for (unsigned i=0;i<myvector4.size();i++)
	std::cout << ' ' << myvector4[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::empty\n" << RESET;

	NAMESPACE::vector<int> myvector5;
	int sum (0);
	for (int i=1;i<=10;i++) myvector5.push_back(i);
	while (!myvector5.empty())
	{
		sum += myvector5.back();
		myvector5.pop_back();
	}
	std::cout << "total: " << sum << '\n';

	std::cout << YELLOW << "\nvector::reserve\n" << RESET;

	NAMESPACE::vector<int>::size_type vsz;
	NAMESPACE::vector<int> vfoo;
	vsz = vfoo.capacity();
	std::cout << "making vfoo grow:\n";
	for (int i=0; i<100; ++i) {
		vfoo.push_back(i);
		if (vsz!=vfoo.capacity()) {
		vsz = vfoo.capacity();
		std::cout << "capacity changed: " << vsz << '\n';
		}
	}
	NAMESPACE::vector<int> vbar;
	vsz = vbar.capacity();
	vbar.reserve(100);   // this is the only difference with foo above
	std::cout << "making vbar grow:\n";
	for (int i=0; i<100; ++i) {
		vbar.push_back(i);
		if (vsz!=vbar.capacity()) {
		vsz = vbar.capacity();
		std::cout << "capacity changed: " << vsz << '\n';
		}
	}

	std::cout << YELLOW << "\nvector::operator[]\n" << RESET;

	NAMESPACE::vector<int> myvector6 (10);   // 10 zero-initialized elements
	NAMESPACE::vector<int>::size_type sz = myvector6.size();
	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector6[i]=i;
	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector6[sz-1-i];
		myvector6[sz-1-i]=myvector6[i];
		myvector6[i]=temp;
	}
	std::cout << "myvector6 contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector6[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::at\n" << RESET;

	NAMESPACE::vector<int> myvector7 (10);   // 10 zero-initialized ints
	// assign some values:
	for (unsigned i=0; i<myvector7.size(); i++)
		myvector7.at(i)=i;
	std::cout << "myvector7 contains:";
	for (unsigned i=0; i<myvector7.size(); i++)
		std::cout << ' ' << myvector7.at(i);
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::front\n" << RESET;

	NAMESPACE::vector<int>myvector8;
	myvector8.push_back(78);
	myvector8.push_back(16);
	// now front equals 78, and back 16
	myvector8.front() -=myvector8.back();
	std::cout << "myvector8.front() is now " <<myvector8.front() << '\n';

	std::cout << YELLOW << "\nvector::back\n" << RESET;

	NAMESPACE::vector<int> myvector9;
	myvector9.push_back(10);
	while (myvector9.back() != 0)
	{
		myvector9.push_back ( myvector9.back() -1 );
	}
	std::cout << "myvector9 contains:";
	for (unsigned i=0; i<myvector9.size() ; i++)
		std::cout << ' ' << myvector9[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::assign\n" << RESET;

	NAMESPACE::vector<int> vfirst2;
	NAMESPACE::vector<int> vsecond2;
	NAMESPACE::vector<int> vthird2;
	vfirst2.assign (7,100);             // 7 ints with a value of 100
	NAMESPACE::vector<int>::iterator it;
	it=vfirst2.begin()+1;
	vsecond2.assign (it,vfirst2.end()-1); // the 5 central values of first
	int vmyints3[] = {1776,7,4};
	vthird2.assign (vmyints3,vmyints3+3);   // assigning from array.
	std::cout << "Size of first: " << int (vfirst2.size()) << '\n';
	std::cout << "Size of second: " << int (vsecond2.size()) << '\n';
	std::cout << "Size of third: " << int (vthird2.size()) << '\n';

	std::cout << YELLOW << "\nvector::push_back\n" << RESET;

	NAMESPACE::vector<int> myvector10;
	for (int i = 0; i < 10; ++i)
		myvector10.push_back (i);
	std::cout << "myvector10 stores " << int(myvector10.size()) << " numbers.\n";

	std::cout << YELLOW << "\nvector::pop_back\n" << RESET;

	NAMESPACE::vector<int> myvector11;
	int sum2 (0);
	myvector11.push_back (100);
	myvector11.push_back (200);
	myvector11.push_back (300);
	while (!myvector11.empty())
	{
		sum2+=myvector11.back();
		myvector11.pop_back();
	}
	std::cout << "The elements of myvector11 add up to " << sum2 << '\n';

	std::cout << YELLOW << "\nvector::insert\n" << RESET;

	NAMESPACE::vector<int> myvector12 (3,100);
	NAMESPACE::vector<int>::iterator it12;
	it12 = myvector12.begin();
	it12 = myvector12.insert ( it12 , 200 );
	myvector12.insert (it12,2,300);
	// "it12" no longer valid, get a new one:
	it12 = myvector12.begin();
	NAMESPACE::vector<int> anothervector (2,400);
	myvector12.insert (it12+2,anothervector.begin(),anothervector.end());
	int myarray [] = { 501,502,503 };
	myvector12.insert (myvector12.begin(), myarray, myarray+3);
	std::cout << "myvector12 contains:";
	for (it12=myvector12.begin(); it12<myvector12.end(); it12++)
		std::cout << ' ' << *it12;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::erase\n" << RESET;

	NAMESPACE::vector<int> myvector13;
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector13.push_back(i);
	// erase the 6th element
	myvector13.erase (myvector13.begin()+5);
	// erase the first 3 elements:
	myvector13.erase (myvector13.begin(),myvector13.begin()+3);
	std::cout << "myvector13 contains:";
	for (unsigned i=0; i<myvector13.size(); ++i)
		std::cout << ' ' << myvector13[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::swap\n" << RESET;

	NAMESPACE::vector<int> vfoo3 (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> vbar3 (5,200);   // five ints with a value of 200
	std::cout << "vfoo3 contains:";
	for (unsigned i=0; i<vfoo3.size(); i++)
		std::cout << ' ' << vfoo3[i];
	std::cout << '\n';
	std::cout << "vbar3 contains:";
	for (unsigned i=0; i<vbar3.size(); i++)
		std::cout << ' ' << vbar3[i];
	std::cout << "\n\n";
	vfoo3.swap(vbar3);
	std::cout << "vfoo3 contains:";
	for (unsigned i=0; i<vfoo3.size(); i++)
		std::cout << ' ' << vfoo3[i];
	std::cout << '\n';
	std::cout << "vbar3 contains:";
	for (unsigned i=0; i<vbar3.size(); i++)
		std::cout << ' ' << vbar3[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::clear\n" << RESET;

	NAMESPACE::vector<int> myvector14;
	myvector14.push_back (100);
	myvector14.push_back (200);
	myvector14.push_back (300);

	std::cout << "myvector14 contains:";
	for (unsigned i=0; i<myvector14.size(); i++)
		std::cout << ' ' << myvector14[i];
	std::cout << '\n';

	myvector14.clear();
	myvector14.push_back (1101);
	myvector14.push_back (2202);

	std::cout << "myvector14 contains:";
	for (unsigned i=0; i<myvector14.size(); i++)
		std::cout << ' ' << myvector14[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::get_allocator\n" << RESET;

	NAMESPACE::vector<int> myvector15;
	int * vp;
	unsigned int vi;
	// allocate an array with space for 5 elements using vector's allocator:
	vp = myvector15.get_allocator().allocate(5);
	// construct values in-place on the array:
	for (vi=0; vi<5; vi++) myvector15.get_allocator().construct(&vp[vi],vi);
	std::cout << "The allocated array contains:";
	for (vi=0; vi<5; vi++) std::cout << ' ' << vp[vi];
	std::cout << '\n';
	// destroy and deallocate:
	for (vi=0; vi<5; vi++) myvector15.get_allocator().destroy(&vp[vi]);
	myvector15.get_allocator().deallocate(vp,5);

	std::cout << YELLOW << "\nrelational operators (vector)\n" << RESET;

	NAMESPACE::vector<int> vfoo4 (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> vbar4 (2,200);   // two ints with a value of 200
	if (vfoo4==vbar4) std::cout << "vfoo4 and vbar4 are equal\n";
	if (vfoo4!=vbar4) std::cout << "vfoo4 and vbar4 are not equal\n";
	if (vfoo4< vbar4) std::cout << "vfoo4 is less than vbar4\n";
	if (vfoo4> vbar4) std::cout << "vfoo4 is greater than vbar4\n";
	if (vfoo4<=vbar4) std::cout << "vfoo4 is less than or equal to vbar4\n";
	if (vfoo4>=vbar4) std::cout << "vfoo4 is greater than or equal to vbar4\n";

	std::cout << YELLOW << "\nswap (vector)\n" << RESET;

	NAMESPACE::vector<int> vfoo5 (3,100);   // three ints with a value of 100
	NAMESPACE::vector<int> vbar5 (5,200);   // five ints with a value of 200
	std::cout << "vfoo5 contains:";
	for (NAMESPACE::vector<int>::iterator it = vfoo5.begin(); it!=vfoo5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "vbar5 contains:";
	for (NAMESPACE::vector<int>::iterator it = vbar5.begin(); it!=vbar5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	vfoo5.swap(vbar5);
	std::cout << "vfoo5 contains:";
	for (NAMESPACE::vector<int>::iterator it = vfoo5.begin(); it!=vfoo5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "vbar5 contains:";
	for (NAMESPACE::vector<int>::iterator it = vbar5.begin(); it!=vbar5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nperformance vector\n" << RESET;
	std::cout << "inserting and deleting lots of elements\n";

	struct timespec timeStart, timeEnd;
	// start timer
	clock_gettime(CLOCK_MONOTONIC, &timeStart);
	NAMESPACE::vector<int> perfV;
	for (size_t i = 0; i < 10000000; ++i)
			perfV.push_back(std::rand());
	NAMESPACE::vector<int> perfV2(perfV);
	NAMESPACE::vector<int> perfV3;
	perfV3.assign(perfV2.begin(), perfV2.end());
	perfV.erase(perfV.begin(), perfV.end());
	// end timer
	clock_gettime(CLOCK_MONOTONIC, &timeEnd);
	double timePerformance = timeStart.tv_sec * 1e9;
	timePerformance = (timeEnd.tv_sec - timeStart.tv_sec) * 1e9;
	timePerformance = (timePerformance + (timeEnd.tv_nsec - timeStart.tv_nsec)) * 1e-9;
	std::cout << "Vector performance test: " <<  timePerformance << "sec.\n";

	std::cout << YELLOW << "\nleaks vector\n" << RESET;

	#ifdef STD
		system("leaks std_container | tail -3");
	#else
		system("leaks ft_container | tail -3");
	#endif

	// stop timer.
	clock_gettime(CLOCK_MONOTONIC, &endVector);

/* ------------------------------------------------------------------------------------------------------------------ */

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startStack);

	std::cout << GREEN << "\n***************************" << std::endl;
	std::cout          <<   "*          STACK          *" << std::endl;
	std::cout          <<   "***************************" << RESET << std::endl;

	std::cout << YELLOW << "\nstack::stack\n" << RESET;

	#ifdef STD
	std::deque<int> smydeque (3,200);         				// deque with 3 elements
	NAMESPACE::vector<int> smyvector (2,200);         		// vector with 2 elements
	NAMESPACE::stack<int> sfirst;                 		    // empty stack
	NAMESPACE::stack<int> ssecond (smydeque);         		// stack initialized to copy of deque
	NAMESPACE::stack<int,NAMESPACE::vector<int> > sthird;	// empty stack using vector
	NAMESPACE::stack<int,NAMESPACE::vector<int> > sfourth (smyvector);
	#else
	std::deque<int> smydeque (2,200);         				// deque with 3 elements
	NAMESPACE::vector<int> smyvector (3,200);        		// vector with 2 elements
	NAMESPACE::stack<int> sfirst;                    		// empty stack
	NAMESPACE::stack<int> ssecond (smyvector);         		// stack initialized to copy of deque
	NAMESPACE::stack<int,std::deque<int> > sthird;  		// empty stack using vector
	NAMESPACE::stack<int,std::deque<int> > sfourth (smydeque);
	#endif
	std::cout << "size of sfirst: " << sfirst.size() << '\n';
	std::cout << "size of ssecond: " << ssecond.size() << '\n';
	std::cout << "size of sthird: " << sthird.size() << '\n';
	std::cout << "size of sfourth: " << sfourth.size() << '\n';

	std::cout << YELLOW << "\nstack::empty\n" << RESET;

	NAMESPACE::stack<int> mystack;
	int ssum (0);
	for (int i=1;i<=10;i++) mystack.push(i);
	while (!mystack.empty())
	{
		ssum += mystack.top();
		mystack.pop();
	}
	std::cout << "total: " << ssum << '\n';

	std::cout << YELLOW << "\nstack::size\n" << RESET;

	NAMESPACE::stack<int> smyints;
	std::cout << "0. size: " << smyints.size() << '\n';
	for (int i=0; i<5; i++) smyints.push(i);
	std::cout << "1. size: " << smyints.size() << '\n';
	smyints.pop();
	std::cout << "2. size: " << smyints.size() << '\n';

	std::cout << YELLOW << "\nstack::top\n" << RESET;

	NAMESPACE::stack<int> mystack2;
	mystack2.push(10);
	mystack2.push(20);
	mystack2.top() -= 5;
	std::cout << "mystack2.top() is now " << mystack2.top() << '\n';

	std::cout << YELLOW << "\nstack::push | stack::pop\n" << RESET;

	NAMESPACE::stack<int> mystack3;
	for (int i=0; i<5; ++i) mystack3.push(i);
	std::cout << "Popping out elements...";
	while (!mystack3.empty())
	{
		std::cout << ' ' << mystack3.top();
		mystack3.pop();
	}
	std::cout << '\n';

	std::cout << YELLOW << "\nrelational operators (stack)\n" << RESET;

	NAMESPACE::stack<int> mystackA;
	std::cout << "StackA contains: ";
	for (int i=1;i<=10;i++)
	{
		std::cout << i << " ";
		mystackA.push(i);
	}
	std::cout << '\n';

	std::cout << "StackB contains: ";
	NAMESPACE::stack<int> mystackB;
	for (int i=1;i<=10;i++)
	{
		std::cout << i << " ";
		mystackB.push(i);
	}
	std::cout << '\n';
	std::cout << std::boolalpha;
	std::cout << "operator== "<<(mystackA == mystackB) << '\n';
	std::cout << "operator!= "<<(mystackA != mystackB) << '\n';
	std::cout << "operator<  "<<(mystackA < mystackB) << '\n';
	std::cout << "operator<= "<<(mystackA <= mystackB) << '\n';
	std::cout << "operator>  "<<(mystackA > mystackB) << '\n';
	std::cout << "operator>= "<<(mystackA >= mystackB) << '\n';
	std::cout << std::noboolalpha;

	std::cout << YELLOW << "\nperformance stack\n" << RESET;
	std::cout << "inserting and deleting lots of elements\n";

	// start timer
	clock_gettime(CLOCK_MONOTONIC, &timeStart);
	NAMESPACE::stack<int> perfS;
	for (size_t i = 0; i < 10000000; ++i)
			perfS.push(std::rand());
	NAMESPACE::stack<int> perfS2(perfS);
	for (size_t i = 0; i < 10000000; ++i)
			perfS.pop();
	// end timer
	clock_gettime(CLOCK_MONOTONIC, &timeEnd);
	timePerformance = timeStart.tv_sec * 1e9;
	timePerformance = (timeEnd.tv_sec - timeStart.tv_sec) * 1e9;
	timePerformance = (timePerformance + (timeEnd.tv_nsec - timeStart.tv_nsec)) * 1e-9;
	std::cout << "Stack performance test: " <<  timePerformance << "sec.\n";

	std::cout << YELLOW << "\nleaks stack\n" << RESET;

	#ifdef STD
		system("leaks std_container | tail -3");
	#else
		system("leaks ft_container | tail -3");
	#endif

	clock_gettime(CLOCK_MONOTONIC, &endStack);
	

// /* ------------------------------------------------------------------------------------------------------------------ */

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startMap);

	std::cout << GREEN << "\n***************************" << std::endl;
	std::cout          <<   "*           MAP           *" << std::endl;
	std::cout          <<   "***************************" << RESET << std::endl;

	std::cout << YELLOW << "\nmap::map\n" << RESET;

	NAMESPACE::map<char,int> mfirst;
	mfirst['a']=10;
	mfirst['b']=30;
	mfirst['c']=50;
	mfirst['d']=70;
	NAMESPACE::map<char,int> msecond (mfirst.begin(),mfirst.end());
	NAMESPACE::map<char,int> mthird (msecond);
	NAMESPACE::map<char,int,classcomp> mfourth;                 // class as Compare
	bool(*fn_pt)(char,char) = fncomp;
	NAMESPACE::map<char,int,bool(*)(char,char)> mfifth (fn_pt);
	for (NAMESPACE::map<char, int>::iterator mit = mthird.begin(); mit != mthird.end(); ++mit)
		std::cout << mit->first << " => " << mit->second << '\n';

	std::cout << YELLOW << "\nmap::operator=\n" << RESET;

	NAMESPACE::map<char,int> mfirst2;
	NAMESPACE::map<char,int> msecond2;
	mfirst2['x']=8;
	mfirst2['y']=16;
	mfirst2['z']=32;
	msecond2=mfirst2;                // second now contains 3 ints
	mfirst2=NAMESPACE::map<char,int>();    // and first is now empty
	std::cout << "Size of mfirst2: " << mfirst2.size() << '\n';
	std::cout << "Size of msecond2: " << msecond2.size() << '\n';

	std::cout << YELLOW << "\nmap::begin | map::end\n" << RESET;

	NAMESPACE::map<char,int> mymap;
	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	// show content:
	for (NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nmap::rbegin | map::rend\n" << RESET;

	NAMESPACE::map<char,int> mymap2;
	mymap2['x'] = 100;
	mymap2['y'] = 200;
	mymap2['z'] = 300;
	// show content:
	NAMESPACE::map<char,int>::reverse_iterator mrit;
	for (mrit=mymap2.rbegin(); mrit!=mymap2.rend(); ++mrit)
		std::cout << mrit->first << " => " << mrit->second << '\n';

	std::cout << YELLOW << "\nmap::empty\n" << RESET;

	NAMESPACE::map<char,int> mymap3;
	mymap3['a']=10;
	mymap3['b']=20;
	mymap3['c']=30;
	while (!mymap3.empty())
	{
		std::cout << mymap3.begin()->first << " => " << mymap3.begin()->second << '\n';
		mymap3.erase(mymap3.begin());
	}

	std::cout << YELLOW << "\nmap::size\n" << RESET;

	NAMESPACE::map<char,int> mymap4;
	mymap4['a']=101;
	mymap4['b']=202;
	mymap4['c']=302;
	std::cout << "mymap4.size() is " << mymap4.size() << '\n';

	std::cout << YELLOW << "\nmap::max_size\n" << RESET;

	NAMESPACE::map<int,int> mymap5;
	if (mymap5.max_size()>1000)
	{
		for (int i=0; i<1000; i++) mymap5[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";

	std::cout << YELLOW << "\nmap::operator[]\n" << RESET;

	NAMESPACE::map<char,std::string> mymap6;
	mymap6['a']="an element";
	mymap6['b']="another element";
	mymap6['c']=mymap6['b'];
	std::cout << "mymap6['a'] is " << mymap6['a'] << '\n';
	std::cout << "mymap6['b'] is " << mymap6['b'] << '\n';
	std::cout << "mymap6['c'] is " << mymap6['c'] << '\n';
	std::cout << "mymap6['d'] is " << mymap6['d'] << '\n';
	std::cout << "mymap6 now contains " << mymap6.size() << " elements.\n";

	std::cout << YELLOW << "\nmap::insert\n" << RESET;

	NAMESPACE::map<char,int> mymap7;
	// first insert function version (single parameter):
	mymap7.insert ( NAMESPACE::pair<char,int>('a',100) );
	mymap7.insert ( NAMESPACE::pair<char,int>('z',200) );
	NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,bool> ret;
	ret = mymap7.insert ( NAMESPACE::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}
	// second insert function version (with hint position):
	NAMESPACE::map<char,int>::iterator mit7 = mymap7.begin();
	mymap7.insert (mit7, NAMESPACE::pair<char,int>('b',300));  // max efficiency inserting
	mymap7.insert (mit7, NAMESPACE::pair<char,int>('c',400));  // no max efficiency inserting
	// third insert function version (range insertion):
	NAMESPACE::map<char,int> anothermap;
	anothermap.insert(mymap7.begin(),mymap7.find('c'));
	// showing contents:
	std::cout << "mymap7 contains:\n";
	for (mit7=mymap7.begin(); mit7!=mymap7.end(); ++mit7)
		std::cout << mit7->first << " => " << mit7->second << '\n';
	std::cout << "anothermap contains:\n";
	for (mit7=anothermap.begin(); mit7!=anothermap.end(); ++mit7)
		std::cout << mit7->first << " => " << mit7->second << '\n';

	std::cout << YELLOW << "\nmap::erase\n" << RESET;

	NAMESPACE::map<char,int> mymap8;
	NAMESPACE::map<char,int>::iterator mit8;
	// insert some values:
	mymap8['a']=10;
	mymap8['b']=20;
	mymap8['c']=30;
	mymap8['d']=40;
	mymap8['e']=50;
	mymap8['f']=60;
	mit8=mymap8.find('b');
	mymap8.erase (mit8);                   // erasing by iterator
	mymap8.erase ('c');                  // erasing by key
	mit8=mymap8.find ('e');
	mymap8.erase ( mit8, mymap8.end() );    // erasing by range
	// show content:
	for (mit8=mymap8.begin(); mit8!=mymap8.end(); ++mit8)
		std::cout << mit8->first << " => " << mit8->second << '\n';

	std::cout << YELLOW << "\nmap::swap\n" << RESET;

	NAMESPACE::map<char,int> mfoo;
	NAMESPACE::map<char,int> mbar;
	mfoo['x']=100;
	mfoo['y']=200;
	mbar['a']=11;
	mbar['b']=22;
	mbar['c']=33;
	std::cout << "mfoo contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mfoo.begin(); it!=mfoo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "mbar contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mbar.begin(); it!=mbar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "\nswapping\n\n";
	mfoo.swap(mbar);
	std::cout << "mfoo contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mfoo.begin(); it!=mfoo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "mbar contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mbar.begin(); it!=mbar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nmap::clear\n" << RESET;

	NAMESPACE::map<char,int> mymap9;
	mymap9['x']=100;
	mymap9['y']=200;
	mymap9['z']=300;
	std::cout << "mymap9 contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	mymap9.clear();
	mymap9['a']=1101;
	mymap9['b']=2202;
	std::cout << "mymap9 contains:\n";
	for (NAMESPACE::map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nmap::key_comp\n" << RESET;

	NAMESPACE::map<char,int> mymap10;
	NAMESPACE::map<char,int>::key_compare mycomp = mymap10.key_comp();
	mymap10['a']=100;
	mymap10['b']=200;
	mymap10['c']=300;
	std::cout << "mymap10 contains:\n";
	char highest = mymap10.rbegin()->first;     // key value of last element
	NAMESPACE::map<char,int>::iterator mit10 = mymap10.begin();
	do {
		std::cout << mit10->first << " => " << mit10->second << '\n';
	} while ( mycomp((*mit10++).first, highest) );
	std::cout << '\n';

	std::cout << YELLOW << "\nmap::value_comp\n" << RESET;

	NAMESPACE::map<char,int> mymap11;
	mymap11['x']=1001;
	mymap11['y']=2002;
	mymap11['z']=3003;
	std::cout << "mymap11 contains:\n";
	NAMESPACE::pair<char,int> highest2 = *mymap11.rbegin();          // last element
	NAMESPACE::map<char,int>::iterator mit11 = mymap11.begin();
	do {
		std::cout << mit11->first << " => " << mit11->second << '\n';
	} while ( mymap11.value_comp()(*mit11++, highest2) );

	std::cout << YELLOW << "\nmap::find\n" << RESET;

	NAMESPACE::map<char,int> mymap12;
	NAMESPACE::map<char,int>::iterator mit12;
	mymap12['a']=50;
	mymap12['b']=100;
	mymap12['c']=150;
	mymap12['d']=200;
	mit12 = mymap12.find('b');
	if (mit12 != mymap12.end())
		mymap12.erase (mit12);
	// print content:
	std::cout << "elements in mymap12:" << '\n';
	std::cout << "a => " << mymap12.find('a')->second << '\n';
	std::cout << "c => " << mymap12.find('c')->second << '\n';
	std::cout << "d => " << mymap12.find('d')->second << '\n';

	std::cout << YELLOW << "\nmap::count\n" << RESET;

	NAMESPACE::map<char,int> mymap13;
	char c;
	mymap13 ['a']=101;
	mymap13 ['c']=202;
	mymap13 ['f']=303;
	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap13.count(c)>0)
			std::cout << " is an element of mymap13.\n";
		else
			std::cout << " is not an element of mymap13.\n";
	}

	std::cout << YELLOW << "\nmap::lower_bound | map::upper_bound\n" << RESET;

	NAMESPACE::map<char,int> mymap14;
	NAMESPACE::map<char,int>::iterator itlow;
	NAMESPACE::map<char,int>::iterator itup;
	mymap14['a']=20;
	mymap14['b']=40;
	mymap14['c']=60;
	mymap14['d']=80;
	mymap14['e']=100;
	itlow=mymap14.lower_bound ('b');  // itlow points to b
	itup=mymap14.upper_bound ('d');   // itup points to e (not d!)
	mymap14.erase(itlow,itup);        // erases [itlow,itup)
	// print content:
	for (NAMESPACE::map<char,int>::iterator it=mymap14.begin(); it!=mymap14.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nmap::equal_range\n" << RESET;

	NAMESPACE::map<char,int> mymap15;
	mymap15['a']=10;
	mymap15['b']=20;
	mymap15['c']=30;
	NAMESPACE::pair<NAMESPACE::map<char,int>::iterator,NAMESPACE::map<char,int>::iterator> mret2;
	mret2 = mymap15.equal_range('b');
	std::cout << "lower bound points to: ";
	std::cout << mret2.first->first << " => " << mret2.first->second << '\n';
	std::cout << "upper bound points to: ";
	std::cout << mret2.second->first << " => " << mret2.second->second << '\n';

	std::cout << YELLOW << "\nmap::get_allocator\n" << RESET;

	int psize;
	NAMESPACE::map<char,int> mymap16;
	NAMESPACE::pair<const char,int>* p;
	// allocate an array of 5 elements using mymap16's allocator:
	p=mymap16.get_allocator().allocate(5);
	// assign some values to array
	psize = sizeof(NAMESPACE::map<char,int>::value_type)*5;
	std::cout << "The allocated array has a size of " << psize << " bytes.\n";
	mymap16.get_allocator().deallocate(p,5);

	std::cout << YELLOW << "\nrelational operators (map)\n" << RESET;

	NAMESPACE::map<int, char> malice;
	malice.insert ( NAMESPACE::pair<int,char>(1,'a') );
	malice.insert ( NAMESPACE::pair<int,char>(2,'b') );
	malice.insert ( NAMESPACE::pair<int,char>(3,'c') );
	NAMESPACE::map<int, char> mbob;
	mbob.insert ( NAMESPACE::pair<int,char>(7,'Z') );
	mbob.insert ( NAMESPACE::pair<int,char>(8,'Y') );
	mbob.insert ( NAMESPACE::pair<int,char>(9,'X') );
	mbob.insert ( NAMESPACE::pair<int,char>(10,'W') );
	NAMESPACE::map<int, char> meve;
	meve.insert ( NAMESPACE::pair<int,char>(1,'a') );
	meve.insert ( NAMESPACE::pair<int,char>(2,'b') );
	meve.insert ( NAMESPACE::pair<int,char>(3,'c') );
	std::cout << std::boolalpha;
	// Compare non equal containers
	std::cout << "malice == mbob returns " << (malice == mbob) << '\n';
	std::cout << "malice != mbob returns " << (malice != mbob) << '\n';
	std::cout << "malice <  mbob returns " << (malice < mbob) << '\n';
	std::cout << "malice <= mbob returns " << (malice <= mbob) << '\n';
	std::cout << "malice >  mbob returns " << (malice > mbob) << '\n';
	std::cout << "malice >= mbob returns " << (malice >= mbob) << '\n';
	std::cout << '\n';
	// Compare equal containers
	std::cout << "malice == meve returns " << (malice == meve) << '\n';
	std::cout << "malice != meve returns " << (malice != meve) << '\n';
	std::cout << "malice <  meve returns " << (malice < meve) << '\n';
	std::cout << "malice <= meve returns " << (malice <= meve) << '\n';
	std::cout << "malice >  meve returns " << (malice > meve) << '\n';
	std::cout << "malice >= meve returns " << (malice >= meve) << '\n';
	std::cout << std::noboolalpha;

	std::cout << YELLOW << "\nswap (map)\n" << RESET;

	NAMESPACE::map<int, char> malice2;
	malice2.insert ( NAMESPACE::pair<int,char>(1,'a') );
	malice2.insert ( NAMESPACE::pair<int,char>(2,'b') );
	malice2.insert ( NAMESPACE::pair<int,char>(3,'c') );
	NAMESPACE::map<int, char> mbob2;
	mbob2.insert ( NAMESPACE::pair<int,char>(7,'Z') );
	mbob2.insert ( NAMESPACE::pair<int,char>(8,'Y') );
	mbob2.insert ( NAMESPACE::pair<int,char>(9,'X') );
	mbob2.insert ( NAMESPACE::pair<int,char>(10,'W') );
	// Print state before swap
	std::cout << "malice2:\n";
	for (NAMESPACE::map<int,char>::iterator it=malice2.begin(); it!=malice2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "\n" "mbob2:\n";
	for (NAMESPACE::map<int,char>::iterator it=mbob2.begin(); it!=mbob2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "\n-- SWAP\n\n";
	std::swap(malice2, mbob2);
	// Print state after swap
	std::cout << "malice2:\n";
	for (NAMESPACE::map<int,char>::iterator it=malice2.begin(); it!=malice2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "\n" "mbob2:\n";
	for (NAMESPACE::map<int,char>::iterator it=mbob2.begin(); it!=mbob2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << YELLOW << "\nperformance map\n" << RESET;
	std::cout << "inserting and deleting lots of elements\n";

	// start timer
	clock_gettime(CLOCK_MONOTONIC, &timeStart);
	NAMESPACE::map<int, std::string> perfM;
	for (size_t i = 0; i < 10000000; ++i) {
	// for (size_t i = 0; i < 100; ++i) {
			// std::cout << "inserting " << std::endl;
			perfM.insert(NAMESPACE::make_pair<int, std::string>(std::rand() % 1000000, "performance: " + std::to_string(i)));
	}
	// std::cout << "Map perfM.size() = " << perfM.size() << std::endl;
	NAMESPACE::map<int, std::string> perfM2(perfM);
	// std::cout << "Map perfM2.size() = " << perfM2.size() << std::endl;
	NAMESPACE::map<int, std::string> perfM3(perfM2.begin(), perfM2.end());
	// std::cout << "Map perfM3.size() = " << perfM3.size() << std::endl;
	perfM.erase(perfM.begin(), perfM.end());
	// std::cout << "Map perfM.size() = " << perfM.size() << std::endl;

	// end timer
	clock_gettime(CLOCK_MONOTONIC, &timeEnd);
	timePerformance = timeStart.tv_sec * 1e9;
	timePerformance = (timeEnd.tv_sec - timeStart.tv_sec) * 1e9;
	timePerformance = (timePerformance + (timeEnd.tv_nsec - timeStart.tv_nsec)) * 1e-9;
	std::cout << "Map performance test: " <<  timePerformance << "sec.\n";

	std::cout << YELLOW << "\nleaks map\n" << RESET;

	#ifdef STD
		system("leaks std_container | tail -3");
	#else
		system("leaks ft_container | tail -3");
	#endif

	clock_gettime(CLOCK_MONOTONIC, &endMap);

/* ------------------------------------------------------------------------------------------------------------------ */

	std::cout << BLUE << "\n--------------------------------------------------------\n" << RESET;;
	double time_takenVector;
	time_takenVector = (endVector.tv_sec - startVector.tv_sec) * 1e9;
	time_takenVector = (time_takenVector + (endVector.tv_nsec - startVector.tv_nsec)) * 1e-9;
	#ifdef STD
	std::cout << CYAN << "Time taken by program for STD_VECTOR is " << std::fixed << std::setprecision(9) << time_takenVector;
	#else
	std::cout << CYAN << "Time taken by program for FT_VECTOR is " << std::fixed << std::setprecision(9) << time_takenVector;
	#endif
	std::cout << " sec" << std::endl << RESET;

	double time_takenStack;
	time_takenStack = (endStack.tv_sec - startStack.tv_sec) * 1e9;
	time_takenStack = (time_takenStack + (endStack.tv_nsec - startStack.tv_nsec)) * 1e-9;
	#ifdef STD
	std::cout << CYAN << "Time taken by program for STD_STACK  is " << std::fixed << std::setprecision(9) << time_takenStack;
	#else
	std::cout << CYAN << "Time taken by program for FT_STACK  is " << std::fixed << std::setprecision(9) << time_takenStack;
	#endif
	std::cout << " sec" << std::endl << RESET;

	double time_takenMap;
	time_takenMap = (endMap.tv_sec - startMap.tv_sec) * 1e9;
	time_takenMap = (time_takenMap + (endMap.tv_nsec - startMap.tv_nsec)) * 1e-9;
	#ifdef STD
	std::cout << CYAN << "Time taken by program for STD_MAP    is " << std::fixed << std::setprecision(9) << time_takenMap;
	#else
	std::cout << CYAN << "Time taken by program for FT_MAP    is " << std::fixed << std::setprecision(9) << time_takenMap;
	#endif
	std::cout << " sec" << std::endl << RESET;

	std::cout << BLUE << "--------------------------------------------------------\n";
	#ifdef STD
	std::cout << "STD_TOTAL                              " << std::fixed << std::setprecision(9) << time_takenVector + time_takenStack + time_takenMap;
	#else
	std::cout << "FT_TOTAL                               " << std::fixed << std::setprecision(9) << time_takenVector + time_takenStack + time_takenMap;
	#endif
	std::cout << " sec\n" << std::endl << RESET;

	return (0);
}
