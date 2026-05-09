
def yj(i: int):
    if i == 0 or i == 1:
        return i
    else:
        return yj(i - 1) + 2 * yj(i - 2)

print([yj(i) for i in range(10)])

print("0: yj(0) = 0")
print("1: yj(1) = 1")
for i in range(2, 10):
    print(f"{i}: yj({i - 1}) + 2 * yj({i - 2}) = ", yj(i))
