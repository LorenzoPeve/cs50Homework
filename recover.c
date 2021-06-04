

    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    
    int main(int argc, char *argv[])
    {
        //Check Command-line Arguments
        if (argc != 2)
        {
            printf("Usage: ./recover image\n");
            return 1;
        }
    
        //Pointer
        FILE *input = fopen(argv[1], "r");
        if (input == NULL)
        {
            printf("ERROR: File cannot be opened.\n");
            return 2;
        }
    
        uint8_t buffer[512];    // Declare buffer of 512 bytes for TEMPORARY storage
        int count = -1;          // Initialize counting variable for file naming
        char filename[8];       // Declare char array for Filename
        FILE *output = NULL;    // Initialize File Pointer
    
        while (fread(buffer, 512, 1, input))
        {
            // Check First 4 bytes and open a new file
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0))
            {
                if (count >= 0)
                {
                    fclose(output);
                }
                count ++;
                sprintf(filename, "%03i.jpg", count);   //String stored into filename
                output = fopen(filename, "w");
            }
    
            if (count >= 0)
            {
                fwrite(buffer, 512, 1, output);
            }
    
        }
        fclose(input);
    }


