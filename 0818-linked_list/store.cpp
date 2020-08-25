#include<iostream>
#include<vector>
using namespace std;
int main() {

	int n;
	cin >> n;
	vector<int>nums(n, 0);

	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	int max_count = 1;
	for (int i = 0; i < n; i++) {
		int k = nums[i];
		int tmp = 1;
		for (int j = i + 1; j < n; j++) {
			if (k + 1 == nums[j]) {
				tmp++;
				k = nums[j];
			}
		}
		if (tmp > max_count) {
			max_count = tmp;
		}
	}
	cout << n - max_count << endl;
	system("pasue");





	return 0;
}
