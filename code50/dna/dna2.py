import csv
import sys


def main():

    # TODO: Check for command-line usage
    #print(len(sys.argv))
    if len(sys.argv) != 3:
        print("python dna.py databases/large.csv sequences/5.txt")
        return False

    # TODO: Read database file into a variable
    people = []
    databasefile = sys.argv[1]
    #print(databasefile)
    with open(databasefile) as f:
        reader = csv.DictReader(f)
        for name in reader:
            people.append(name)

    #print("People are ")
    #for i in range(len(people)):
        #print(people[i]['name'])


    # TODO: Read DNA sequence file into a variable
    file = open(sys.argv[2])
    t = file.read()
    #print("t = ")
    #print(t)
    file.close()


    # TODO: Find longest match of each STR in DNA sequence
    subs = []
    with open(databasefile) as f:
        reader = csv.reader(f, delimiter = ',')
        for row in reader:
            subs.append(row)
    #print("Subsequences are ")
    x = len(subs[0])
    #print(x)
    #for i in range(1,x):
        #print(subs[0][i])
    #print("Longest Matches are")
    matches = []
    for i in range(1,x):
        y = longest_match(t,subs[0][i])
        matches.append(y)
        #print(y)
    #longest_match(t, get subsequence somehow)
    #print(matches)

    # TODO: Check database for matching profiles
    no_match = 0
    for i in range(0,len(people)):
        total_sum = 0
        for j in range(1,x):
            code = subs[0][j]
            #print(code)
            if int(matches[j-1]) == int(people[i][code]):
                total_sum = total_sum + 1
                #print("Success")
                #print(people[i]['name'])
            # else:
            #      print("Failed")
            #      print(people[i]['name'])
        #print(total_sum)
        if total_sum == len(matches):
            print(people[i]['name'])
            break
        else:
            no_match = no_match + 1

    #print(no_match)
    if no_match == len(people):
        print("No match")
            # if total_sum == len(people):
            #     res = people[i]['name']
            #     print(res)




    #if int(matches[0]) == int(people[1][1]):
        #print("Success")
    #code = subs[0][1]
    # print("Code is ")
    # print(code)
    # print(int(matches[0]))
    # print(people[1]['name'])
    # print(people[1][code])

    #print(len(people))
    #print(x)






    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
