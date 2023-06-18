def main():
    str = input("Text: ")
    str = str.lower()

    W = countWords(str)
    L = countLetters(str) / W * 100
    S = countSentences(str) / W * 100

    Grade = int(0.0588 * L - 0.296 * S - 15.8 + 0.5)
    if Grade > 16:
        print("Grade 16+")
    elif Grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {Grade}")


def countWords(text):
    return len(text.split(" "))


def countLetters(text):
    L = 0
    for i in range(len(text)):
        charCode = ord(text[i])
        if (charCode > 96 and charCode < 123):
            L += 1
    return L


def countSentences(text):
    S = 0
    for i in range(len(text)):
        charCode = ord(text[i])
        if ((charCode == 33 or charCode == 46 or charCode == 63) and (ord(text[i - 1]) != 46 or ord(text[i + 1] != 46))):
            S += 1
    return S


main()