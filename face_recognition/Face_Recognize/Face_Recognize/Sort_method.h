// InsertSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h> 
//#include "Sort.h"
using namespace std;

#define MAX_NUM 100



template <typename T>
int count_size(T& x)
{
	int s1 = sizeof(x);
	int s2 = sizeof(x[0]);
	int result = s1 / s2;
	return result;
}


void printArrary(int *a, size_t len, string m_str) 
{
	m_str.append(": ");
	cout << m_str;
	for (size_t t = 0; t < len; t++)
		cout << a[t] << " ";
	cout << endl;
}

template <typename T>
void printVector(std::vector<T> &a, string m_str) 
{
	m_str.append(":");
	cout << m_str;
	for(size_t t = 0; t < a.size(); t++)    /*print each step*/
		cout << a[t] << " ";
	cout << endl;
}
/*--------------------------------------------------------------------------------
* Function : BrowseVectorElement
*
* Purpose  : Browse the input vector
*
* Inputs   : -
* Outputs  : -
* Returns  : NULL
*
* Version    Date         Author         Comment
*  00.01     2017/04/01   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
template <typename T>
void BrowseVectorElement(std::vector<T> &a, string m_str)
{
	std::vector<T>::iterator iter_begin = a.begin(),
		iter_end = a.end();
	//print the input vector  
	m_str.append("vector element:");
	cout << m_str << endl;

	while (iter_begin != iter_end)
	{
		cout << *iter_begin << " ";
		iter_begin++;
	}
	cout << endl;
}

/*--------------------------------------------------------------------------------
* Function : CreatRand
*
* Purpose  : Creat int type vector
*
* Inputs   : -
* Outputs  : -
* Returns  : Vector of int
*
* Version    Date         Author         Comment
*  00.01     2017/03/31   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
std::vector<int> CreatRand(size_t size)
{
	/*产生随机数*/
	std::vector<int> a_vec;
	a_vec.reserve(size);
	srand((unsigned)time(NULL));//srand()函数产生一个以当前时间开始的随机种子.应该放在for等循环语句前面 不然要很长时间等待 

	while (a_vec.size() != a_vec.capacity())
	{
		a_vec.push_back(std::rand() % MAX_NUM);
	}
	return a_vec;
}

