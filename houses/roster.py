# Program takes as an input a name of a school house - and prints a summary of all students that belong to that particular house

from cs50 import SQL
from sys import argv, exit

# Check command-line arguments
if len(argv) != 2 or argv[1] not in ["Slytherin", "Hufflepuff", "Gryffindor", "Ravenclaw"]:
    print("Error - in -  command-line arguments")
    exit(1)

# Open students.db through SQL library
db = SQL("sqlite:///students.db")
# Returns a list of the selected columns WHERE house is equal to Slytherin or Hufflepuff, etc.
student_info = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

# Print out the elements of the list
for row in student_info:
    # Checking for NULL values
    if row["middle"] == None:
        print(row["first"], row["last"] + ", born", str(row["birth"]))
    else:
        print(row["first"],row["middle"], row["last"] + ", born", str(row["birth"]))
