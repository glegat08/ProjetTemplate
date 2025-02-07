#include "mathLib.h"
#include "myArray.h"
#include "myIntrusiveList.h"
#include "myList.h"
#include "myVector.h"
#include "myVectorND.h"
#include "myMatrix.h"

int main()
{
	//// Test Array
	myArray<int, 5> testArray{6,7,8,9,0};
	myArray<int, 5> testArray2{ 1,2,3,4,5 };
	myArray<int, 5> testArray3(testArray2);
	myArray<int, 3 >testArray4{ 1,2,3 };

	std::cout << "Size && max size = 5 -> ";
	std::cout << testArray.size() << " & " << testArray.max_size() << std::endl;

	std::cout << "array = 6,7,8,9,0 -> ";
	std::cout << testArray << std::endl;

	std::cout << "array2 = 1,2,3,4,5 -> ";
	std::cout << testArray2 << std::endl;

	std::cout << "array3 = 1,2,3,4,5 -> ";
	std::cout << testArray3 << std::endl;

	std::cout << "array4 = 1,2,3 -> ";
	std::cout << testArray4 << std::endl;

	std::cout << "array[0] = 1 -> ";
	std::cout << testArray[0] << std::endl;

	std::cout << "array.at(0) = 1 -> ";
	std::cout << testArray.at(0) << std::endl;

	std::cout << "*Begin && *data = 1 -> ";
	std::cout << *testArray.begin() << " & " << *testArray.data() << std::endl;

	std::cout << "front && end = 1 et 5 -> ";
	std::cout << testArray.front() << " & " << testArray.back() << std::endl;

	glg::swap(testArray2, testArray);

	std::cout << "Array is -> " << testArray << std::endl;
	std::cout << "Array2 is -> " << testArray2 << std::endl;

	glg::fill(testArray.begin(), testArray.end(), 5);
	std::cout << "array == 5,5,5,5,5 : ";
	std::cout << testArray << std::endl;

	glg::fill(testArray.rbegin(), testArray.rend(), 10);
	std::cout << "array == 10,10,10,10,10 : ";
	std::cout << testArray << std::endl;

	// test const Array
	const myArray<int, 5> testArrayconst{ 1,2,3,4,5 };
	const myArray<int, 5> testArray2const{ 1,2,3,4,5 };
	const myArray<int, 5> testArray3const(testArray2const);
	const myArray<int, 3 >testArray4const{ 1,2,3 };

	std::cout << "Size  && max size = 5 : ";
	std::cout << testArrayconst.size() << "," << testArrayconst.max_size() << std::endl;

	std::cout << "array == 1,2,3,4,5 : ";
	std::cout << testArrayconst << std::endl;

	std::cout << "array4 == 1,2,3 : ";
	std::cout << testArray4const << std::endl;

	std::cout << "array[0] == 1 : ";
	std::cout << testArrayconst[0] << std::endl;

	std::cout << "array.at(0) == 1 : ";
	std::cout << testArrayconst.at(0) << std::endl;

	std::cout << "*Begin && *data && rbegin = 1,1,5 : ";
	std::cout << *testArrayconst.begin() << "," << *testArrayconst.data() << "," << *testArrayconst.rbegin() << std::endl;

	std::cout << "front && end = 1 et 5 : ";
	std::cout << testArrayconst.front() << "," << testArrayconst.back() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	// test Vector

	myVector<int, 5> testVector;
	myVector<int, 5> testVector2{ 1,2,3,4,5 };
	myVector<int, 5> testVector3(testVector2);
	myVector<int, 5>testVector4{ 1,2,3 };

	testVector = testVector3;

	std::cout << "Size  && max size = 5 :";
	std::cout << testVector.size() << "," << testVector.max_size() << std::endl;

	std::cout << "vector == 1,2,3,4,5 : ";
	std::cout << testVector << std::endl;

	std::cout << "vector2 == 1,2,3,4,5 : ";
	std::cout << testVector2 << std::endl;

	std::cout << "vector3 == 1,2,3,4,5 : ";
	std::cout << testVector3 << std::endl;

	std::cout << "vector4 == 1,2,3,0,0 : ";
	std::cout << testVector4 << std::endl;

	std::cout << "vector[0] == 1 :";
	std::cout << testVector[0] << std::endl;

	std::cout << "vector.at(0) == 1 :";
	std::cout << testVector.at(0) << std::endl;

	std::cout << "*Begin && *data && rbegin = 1,1,5 : ";
	std::cout << *testVector.begin() << "," << *testVector.data() << "," << *testVector.rbegin() << std::endl;

	std::cout << "front && end = 1 et 5 :";
	std::cout << testVector.front() << "," << testVector.back() << std::endl;

	std::fill(testVector.begin(), testVector.end(), 5);
	std::cout << "vector == 5,5,5,5,5 : ";
	std::cout << testVector << std::endl;

	std::fill(testVector.rbegin(), testVector.rend(), 10);
	std::cout << "vector == 10,10,10,10,10 : ";
	std::cout << testVector << std::endl;


	glg::swap(testVector, testVector2);
	std::cout << "vector == 1,2,3,4,5 : ";
	std::cout << testVector << std::endl;
	testVector2 = { 1,2,3,4,5 };
	testVector.push_back(100);
	std::cout << "vector == 1,2,3,4,5,100 && size = 6 : ";
	std::cout << testVector << "," << testVector.size() << std::endl;

	testVector.pop_back();
	std::cout << "vector == 1,2,3,4,5 && size = 5 : ";
	std::cout << testVector << "," << testVector.size() << std::endl;

	testVector.erase(testVector.begin());
	std::cout << "vector == 2,3,4,5 : ";
	std::cout << testVector << std::endl;

	testVector.insert(testVector.begin(), 100);
	std::cout << "vector == 100,2,3,4,5 : ";
	std::cout << testVector << std::endl;

	testVector.assign({ 1,2,3 });
	std::cout << "vector == 1,2,3 : ";
	std::cout << testVector << std::endl;

	testVector.assign(3, 3);
	std::cout << "vector == 3,3,3 : ";
	std::cout << testVector << std::endl;

	testVector.assign(testVector2.begin(), testVector2.end());
	std::cout << "vector == 1,2,3,4,5 : ";
	std::cout << testVector << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	const myVector<int, 5> testVectorconst{ 1,2,3,4,5 };
	const myVector<int, 5> testVector2const{ 1,2,3,4,5 };
	const myVector<int, 5> testVector3const(testVector2const);
	const myVector<int, 3>testVector4const{ 1,2,3 };

	std::cout << "Size  && max size = 5 :";
	std::cout << testVectorconst.size() << "," << testVectorconst.max_size() << std::endl;

	std::cout << "vector == 1,2,3,4,5 : ";
	std::cout << testVectorconst << std::endl;


	std::cout << "vector4 == 1,2,3 : ";
	std::cout << testVector4const << std::endl;

	std::cout << "vector[0] == 1 :";
	std::cout << testVectorconst[0] << std::endl;

	std::cout << "vector.at(0) == 1 :";
	std::cout << testVectorconst.at(0) << std::endl;

	std::cout << "*Begin && *data = 1 : ";
	std::cout << *testVectorconst.begin() << "," << *testVectorconst.data() << std::endl;

	std::cout << "front && end = 1 et 5 :";
	std::cout << testVectorconst.front() << "," << testVectorconst.back() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	//test List
	myList<int> testList{ 1,2,3,4,5 };
	myList<int> testList2{ 1,2,3,4,5 };
	myList<int> testList3(testList2);
	myList<int> testList4{ 1,2,3 };

	testList = testList2;

	std::cout << "Size  && max size = 5 :";
	std::cout << testList.size() << "," << testList.max_size() << std::endl;

	std::cout << "List == 1,2,3,4,5 : ";
	std::cout << testList << std::endl;

	std::cout << "List2 == 1,2,3,4,5 : ";
	std::cout << testList2 << std::endl;

	std::cout << "List3 == 1,2,3,4,5 : ";
	std::cout << testList3 << std::endl;

	std::cout << "List4 == 1,2,3,0,0 : ";
	std::cout << testList4 << std::endl;

	std::cout << "List[0] == 1 :";
	std::cout << testList[0] << std::endl;

	std::cout << "List.at(0) == 1 :";
	std::cout << testList.at(0) << std::endl;

	std::cout << "*Begin && rbegin  1 , 5 : ";
	std::cout << *testList.begin() << "," << *testList.rbegin() << std::endl;

	std::cout << "front && end = 1 et 5 :";
	std::cout << testList.front() << "," << testList.back() << std::endl;

	glg::fill(testList.begin(), testList.end(), 5);
	std::cout << "List == 5,5,5,5,5 : ";
	std::cout << testList << std::endl;

	glg::fill(testList.rbegin(), testList.rend(), 10);
	std::cout << "List == 10,10,10,10,10 : ";
	std::cout << testList << std::endl;


	glg::swap(testList, testList2);
	std::cout << "List == 1,2,3,4,5 : ";
	std::cout << testList << std::endl;
	testList2 = { 1,2,3,4,5 };
	testList.push_back(100);
	std::cout << "List == 1,2,3,4,5,100 && size = 6 : ";
	std::cout << testList << "," << testList.size() << std::endl;

	testList.pop_back();
	std::cout << "List == 1,2,3,4,5 && size = 5 : ";
	std::cout << testList << "," << testList.size() << std::endl;

	testList.erase(testList.begin());
	std::cout << "List == 2,3,4,5 : ";
	std::cout << testList << std::endl;

	testList.insert(testList.begin(), 100);
	std::cout << "List == 100,2,3,4,5 : ";
	std::cout << testList << std::endl;

	testList.assign({ 1,2,3 });
	std::cout << "List == 1,2,3 : ";
	std::cout << testList << std::endl;

	testList.assign(3, 3);
	std::cout << "List == 3,3,3 : ";
	std::cout << testList << std::endl;

	testList.assign(testList2.begin(), testList2.end());
	std::cout << "List == 1,2,3,4,5 : ";
	std::cout << testList << std::endl;

	std::cout << std::endl;

	const myList<int> testListconst{ 1,2,3,4,5 };
	const myList<int> testList2const{ 1,2,3,4,5 };
	const myList<int> testList3const(testList2const);
	const myList<int>testList4const{ 1,2,3 };


	std::cout << "Size  && max size = 5 :";
	std::cout << testListconst.size() << "," << testListconst.max_size() << std::endl;

	std::cout << "List == 1,2,3,4,5 : ";
	std::cout << testListconst << std::endl;


	std::cout << "List == 1,2,3,0,0 : ";
	std::cout << testList4const << std::endl;

	std::cout << "List[0] == 1 :";
	std::cout << testListconst[0] << std::endl;

	std::cout << "List.at(0) == 1 :";
	std::cout << testListconst.at(0) << std::endl;

	std::cout << "*Begin = 1 rbegin = 5 : ";
	std::cout << *testListconst.begin() << "," << *testListconst.rbegin() << std::endl;

	std::cout << "front && end = 1 et 5 :";
	std::cout << testListconst.front() << "," << testListconst.back() << std::endl;

	//// test Intrusive List

	PLEASE::myIntrusiveList<int> testIntrusiveList;
	testIntrusiveList.push_back(1);
	testIntrusiveList.push_back(2);
	testIntrusiveList.push_back(3);
	testIntrusiveList.push_back(4);
	testIntrusiveList.push_back(5);

	PLEASE::myIntrusiveList<int> testIntrusiveList2;
	testIntrusiveList2.push_back(1);
	testIntrusiveList2.push_back(2);
	testIntrusiveList2.push_back(3);
	testIntrusiveList2.push_back(4);
	testIntrusiveList2.push_back(5);

	PLEASE::myIntrusiveList<int> testIntrusiveList3(testIntrusiveList2);

	PLEASE::myIntrusiveList<int>testIntrusiveList4;
	testIntrusiveList4.push_back(1);
	testIntrusiveList4.push_back(2);
	testIntrusiveList4.push_back(3);

	testIntrusiveList = testIntrusiveList2;

	std::cout << "Size  && max size = 5 :";
	std::cout << testIntrusiveList.size() << "," << std::endl;

	std::cout << "myIntrusiveList == 1,2,3,4,5 : ";
	std::cout << testIntrusiveList << std::endl;

	std::cout << "IntrusiveList2 == 1,2,3,4,5 : ";
	std::cout << testIntrusiveList2 << std::endl;

	std::cout << "IntrusiveList3 == 1,2,3,4,5 : ";
	std::cout << testIntrusiveList3 << std::endl;

	std::cout << "IntrusiveList4 == 1,2,3,0,0 : ";
	std::cout << testIntrusiveList4 << std::endl;

	std::cout << "myIntrusiveList[0] == 1 :";
	std::cout << testIntrusiveList[0] << std::endl;

	std::cout << "myIntrusiveList.at(0) == 1 :";
	std::cout << testIntrusiveList.at(0) << std::endl;

	std::cout << "*Begin && rbegin  1 , 5 : ";
	std::cout << *testIntrusiveList.begin() << "," << *testIntrusiveList.rbegin() << std::endl;

	std::cout << "front && end = 1 et 5 :";
	std::cout << testIntrusiveList.front() << "," << testIntrusiveList.back() << std::endl;

	glg::swap(testIntrusiveList, testIntrusiveList2);
	std::cout << "myIntrusiveList == 1,2,3,4,5 : ";
	std::cout << testIntrusiveList << std::endl;
	testIntrusiveList2.push_back(1);
	testIntrusiveList2.push_back(2);
	testIntrusiveList2.push_back(3);
	testIntrusiveList2.push_back(4);
	testIntrusiveList2.push_back(5);

	testIntrusiveList.push_back(100);
	std::cout << "myIntrusiveList == 1,2,3,4,5,100 && size = 6 : ";
	std::cout << testIntrusiveList << "," << testIntrusiveList.size() << std::endl;

	testIntrusiveList.pop_back();
	std::cout << "v == 1,2,3,4,5 && size = 5 : ";
	std::cout << testIntrusiveList << "," << testIntrusiveList.size() << std::endl;

	testIntrusiveList.erase(testIntrusiveList.begin());
	std::cout << "myIntrusiveList == 2,3,4,5 : ";
	std::cout << testIntrusiveList << std::endl;

	testIntrusiveList.insert(testIntrusiveList.begin(), PLEASE::Node(100));
	std::cout << "myIntrusiveList == 100,2,3,4,5 : ";
	std::cout << testIntrusiveList << std::endl;

	testIntrusiveList.clear();
	testIntrusiveList.assign(testIntrusiveList2.begin(), testIntrusiveList2.end());
	std::cout << "myIntrusiveList == 1,2,3,4,5 : ";
	std::cout << testIntrusiveList << std::endl;

	std::cout << std::endl;

	myArray<int, 5> testArraysort{ 5,4,3,2,1 };
	std::cout << testArraysort << std::endl;
	glg::sort(testArraysort);
	std::cout << testArraysort << std::endl;

	myVector<int, 5> testVectorsort{ 5,4,3,2,1 };
	std::cout << testVectorsort << std::endl;
	glg::sort(testVectorsort);
	std::cout << testVectorsort << std::endl;

	myList<int> testListsort{ 5,4,3,2,1 };
	std::cout << testListsort << std::endl;
	glg::sort(testListsort);
	std::cout << testListsort << std::endl;

	myVectorND<int, 5> testVectorND;
	myVectorND<int, 5> testVector2ND{ 1,2,3,4,5 };
	myVectorND<int, 5> testVector3ND(testVector2ND);
	myVectorND<int, 5> testVector4ND{ 1,2,3 };

	testVectorND = testVector3ND;

	std::cout << std::endl;
	std::cout << "test vector nd: " << std::endl;
	std::cout << testVectorND;

	myVectorND<float, 3> lhs{ 3,4,0 };
	myVectorND<float, 3> rhs{ 3,4,1 };
	lhs = Math::crossProduct(lhs, rhs);
	//lhs = KT::VectorNormalization(lhs);
	std::cout << std::endl;
	bool t = lhs != rhs;
	std::cout << t << std::endl;
	std::cout << "test cross product :" << std::endl << lhs << std::endl;
	std::cout << "test produit scalaire :" << std::endl << Math::scalarProduct(lhs, rhs) << std::endl;

	myMatrix<int, 3, 3> testmatrix1{ 1,2,3,4,5,6,7,8,9 };
	std::cout << "test matrix :" << std::endl << testmatrix1;
}