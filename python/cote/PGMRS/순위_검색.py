import random
import re
from collections import OrderedDict
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

	# query.append(str(random.randrange(MAX_SOCRE)))

	return " and ".join(query) +" "+ str(random.randrange(MAX_SOCRE))
	# return " and ".join(query) 

def initializeQuery() :
	query_size = random.randrange(QUERY_SIZE)

	return [makeQuery() for _ in range(query_size) ]


def forEachKey(index, prefix, tokens, action) :
	if index == len(tokens)-1 :
		action(prefix) 
		return
		
	forEachKey(index+1, prefix+tokens[index], tokens, action)
	forEachKey(index+1, prefix+"-", tokens, action)


def addScoresMap(scoresMap, prefix, score) :
	
	if scoresMap.get(prefix) is None :
		scoresMap[prefix] = []
	scoresMap.get(prefix).append(score) 

	return

def makeScoresMap(info) :
	scoresMap = OrderedDict()

	for tmp in info :
		tokens = tmp.split(" ")
		forEachKey(0, "", tokens, lambda p : addScoresMap(scoresMap, p, tokens[-1]) )

	for key in scoresMap.keys() :
		scoresMap.get(key).sort()

	return scoresMap


def binarySearch(score, scores) :
	start = 0
	end = len(scores)-1

	while start < end : 
		mid = (end+start)//2

		if scores[mid] >=  score : 
			end = mid
		else :
			start = mid+1

	if (scores[start] < score) : 
		return len(score)

	return start;

def count(query, scoresMap) :
	
	tokens = list(filter(lambda x : x != 'and', re.split(r' ', query)))
	key = "".join(tokens[:-1])
	score = tokens[-1]
	scores = scoresMap.get(key)
	
	if scores :
		return binarySearch(score, scores)

	return 0;

def solve(info, query) :

	scoresMap = makeScoresMap(info) 

	ret = []

	for q in query : 
		ret.append(count(q, scoresMap))

	return ret;


if __name__ == "__main__" :
	random.seed(43)

	for _ in range(1) :
		info = initializeInfo()
		query = initializeQuery()
		# solve(info, query)
		pprint(solve(info, query), compact=True)

