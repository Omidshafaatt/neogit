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
void run_add(int argc, char *argv[]);
void listFilesRecursively(char *, FILE *);
int compareFiles(FILE *, FILE *);
void copy_file(char *, char *);
void copy_folder(char *, char *);
int isDirectoryEmpty(const char *);
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
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "add") == 0)
    {
        run_add(argc, argv);
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
        chdir(".neogit");
        system("mkdir stage");
        FILE *file = fopen("ALL.txt", "w");
        listFilesRecursively(firstDirectory, file);
        fclose(file);
        chdir(firstDirectory);
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
void run_add(int argc, char *argv[])
{
    if (argc == 2)
    {
        printf("please enter a valid command\n");
    }
    else if (strcmp(argv[2], "-f") == 0)
    {
        /* code */
    }
    else if (strcmp(argv[2], "-n") == 0)
    {
        /* code */
    }
    else if (strcmp(argv[2], "-redo") == 0)
    {
        /* code */
    }
    else if (argc == 3)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));

        char *origin = (char *)malloc(100 * sizeof(char));
        strcpy(origin, firstDirectory);
        strcat(origin, "\\");
        strcat(origin, argv[2]);

        struct stat file_info;
        stat(origin, &file_info);
        char *temptemp = where_is_neogit();
        chdir(temptemp);
        chdir(".neogit\\stage");
        free(temptemp);
        if (S_ISDIR(file_info.st_mode))
        {
            for (int i = 0; i < 10; i++)
            {
                char *temp = (char *)malloc(sizeof(char));
                sprintf(temp, "%d", i);
                char *temp1 = (char *)malloc(sizeof(char));
                sprintf(temp1, "%d", i - 1);
                DIR *dir = opendir(temp);
                if (dir == NULL)
                {
                    mkdir(temp);
                    if (i == 0)
                    {
                        char *destination = (char *)malloc(100 * sizeof(char));
                        destination = where_is_neogit();
                        strcat(destination, "\\.neogit\\stage\\");
                        strcat(destination, temp);
                        copy_folder(origin, destination);
                        free(destination);
                    }
                    else
                    {
                    }
                }
                free(temp);
                free(temp1);
                break;
            }
        }
        else
        {
            FILE *file1 = fopen(origin, "r");
            for (int i = 0; i < 10; i++)
            {
                char *temp = (char *)malloc(sizeof(char));
                sprintf(temp, "%d", i);
                char *temp1 = (char *)malloc(sizeof(char));
                sprintf(temp1, "%d", i - 1);
                DIR *dir = opendir(temp);
                if (dir == NULL)
                {
                    mkdir(temp);
                    if (i == 0)
                    {
                        copy_file(origin, temp);
                        free(temp);
                        break;
                    }
                    else
                    {
                        int flag = 0;
                        chdir(temp1);
                        struct dirent *entry;
                        DIR *dir1 = opendir(".");
                        while ((entry = readdir(dir1)) != NULL)
                        {
                            if (strcmp(entry->d_name, argv[2]) == 0)
                            {
                                flag = 1;
                                FILE *file2 = fopen(entry->d_name, "r");
                                if (compareFiles(file1, file2) == 0)
                                {
                                    chdir("..");
                                    copy_file(origin, temp);
                                    fclose(file2);
                                    break;
                                }
                                else
                                {
                                    chdir("..");
                                    fclose(file2);
                                    printf("Already in stage\n");
                                    break;
                                }
                            }
                        }
                        if (flag == 0)
                        {
                            chdir("..");
                            copy_file(origin, temp);
                            break;
                        }
                    }
                    if (isDirectoryEmpty(temp) == 1)
                    {
                        char *temppppp = (char *)malloc(100 * sizeof(char));
                        strcpy(temppppp, "rmdir ");
                        strcat(temppppp, temp);
                        system(temppppp);
                        free(temppppp);
                    }
                    break;
                }
                free(temp);
                free(temp1);
            }
            fclose(file1);
        }
        free(origin);
        chdir(firstDirectory);
    }

    else
    {
        printf("please enter a valid command\n");
    }
}
void listFilesRecursively(char *basePath, FILE *file)
{
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Failed to open directory
    if (!dir)
    {
        perror("Unable to open directory");
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        // Ignore "." and ".."
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strstr(dp->d_name, ".git") == 0) ////need change
        {
            // Construct the full path
            char filePath[PATH_MAX];
            snprintf(filePath, PATH_MAX, "%s/%s", basePath, dp->d_name);

            // Check if it's a directory
            struct stat st;
            if (stat(filePath, &st) == 0 && S_ISDIR(st.st_mode))
            {
                // Recursively list files in subdirectory
                listFilesRecursively(filePath, file);
            }
            else
            {
                // Print the file path
                // printf("%s\n", filePath);
                fprintf(file, "%s\n", filePath);
            }
        }
    }

    closedir(dir);
}
int compareFiles(FILE *file1, FILE *file2)
{
    char ch1, ch2;
    // Compare each character in the files
    while ((ch1 = fgetc(file1)) != EOF && (ch2 = fgetc(file2)) != EOF)
    {
        if (ch1 != ch2)
        {
            return 0; // Files are different
        }
    }
    return 1;
}
void copy_file(char *origin, char *destination)
{
    char *temp = (char *)malloc(100 * sizeof(char));
    strcpy(temp, "copy ");
    strcat(temp, origin);
    strcat(temp, " ");
    strcat(temp, destination);
    system(temp);
    free(temp);
}
void copy_folder(char *origin, char *destination)
{
    char *temp = (char *)malloc(100 * sizeof(char));
    strcpy(temp, "xcopy ");
    strcat(temp, origin);
    strcat(temp, " ");
    strcat(temp, destination);
    system(temp);
    free(temp);
}
int isDirectoryEmpty(const char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    int x = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        x++;
    }
    if (x > 2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}