def solve(a: str, b: str) -> str:
    max_len = max(len(a), len(b))
    carry = 0
    result = []

    for i in range(-1, -max_len - 1, -1):
        element_a = a[i] if abs(i) <= len(a) else 0
        element_b = b[i] if abs(i) <= len(b) else 0

        add = int(element_a) + int(element_b) + int(carry)
        value = add % 2
        carry = add // 2
        result.insert(0, str(value))

    if carry != 0:
        result.insert(0, str(carry))

    return "".join(result)
