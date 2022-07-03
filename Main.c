// Diese Datei dient mir als Dokumentation für die wichtigsten Handlungen (auch für mich persönlich) in der Programmiersprache C.
// Diese Datei wird von Visual Studio als C-Code kompiliert.

#pragma warning(disable : 4996) // Visual Studio doesn't want to see old functions like ‘scanf’.

#include <Windows.h>
#include <limits.h>
#include "Birgers_Documentation.h"

bool supposed_to_run = true;
VOID KeyEventProc(KEY_EVENT_RECORD);
unsigned short current_KeyCode = (unsigned short)0;

void evaluate_key_presses(INPUT_RECORD rec)
{
	if (rec.Event.KeyEvent.wVirtualKeyCode == (unsigned short)0)
	{
		return;
	}

	if (rec.Event.KeyEvent.bKeyDown)
	{
		switch (rec.Event.KeyEvent.wVirtualKeyCode)
		{
		case VK_SHIFT:
			current_KeyCode = VK_SHIFT;
			break;
		case VK_CONTROL:
			current_KeyCode = VK_CONTROL;
			break;
		case VK_SPACE:
			current_KeyCode = VK_SPACE;
			break;
		case VK_LEFT:
			current_KeyCode = VK_LEFT;
			break;
		case VK_UP:
			current_KeyCode = VK_UP;
			break;
		case VK_RIGHT:
			current_KeyCode = VK_RIGHT;
			break;
		case VK_DOWN:
			current_KeyCode = VK_DOWN;
			break;
		case 0x41: /*A 65*/
			current_KeyCode = 0x41;
			break;
		case 0x51: /*Q 81*/
			current_KeyCode = 0x51;
			break;
		case 0x5A:  /*Z 90*/
			current_KeyCode = 0x5A;
			supposed_to_run = false;
			break;
		default:
			current_KeyCode = 0;
			break;
		}
		printf("%u ", rec.Event.KeyEvent.wVirtualKeyCode);
	}
}

#define max_count_of_numbers 10

