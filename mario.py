# Takes as an input a number (a height) between 1 and 8
# Prints a pyramid made out of hash characters of the specified height
from cs50 import get_int


height = 0

# Get a suitable number as an input
while height < 1 or height > 8: :
    height = get_int("Height:")
    
    
# Iterate
for i in range(1, height + 1):

    # Hashes of the left-side pyramid
    print(" " * (height - i), end="")
    print("#" * i, end="")
    
    # Space between both pyramids
    print("  ",end="")
    
    # Hashes of the right-side pyramid
    print("#" * i, end="")
    
    # New line
    print()
