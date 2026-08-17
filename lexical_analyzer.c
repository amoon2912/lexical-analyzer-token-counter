#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN 100

/* C keywords */
const char *keywords[] = {
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for",
    "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile",
    "while"
};

int keywordCount = 32;

/* Token counters */
int keywords_count = 0;
int identifiers_count = 0;
int operators_count = 0;
int constants_count = 0;
int string_literals_count = 0;
int separators_count = 0;
int comments_count = 0;
int special_symbols_count = 0;

/* Check whether a word is a keyword */
int isKeyword(char *word)
{
    int i;

    for (i = 0; i < keywordCount; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

/* Check whether a character is a separator */
int isSeparator(char ch)
{
    return ch == '(' || ch == ')' ||
           ch == '{' || ch == '}' ||
           ch == '[' || ch == ']' ||
           ch == ';' || ch == ',' ||
           ch == ':';
}

/* Check whether a character is an operator */
int isOperator(char ch)
{
    return ch == '+' || ch == '-' ||
           ch == '*' || ch == '/' ||
           ch == '%' || ch == '=' ||
           ch == '<' || ch == '>' ||
           ch == '!' || ch == '&' ||
           ch == '|';
}

/* Print token */
void printToken(char *token, char *type)
{
    printf("%-20s %s\n", token, type);
}

int main()
{
    FILE *fp;
    char filename[100];
    char ch;
    char token[MAX_TOKEN];
    int i;

    printf("Enter source file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    printf("\nTOKEN                TYPE\n");
    printf("------------------------------------------\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        /* Ignore white spaces */
        if (isspace(ch))
            continue;

        /* Identifier or Keyword */
        if (isalpha(ch) || ch == '_')
        {
            i = 0;
            token[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_'))
            {
                token[i++] = ch;
            }

            token[i] = '\0';

            if (isKeyword(token))
            {
                printToken(token, "Keyword");
                keywords_count++;
            }
            else
            {
                printToken(token, "Identifier");
                identifiers_count++;
            }

            if (ch != EOF)
                ungetc(ch, fp);
        }

        /* Numeric Constant */
        else if (isdigit(ch))
        {
            i = 0;
            token[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.'))
            {
                token[i++] = ch;
            }

            token[i] = '\0';

            printToken(token, "Constant");
            constants_count++;

            if (ch != EOF)
                ungetc(ch, fp);
        }

        /* String Literal */
        else if (ch == '"')
        {
            i = 0;
            token[i++] = ch;

            while ((ch = fgetc(fp)) != EOF)
            {
                token[i++] = ch;

                if (ch == '"')
                    break;
            }

            token[i] = '\0';

            printToken(token, "String Literal");
            string_literals_count++;
        }

        /* Character Constant */
        else if (ch == '\'')
        {
            i = 0;
            token[i++] = ch;

            while ((ch = fgetc(fp)) != EOF)
            {
                token[i++] = ch;

                if (ch == '\'')
                    break;
            }

            token[i] = '\0';

            printToken(token, "Constant");
            constants_count++;
        }

        /* Comment or Division Operator */
        else if (ch == '/')
        {
            char next = fgetc(fp);

            /* Single-line comment */
            if (next == '/')
            {
                i = 0;
                token[i++] = '/';
                token[i++] = '/';

                while ((ch = fgetc(fp)) != EOF && ch != '\n')
                {
                    if (i < MAX_TOKEN - 1)
                        token[i++] = ch;
                }

                token[i] = '\0';

                printToken(token, "Comment");
                comments_count++;
            }

            /* Multi-line comment */
            else if (next == '*')
            {
                i = 0;
                token[i++] = '/';
                token[i++] = '*';

                while ((ch = fgetc(fp)) != EOF)
                {
                    if (i < MAX_TOKEN - 1)
                        token[i++] = ch;

                    if (ch == '*')
                    {
                        ch = fgetc(fp);

                        if (ch == '/')
                        {
                            if (i < MAX_TOKEN - 1)
                                token[i++] = ch;
                            break;
                        }

                        if (ch != EOF)
                            ungetc(ch, fp);
                    }
                }

                token[i] = '\0';

                printToken(token, "Comment");
                comments_count++;
            }

            /* Division operator */
            else
            {
                printToken("/", "Operator");
                operators_count++;

                if (next != EOF)
                    ungetc(next, fp);
            }
        }

        /* Operators */
        else if (isOperator(ch))
        {
            char next = fgetc(fp);

            token[0] = ch;
            token[1] = '\0';

            /* Two-character operators */
            if ((ch == '+' && next == '+') ||
                (ch == '-' && next == '-') ||
                (ch == '=' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|'))
            {
                token[1] = next;
                token[2] = '\0';
            }
            else
            {
                if (next != EOF)
                    ungetc(next, fp);
            }

            printToken(token, "Operator");
            operators_count++;
        }

        /* Separators */
        else if (isSeparator(ch))
        {
            token[0] = ch;
            token[1] = '\0';

            printToken(token, "Separator");
            separators_count++;
        }

        /* Special Symbols */
        else
        {
            token[0] = ch;
            token[1] = '\0';

            printToken(token, "Special Symbol");
            special_symbols_count++;
        }
    }

    fclose(fp);

    printf("------------------------------------------\n");

    printf("\nTOKEN COUNT\n");
    printf("------------------------------------------\n");
    printf("Keywords        : %d\n", keywords_count);
    printf("Identifiers     : %d\n", identifiers_count);
    printf("Operators       : %d\n", operators_count);
    printf("Constants       : %d\n", constants_count);
    printf("String Literals : %d\n", string_literals_count);
    printf("Separators      : %d\n", separators_count);
    printf("Comments        : %d\n", comments_count);
    printf("Special Symbols : %d\n", special_symbols_count);

    return 0;
}