/*--------------------------------------------------------------------------------
* Function : InsertSort
*
* Purpose  : Simple insert sort algorithm
*
* Inputs   : -
* Outputs  : -
* Returns  : TRUE or False
*
* Version    Date         Author         Comment
*  00.01     2017/03/27   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
int InsertSort(int *a, int len)  /*C Style*/
{
	int i, j,t, tmp = 0;

	if (a == NULL) return -1;

	cout << "Input string len ="<< len << endl;

	if (len < 2) return -2;

	for (i = 1; i < len; i++)
	{
		if (a[i] < a[i - 1])//前面i-1个已经排好，有序。
		{
			tmp = a[i];//a[i]要插入排好的数组
			for (j = i - 1; tmp<a[j]; j--)
				a[j+1] = a[j];  //往后移动
			a[j+1] = tmp; //因为在退出循环前j--了，所以是a【j+1】的位置
		}

		for (t = 0; t < len; t++)
			cout << a[t] << " ";
		cout<<endl;
	}

	return 0;
}
/*--------------------------------------------------------------------------------
* Function : Binary_InsertSort
*
* Purpose  : Binary insert sort algorithm
*
* Inputs   : -
* Outputs  : -
* Returns  : TRUE or False
*
* Version    Date         Author         Comment
*  00.01     2017/03/27   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
int Binary_InsertSort(int *a, int len)  /*C Style*/
{
	int i, j, tmp,mid,low,high= 0;

	if (a == NULL) return -1;
	if (len < 2) return -2;

	cout << "Input string len =" << len << endl;

	for (i = 1; i < len; i++)
	{
	    low = 0;
	    high = i;
		//判断该元素是否需要排序
		if (a[i] < a[i - 1])
		{
			//记录将要插入有序数组的a【i】
			tmp = a[i];
			//用二分法查找插入位置
			while (low <= high)
			{
				mid = (low + high) / 2;
				if (a[mid] > tmp)
					high = mid-1;
				else
					low = mid+1;
			}
			//插入位置为最终的high+1位置，因为high=mid-1
			//从i-1开始，排在high+1前的有序集体向后移动
			for (j = i - 1; j >= high+1; j--)
				a[j + 1] = a[j];
			a[j + 1] = tmp;

			for (int t = 0; t < len; t++)
				cout << a[t] << " ";
			cout << endl;		
		}
	}

	return true;
}
/*--------------------------------------------------------------------------------
* Function : findMax
*
* Purpose  : Find max value from the input vector
*
* Inputs   : -
* Outputs  : -
* Returns  : return the max value in the vector
*
* Version    Date         Author         Comment
*  00.01     2017/03/31   Jiang Wenfei   Intial version 
*------------------------------------------------------------------------------*/
template <typename Comparable>
const Comparable & findMax(const std::vector<Comparable> & a)
{
	int maxIndex = 0;
	for (int i = 1; i < a.size(); i++)
	{
		if (a[maxIndex] < a.[i])
			maxIndex = i;
	}
	return a[maxIndex];
}
/*--------------------------------------------------------------------------------
* Function : InsertionSort
*
* Purpose  : Simple insert sort algorithm 
*
* Inputs   : -
* Outputs  : -
* Returns  : return the max value in the vector
*
* Version    Date         Author         Comment
*  00.01     2017/03/31   Jiang Wenfei   Intial version
*  00.02     2017/03/31   Jiang Wenfei   print each setp
*------------------------------------------------------------------------------*/
template <typename Comparable>
void InsertionSort(std::vector<Comparable> &a)
{
	int j;
	//static_assert(a.size() > 100, "Input vector size is too large!");	
	BrowseVectorElement(a,"Log privious ");

	for (unsigned int p = 1; p < a.size(); p++)
	{
		Comparable tmp = a[p];                    /*Record the value*/ 
		for (j = p; j > 0 && tmp < a[j - 1]; j--) /*right shift*/
			a[j] = a[j - 1];
		a[j] = tmp;                               /*Insert to the right place*/

		for (unsigned int t = 0; t < a.size(); t++)    /*print each step*/
			cout << a[t] << " ";
		cout << endl;
	}
	//print vecotr element
	BrowseVectorElement(a,"Log end ");
}

