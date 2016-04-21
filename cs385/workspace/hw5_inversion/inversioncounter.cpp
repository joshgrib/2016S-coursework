/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Josh Gribbon
 * Version     : 1.0
 * Date        : 3-30-2016
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor I have abided by the Stevens Honor Code.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long count = 0;
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (array[j] < array[i]) {
				count++;
			}
		}
	}
	return count;
}


/**
 * BEGINNING of stuff I found online
 */



int  mergeSort2(int arr[], int temp[], int left, int right);
int merge(int arr[], int temp[], int left, int mid, int right);
/* This function sorts the input array and returns the
   number of inversions in the array */
int mergeSort(int arr[], int array_size)
{
    int *temp = (int *)malloc(sizeof(int)*array_size);
    return mergeSort2(arr, temp, 0, array_size - 1);
}

/* An auxiliary recursive function that sorts the input array and
  returns the number of inversions in the array. */
int mergeSort2(int arr[], int temp[], int left, int right)
{
  int mid, inv_count = 0;
  if (right > left)
  {
    /* Divide the array into two parts and call _mergeSortAndCountInv()
       for each of the parts */
    mid = (right + left)/2;

    /* Inversion count will be sum of inversions in left-part, right-part
      and number of inversions in merging */
    inv_count  = mergeSort2(arr, temp, left, mid);
    inv_count += mergeSort2(arr, temp, mid+1, right);

    /*Merge the two parts*/
    inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}

/* This funt merges two sorted arrays and returns inversion count in
   the arrays.*/
int merge(int arr[], int temp[], int left, int mid, int right)
{
  int i, j, k;
  int inv_count = 0;

  i = left; /* i is index for left subarray*/
  j = mid;  /* i is index for right subarray*/
  k = left; /* i is index for resultant merged subarray*/
  while ((i <= mid - 1) && (j <= right))
  {
    if (arr[i] <= arr[j])
    {
      temp[k++] = arr[i++];
    }
    else
    {
      temp[k++] = arr[j++];

     /*this is tricky -- see above explanation/diagram for merge()*/
      inv_count = inv_count + (mid - i);
    }
  }

  /* Copy the remaining elements of left subarray
   (if there are any) to temp*/
  while (i <= mid - 1)
    temp[k++] = arr[i++];

  /* Copy the remaining elements of right subarray
   (if there are any) to temp*/
  while (j <= right)
    temp[k++] = arr[j++];

  /*Copy back the merged elements to original array*/
  for (i=left; i <= right; i++)
    arr[i] = temp[i];

  return inv_count;
}

/**
 * END of stuff I found online
 */




/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */

long count_inversions_fast(int array[], int length) {
	// Hint: Use mergesort!
	int *scratch = new int[length];
	long count = mergesort(array, scratch, 0, length);//putting things other than small ints make this not work
	delete scratch;
	return count;
}


/**
 * Sorts the given array using a mergesort, while also counting inversions
 * Returns the amount of inversions
 */

static long mergesort(int array[], int scratch[], int low, int high) {
	long count = 0;
	if (low < high) {
		int mid = low + ((low + high) / 2);
		count += mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid + 1, high);
		int L = low;
		int H = mid + 1;
		for (int k = low; k < high; k++) {
			if ((L <= mid) && ((H > high) || (array[L] <= array[H]))) {
				scratch[k] = array[L];
				L++;
			} else {
                count += mid - L +1;
				scratch[k] = array[H];
				H++;
			}
		}
		for (int k = low; k < high; k++) { //copy the new array over
			array[k] = scratch[k];
		}
	}
	return count;
}


int main(int argc, char *argv[]) {
	if (argc != 1) { //there is some argument
		if (argc > 2) { //too many args
			cerr << "Usage: ./inversioncounter [slow]" << endl;
			return 1;
		}
		string input;
		istringstream iss(argv[1]);
		iss >> input;
		if (input != "slow") { //not the right arg
			cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
			return 1;
		}
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;

	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
				} else {
					cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}

	if (values.size() == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}

	cout << "Number of inversions: ";
	if (argc > 1) { //slow mode because there is an input which is already checked
		cout << count_inversions_slow(&values[0], values.size()) << endl;
		return 0;
	}
	/**
	 * For below:
	 * I couldn't get the mergesort one to count the inversions, so the slow
	 * one is used for both because it passes way more test cases this way...
	 */
	cout << count_inversions_fast(&values[0], values.size()) << endl;

	//This one uses the stuff I found online - not submitted like this
	//This was just to workshop and try to get something working
	//cout << mergeSort(&values[0], values.size()) << endl;

	return 0;
}
