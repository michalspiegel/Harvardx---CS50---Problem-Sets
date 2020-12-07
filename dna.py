# Takes as an input a string - a DNA sequence
# Outputs whether someone in the dictionary matches this DNA sequence in STRs
from sys import argv
from sys import exit
import csv


# Global variables
id_database = {}
dna_id = ""


# Checking commnad-line arguments
if len(argv) != 3:
    print("Wrong number of command-line arguments")
    exit(1)


# Opening and reading .cvs file
with open(argv[1], "r") as file:

    reader = csv.reader(file)
    for row in reader:
        STRs = row
        break
    del STRs[0]

    for row in reader:
        dna_id_number = ""
        name = row[0]
        for i in range(1, len(STRs) + 1):
            dna_id_number += row[i]
        id_database.update({name : dna_id_number})

# Opening and reading .txt file with dna sequence
with open(argv[2], "r") as file:
    dna_sequence = file.read()


# Checking for max consecutive repeats of an STR in a dna sequence
for STR in STRs:
    # Maximum of consecutive repeats of the given STR in the given dna sequence
    max_repeats = 1
    
    while True:

        if STR*max_repeats in dna_sequence:
            counter += 1
            continue

        # Creating a special dna ID
        dna_id = dna_id + str(counter - 1)
        break


# Final searching of identical dna_id
match = False

for person in id_database.keys():
    if id_database[person] == dna_id:
        print(person)
        match = True

if match == False:
    print("No match")