int main(void)
{
	puts("Schriftfarbe ausw\x84 \bhlen: 1 = Casino-Gr\x81 \bn; 2 = Mittelblau; 3 = Gelb; 4 = Rot; 5 = Grau; sonst Wei\xE1 \b.");
	int scanf_error = 0;
	unsigned short Color = (unsigned short)0;
	do
	{
		scanf_error = scanf("%hu", &Color);
		if (scanf_error == 0)
		{
			printf("nochmal\n");
			flush_input_buffer();
		}
	} while (scanf_error == 0);
	SetFontSize();
	Change_size_position_and_color(Color);
	printf("\n");
	check_Limits();
	printf("dr\x81 \bck Enter\n");
	flush_input_buffer();

	for (int b = 32; b < 256; b++)
	{
		printf("%#X     %c\n", b, b);
	}

	//printf("Key Events:\n");
	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
	// Stellt eine Funktion zum Verarbeiten von Tastendrücken dar. „ReadConsoleInput“ reagiert sowohl auf's Runterdrücken von Tasten als auch auf's Loslassen. Es werden die jeweiligen Zahlen ausgegeben, nicht die Buchstaben. Achtung: Die Umschalttaste wird auch gewertet!
	/*INPUT_RECORD rec = { 0 };
	HANDLE hConInp = GetStdHandle(STD_INPUT_HANDLE);
	DWORD ReadCount = 0ul;

	for (int i = 0; i < 20; i++)
	{
		ReadConsoleInput(hConInp, &rec, 1ul, &ReadCount);
		evaluate_key_presses(rec);
	}*/
	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
	//printf("\n");


	//printf("int scanf: ");
	//int input0;
	//scanf("%d", &input0);

	//printf("uint scanf: ");
	//unsigned int input1;
	//scanf("%u", &input1);

	//printf("short scanf: ");
	//short input2;
	//scanf("%hd", &input2);

	//printf("ushort scanf: ");
	//unsigned short input3;
	//scanf("%hu", &input3);

	//printf("long scanf: ");
	//long input4;
	//scanf("%ld", &input4);

	//printf("ulong scanf: ");
	//unsigned long input5;
	//scanf("%lu", &input5);

	//printf("long long scanf: ");
	//long long input6;
	//scanf("%lld", &input6);

	//printf("ulong long scanf: ");
	//unsigned long long input7;
	//scanf("%llu", &input7);

	//printf("size_t scanf: ");
	//size_t input8;
	//scanf("%zu", &input8);

	//printf("char scanf: ");
	//char input9;
	//scanf("%c", &input9);

	//flush_input_buffer();

	//printf("uchar scanf: ");
	//unsigned char input10;
	//scanf("%c", &input10);

	//wchar_t wchar = '\x8E'; // Ä
	//printf("%c\n", wchar);

	//wchar_t str[] = {L"This is a widestring."};
	//printf("%S\n", str);

	char* Rueckgabestring = Return_a_string_from_a_function();
	if (Rueckgabestring == NULL)
	{
		printf("Zur\x81 \bckgegebener String war NULL.\n");
	}
	else
	{
		printf("%s\n", Rueckgabestring);
	}
	free(Rueckgabestring);

	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
	// Number to String
	// Zahl als String

	//char Number_as_String[6] = {'\0'};
	//int AInt = 12345;
	//itoa(AInt, Number_as_String, 10); // Zahl muss von der Länge her kleiner sein als Platz im Array -1 !
	//int length = sizeof(Number_as_String);

	char Acell[9] = {'\0'};
	unsigned short meinInt = (unsigned short)65535; // Zahl muss von der Länge her kleiner sein als Platz im Array -1 - geplante Zeichen !
	sprintf(Acell, "\"%c%hu\"", 'A', meinInt);

	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

	/*int x = 1;
	procedure_by_address(&x);
	printf("Bearbeitete Variable: %d\n", x);*/

	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

	char StringToSplit[] = { "This is - www.tutorialspoint.com - website" };
	char separators[2] = "-";
	short how_many = (short)0;
	char** Strings = split(StringToSplit, separators, &how_many);
	if (Strings == NULL)
	{
		printf("Zur\x81 \bckgegebene Strings waren NULL.\n");
	}
	else
	{
		for (short i = (short)0; i < how_many; i++)
		{
			printf("%s\n", Strings[i]);
		}
	}
	free(Strings);

	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

	short indexes[max_count_of_numbers] = {(short)0};
	char String[] = { "This is a sample string" };
	char C_ = 's';
	find_indexes_of_character(String, C_, indexes, max_count_of_numbers);
	 
	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
	
	char Origi[] = { "Hallo Welt." };
	char Sub[] = { "Welt" };
	bool unused4 = contains(Origi, Sub);

	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

	// An unsigned char is passed because the function also converts this uchar to int in this way.
	char String2[] = { "Hello there." };
	unsigned char oe = 'ö';
	void* unused2 = memset(String2, oe, (size_t)3);
	printf("%s\n", String2);

	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
	// how to use memcpy
	struct unnamed
	{
		char name[10];
		int age;
	} person1 = { '\0' }, person2 = { '\0' };
	strcpy(person1.name, "Jens");
	person1.age = 30;
	void* unused = memcpy(&person2, &person1, sizeof(person1));
	// PS: Within a structure, the elements in memory are densely packed in increments of one, two, four, or eight. Therefore, the size returned by ‘sizeof’ is 16 instead of 14.
	
	// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

	char StringToEdit[] = "model name: Intel(R) Core(TM) i7-9700K CPU @ 3.60GHz";
	remove_characters_from_a_string(StringToEdit, 12);
	// Get on with StringToEdit because it's been edited!

	//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

	// read a string with spaces because scanf stops at a space.
	printf("\nRead a string with spaces because scanf stops at a space.\n");
	char stringwithspaces[100] = { '\0' };
	fgets(stringwithspaces, 99, stdin); // Provide a lot of space because otherwise this command writes too far in the array. Contains '\n'.

	//––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
	
	Say_Programme_ends_with_frame();
	unsigned char unused3 = getchar();
	return 0;
}