dollars = -1
while (dollars < 0):
    dollars = float(input("Change owed: "))

cents = 100 * dollars

quarters = int(cents / 25)
cents -= quarters * 25

dimes = int(cents / 10)
cents -= dimes * 10

nickels = int(cents / 5)
cents -= nickels * 5

pennies = int(cents / 1)
cents -= cents * 1

coins = quarters + dimes + nickels + pennies
print(coins)