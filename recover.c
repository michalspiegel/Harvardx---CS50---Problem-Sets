//An algorithm that takes as an input 'memory data' - seemingly lost (accidently deleted) data from a camera memory card
//Searches for JPEG files in the data input - and them outputs these JPEGs

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
bool file_opened = false;
int outfile_count;

int main(int argc, char *argv[])
{
    //Make sure there is the right amount of arguments
    if (argc != 2)
    {
        printf("Usage:  ./recover *image*");
        return 1;
    }

    // Open the file
    FILE *infile = fopen(argv[1], "r");

    //If file null cannot be opened display error
    if (infile == NULL)
    {
        printf("Could not open file");
        return 1;
    }



    //Open the output file (all the opening of other files is going to be)
    FILE *outfile = NULL;
    //Allocate memory for the 'name formatting' in the heap
    char *outfilename = malloc(8);
    size_t bytesRead = 0;
    //Allocate memory(buffer) of 512 Bytes in the heap
    BYTE *buffer = malloc(512);
    //if error
    if (buffer == NULL)
    {
        printf("Not enought memory");
        return 1;
    }



    //Repeat until the end of the file - fread() returns the number of elements of the given size that were succesfuly read - if fread() == 0 -> end of file
    while ((bytesRead = fread(buffer, sizeof(BYTE), 512, infile)) > 0)
    {
        
        //Find out if the first 4 bytes of the 512 B block  match with so-called JPEG 'initials'
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If an outfile is currently open -> close him, open another one, format the outfilename string to the name of the file, write the buffer into the file
            if (file_opened)
            {
                fclose(outfile);
                sprintf(outfilename, "%03i.jpg", outfile_count);
                outfile = fopen(outfilename, "w");
                outfile_count++;
                fwrite(buffer, sizeof(BYTE), 512, outfile);

            }

            //If there is no outfile opened -> open a file, format the outfilename, write the buffer into the fie
            else
            {
                file_opened = true;
                sprintf(outfilename, "%03i.jpg", outfile_count);
                outfile = fopen(outfilename, "w");
                outfile_count++;
                fwrite(buffer, sizeof(BYTE), 512, outfile);

            }
        }
        
        
        // The first four bytes don't match
        else
        {
            //If an outfile is currently open -> write the buffer into that file
            if (file_opened)
            {
                fwrite(buffer, sizeof(BYTE), 512, outfile);
            }

            //If there is no outfile opened - just skip to next the 512 bytes of the file
            else
            {
                continue;
            }
        }

    }


    //Free all the allocated memory in the heap
    free(buffer);
    free(outfilename);
    //Close any remaining files
    fclose(outfile);

    return 0;
}
