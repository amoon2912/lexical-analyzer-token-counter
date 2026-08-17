# Lexical Analyzer and Token Counter

## 1. Objective

To develop a lexical analyzer in C that reads a source-code file, identifies different types of tokens, classifies them, and counts the number of tokens in each category.

## 2. Problem Statement

Develop a program that performs lexical analysis on a given source-code file and identifies the following token types:

- Keywords
- Identifiers
- Operators
- Constants
- String Literals
- Separators
- Comments
- Special Symbols

The program should also display the total count of each type of token.

## 3. Algorithm

1. Start the program.
2. Read the name of the source-code file.
3. Open the source-code file.
4. Read the file character by character.
5. Ignore white spaces and newline characters.
6. If a sequence starts with a letter or underscore, identify it as a keyword or identifier.
7. If a sequence starts with a digit, identify it as a constant.
8. If double quotes are encountered, read the complete string and identify it as a string literal.
9. If `//` or `/* */` is encountered, identify it as a comment.
10. Identify operators such as `+`, `-`, `*`, `/`, `=`, `<`, `>` and others.
11. Identify separators such as `(`, `)`, `{`, `}`, `[`, `]`, `;`, and `,`.
12. Identify any remaining characters as special symbols.
13. Count each token according to its category.
14. Display all tokens with their corresponding types.
15. Display the total count of each token type.
16. Stop the program.

## 4. Source Code

The complete source code is available in:

`lexical_analyzer.c`

## 5. Sample Input

The following source code is used as the sample input:
The sample input is stored in:
sample.c

## 6. Sample Output
TOKEN                TYPE
------------------------------------------
int                  Keyword
sum                  Identifier
=                    Operator
a                    Identifier
+                    Operator
b                    Identifier
;                    Separator
float                Keyword
average              Identifier
=                    Operator
sum                  Identifier
/                    Operator
2.0                  Constant
;                    Separator
// Calculate average Comment
if                   Keyword
(                    Separator
average              Identifier
>                    Operator
50                   Constant
)                    Separator
printf               Identifier
(                    Separator
"Pass"               String Literal
)                    Separator
;                    Separator
------------------------------------------

TOKEN COUNT
------------------------------------------
Keywords        : 3
Identifiers     : 7
Operators       : 5
Constants       : 2
String Literals : 1
Separators      : 7
Comments        : 1
Special Symbols : 0


## 8. Test Cases
# Test Case 1 – Keywords, Identifier and Constant

Input:

int x = 10;

Expected Classification:

int     → Keyword
x       → Identifier
=       → Operator
10      → Constant
;       → Separator
# Test Case 2 – Floating Point Constant

Input:

float value = 25.5;

Expected Classification:

float   → Keyword
value   → Identifier
=       → Operator
25.5    → Constant
;       → Separator
# Test Case 3 – String Literal

Input:

printf("Hello");

Expected Classification:

printf  → Identifier
(       → Separator
"Hello" → String Literal
)       → Separator
;       → Separator
# Test Case 4 – Comment

Input:

// This is a comment

Expected Classification:

// This is a comment → Comment
Test Case 5 – Operators

Input:

a = b + c;

Expected Classification:

a       → Identifier
=       → Operator
b       → Identifier
+       → Operator
c       → Identifier
;       → Separator
## 9. Conclusion

The Lexical Analyzer successfully reads a source-code file and performs lexical analysis by identifying, classifying, and counting different types of tokens. The program demonstrates the basic functionality of lexical analysis, which is the first phase of a compiler.


