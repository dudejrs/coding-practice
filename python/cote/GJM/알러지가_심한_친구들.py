N = 20
M = 20

INF = 987_654_321
best = INF

def get_edibility(fd, n, m) :

	persons = fd.readline().strip().split(" ")

	person_to_int = { persons[i] : i for i in range(n)} 

	can_eat = [ [] for _ in range(n)]
	eater = [[] for _ in range(m)]

	for i in range(m) :
		eater_per_food =  fd.readline().strip().split(" ")
		for person in eater_per_food[1: ] :
			j = person_to_int[person]
			can_eat[j].append(i)
			eater[i].append(j)

	return can_eat, eater

def search(eater, can_eat, edible, n, m, chosen) :
	global best

	if len(chosen) >= best  : return 
	
	target = -1

	for i in range(len(edible)) :
		if edible[i] == 0 :
			target = i 

	if target == -1 :
		best = min(len(chosen), best)
		return

	for food in can_eat[target] :
		for person in eater[food] :
			edible[person] += 1

		newChosen = list(chosen)
		newChosen.append(food)
		search(eater, can_eat, edible, n, m, newChosen)

		for person in eater[food] :
			edible[person] -= 1

	return


def solve(eater, can_eat, n, m) :
	global best
	best = INF
	edible = [0 for i in range(n)]

	search(eater, can_eat, edible, n, m, [] )

	return best

if __name__ == "__main__" :
	
	with open("data/알러지가_심한_친구들.txt") as fd :
		TEST_CASES = int(fd.readline())

		while TEST_CASES > 0 :

			n, m = map(int, fd.readline().split(" "))
			can_eat, eater = get_edibility(fd, n, m)
			print(solve(eater,can_eat,n,m))

			TEST_CASES-=1
