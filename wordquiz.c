#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <ctype.h>

typedef 
	enum {
		C_ZERO,
		C_LIST,
		C_SHOW,
		C_TEST,
		C_EXIT,
		C_ADD,
        C_ADD_WORD
	}
	command_t;

void list_wordbooks () ;
void add_wordbook() {
    char wordbook_name[256];
    printf("Enter the name of the new wordbook: ");
    scanf("%s", wordbook_name);

    char path[300];
    sprintf(path, "wordbooks\\%s", wordbook_name);

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to create the wordbook.\n\n");
        return;
    }

    printf("Wordbook '%s' has been successfully created.\n", wordbook_name);
    fclose(file);
}

void add_word_to_wordbook() {
	list_wordbooks() ;
	
    char wordbook_name[256];
    printf("Enter the name of the wordbook to add a word: ");
    scanf("%s", wordbook_name);

    char path[300];
    sprintf(path, "wordbooks\\%s", wordbook_name);

    FILE *file = fopen(path, "a");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open the wordbook.\n\n");
        return;
    }

    char word[256], meaning[256];
    printf("Enter the word: ");
    scanf("%s", word);
	fflush(stdin);
    printf("Enter the meaning: ");
    gets(meaning);

    fprintf(file, "\"%s\" \"%s\"\n", word, meaning);
    printf("Word '%s' has been successfully added to the wordbook '%s'.\n", word, wordbook_name);

    fclose(file);
}

// strndup 함수 구현
char* strndup(const char* s, size_t n) {
	char* result;
	size_t len = strnlen(s, n);
	result = (char*)malloc(len + 1);
	if (result == NULL) {
		fprintf(stderr, "Error: Memory Allocation Fail\n\n");
		exit(EXIT_FAILURE);	// End program if allocation fails
	}
	memcpy(result, s, len);
	result[len] = '\0';
	return result;
}

char * read_a_line (FILE * fp)
{
	static char buf[BUFSIZ] ;
	static int buf_n = 0 ;
	static int curr = 0 ;

	if (feof(fp) && curr == buf_n - 1)
		return 0x0 ;

	char * s = 0x0 ;
	size_t s_len = 0 ;
	do {
		int end = curr ;
		while (!(end >= buf_n || !iscntrl(buf[end]))) {
			end++ ;
		}
		if (curr < end && s != 0x0) {
			curr = end ;
			break ;
		}
		curr = end ;
		while (!(end >= buf_n || iscntrl(buf[end]))) {
			end++ ;
		}
		if (curr < end) {
			if (s == 0x0) {
				s = strndup(buf + curr, end - curr) ;
				s_len = end - curr ;
			}
			else {
				char* new_s = realloc(s, s_len + end - curr + 1);
				if (new_s == NULL)
				{
					fprintf(stderr, "Error: Memory Allocation Fail\n\n");
					free(s);	// free existing allocated memory
					exit(EXIT_FAILURE);	// End program if allocation fails
				}
				s = new_s;
				strncat(s, buf + curr, end - curr) ;
				s_len = s_len + end - curr ;
			}
		}
		if (end < buf_n) {
			curr = end + 1 ;
			break ;
		}

		buf_n = fread(buf, 1, sizeof(buf), fp) ;
		curr = 0 ;
	} while (buf_n > 0) ;
	return s ;
}

void print_menu() {

	printf("1. List all wordbooks\n") ;
	printf("2. Show the words in a wordbook\n") ;
	printf("3. Test with a wordbook\n") ;
	printf("4. Exit\n") ;
	printf("5. Add a wordbook\n") ;
    printf("6. Add a word to a wordbook\n") ;
}

int get_command() {
	int cmd;
	int res;

	while(1) 
	{
		printf(">");
		res = scanf("%d", &cmd);

		if (res != 1 || cmd > 6 || cmd < 1) 
		{
			fprintf(stderr, "Error: Invalid command. Please enter a number between 1 ~ 4.\n\n");
			while (getchar() != '\n'); // Remove invalid input
			print_menu();
			continue; // return to the begining of the loop
		}
		break;	// End the loop if it is a valid input
	}

	return cmd;
}

void list_wordbooks ()
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile("wordbooks\\*", &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		printf("\nNo wordbooks found.\n");
		fprintf(stderr, "Error: Unable to access the worbks directory.\n\n");
		return;
	}

	printf("\n  ----\n");
	do {
		const char* name = findFileData.cFileName;
		if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0) {
			printf("  %s\n", name);
		}
	} while (FindNextFile(hFind, &findFileData) != 0);
	FindClose(hFind);

	printf("  ----\n");
}

