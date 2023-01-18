people = {
    "Carter": "4",
    "David": "3",
    "Jamie": "7"
}

name = input("Name ")
if name in people:
    number = people[name]
    print(f"Number: {number}")