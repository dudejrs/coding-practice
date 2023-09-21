from collections import defaultdict
import random

TEST_CASES = 1

MAX_STORES = 100_000
MAX_SELLS = 100_000
MAX_DAYS = 1_000_000_000
MAX_QUANTITY = 1_000_000_000



class Stock : 

	def __init__(self) :
		self._data = defaultdict(int)

	def store(self, quantity, current_day, limit) : 

		self._data[current_day + limit ] += quantity
		return

	def sell(self, quantity, customer_type) :

		if len(self._data) == 0 : return

		if customer_type == 0 :
			while quantity > 0 :
				if len(self._data) == 0 : break
				
				cur = self.earliest_day()
				cur_quantity = self._data[cur]
				if cur_quantity < quantity :
					quantity -= cur_quantity;
					del self._data[cur]
				else :
					self._data[cur] -= quantity
					quantity = 0
		else :
			while quantity > 0 :
				if len(self._data) == 0 : break

				cur = self.latest_day()
				cur_quantity = self._data[cur]
				if cur_quantity < quantity :
					quantity -= cur_quantity
					del self._data[cur]
				else :
					self._data[cur] -= quantity
					quantity = 0


	def discard(self, day) :
		if len(self._data) == 0 : return []

		cur = self.earliest_day()
		ret = []
		while cur < day and len(self._data) != 0 :
			cur = self.earliest_day()
			ret.append([cur, self._data[cur]])
			del self._data[cur]


		return ret


	def discard_all(self) :
		if len(self._data) == 0 : return []

		return self.discard(self.latest_day() +1)

	def earliest_day(self) :
		
		return list(self._data.keys())[0]

	def latest_day(self) :
		return list(self._data.keys())[-1]


	def __str__ (self) :
		return str(self._data)



def sampled_days(n, limit= MAX_DAYS) :
	return sorted(list(random.sample(range(limit), k=n)))

def make_store(day) :
	return [
	day,
	random.randint(1,MAX_STORES)
	]

def make_sell(day) :
	return [
	day,
	random.randint(1,MAX_SELLS),
	round(random.random())
	]


def solve(stores, sells) :

	ret = []

	current_day = 0

	stock = Stock()

	while (len(stores) != 0) or (len(sells) != 0) :

		# 남은 store 상품 다 폐기처리
		if len(stores) == 0 :
			while len(sells) != 0 :
				day, quantity, customer_type = sells.pop(0)
				discarded = stock.discard(day)
				ret.extend(discarded)
				stock.sell(quantity, customer_type)

			discarded = stock.discard_all()
			ret.extend(discarded)
			break
			
		# 남은 구매들 다 진행 
		if len(sells) == 0 :
			while len(stores) != 0 :
				limit, quantity = stores.pop(0)
				stock.store(quantity, current_day, 3)

			discarded = stock.discard_all()
			ret.extend(discarded)
			break

		store_day = stores[0][0]
		sell_day = sells[0][0]
		current_day = min(store_day, sell_day)

		# 먼저 폐기 처리한다
		discarded = stock.discard(current_day)
		ret.extend(discarded)

		# 그다음에 입고한다
		if store_day == current_day :
			day, quantity= stores.pop(0)
			stock.store(quantity, current_day, 3)

		# 그다음에 판매를 진해한다 
		if sell_day == current_day : 
			day, quantity, customer_type = sells.pop(0)
			stock.sell(quantity, customer_type)

	return ret

if __name__ == "__main__" :	
	
	random.seed(43)
	
	with open("data/폐기제품_집계.txt") as fd :
		test_cases = int(fd.readline().strip())

		for _ in range(test_cases) : 
			tokens = list(map(int, fd.readline().strip().split(" ")))
			stores = [ [ tokens[2*i], tokens[2*i+1]] for i in range(len(tokens)//2)] 
			tokens = list(map(int, fd.readline().strip().split(" ")))
			sells = [ [ tokens[3*i], tokens[3*i+1], tokens[3*i+2]] for i in range(len(tokens)//3)] 
			print(solve(stores,sells))

	for _ in range(TEST_CASES) :
		n = random.randint(1, MAX_STORES)
		stores  = [ make_store(day) for day in sampled_days(n)]

		m = random.randint(1,MAX_SELLS)
		sells = [make_sell(day) for day in sampled_days(n)]

		print(solve(stores, sells))
