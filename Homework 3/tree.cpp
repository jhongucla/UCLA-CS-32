int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 == 0)
	{
		if (n2 == 0)
			return 1;
		else
			return 0;
	}
	if (n2 == 0)
		return 1;
	if (a1[0] == a2[0])
		return countIncludes(a1+1, n1-1, a2, n2) + countIncludes(a1+1, n1-1, a2+1, n2-1);
	else
		return countIncludes(a1+1, n1-1, a2, n2);
}

void exchange(string& x, string& y)
{
	string t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < divider come before all the other elements,
// and all the elements whose value is > divider come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= divider, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < divider
//   * for firstNotLess <= i < firstGreater, a[i] == divider
//   * for firstGreater <= i < n, a[i] > divider
// All the elements < divider end up in no particular order.
// All the elements > divider end up in no particular order.
void divide(string a[], int n, string divider,
	int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < divider
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == divider
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > divider

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > divider)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < divider)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

void order(string a[], int n)
{
	if (n <= 1)
		return;
    int firstNotLess = 0, firstGreater = 0;
    divide(a, n, a[n/2], firstNotLess, firstGreater);
    order(a, firstNotLess);
    order(a+firstGreater, n-firstGreater);
}