import re


def main():
    cardNo = input("Number: ")
    if (re.match(r"3[47]\d{13}", cardNo) and isValidCheckSum(cardNo)):
        print("AMEX")
    elif (re.match(r"5[1-5]\d{14}", cardNo) and isValidCheckSum(cardNo)):
        print("MASTERCARD")
    elif ((re.match(r"4\d{12}", cardNo) or re.match(r"4\d{15}", cardNo)) and isValidCheckSum(cardNo)):
        print("VISA")
    else:
        print("INVALID")


def isValidCheckSum(noStr):
    checksum = 0
    length = len(noStr)
    for i in range(int(length / 2)):
        doubleDigit = int(noStr[length - 2 * (1 + i)]) * 2
        if doubleDigit < 10:
            checksum += doubleDigit
        else:
            checksum += 1 + doubleDigit % 10
        singleDigit = int(noStr[length - 1 - 2 * i])
        checksum += singleDigit
    if (length % 2 == 1):
        checksum += int(noStr[0])
    if (checksum % 10 == 0):
        return True
    else:
        return False


main()