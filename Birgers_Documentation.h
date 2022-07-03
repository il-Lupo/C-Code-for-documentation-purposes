#pragma warning(disable:4996)
#ifndef Birgers_Documentation_H
#define Birgers_Documentation_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void flush_input_buffer()
{
    int c = 0;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF); // geht bei „Enter“ raus
}

void Change_size_position_and_color(unsigned short Color)
{
    //Größe
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX csbiInfo = { 0 };
    csbiInfo.cbSize = sizeof(csbiInfo);
    GetConsoleScreenBufferInfoEx(hStdout, &csbiInfo);
    csbiInfo.srWindow.Right = 10;
    csbiInfo.srWindow.Bottom = 18;
    SetConsoleScreenBufferInfoEx(hStdout, &csbiInfo);

    //Start-Position
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    //Farben
    csbiInfo.ColorTable[0] = RGB(0, 0, 0); // Hintergrund
    switch (Color)
    {
    case 1: csbiInfo.ColorTable[1] = RGB(0, 190, 0); break; // Green
    case 2: csbiInfo.ColorTable[1] = RGB(0, 195, 255); break; // middle blue
    case 3: csbiInfo.ColorTable[1] = RGB(255, 255, 0); break; // yellow
    case 4: csbiInfo.ColorTable[1] = RGB(255, 0, 0); break; // red
    case 5: csbiInfo.ColorTable[1] = RGB(190, 190, 190); break; // gray

    default: csbiInfo.ColorTable[1] = RGB(255, 255, 255); break; // white
    }
    
    SetConsoleScreenBufferInfoEx(hStdout, &csbiInfo);
    SetConsoleTextAttribute(hStdout, 1);
    system("color 01");
}

bool SetFontSize()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = { 24, 24 };
    CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };

    if (!GetCurrentConsoleFontEx(handle, 0, &font))
    {
        return false;
    }

    font.dwFontSize = size;

    if (!SetCurrentConsoleFontEx(handle, 0, &font))
    {
        return false;
    }

    return true;
}

void check_Limits()
{
    printf("short-Wert mind.: %d\n", SHRT_MIN);
    printf("short-Wert max. :  %d\n", SHRT_MAX);
    printf("ushort-Wert max. : %u\n", USHRT_MAX);
    printf("int-Wert mind.: %d\n", INT_MIN);
    printf("int-Wert max. :  %d\n", INT_MAX);
    printf("uint-Wert max. : %u\n", UINT_MAX);
    printf("Ein int ben\x94 \btigt auf diesem System %zu Byte (%zu Bit).\n", sizeof(int), sizeof(int) * CHAR_BIT);
    printf("long-Wert mind.:  %ld\n", LONG_MIN);
    printf("long-Wert max. :   %ld\n", LONG_MAX);
    printf("ulong-Wert max. : %ul\n", ULONG_MAX);
    printf("long-Wert mind.:  %lld\n", LLONG_MIN);
    printf("long-Wert max. :   %lld\n", LLONG_MAX);
    printf("ulong-Wert max. : %llu\n", ULLONG_MAX);
    printf("size_t-Wert max. : %llu\n", SIZE_MAX);
    printf("Ein size_t ben\x94 \btigt auf diesem System %zu Byte (%zu Bit).\n", sizeof(size_t), sizeof(size_t) * CHAR_BIT);
}

void procedure_by_address(int* value)
{
    *value = 5;
}

char* Return_a_string_from_a_function()
{
    char Originalstring[] = { "Dies ist ein String." };
    char* uStrOut = (char*)malloc((size_t)21);
    if (uStrOut == NULL)
    {
        printf("insufficient memory\n");
        return NULL;
    }
    strcpy(uStrOut, Originalstring);
    return uStrOut;
}

/// <summary>
/// This function splits a “string” using a separator. The function returns a two-dimensional char array – a “string” array.
/// </summary>
/// <returns></returns>
char** split(char* StringToSplit, char* delimiters, short* how_many)
{
    int a = 0;
    char* token;

    //allocate string memory
    char** temp = malloc(10 * sizeof(char*));
    if (temp == NULL)
    {
        printf("Insufficient memory!\n");
        return NULL;
    }
    for (int i = 0; i < 10; ++i) 
    {
        temp[i] = malloc(20 * sizeof(char));
        if (temp[i] == NULL)
        {
            printf("Insufficient memory!\n");
            return NULL;
        }
        temp[i][0] = 0;
    }

    /* have a look first */
    token = strtok(StringToSplit, delimiters);
    /* walk through tokens */
    while (token != NULL)
    {
        strcpy(temp[a], token);
        a++;
        *how_many = a;
        //printf(" %s\n", token);
        token = strtok(NULL, delimiters);
    }
    return temp;
}

void find_indexes_of_character(char* StringToBeSearched, char lookFor, short* indexes, int max)
{
    printf("Looking for the '%c' character in \"%s\"...\n", lookFor, StringToBeSearched);
    char* pch = strchr(StringToBeSearched, lookFor);
    int i = 0;
    while (pch != NULL)
    {
        printf("'%c' found at index %td.\n", lookFor, pch - StringToBeSearched);
        if (i > (max-1))
        {
            break;
        }
        indexes[i] = (short)(pch - StringToBeSearched);
        pch = strchr(pch + 1, lookFor);
        i++;
    }
    return;
}

/// <summary>
/// If the substring occurs exactly like this in the string, the result becomes true, otherwise false.
/// </summary>
/// <returns></returns>
bool contains(char* StringToCheck, char* Substring)
{
    // strstr is a char pointer that in this example points 6 characters further than the start of “Origi”.
    if (strstr(StringToCheck, Substring) == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void remove_characters_from_a_string(char* StringToEdit, int offset)
{
    memmove(StringToEdit, 
            StringToEdit + offset, 
            strlen(StringToEdit) + 1 - offset);
}

void Say_Programme_ends_with_frame()
{
    printf("%c", '\xC9'); // ╔
    for (int i = 0; i < 43; i++)
    {
        printf("%c", '\xCD'); // ═
    }
    printf("%c", '\xBB'); // ╗
    printf("\n");

    //      ║                                                         ║
    printf("\xBA \bProgramm wird beendet. Dr\x81 \bcken Sie 'Enter'.\xBA \b\n");
    printf("%c", '\xC8'); // ╚
    for (int i = 0; i < 43; i++)
    {
        printf("%c", '\xCD'); // ═
    }
    printf("%c", '\xBC'); // ╝
}

#endif // !Birgers_Documentation_H