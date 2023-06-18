import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        return print("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    data = []
    with open(sys.argv[1], "r") as dataFile:
        reader = csv.DictReader(dataFile)
        for row in reader:
            element = {}
            for key in row:
                element[key] = row[key]
            data.append(element)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as sequenceFile:
        sequence = sequenceFile.read()

    # Find longest match of each STR in DNA sequence
    sequenceData = {}
    for key in data[0]:
        if (key != "name"):
            sequenceData[key] = longest_match(sequence, key)

    # Check database for matching profiles
    for i in range(len(data)):
        matched = True
        for STR in sequenceData:
            data[i][STR] = int(data[i][STR])
            if (data[i][STR] != 0 and data[i][STR] != sequenceData[STR]):
                matched = False
        if (matched):
            return print(data[i]["name"])
    return print("No match")


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
