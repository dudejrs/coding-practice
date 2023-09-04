import random
from pprint import pprint 

TEST_CASES = 10
INFO_SIZE = 50000
QUERY_SIZE = 100000;
MAX_SOCRE = 100000

LANGAUAGES = ["cpp", "java", "python"]
POSITIONS = ["backend", "frontend"]
CARRIERS = ["junior", "sinior"]
SOUL_FOODS = ["chicken", "pizza"]
CATEGORIES = [LANGAUAGES, POSITIONS, CARRIERS, SOUL_FOODS]



def makeInfo() :
	info = []
	for category in CATEGORIES : 
		info.append(random.choice(category))

	info.append(str(random.randrange(0,MAX_SOCRE)))

	return " ".join(info)

def initializeInfo() :
	info_size = random.randint(0,INFO_SIZE)	
	return [ makeInfo() for _ in range(info_size) ]

def makeQuery() :
	query = []

	for category in CATEGORIES : 
		if(random.random() < 0.2 ):
			query.append("-")
		else : 
			query.append(random.choice(category))

	query.append(str(random.randrange(MAX_SOCRE)))

	return " and ".join(query)

def initializeQuery() :
	query_size = random.randrange(QUERY_SIZE)

	return [makeQuery() for _ in range(query_size) ]

def solve(info, query) :
	return []

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		info = initializeInfo()
		query = initializeQuery()
		# pprint (info, compact=True)
		pprint (query, compact=True)
		pprint(solve(info, query))