/*--------------------------------------------------------------------------------
* Function : binary_InsertSort
*
* Purpose  : binary insert sort algorithm
*
* Inputs   : -
* Outputs  : -
* Returns  : NULL
*
* Version    Date         Author         Comment
*  00.01     2017/04/02   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
template <typename T>
void binary_InsertSort(std::vector<T> &a) /*C++ style*/
{
	unsigned int i,t, j,low, high,mid=0;
	T tmp;

	BrowseVectorElement(a, "binary_InsertSort Log start ");
	for (i = 1; i < a.size(); i++)
	{
		low = 0;
		high = i - 1;
		/*check if less than the sorted arrary*/
		if (a[i] < a[i - 1])
		{
			tmp = a[i]; //Record the value
			/*Find the position for insert*/
			while (low < high)
			{
				mid = (low + high) / 2;
				if (tmp < a[mid])
					high =mid>1? mid-1:0;
				//high = mid - 1;
				else
					low = mid+1;
			}
			/*Right shift the sorted arrary and insert to the right position*/
			for (j = i - 1; j >= high + 1; j--)
				a[j + 1] = a[j];
			a[j + 1] = tmp;

			for (t = 0; t < a.size(); t++)    /*print each step*/
				cout << a[t] << " ";
			cout << endl;
		}
	}
	BrowseVectorElement(a, "binary_InsertSort Log end ");
}
/*--------------------------------------------------------------------------------
* Function : binary_InsertSort
*
* Purpose  : shell sort algorithm
*
* Inputs   : -
* Outputs  : -
* Returns  : NULL
*
* Version    Date         Author         Comment
*  00.01     2017/04/02   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
template <typename T>
void shellSort(std::vector<T> &a)
{
	BrowseVectorElement(a, "Shell sort start ");

	for (size_t gap = a.size() / 2; gap > 0; gap /= 2)
	{
		for (size_t i = gap; i < a.size(); i++)
		{
			T tmp = a[i];
			size_t  j = i;
			for (; j >= gap&&tmp < a[j - gap]; j -= gap)
				a[j] = a[j - gap];
			a[j] = tmp;

			printVector(a, "gap");
		}

		BrowseVectorElement(a, "Shell sort end ");
	}
	BrowseVectorElement(a, "Shell sort end ");
}

/*--------------------------------------------------------------------------------
* Function : swap
*
* Purpose  :swap between the first and last one in the arrary
*
* Inputs   : a: input arrary
*            m:
* Outputs  : -
* Returns  : NULL
*
* Version    Date         Author         Comment
*  00.01     2017/04/03   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
void swap(int *a, size_t pos1, size_t pos2)
{
	a[pos1] = a[pos1] ^ a[pos2];
	a[pos2] = a[pos1] ^ a[pos2];
	a[pos1] = a[pos1] ^ a[pos2];

}

/*************************************************
******************HEAP SORT***********************
**************************************************/
/*--------------------------------------------------------------------------------
* Function : HeapAdjust
*
* Purpose  :For build a heap to the big top heap
*
* Inputs   : a: input arrary
             m: current
			 size: the size of the arrary
* Outputs  : -
* Returns  : NULL
*
* Version    Date         Author         Comment
*  00.01     2017/04/03   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
void HeapAdjust(int *a,int m, int len) /*C Style*/
{
	int j = 0;

	/*First record the */
	int tmp = a[m];

	int size = len - 1;

#if 0
	for (j = 2 * m; j <= size; j *= 2)
	{
		/*Compare between left and right child of this node*/
		if (a[j] < a[j+1] && j != size - 1)
			++j; /**/

		/*Compare the bigger value of child with this node */
		if (tmp >= a[j]) break; 

		/*Replace the root value with the bigger one*/
		a[m] = a[j];

		/*update the subscript of m*/
		m = j;
	}

	/*update the latest a[m] - m already changed to j */
	a[m] = tmp;
#endif

	int lchild = 2 * (m + 1) - 1;
	int rchild = 2 * (m + 1);
	int max = m;

	if (a[lchild] >= a[rchild] && lchild < size && rchild < size)
		max = lchild;
	else if (a[lchild] <= a[rchild] && lchild < size && rchild < size)
		max = rchild;
	else
		max = m;

	if (a[m] >= a[max])
		max = m;

	if (max != m)
	{
		swap(a,max,m);
		HeapAdjust(a, max, size);
	}

	printArrary(a, 12, "rebuilding arrary");
}


/*--------------------------------------------------------------------------------
* Function : HeapSort
*
* Purpose  :For adjust a heap to the big top heap
*
* Inputs   : a: input arrary
             m:
* Outputs  : -
* Returns  : NULL
*
* Version    Date         Author         Comment
*  00.01     2017/04/03   Jiang Wenfei   Intial version
*------------------------------------------------------------------------------*/
void HeapSort(int *a,int size)
{
	size_t i, j;

	printArrary(a, size, "input arrary");
	/*adjust a heap to the big top heap*/
	for (i = size / 2 -1; i >=0; i--)
		HeapAdjust(a, i, size);
	printArrary(a, size, "max heap arrary");

	for (j = size - 1 ; j > 0; j--)
	{
		swap(a, 0, j);
		printArrary(a, 12, "swap arrary ended");
		HeapAdjust(a, 0, j);
	}
	printArrary(a, size, "max heap arrary");
}

#if 0
int _tmain(int argc, _TCHAR* argv[])
{
	/*Two C style sort funtion*/
	int b[] = {8,12,4,7,2,6,3,11,9,15,1,7};
	int len = sizeof(b) / sizeof(b[0]);
	InsertSort(b,len);

	int c[] = { 8, 12, 4, 7, 2, 6, 3, 11, 9, 15, 1, 7,11 };
	Binary_InsertSort(c,len);

	vector<int> vec_t = CreatRand(20);
	BrowseVectorElement(vec_t,"Log rand ");
	InsertionSort(vec_t);

	//vector<int> vec = CreatRand(9);
	//BrowseVectorElement(vec_t, "Log rand ");
	//binary_InsertSort(vec);

	shellSort(CreatRand(10));

	int d[] = { 8, 12, 4, 7, 2, 6, 3, 11, 9, 15, 1, 7};
	HeapSort(d, count_size(d));

	system("pause");
	return 0;
}
#endif
