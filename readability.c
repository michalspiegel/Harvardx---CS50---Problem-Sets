// A program that expects a piece of text as an input and outputs a grade of readability 

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int letters = 0;
    int words = 0;
    int sentences = 0;
    
    //GETS THE TEXT AS AN INPUT
    string text_input = get_string("Text:");
   
    //CODE THAT COUNTS THE NUMBER OF LETTERS, WORDS AND SENTENCES
    for (int i = 0, n = strlen(text_input); i < n; i++ )
    {
        if (text_input[i] >= 'A' && text_input[i] <= 'z')
        {
            letters += 1;
        }
        
        else if (text_input[i] == ' ')
        {
            words += 1;
        }
        
        else if (text_input[i] == '.' || text_input[i] == '?' || text_input[i] == '!')
        {
            sentences += 1;
        }
    }
    words += 1;
    
    
    //ALGORITHM THAT CALCULATES THE GRADE PRECISELY AS A FLOAT
    float avrg_letters = ((float) letters / (float) words) * 100;
    float avrg_sentences = ((float) sentences / (float) words) * 100;
    float grade = (0.0588 * avrg_letters) - (0.296 * avrg_sentences) - 15.8;
    
    
    
    // FINAL GRADING AND ROUNDING
    if (grade >= 15.5)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    
    else
    {
        if (grade >= (int)grade + 0.5)
        {
            printf("Grade %d\n", (int)grade + 1);
        }
        else
        {
            printf("Grade %d\n", (int)grade);
        }
    }
  
    
    return 0;
}

