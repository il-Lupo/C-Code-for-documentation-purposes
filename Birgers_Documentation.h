﻿#pragma warning(disable:4996)
#ifndef Birgers_Documentation_H
#define Birgers_Documentation_H

#include <io.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define PathLength 200

/// <summary>
/// \n
/// </summary>
/// <returns></returns> 
#define newline putchar(10)

void flush_input_buffer()
{
    int c = 0;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF); // geht bei „Enter“ raus
}

void WelcomeScreen(int countdownTimeInS)
{
    system("cls");
    for (int i = 0; i < 15; i++)
    {
        putchar('\xB1'); // ▒
    }
    newline;

    //      ▒                 ▒                                                         
    puts("\xB1 \b WILLKOMMEN! \xB1");
    for (int i = 0; i < 15; i++)
    {
        putchar('\xB1'); // ▒
    }
    newline;

    clock_t akt_zeit = clock();
    clock_t end_zeit;

    // Diese Lösung mit einer do-While-Schleife innerhalb einer While-Schleife sieht auf den ersten Blick etwas kompliziert aus, hat aber Gründe. Man muss zur Endzeit immer wieder eine Sekunde hinzuaddieren, sonst hängt das Programm für den ganzen Zeitraum in der do-While-Schleife fest.
    while (countdownTimeInS > 0)
    {
        //printf("%d\n", countdownTimeInS);
        end_zeit = clock() + 1000;
        do
        {
            akt_zeit = clock();
            Sleep(1);
        } while (akt_zeit < end_zeit);
        countdownTimeInS--;
    }

    flush_input_buffer();
    system("cls");
}

void print_all_characters(unsigned short from, unsigned short to)
{
    for (unsigned short b = from; b < to; b++)
    {
        printf("%#X     %c\n", b, b);
    }
}

bool SetFontSize()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = { 22, 22 };
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

void Change_size_position_and_color(unsigned short Color)
{
    //Größe
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX csbiInfo = { 0 };
    csbiInfo.cbSize = sizeof(csbiInfo);
    GetConsoleScreenBufferInfoEx(hStdout, &csbiInfo);
    //csbiInfo.srWindow.Right = 0;
    csbiInfo.srWindow.Bottom = 33;
    csbiInfo.dwSize.X = 85;
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
    case 6: csbiInfo.ColorTable[1] = RGB(240, 230, 140); break; // khaki
    case 7: csbiInfo.ColorTable[1] = RGB(165, 42, 42); break; // brown
    default: csbiInfo.ColorTable[1] = RGB(255, 255, 255); break; // white
    }
    
    SetConsoleScreenBufferInfoEx(hStdout, &csbiInfo);
    SetConsoleTextAttribute(hStdout, 1);
    system("color 01");
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
    printf("long-Wert mind.:   %lld\n", LLONG_MIN);
    printf("long-Wert max. :    %lld\n", LLONG_MAX);
    printf("ulong-Wert max. :  %llu\n", ULLONG_MAX);
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
    // hier verarbeiten
    size_t bytesize = sizeof(char) * strlen(Originalstring) + 1;
    char* RetStr = (char*)malloc(bytesize);
    if (RetStr == NULL)
    {
        puts("insufficient memory\n");
        return NULL;
    }
    return strcpy(RetStr, Originalstring);
}

/// <summary>
/// This function splits a “string” using a separator. The function returns a two-dimensional char array – a “string” array.
/// </summary>
/// <returns></returns>
char** split(char* StringToSplit, char* delimiters, short* how_many)
{   
    //allocate string memory
    char** temp = malloc(10 * sizeof(char*));
    if (temp == NULL)
    {
        puts("Insufficient memory!\n");
        return NULL;
    }
    for (int i = 0; i < 10; ++i) 
    {
        temp[i] = malloc(20 * sizeof(char));
        if (temp[i] == NULL)
        {
            puts("Insufficient memory!\n");
            return NULL;
        }
        temp[i][0] = 0;
    }

    char* token = strtok(StringToSplit, delimiters);
    int a = 0;
    while (token != NULL)
    {
        strcpy(temp[a], token);
        a++;
        *how_many = a;
        token = strtok(NULL, delimiters);
    }
    return temp;
}

