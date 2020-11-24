# A program that expects a piece of text as an input and outputs a grade of difficulty (readability)

letters = 0
words = 0
sentences = 0

text_input = input("Text:")



# Determine the number of letter, words and sentences in the text - iterate over the individual characters in the text
for char in text_input:
    
    if char.isalpha():
        letters += 1
    
    elif char == " ":
        words += 1
        
    elif char in [".", "?", "!"]:
        sentences += 1
        
# Add the last word (because it as the only word in a sentece doesn't end with whitespace)       
words += 1        



# Determine averages
avrg_letters = (letters / words) * 100
avrg_sentences = (sentences / words) * 100
# Calculate the grade of readability
grade = (0.0588 * avrg_letters) - (0.296 * avrg_sentences) - 15.8



# FINAL GRADING AND ROUNDING
if grade >= 15.5:
    print("Grade 16+");
    
elif grade < 1:
    print("Before Grade 1");
    
else:
    
    if grade >= round(grade) + 0.5:
        print(f"Grade {round(grade) + 1}")
        
    else:
        print(f"Grade {round(grade)}")
   
