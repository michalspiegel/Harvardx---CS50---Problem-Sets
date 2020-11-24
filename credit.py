# Takes as an input a card number
# And determines whether the number is valid and if, what kind of card it is

import sys


def main():
    card_number = input("Your card number:")
    lenght = len(card_number)

    if (card_number.isdigit()) == False:
        print("INVALID")
        sys.exit(1)
        
    if (12 < int(card_number) > 17) == False:
        print("INVALID")
        sys.exit(1)
        
    if luhn(card_number) == False:
        print("INVALID")
        sys.exit(1)

    
    first_digits = card_number[0] + card_number[1]
    if lenght == 15 and first_digits in ["34", "37"]:
        print("AMEX")
    elif lenght == 16 and first_digits in ["51","52","53","54","55"]:
        print("MASTERCARD")
    elif (lenght == 13 or lenght == 16) and card_number[0] == "4":
        print("VISA")
    else:
        print("INVALID")


def luhn(card_number):
    card_number = list(map(int, card_number))
    sum1 = 0
    sum2 = 0
    
    # Calculate sum2 - every other digit - starting from the second-to-last digit 
    for i in range(len(card_number) - 2, -1, -2):
        # Add only to the sum only the product's digits (so if the product is a number 16 - add 1 and 6)
        if card_number[i] * 2 >= 10:
            sum1 += 1
            sum1 += card_number[i] * 2 % 10
        else:
            sum1 += card_number[i] * 2
            
    # Calculate sum2 - every other digit - starting from the last digit
    for i in range(len(card_number) - 1, -1, -2):
        sum2 += card_number[i]

    # Calculate final outcome
    if (sum1 + sum2) % 10 == 0:
        return True
    else:
        return False

main()