void show_words ()
{
    char wordbook[128] ;
    char filepath[256] ;
    FILE * fp = NULL;

    do {
        list_wordbooks() ;

        printf("Type in the name of the wordbook?\n") ;
        printf(">") ;
        scanf("%127s", wordbook);

        snprintf(filepath, sizeof(filepath), "wordbooks\\%s", wordbook);

        fp = fopen(filepath, "r") ;

        if (!fp) {
            printf("\nFailed to open wordbook %s\n", wordbook);
            fprintf(stderr, "Error: Failed to open file, %s\n\n", filepath);
        }
    } while (!fp);

    printf("\n  -----\n") ;
    char * line ;
    while (line = read_a_line(fp)) {
        char * word = strtok(line, "\"") ;
        strtok(NULL, "\"") ;
        char * meaning = strtok(NULL, "\"") ;

        printf("  %s : %s\n", word, meaning) ;

        free(line) ;
    }
    printf("  -----\n\n") ;

    fclose(fp) ;
}

void run_test ()
{
    char wordbook[128] ;
    char filepath[256] ;
    FILE * fp = NULL;

    do {
        list_wordbooks() ;

        printf("Type in the name of the wordbook?\n") ;
        printf(">") ;
        scanf("%127s", wordbook);

        snprintf(filepath, sizeof(filepath), "wordbooks\\%s", wordbook);

        fp = fopen(filepath, "r") ;

        if (!fp) {
            printf("\nFailed to open wordbook %s\n", wordbook);
            fprintf(stderr, "Error: Failed to open file, %s.\n\n", filepath);
        }
    } while (!fp);

    printf("\n-----\n") ;

    int n_questions = 0 ;
    int n_correct = 0 ; 

    char * line ;
    printf("Which type of test do you want to take?\n");
    printf("1. Word -> Meaning\n");
    printf("2. Meaning -> Word\n");
    printf(">");

    int select = 0;

    scanf("%d", &select);
    if (select == 1)
        while (line = read_a_line(fp)) {
            char* word = strtok(line, "\"");
            strtok(NULL, "\"");
            char* meaning = strtok(NULL, "\"");

            printf("Q. %s\n", meaning);
            printf("?  ");

            char answer[128] ;
            scanf("%127s", answer) ;

            if (strcmp(answer, word) == 0) {
                printf("- correct\n");
                n_correct++;
            }
            else {
                printf("- wrong: %s\n", word);
            }

            n_questions++;
            free(line);
        }
    else if (select == 2)
    {
        getchar();
        while (line = read_a_line(fp)) {
            // Remove the newline character
            char* word = strtok(line, "\"");
            strtok(NULL, "\"");
            char* meaning = strtok(NULL, "\"");

            printf("Q. %s\n", word);
            printf("?  ");

            char answer[128];
            fgets(answer, sizeof(answer), stdin);

            // Remove the newline character
            size_t len = strlen(answer);
            if (len > 0 && answer[len - 1] == '\n') {
                answer[len - 1] = '\0';
            }

            if (strcmp(answer, meaning) == 0) {
                printf("- correct\n");
                n_correct++;
            }
            else {
                printf("- wrong: %s\n", meaning);
            }

            n_questions++;
            free(line);
        }
    }
    else {
        while (getchar() != '\n');
        printf("Error: Invalid Input\n\n");
        fclose(fp);
        return;
    }

    printf("(%d/%d)\n", n_correct, n_questions) ;

    printf("-----\n\n") ;

    fclose(fp) ;
}

int main ()
{
	printf(" *** Word Quiz *** \n\n") ;

	int cmd ;
	do {
		print_menu() ;

		cmd = get_command() ;
		switch (cmd) {
			case C_LIST : {
				list_wordbooks() ;
				break ;
			}

			case C_SHOW: {
				show_words() ;
				break ;
			}

			case C_TEST: {
				run_test() ;
				break ;
			}

			case C_EXIT: {
				return EXIT_SUCCESS ;
			}

			case C_ADD: {
                add_wordbook();
                break;
            }

            case C_ADD_WORD: {
                add_word_to_wordbook();
                break;
            }
		}
	}
	while (cmd != C_EXIT) ;

	return EXIT_SUCCESS ;
}
