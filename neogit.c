#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void run_init(int argc, char *argv[]);
char *where_is_neogit();
int count_character(char *, char);
char *where_is_global_information();
void run_config(int argc, char *argv[]);
void run_add(int argc, char *argv[]);
void add_for_absolute_address(char *);
void listFilesRecursively(char *, FILE *);
char *modification_time(char *);
void copy_file(char *, char *);
void listFilesRecursively_depth(char *, FILE *, int);
int searchInFile(FILE *, char *);

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
        printf("\033[32mInitialized empty Git repository in %s\033[0m", firstDirectory);
        system("mkdir .neogit");
        system("attrib +h .neogit");
        chdir(".neogit");
        FILE *file = fopen("stageHASH.txt", "w");
        fclose(file);
        file = fopen("stageADDRESS.txt", "w");
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
        printf("\033[31mplease enter a valid command\033\n[0m");
    }
    else if (strcmp(argv[2], "-f") == 0 || (strcmp(argv[2], "-n") != 0 && strcmp(argv[2], "-redo") != 0))
    {
        int X;
        if (strcmp(argv[2], "-f") == 0)
            X = 3;
        else
            X = 2;

        //////
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        FILE *temp_file = fopen("temp.txt", "a");
        // fclose(temp_file);
        //  ساخت فایل آدرس ها
        while (X < argc)
        {
            char *origin = (char *)malloc(100 * sizeof(char));
            strcpy(origin, firstDirectory);
            strcat(origin, "\\");
            strcat(origin, argv[X]);
            struct stat file_info;
            stat(origin, &file_info);
            if (S_ISDIR(file_info.st_mode)) /// اگر مورد خواسته شده یک فولدر باشد
            {
                listFilesRecursively(origin, temp_file);
            }
            else ///// اگر فایل باشد
            {
                fprintf(temp_file, "%s\n", origin);
            }
            X++;
        }
        fclose(temp_file);
        temp_file = fopen("temp.txt", "r");
        char line[100];
        while (fgets(line, sizeof(line), temp_file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            add_for_absolute_address(line);
        }
        fclose(temp_file);
        system("del temp.txt");
        chdir(firstDirectory);
    }
    else if (strcmp(argv[2], "-n") == 0)
    {
        if (argc != 4)
        {
            printf("\033[31mplease enter a valid command\033\n[0m");
        }
        else
        {
            char firstDirectory[FILENAME_MAX];
            getcwd(firstDirectory, sizeof(firstDirectory));
            FILE *temp_file = fopen("temp.txt", "w");
            listFilesRecursively_depth(firstDirectory, temp_file, atoi(argv[3]));
            fclose(temp_file);
            temp_file = fopen("temp.txt", "r");
            char *temp = where_is_neogit();
            chdir(temp);
            chdir(".neogit");
            free(temp);
            char line[100];
            while (fgets(line, sizeof(line), temp_file) != NULL)
            {
                FILE *stage = fopen("stageHASH.txt", "r");
                line[strlen(line) - 1] = '\0';
                temp = modification_time(line);
                if (searchInFile(stage, temp) == 0)
                {
                    printf("\033[32m%s is already in stage\033[0m\n", line);
                }
                else
                {
                    printf("\033[31m%s isn't in stage\033[0m\n", line);
                }
                fclose(stage);
                free(temp);
            }
            fclose(temp_file);
            chdir(firstDirectory);
            system("del temp.txt");
        }
    }
}
void add_for_absolute_address(char *input)
{
    FILE *file_check = fopen(input, "r");
    if (file_check == NULL)
    {
        perror("\033[31mthere is no such file or directory here\033[0m\n");
        fclose(file_check); //////////////////??????
    }
    else
    {
        fclose(file_check);
        FILE *stage = fopen("stageHASH.txt", "r");
        char line[100];
        int flag = 0;
        char *HASH = modification_time(input);
        while (fgets(line, sizeof(line), stage) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            if (strcmp(line, HASH) == 0)
            {
                printf("\033[33mAlready in stage\033\n[0m");
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            fclose(stage);
            stage = fopen("stageHASH.txt", "a");
            fprintf(stage, "%s\n", HASH); ///// STAGE HASH COMPLITED
            fclose(stage);
            stage = fopen("stageADDRESS.txt", "a");
            fprintf(stage, "%s\n", input);
            fclose(stage); ///// STAGE ADDRESS COMPLITED
            mkdir(HASH);
            chdir(HASH);
            copy_file(input, ".");
            chdir("..");
            printf("\033[32m%s successfully add to stage\033[0m\n", input);
        }
        free(HASH);
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
            snprintf(filePath, PATH_MAX, "%s\\%s", basePath, dp->d_name);

            // Check if it's a directory
            struct stat st;
            if (stat(filePath, &st) == 0 && S_ISDIR(st.st_mode))
            {
                // Recursively list files in subdirectory
                listFilesRecursively(filePath, file);
            }
            else
            {
                fprintf(file, "%s\n", filePath);
            }
        }
    }

    closedir(dir);
}
char *modification_time(char *file_path) // remember to free
{
    struct stat file_info;

    if (stat(file_path, &file_info) == 0)
    {
        time_t modification_time = file_info.st_mtime;

        char time_string[50];
        strftime(time_string, sizeof(time_string), "%Y%m%d%H%M%S", localtime(&modification_time));
        char *temp = (char *)malloc(50 * sizeof(char));
        strcpy(temp, time_string);

        return temp;
    }
    else
    {
        perror("error!");
    }
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
void listFilesRecursively_depth(char *basePath, FILE *file, int n)
{
    if (n <= 0)
    {
        return;
    }
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
            snprintf(filePath, PATH_MAX, "%s\\%s", basePath, dp->d_name);

            // Check if it's a directory
            struct stat st;
            if (stat(filePath, &st) == 0 && S_ISDIR(st.st_mode))
            {
                // Recursively list files in subdirectory
                listFilesRecursively_depth(filePath, file, n - 1);
            }
            else
            {
                fprintf(file, "%s\n", filePath);
            }
        }
    }

    closedir(dir);
}
int searchInFile(FILE *file, char *targetString) // remember to fclose file
{
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, targetString) == 0)
        {
            return 0;
        }
    }
    return 1;
}
