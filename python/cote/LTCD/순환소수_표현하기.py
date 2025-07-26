def fractional_part(remainder: int, dominator: int) -> str:
    assert remainder < dominator

    result = ["0", "."]

    seen = {}

    while remainder:
        if remainder in seen:
            idx = seen[remainder]
            result.insert(idx, '(')
            result.append(')')
            break

        seen[remainder] = len(result)
        remainder *= 10
        digit = remainder // dominator
        result.append(str(digit))
        remainder %= dominator

    return "".join(result)


def solve(numerator: int, dominator: int) -> str:
    if numerator == 0:
        return "0"

    negative = (numerator < 0) ^ (dominator < 0)

    numerator, dominator = abs(numerator), abs(dominator)
    integer_part = numerator // dominator
    remainder = numerator % dominator

    result = []

    if negative:
        result.append("-")

    result.append(str(integer_part))

    if remainder == 0:
        return ''.join(result)

    t = fractional_part(remainder, dominator)

    result.extend(t[1:])

    return "".join(result)
