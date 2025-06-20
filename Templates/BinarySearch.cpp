int binary_search(int destination, const std::vector<int> &vec) {
	int l = 0, r = static_cast<int>(vec.size()) - 1;
	// 全都不满足条件，归0，区间外
	//全都满足就是最后一个，区间内
	while(l < r) {
		int mid = (l + r + 1) / 2;//attention
		if(vec[mid] < destination) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	return r;
}
//此方法是在讲，期望l，r都指向满足条件的最后一个

int binary_search(int destination, const std::vector<int> &vec) {
	int l = 1, r = static_cast<int>(vec.size());
	// 全都不满足条件，归1，区间内
	//全都满足就是最后一个 + 1，区间外
	while(l < r) {
		int mid = (l + r) / 2;//attention
		if(vec[mid] < destination) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	return r;
}
//此方法是在讲，期望l，r都指向不满足条件的第一个

int binary_search(int destination, const std::vector<int> &vec) {
	int l = 0, r = static_cast<int>(vec.size());//n + 1
	while(l + 1 < r) {
		int mid = (l + r) / 2;
		if(vec[mid] < destination) {
			l = mid;
		} else {
			r = mid;
		}
	}
	return r;
}
//此方法是在讲期望l指向满足条件最后一个，r期望指向不满足条件第一个