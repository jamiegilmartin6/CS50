scores = []

for i in range(3):
    score = int(input("Score? "))
    scores.append(score) # Could also use, scores += [score] or scores = scores + [score]

average = sum(scores)/len(scores)
print("Average " + str(average))