void find_indexes_of_character(char* StringToBeSearched, char lookFor, short* indexes, short arraySize)
{
    memset(indexes, (short)-1, sizeof(short) * arraySize);
    
    printf("Looking for the '%c' character in \"%s\"...\n", lookFor, StringToBeSearched);
    char* pch = strchr(StringToBeSearched, lookFor);
    short i = 0;
    while (pch != NULL)
    {
        printf("'%c' found at index %td.\n", lookFor, pch - StringToBeSearched);
        if (i > (arraySize-1))
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
    // strstr returns a char pointer that points x characters further than the start of the original string.
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
    putchar('\xC9'); // ╔
    for (int i = 0; i < 43; i++)
    {
        putchar('\xCD'); // ═
    }
    putchar('\xBB'); // ╗
    newline;

    //      ║                                                         ║
    puts("\xBA \bProgramm wird beendet. Dr\x81 \bcken Sie 'Enter'.\xBA");
    putchar('\xC8'); // ╚
    for (int i = 0; i < 43; i++)
    {
        putchar('\xCD'); // ═
    }
    putchar('\xBC'); // ╝
}

/// <summary>
/// This function reads a file line by line. The char arrays (strings) are stored. To be able to return a string array, so to speak, a pointer pointing to an array of pointers is returned.
/// </summary>
/// <returns></returns>
char** readAllLines(char* fullPath, short* how_many)
{
    FILE* textfilefh = NULL;
    textfilefh = fopen(fullPath, "r");
    if (textfilefh == NULL)
    {
        puts("Fehler beim \x99 \bffnen der Datei.\n");
        return NULL;
    }

    //allocate string memory
    char** ret = malloc(10 * sizeof(char*));
    if (ret == NULL)
    {
        puts("Insufficient memory!\n");
        fclose(textfilefh);
        return NULL;
    }
    for (int i = 0; i < 10; ++i)
    {
        ret[i] = malloc(20 * sizeof(char));
        if (ret[i] == NULL)
        {
            puts("Insufficient memory!\n");
            fclose(textfilefh);
            return NULL;
        }
        ret[i][0] = 0;
    }

    short a = (short)0;

    while (fgetc(textfilefh) != EOF)
    {
        fseek(textfilefh, -1L, SEEK_CUR); // Go back one character because fgetc read one.
        char Line[100] = { '\0' };
        fgets(Line, 99, textfilefh);
        strcpy(ret[a], Line);
         a++;
        *how_many = a;
    }
    fclose(textfilefh);
    return ret;
}

bool FileExists(char* fullPath)
{
    if (_access(fullPath, 0) == 0) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

/// <summary>
/// This function returns the folder path of this application, but without ‘Name.exe’, i.e., up to the last slash.
/// </summary>
/// <returns></returns>
char* ApplicationPath()
{
    char buffer[PathLength] = {'\0'};
    GetModuleFileNameA(NULL, buffer, PathLength);
    int cnt1 = 0;
    for (int i = 0; i < PathLength; i++)
    {   
        if (buffer[i] == '\0')
        {
            break;
        }
        if (buffer[i] == '\\')
        {
            cnt1 = i;
        }   
    }

    size_t bytesize = sizeof(char) * cnt1 + sizeof(char);
    char* Path = malloc(bytesize);
    memset(Path, 0, bytesize);
    int i = 0;
    for (; i < cnt1; i++)
    {
        Path[i] = buffer[i];
    }
    Path[i] = '\0';

    return Path;
}

char* concatenate(char* S1, char* S2)
{
    size_t bytesize = strlen(S1) + strlen(S2) + 2;
    char* OutString = malloc(bytesize);
    for (int i = 0; i < bytesize; i++)
    {
        OutString[i] = S1[i];
    }
    strcat(OutString, S2);
    return OutString;
}

#endif // !Birgers_Documentation_H