def is_valid_e_notation(significand: str, exponent: str) -> bool:
    if not exponent:
        return False

    if exponent[0] in ["+", "-"]:
        exponent = exponent

    return exponent.isnumeric() and is_valid_number(significand)


def is_valid_number(number: str) -> bool:
    if not number:
        return False

    if number[0] in ["+", "-"]:
        number = number[1:]

    tokens = number.split(".")

    match tokens:
        case [integer] if len(tokens) == 1:
            return integer.isnumeric()
        case [integer, decimal] if len(tokens) == 2:
            return integer.isnumeric() and decimal.isnumeric()
        case _:
            return False


def solve(s: str) -> bool:
    s = s.strip()

    tokens = s.split("e")

    match tokens:
        case [significand, exponent] if len(tokens) == 2:
            return is_valid_e_notation(significand, exponent)
        case [number] if len(tokens) == 1:
            return is_valid_number(number)
        case _:
            return False
