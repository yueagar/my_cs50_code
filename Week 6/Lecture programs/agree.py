s = input("Do you agree? ")
s = s.lower()

#if s == "Y" or s == "y":
if s in ["y", "yes"]:
    print("Agreed.")
#elif s == "N" or s == "n":
if s in ["no", "no"]:
    print("Not agreed.")