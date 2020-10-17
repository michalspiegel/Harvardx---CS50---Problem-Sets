// Converts plain text into a cipher using 26-character-long key, that specifies what character should be substituted with which character

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int get_alphabet_position(char chr);

int main(int argc, string argv[])
{
    //Check if there is precisely one command_line argument
    if (argc != 2)
    {
        printf("Wrong number of arguments given");
        return 1;
    }

    //Check the length of the command-line argument
    if (strlen(argv[1]) != 26)
    {
        printf("Command-line argument must contain precisely 26 alphabetical characters!");
        return 1;
    }
    //Check every character of the input
    for (int i = 0; i < 26; i++)
    {
        //Check that every character is an alphabetical one
        if ((argv[1][i] < 'A' || argv[1][i] > 'Z') && (argv[1][i] < 'a' || argv[1][i] > 'z'))
        {
            printf("All characters must be alphabetic\n");
            return 1;
        }

        //Check that there is no character reoccuring more than once
        for (int k = 0, n = 26 - i - 1; k < n; k++)
        {
            if (argv[1][k] == toupper(argv[1][k + i + 1]) || argv[1][k] == tolower(argv[1][k + i + 1]))
            {
                printf("Characters cannot repeat!!");
                return 1;
            }
        }
    }

    //Get a piece of text, which you want to be enciphered, as an input
    string plain_text = get_string("plain_text:  ");
    printf("ciphertext: ");

    //Go through every character in the plain_text
    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        //In case any of the chars are not alphabetic, output the char without enciphering it
        if ((plain_text[i] < 'A' || plain_text[i] > 'Z') && (plain_text[i] < 'a' || plain_text[i] > 'z'))
        {
            printf("%c", plain_text[i]);
        }

        else
        {
            //Find out if the char is lowercase or uppercase
            if (islower(plain_text[i]) > 0)
            {
                //Get the position of the plain_text char in the alphabet itself
                //And output a character from the key (argv) that has the same position
                char cipher_char = (char) argv[1][get_alphabet_position(plain_text[i])];
                printf("%c", tolower(cipher_char));
            }

            else
            {
                char cipher_char = (char) argv[1][get_alphabet_position(plain_text[i])];
                printf("%c", toupper(cipher_char));
            }

        }

    }
    //End with a newline
    printf("\n");

}

//Takes a char from the plain_text as an input and returns it's position in the alphabet
int get_alphabet_position(char chr)
{
    chr = toupper(chr);
    for (int i = 0; i < 26; i++)
    {
        if (chr == alphabet[i])
        {
            return i;
        }
    }
    return 1;
}
