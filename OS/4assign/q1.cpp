#include <iostream>

using namespace std;

int main() {
	int pageRequests[20] = {0, 1, 20, 2, 20, 21, 32, 31, 0, 60, 0, 0, 16, 1, 17, 18, 32, 31, 0, 61};
	
	for(int i = 0; i < 20; i++) {
		cout << (pageRequests[i] >> 4) << " ";
	}
	cout << endl;
	return 0;
}
