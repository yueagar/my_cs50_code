import csv

with open("favorites.csv", "r") as file:
    #reader = csv.reader(file)
    reader = csv.DictReader(file)
    #scratch, c, python = 0, 0, 0
    counts = {}
    for row in reader:
        #favorite = row[1]
        favorite = row["language"]
        #print(favorite)
        """if favorite == "Scratch":
            scratch += 1
        elif favorite == "C":
            c += 1
        elif favorite == "Python":
            python += 1"""
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

"""def get_value(favorite):
    return counts[favorite]"""

"""print(f"Scratch: {scratch}")
print(f"C: {c}")
print(f"Python: {python}")"""
for favorite in sorted(counts, key=lambda favorite: counts[favorite], reverse=True):
    print(f"{favorite}: {counts[favorite]}")