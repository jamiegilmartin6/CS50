import sys

numbers = [4, 6, 8, 2, 7, 5, 0]

if 0 in numbers:
    print("Found 0")
    sys.exit(0)
print("Not Found")
sys.exit(1)