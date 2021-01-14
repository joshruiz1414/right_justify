#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_word_character(char c)
{
    if (isalpha(c) || c == '-' || c == '\'')
        return 1;
    else
        return 0;
}

int read_word(FILE *input_file, char word[])
{
    int ch = fgetc(input_file);
    int i = 0;
    while (is_word_character(ch) == 0 && ch != EOF)
    {
        ch = fgetc(input_file);
    }
    if (ch == EOF)
    {
        word[i] = '\0';
        return 0;
    }
    while (is_word_character(ch) == 1 && ch != EOF)
    {
        word[i++] = ch;
        ch = fgetc(input_file);
    }
    word[i] = '\0';
    return 1;
}

void write_line(FILE *output_file, char line[])
{
    int lineLength = strlen(line);
    int spaces = 30 - lineLength;
    int i = 0;

    while (i < spaces)
    {
        fprintf(output_file, " ");
        i += 1;
    }

    fprintf(output_file, "%s", line);
}

void read_line(FILE *output_file, FILE *input_file, char word[], char line[])
{

    int line_number = 0;
    int limit = 0;

    while (read_word(input_file, word) != 0)
    {

        if (limit + 1 + strlen(word) > 30 && limit != 0)
        {
            if (line_number != 0)
            {
                fprintf(output_file, "\n");
            }
            line_number += 1;
            line[limit] = '\0';
            write_line(output_file, line);
            limit = 0;
        }

        if (limit != 0)
        {
            line[limit] = ' ';
            limit += 1;
        }

        int index = 0;
        while (word[index] != '\0')
        {
            line[limit] = word[index];
            index += 1;
            limit += 1;
        }
    }

    if (limit != 0)
    {
        if (line_number != 0)
        {
            fprintf(output_file, "\n");
        }
        line[limit] = '\0';
        write_line(output_file, line);
    }
}

int main()
{
    FILE *input_file = fopen("input_text.txt", "r");

    if (input_file == NULL)
    {
        printf("Unable to open input file\n");
        return 1;
    }

    FILE *output_file = fopen("output_text.txt", "w");


    if (output_file == NULL)
    {
        printf("Unable to open output file\n");
        fclose(input_file);
        return 1;
    }
    char line[101];

    char word[101];

    read_line(output_file, input_file, word, line);

    fclose(input_file);
    fclose(output_file);

    return 0;
}