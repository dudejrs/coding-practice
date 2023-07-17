
def solve(fences, left, right) :

	if(left == right) : return fences[left]

	mid = (left + right) // 2
	ret = max(solve(fences,left, mid), solve(fences, mid+1, right))

	lo , hi = mid, mid+1
	h = min(fences[lo], fences[hi])
	ret = max(ret, h*2)

	while left < lo or hi < right :
		if left < lo and (hi == right or fences[hi+1] < fences[lo-1])   :
			lo-=1;
			h = min(h, fences[lo])
		else :
			hi+=1;
			h = min(h, fences[hi])
		ret = max(ret, h * (hi-lo+1))

	return ret

if __name__ == "__main__" :
	with open("data/울타리_잘라내기.txt") as f :
		test_cases = int(f.readline());

		for _ in range(test_cases) :
			n = int(f.readline())
			fences = list(map( lambda x : int(x), f.readline().split()))
			print(solve(fences, 0, len(fences)-1))
