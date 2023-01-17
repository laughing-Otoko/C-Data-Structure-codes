//Snippet: Sequential search
template<class elemType>
int arrayListType<elemType>::seqSearch(const elemType& searchItem) const
{
	int loc;
	bool found = false;

	for (loc = 0; loc < length; loc++)
		if (list[loc] == item)
		{
			found = true;
			break;
		}
	if (found)
		return loc;
	else
		return -1;
}

//Snippet: Binary seach
template <class elemType>
int orderedArryListType<elemType>::binarySearch(const elemType& item) const
{
	int first = 0;
	int last = length - 1;
	int mid;
	bool found = false;

	while (first <= last && !found) {
		mid = (first + last) / 2;
		if (list[mid] == item)
			found = true;
		else if (list[mid] > item)
			last = mid - 1;
		else
			first = mid + 1;
	}
	if (found)
		return mid;
	else
		return -1;
}