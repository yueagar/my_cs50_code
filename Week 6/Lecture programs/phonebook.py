import csv

#people = dict()
"""people = {
    "Carter": "+1-617-495-1000",
    "David": "+1-949-468-2750"
}

name = input("Name: ")
if name in people:
    number = people[name]
    print(f"Number: {number}")"""

with open("phonebook.csv", "a") as file:

    name = input("Name: ")
    number = input("Number: ")

    #writer = csv.writer(file)
    writer = csv.DictWriter(file, fieldnames=["name", "number"])
    #writer.writerow([name, number])
    writer.writerow({"name": name, "number": number})

    #file.close()