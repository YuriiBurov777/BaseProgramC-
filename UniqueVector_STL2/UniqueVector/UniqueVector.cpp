

#include <iostream>
#include <vector> 
#include <algorithm>

 void  Print(std::vector<int>& vec) {
	for(int var : vec)
	{
		std::cout << var << " ";
	}
	std::cout << std::endl;
}
 template<typename T>
 std::vector<T> Sort(std::vector<T>& vec) {
	std::sort(vec.begin(), vec.end());
	auto last = std::unique(vec.begin(), vec.end());
	vec.erase(last, vec.end());
	return vec;
}



 int main()
 {
	 std::vector<int> vec{ 1, 1, 2, 5, 6, 1, 2, 4 };
	 Print(vec);
	 Sort(vec);
	 Print(vec);
 }

