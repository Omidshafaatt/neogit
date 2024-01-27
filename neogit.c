#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void run_init(int argc, char *argv[]);
char *where_is_neogit();
int count_character(char *, char);
char *where_is_global_information();
void run_config(int argc, char *argv[]);

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(stdout, "please enter a valid command");
        return 1;
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "init") == 0)
    {
        run_init(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "config") == 0)
    {
        run_config(argc, argv);
    }
    return 0;
}
void run_init(int argc, char *argv[])
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));

    struct dirent *entry;
    struct stat file_info;

    int neogit_exists = 0;
    char currentDirectory[FILENAME_MAX];
    do
    {
        getcwd(currentDirectory, sizeof(currentDirectory));
        DIR *dir = opendir(".");
        while ((entry = readdir(dir)) != NULL)
        {
            stat(entry->d_name, &file_info);
            if (S_ISDIR(file_info.st_mode) && strcmp(entry->d_name, ".neogit") == 0)
            {
                printf("neogit repository has already initialized in %s\n", currentDirectory);
                neogit_exists = 1;
                break;
            }
        }
        chdir("..");
    } while (neogit_exists != 1 && strcmp(currentDirectory, "C:\\") != 0);
    chdir(firstDirectory);

    if (neogit_exists == 0)
    {
        printf("Initialized empty Git repository in %s\n", firstDirectory);
        system("mkdir .neogit");
        system("attrib +h .neogit");
    }
}
char *where_is_neogit() // remember to free the pointer
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));

    struct dirent *entry;
    struct stat file_info;

    char currentDirectory[FILENAME_MAX];
    do
    {
        getcwd(currentDirectory, sizeof(currentDirectory));
        DIR *dir = opendir(".");
        while ((entry = readdir(dir)) != NULL)
        {
            stat(entry->d_name, &file_info);
            if (S_ISDIR(file_info.st_mode) && strcmp(entry->d_name, ".neogit") == 0)
            {
                chdir(firstDirectory);
                char *output = (char *)malloc(100 * sizeof(char));
                strcpy(output, currentDirectory);
                return output;
            }
        }
        chdir("..");
    } while (strcmp(currentDirectory, "C:\\") != 0);
}
int count_character(char *input, char character)
{
    int x = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == character)
        {
            x++;
        }
    }
    return x;
}
char *where_is_global_information() // remember to free the pointer
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));

    char currentDirectory[FILENAME_MAX];
    while (1)
    {
        getcwd(currentDirectory, sizeof(currentDirectory));
        if (count_character(currentDirectory, '\\') == 2)
        {
            break;
        }
        chdir("..");
    }
    char *output = (char *)malloc(100 * sizeof(char));
    strcpy(output, currentDirectory);
    chdir(firstDirectory);
    return output;
}
void run_config(int argc, char *argv[])
{
    if (argc == 2)
    {
        printf("please enter a valid command\n");
    }
    else if (strcmp(argv[2], "--global") == 0)
    {
        if (argc != 5)
        {
            printf("please enter a valid command\n");
        }
        else if (strcmp(argv[3], "user.name") == 0)
        {
            char firstDirectory[FILENAME_MAX];
            getcwd(firstDirectory, sizeof(firstDirectory));
            char *temp = where_is_global_information();
            chdir(temp);
            FILE *file = fopen("configNGLOB.txt", "w");
            fprintf(file, "%s", argv[4]);
            fclose(file);
            free(temp);
            chdir(firstDirectory);
        }
        else if (strcmp(argv[3], "user.email") == 0)
        {
            char firstDirectory[FILENAME_MAX];
            getcwd(firstDirectory, sizeof(firstDirectory));
            char *temp = where_is_global_information();
            chdir(temp);
            FILE *file = fopen("configEGLOB.txt", "w");
            fprintf(file, "%s", argv[4]);
            fclose(file);
            free(temp);
            chdir(firstDirectory);
        }
        else
        {
            printf("please enter a valid command\n");
        }
    }
    else
    {
        if (argc != 4)
        {
            printf("please enter a valid command\n");
        }
        else if (strcmp(argv[2], "user.name") == 0)
        {
            char firstDirectory[FILENAME_MAX];
            getcwd(firstDirectory, sizeof(firstDirectory));
            char *temp = where_is_neogit();
            chdir(temp);
            chdir(".neogit");
            FILE *file = fopen("configN.txt", "w");
            fprintf(file, "%s", argv[3]);
            fclose(file);
            free(temp);
            chdir(firstDirectory);
        }
        else if (strcmp(argv[2], "user.email") == 0)
        {
            char firstDirectory[FILENAME_MAX];
            getcwd(firstDirectory, sizeof(firstDirectory));
            char *temp = where_is_neogit();
            chdir(temp);
            chdir(".neogit");
            FILE *file = fopen("configE.txt", "w");
            fprintf(file, "%s", argv[3]);
            fclose(file);
            free(temp);
            chdir(firstDirectory);
        }
        else
        {
            printf("please enter a valid command\n");
        }
    }
}