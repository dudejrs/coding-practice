def refinedata(data):
    ret = []
    time = list(map(int, data[0].split(":")))
    ret.append(time[0] * 60 + time[1])
    ret.append(data[1])
    return ret


def solve(booked, unbooked):

    refined_booked = list(map(refinedata, booked))
    refined_unbooked = list(map(refinedata, unbooked))

    ret = []

    currenttime = 0

    while (len(refined_booked) != 0) or (len(refined_unbooked) != 0):

        if len(refined_booked) == 0:
            for customer in refined_unbooked:
                ret.append(customer[1])
            break
        if len(refined_unbooked) == 0:
            for customer in refined_booked:
                ret.append(customer[1])
            break

        booked_arrived = refined_booked[0][0]
        unbooked_arrived = refined_unbooked[0][0]

        if currenttime >= booked_arrived:
            customer = refined_booked.pop(0)
            ret.append(customer[1])
            currenttime += 10
        elif currenttime >= unbooked_arrived:
            customer = refined_unbooked.pop(0)
            ret.append(customer[1])
            currenttime += 10
        else:
            if booked_arrived <= unbooked_arrived:
                customer = refined_booked.pop(0)
            else:
                customer = refined_unbooked.pop(0)
            ret.append(customer[1])
            currenttime = customer[0] + 10

    return ret


if __name__ == "__main__":

    with open("data/상담예약제.txt") as fd:

        test_cases = int(fd.readline().strip())

        for _ in range(test_cases):

            token = fd.readline().strip().split(' ')
            booked = [[token[2 * i], token[2 * i + 1]] for i in range(len(token) // 2)]

            token = fd.readline().strip().split(' ')
            unbooked = [[token[2 * i], token[2 * i + 1]] for i in range(len(token) // 2)]

            answer = fd.readline().strip().split(' ')

            print(solve(booked, unbooked))
            print(answer)
