# Takes as an input a string - a DNA sequence
# Outputs whether someone in the dictionary matches this DNA sequence in STRs

from sys import argv, exit
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
    consecutive_repeats = []

    # For every char in dna_sequence
    for i in range(len(dna_sequence)):

        tempMax = 0
        l = len(STR)

        # Slice array into subarrays with length l and see if it equals to STR
        if dna_sequence[i: i + l] == STR:
            tempMax = 1

            #If yes, see, if it repeats
            while dna_sequence[i + l: i + 2*l] == dna_sequence[i: i+ l]:

                #If yes add "one repeat" to tempMax and advance in list
                tempMax += 1
                i += l

            consecutive_repeats.append(tempMax)


    # If the list is not empty
    if consecutive_repeats:
        # Creating a special dna ID
        dna_id = dna_id + str(max(consecutive_repeats))




# Final searching for identical dna_id
for person in id_database.keys():

    if id_database[person] == dna_id:
        print(person)
        exit(0)

print("No match")












