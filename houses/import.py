# Takes as an input a .csv file, containing not specified number of people - and columns with their names, school houses they're in and birth year

from csv import DictReader
from cs50 import SQL
from sys import exit, argv

if len(argv) != 2:
    print("Wrong number of command-line arguments")
    exit(1)

with open(argv[1], "r") as csv_file:

    db = SQL("sqlite:///students.db")
    reader = DictReader(csv_file)


    for row in reader:

        first_v = row["name"].split()[0]

        if len(row["name"].split()) > 2:
            middle_v = row["name"].split()[1]
            last_v = row["name"].split()[2]
        else:
            middle_v = None
            last_v = row["name"].split()[1]

        house_v = row["house"]

        birth_v = int(row["birth"])

        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first_v, middle_v, last_v, house_v, birth_v )



