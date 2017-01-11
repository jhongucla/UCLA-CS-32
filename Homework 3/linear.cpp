bool allTrue(const string a[], int n)
{
    if (n <= 0)
        return true;
    if (!somePredicate(a[0]))
        return false;
    return allTrue(a+1, n-1);
}

int countFalse(const string a[], int n)
{
    if (n <= 0)
        return 0;
    if (!somePredicate(a[0]))
        return countFalse(a+1, n-1) + 1;
    return countFalse(a+1, n-1);
}

int firstFalse(const string a[], int n)
{
    if (n <= 0)
        return -1;
    if (!somePredicate(a[n-1]))
        if(firstFalse(a, n-1) == -1)
            return n-1;
    return firstFalse(a, n-1);
}

int indexOfLeast(const string a[], int n)
{
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;
    if (a[n-1] < a[indexOfLeast(a, n-1)])
        return n-1;
    else
        return indexOfLeast(a, n-1);
}

bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 <= 0)
		return true;
	if (n1 <= 0)
		return false;
	if (a1[0] == a2[0])
		return includes(a1+1, n1-1, a2+1, n2-1);
	else
		return includes(a1+1, n1-1, a2, n2);
}