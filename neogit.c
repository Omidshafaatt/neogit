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
void copy_folder(char *origin, char *destination);
void run_reset(int argc, char *argv[]);
void reset_for_absolute_address(char *);
void removeLineFromFile(FILE *, int, char *);
void run_status(int argc, char *argv[]);
void run_commit(int argc, char *argv[]);
char *getCurrentTime();
void move_file(char *origin, char *destination);
int how_many_differnt_line(FILE *file);
char *WHO_NAME();
char *WHO_EMAIL();
void run_set(int argc, char *argv[]);
char *shortcut(char *file_name, char *target);
void run_replace(int argc, char *argv[]);
void run_remove(int argc, char *argv[]);
void run_log(int argc, char *argv[]);
void reverseLines(char *, char *);
void run_branch(int argc, char *argv[]);
void run_checkout(int argc, char *argv[]);
int HEAD_OR_NOT(char *);
char *HEAD_HASH(int);
void run_tag(int argc, char *argv[]);
int *organize(char **, int);
void run_diff(int argc, char *argv[]);
void diff(char *, int, int, char *, int, int);
int file_line_count(char *);
int ADD_COUNT(char *);
int check_NULL_space(char *);
void run_merge(int argc, char *argv[]);
char *branch_head_hash(char *);
void all_stage();
int check_invalid_alias(char *);
int run_alias(int argc, char *argv[]);
void reverseString(char str[]);
void run_precommit(int argc, char *argv[]);
int todo_check(char *);
char *what_is_file_format(char *);
int eof_blank_space(char *);
int format_check(char *);
int balance_braces(char *);
int getFileSize(char *);
int file_size_check(char *);
int countCharacters(char *);
int character_limit(char *);
int static_error_check(char *);
void run_grep(int argc, char *argv[]);
void grep_for_filepath(char *, char *, int);

int main(int argc, char *argv[])
{
    if (run_alias(argc, argv) == 1)
    {
        return 0;
    }
    if (argc < 2)
    {
        fprintf(stdout, "please enter a valid command");
        return 1;
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "init") == 0)
    {
        run_init(argc, argv);
    }
    else if (where_is_neogit() == NULL)
    {
        printf("\033[31mThere is no neogit repo\033\n[0m");
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "config") == 0)
    {
        run_config(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "add") == 0)
    {
        run_add(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "reset") == 0)
    {
        run_reset(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "status") == 0)
    {
        run_status(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "commit") == 0)
    {
        run_commit(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "set") == 0)
    {
        run_set(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "replace") == 0)
    {
        run_replace(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "remove") == 0)
    {
        run_remove(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "log") == 0)
    {
        run_log(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "branch") == 0)
    {
        run_branch(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "checkout") == 0)
    {
        run_checkout(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "tag") == 0)
    {
        run_tag(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "diff") == 0)
    {
        run_diff(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "merge") == 0)
    {
        run_merge(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "pre-commit") == 0)
    {
        run_precommit(argc, argv);
    }
    else if (strcmp(argv[0], "neogit") == 0 && strcmp(argv[1], "grep") == 0)
    {
        run_grep(argc, argv);
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
                printf("\033[31mneogit repository has already initialized in %s\n\033[0m", currentDirectory);
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
        file = fopen("WHICHBRANCH.txt", "w");
        fprintf(file, "master");
        fclose(file);
        file = fopen("ALLBRANCHS.txt", "w");
        fprintf(file, "master\n");
        fclose(file);
        file = fopen("HEAD.txt", "w");
        fprintf(file, "YES");
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
        printf("\033[31mplease enter a valid command\n\033[0m");
    }
    else if (strcmp(argv[2], "--global") == 0)
    {
        if (argc != 5)
        {
            printf("\033[31mplease enter a valid command\n\033[0m");
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
            temp = where_is_neogit();
            chdir(temp);
            chdir(".neogit");
            system("del configN.txt");
            free(temp);
            chdir(firstDirectory);
            printf("\033[32msuccessfully\n\033[0m");
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
            temp = where_is_neogit();
            chdir(temp);
            chdir(".neogit");
            system("del configE.txt");
            free(temp);
            chdir(firstDirectory);
            printf("\033[32msuccessfully\n\033[0m");
        }
        else if (argv[3][0] == 'a' && argv[3][1] == 'l' && argv[3][2] == 'i' && argv[3][3] == 'a' && argv[3][4] == 's' && argv[3][5] == '.')
        {
            char firstDirectory[FILENAME_MAX];
            getcwd(firstDirectory, sizeof(firstDirectory));
            char *temp = where_is_global_information();
            chdir(temp);
            if (check_invalid_alias(argv[4]) == 0)
            {
                printf("\033[31mthe command alias is invalid\n\033[0m");
            }
            else
            {
                char alias[30];
                for (int i = 0; i < strlen(argv[3]) - 6; i++)
                {
                    alias[i] = argv[3][i + 6];
                }
                alias[strlen(argv[3]) - 6] = '\0';
                FILE *file = fopen("aliasGLOB.txt", "a");
                fprintf(file, "%s\n", alias);
                fprintf(file, "%s\n", argv[4]);
                fclose(file);
                printf("\033[32msuccessfully\n\033[0m");
            }
            free(temp);
            chdir(firstDirectory);
        }
        else
        {
            printf("\033[31mplease enter a valid command\n\033[0m");
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
        else if (argv[2][0] == 'a' && argv[2][1] == 'l' && argv[2][2] == 'i' && argv[2][3] == 'a' && argv[2][4] == 's' && argv[2][5] == '.')
        {
            char firstDirectory[FILENAME_MAX];
            getcwd(firstDirectory, sizeof(firstDirectory));
            char *temp = where_is_neogit();
            chdir(temp);
            chdir(".neogit");
            if (check_invalid_alias(argv[3]) == 0)
            {
                printf("\033[31mthe command alias is invalid\n\033[0m");
            }
            else
            {
                char alias[30];
                for (int i = 0; i < strlen(argv[2]) - 6; i++)
                {
                    alias[i] = argv[2][i + 6];
                }
                alias[strlen(argv[2]) - 6] = '\0';
                FILE *file = fopen("alias.txt", "a");
                fprintf(file, "%s\n", alias);
                fprintf(file, "%s\n", argv[3]);
                fclose(file);
                printf("\033[32msuccessfully\n\033[0m");
            }
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
        printf("\033[31mplease enter a valid command\033[0m\n");
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
        char *temp1 = modification_time("stageHASH.txt");
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
        char *temp2 = modification_time("stageHASH.txt");
        if (strcmp(temp1, temp2) != 0)
        {
            FILE *file1 = fopen("stageHASH.txt", "a");
            FILE *file2 = fopen("stageADDRESS.txt", "a");
            fprintf(file1, "ADD\n");
            fprintf(file2, "ADD\n");
            fclose(file1);
            fclose(file2);
        }
        free(temp1);
        free(temp2);
        chdir(firstDirectory);
    }
    else if (strcmp(argv[2], "-n") == 0)
    {
        if (argc != 4)
        {
            printf("\033[31mplease enter a valid command\033[0m\n");
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
                if (searchInFile(stage, temp) != 0)
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
    else if (strcmp(argv[2], "-redo") == 0)
    {
        if (argc != 3)
        {
            printf("\033[31mplease enter a valid command\033[0m\n");
        }
        else
        {
            char firstDirectory[FILENAME_MAX];
            getcwd(firstDirectory, sizeof(firstDirectory));

            char *temp = where_is_neogit();
            chdir(".neogit");
            free(temp);
            FILE *stage = fopen("stageHASH.txt", "r");
            char line[20];
            int HOW_MANY_ADD = 0;
            while (fgets(line, sizeof(line), stage) != NULL)
            {
                line[strlen(line) - 1] = '\0';
                if (strcmp(line, "ADD") == 0)
                {
                    HOW_MANY_ADD++;
                }
            }
            fclose(stage);
            FILE *stagehash = fopen("stageHASH.txt", "r");
            FILE *stageaddress = fopen("stageADDRESS.txt", "r");
            char line1[100];
            char line2[100];
            int flag = 0;
            while (fgets(line1, sizeof(line1), stagehash) != NULL)
            {
                line1[strlen(line1) - 1] = '\0';
                fgets(line2, sizeof(line2), stageaddress);
                line2[strlen(line2) - 1] = '\0';
                if (strcmp(line1, "ADD") == 0)
                {
                    flag++;
                }
                if (flag == HOW_MANY_ADD - 1 && strcmp(line1, "ADD") != 0)
                {
                    char *temp_del = (char *)malloc(100 * sizeof(char));
                    strcpy(temp_del, "del ");
                    strcat(temp_del, line2);
                    system(temp_del);
                    free(temp_del);
                    chdir(line1);
                    copy_folder(".", line2);
                    chdir("..");
                }
            }
            fclose(stagehash);
            fclose(stageaddress);
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
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strstr(dp->d_name, ".git") == 0 && strstr(dp->d_name, ".neogit") == 0) ////need change
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
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strstr(dp->d_name, ".git") == 0 && strstr(dp->d_name, ".neogit") == 0) ////need change
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
    int lineCount = 1;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, targetString) == 0)
        {
            return lineCount;
        }
        lineCount++;
    }
    return 0;
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
void run_reset(int argc, char *argv[])
{
    if (argc == 2)
    {
        printf("\033[31mplease enter a valid command\033\n[0m");
    }
    else if (strcmp(argv[2], "-undo") == 0)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        FILE *stage = fopen("stageHASH.txt", "r");
        char line[20];
        int HOW_MANY_ADD = 0;
        while (fgets(line, sizeof(line), stage) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            if (strcmp(line, "ADD") == 0)
            {
                HOW_MANY_ADD++;
            }
        }
        fclose(stage);
        char line1[100];
        int flag = 0;
        int line_counter = 1;
        FILE *stagehash = fopen("stageHASH.txt", "r");
        while (fgets(line1, sizeof(line1), stagehash) != NULL)
        {
            line1[strlen(line1) - 1] = '\0';
            if (strcmp(line1, "ADD") == 0)
            {
                flag++;
            }
            if (strcmp(line1, "ADD") == 0 && flag == HOW_MANY_ADD - 1)
            {
                break;
            }
            line_counter++;
        }
        fclose(stagehash);
        stagehash = fopen("stageHASH.txt", "r");
        FILE *stageaddress = fopen("stageADDRESS.txt", "r");
        FILE *hash = fopen("stagehashtemp.txt", "w");
        FILE *address = fopen("stageaddresstemp.txt", "w");
        char line2[100];
        char line3[100];
        int A = 1;
        while (fgets(line2, sizeof(line2), stagehash) != NULL)
        {
            fgets(line3, sizeof(line3), stageaddress);
            if (A <= line_counter)
            {
                fputs(line2, hash);
                fputs(line3, address);
            }
            else
            {
                char *temp_rmdir = (char *)malloc(100 * sizeof(char));
                strcpy(temp_rmdir, "rmdir /s ");
                strcat(temp_rmdir, line2);
                system(temp_rmdir);
                free(temp_rmdir);
            }
            A++;
        }
        fclose(stagehash);
        fclose(stageaddress);
        fclose(hash);
        fclose(address);
        system("del stageHASH.txt");
        system("del stageADDRESS.txt");
        rename("stagehashtemp.txt", "stageHASH.txt");
        rename("stageaddresstemp.txt", "stageADDRESS.txt");
        chdir(firstDirectory);
    }
    else
    {
        int X;
        if (strcmp(argv[2], "-f") == 0)
            X = 3;
        else
            X = 2;
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        FILE *temp_file = fopen("temp.txt", "a");
        ///// فایل آدرس ها
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
            reset_for_absolute_address(line);
        }
        fclose(temp_file);
        system("del temp.txt");
        chdir(firstDirectory);
    }
}
void reset_for_absolute_address(char *input)
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
        /*FILE *stage = fopen("stageHASH.txt", "r");
        char line[20];
        int HOW_MANY_ADD = 0;
        while (fgets(line, sizeof(line), stage) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            if (strcmp(line, "ADD") == 0)
            {
                HOW_MANY_ADD++;
            }
        }
        fclose(stage);*/
        FILE *stagehash = fopen("stageHASH.txt", "r");
        FILE *stageaddress = fopen("stageADDRESS.txt", "r");
        char line1[100];
        char line[20];
        // int flag = 0;
        // int WHICH_LINE = 1;
        // char *temp = modification_time(input);
        FILE *newstagehash = fopen("stageHASH1.txt", "a");
        FILE *newstageaddress = fopen("stageADDRESS1.txt", "a");
        while (fgets(line1, sizeof(line1), stageaddress) != NULL)
        {
            fgets(line, sizeof(line), stagehash);
            line1[strlen(line1) - 1] = '\0';
            line[strlen(line) - 1] = '\0';
            if (strcmp(input, line1) == 0)
            {
                char *temp_rmdir = (char *)malloc(100 * sizeof(char));
                strcpy(temp_rmdir, "rmdir /s ");
                strcat(temp_rmdir, line);
                system(temp_rmdir);
                free(temp_rmdir);
                continue;
            }
            fprintf(newstageaddress, "%s\n", line1);
            fprintf(newstagehash, "%s\n", line);
            /*if (strcmp(line1, "ADD") == 0)
            {
                flag++;
            }*/
            /*if (/*flag == HOW_MANY_ADD - 1 && strcmp(input, line1) == 0)
            {
                fclose(stagehash);
                stagehash = fopen("stageHASH.txt", "r");
                removeLineFromFile(stagehash, WHICH_LINE, "stageHASH1.txt");
                fclose(stagehash);
                system("del stageHASH.txt");
                rename("stageHASH1.txt", "stageHASH.txt");
                removeLineFromFile(stageaddress, WHICH_LINE, "stageADDRESS1.txt");
                fclose(stageaddress);
                system("del stageADDRESS.txt");
                rename("stageADDRESS1.txt", "stageADDRESS.txt");
                char *temp_rmdir = (char *)malloc(100 * sizeof(char));
                strcpy(temp_rmdir, "rmdir /s ");
                strcat(temp_rmdir, line);
                system(temp_rmdir);
                free(temp_rmdir);
                //break;
            }*/
            // WHICH_LINE++;
        }
        fclose(stageaddress);
        fclose(stagehash);
        fclose(newstageaddress);
        fclose(newstagehash);
        system("del stageHASH.txt");
        rename("stageHASH1.txt", "stageHASH.txt");
        system("del stageADDRESS.txt");
        rename("stageADDRESS1.txt", "stageADDRESS.txt");
        // free(temp);
        //  fclose(stagehash);
        //  fclose(stageaddress);
    }
}
void removeLineFromFile(FILE *file, int lineToRemove, char *file_name)
{
    FILE *outputFile = fopen("tempfile.txt", "w");
    char line[100];
    if (outputFile == NULL)
    {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }
    int currentLine = 1;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (currentLine != lineToRemove)
        {
            fputs(line, outputFile);
        }
        currentLine++;
    }
    fclose(outputFile);
    rename("tempfile.txt", file_name);
}
void run_status(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
    else
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        FILE *all = fopen("ALL.txt", "w");
        listFilesRecursively(temp, all);
        free(temp);
        fclose(all);
        all = fopen("ALL.txt", "r");
        char line[100];
        while (fgets(line, sizeof(line), all) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            printf("%s\t", line);
            FILE *stagehash = fopen("stageHASH.txt", "r");
            FILE *stageaddress = fopen("stageADDRESS.txt", "r");
            temp = modification_time(line);
            if (searchInFile(stagehash, temp) != 0)
            {
                printf("\033[32m+\033[0m\n");
            }
            else
            {
                printf("\033[31m-\033[0m");
                if (searchInFile(stageaddress, line) != 0)
                {
                    printf("\033[33mM\033[0m\n");
                }
                else
                {
                    printf("\033[34mA\033[0m\n");
                }
            }
            free(temp);
            fclose(stagehash);
            fclose(stageaddress);
        }
        fclose(all);
        FILE *stageaddress = fopen("stageADDRESS.txt", "r");
        while (fgets(line, sizeof(line), stageaddress) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            FILE *check = fopen(line, "r");
            if (check == NULL && strcmp(line, "ADD") != 0)
            {
                printf("%s\t-\033[31mD\033[0m\n", line);
            }
            fclose(check);
        }
        system("del ALL.txt");
        fclose(stageaddress);
        chdir(firstDirectory);
    }
}
void run_commit(int argc, char *argv[])
{
    if (strcmp(argv[2], "-s") == 0)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        char *shr = shortcut("COMMITMSG.txt", argv[3]);
        if (strcmp(shr, "NO") == 0)
        {
            return;
        }
        strcpy(argv[3], shr);
        free(shr);
        chdir(firstDirectory);
    }
    if (argc != 4 || (strcmp(argv[2], "-m") != 0 && strcmp(argv[2], "-s") != 0))
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
    else
    {
        /// check stagehash is not empty
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        FILE *file = fopen("stageHASH.txt", "r");
        char line[20];
        fgets(line, sizeof(line), file);
        fclose(file);
        if (line[0] != '2' && line[0] != 'A')
        {
            printf("\033[31mnothing in stage\033\n[0m");
        }
        else
        {
            if (strlen(argv[3]) > 72)
            {
                printf("\033[31mthe message has more than 72 character\033\n[0m");
            }
            else
            {
                FILE *head = fopen("HEAD.txt", "r");
                char checkhead[5];
                fgets(checkhead, sizeof(checkhead), head);
                if (strcmp(checkhead, "NO") == 0)
                {
                    printf("\033[31myou are not in HEAD\033\n[0m");
                }
                else
                {
                    int HOW_MANY_FILE;
                    file = fopen("stageADDRESS.txt", "r");
                    HOW_MANY_FILE = how_many_differnt_line(file);
                    fclose(file);
                    /////
                    temp = getCurrentTime();
                    mkdir(temp);
                    move_file("stageHASH.txt", temp);
                    move_file("stageADDRESS.txt", temp);
                    file = fopen("stageHASH.txt", "w");
                    fclose(file);
                    file = fopen("stageADDRESS.txt", "w");
                    fclose(file);
                    file = fopen("COMMIT.txt", "a");
                    fprintf(file, "%s\n", temp);
                    printf("\033[32mID : %s\033\n[0m", temp);
                    printf("\033[32mTIME : Y:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n[0m", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8], temp[9], temp[10], temp[11], temp[12], temp[13]);
                    printf("\033[32mMESSAGE : %s\033\n[0m", argv[3]);
                    FILE *change_commit = fopen("NOW.txt", "w");
                    fprintf(change_commit, "%s", temp);
                    fclose(change_commit);
                    free(temp);
                    /////////////
                    FILE *branch = fopen("WHICHBRANCH.txt", "r");
                    fgets(line, sizeof(line), branch);
                    fprintf(file, "%s\n", line);
                    fclose(branch);
                    /////////////
                    temp = WHO_NAME();
                    fprintf(file, "%s\n", temp);
                    free(temp);
                    temp = WHO_EMAIL();
                    fprintf(file, "%s\n", temp);
                    free(temp);
                    fprintf(file, "%s\n", argv[3]);
                    fprintf(file, "%d\n", HOW_MANY_FILE);
                    fclose(file);
                }
            }
        }
        chdir(firstDirectory);
    }
}
char *getCurrentTime()
{
    time_t current_time;
    time(&current_time);
    struct tm *time_info = localtime(&current_time);
    char *time_str = (char *)malloc(30);
    strftime(time_str, 30, "%Y%m%d%H%M%S", time_info);
    return time_str;
}
void move_file(char *origin, char *destination)
{
    char *temp = (char *)malloc(100 * sizeof(char));
    strcpy(temp, "move ");
    strcat(temp, origin);
    strcat(temp, " ");
    strcat(temp, destination);
    system(temp);
    free(temp);
}
int how_many_differnt_line(FILE *file)
{
    int x = 0;
    char line[50][100];
    while (fgets(line[x], sizeof(line[x]), file) != NULL)
    {
        line[x][strlen(line[x]) - 1] = '\0';
        x++;
    }
    int count = 0;
    for (int i = 0; i < x; i++)
    {
        if (strcmp(line[i], "ADD") == 0)
        {
            continue;
        }
        else
        {
            int flag = 0;
            for (int j = 0; j < i; j++)
            {
                if (strcmp(line[j], line[i]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                count++;
            }
        }
    }
    return count;
}
char *WHO_NAME() ///////////remember to free
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));

    char *output = (char *)malloc(50 * sizeof(char));
    char line[50];
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);
    FILE *file = fopen("configN.txt", "r");
    if (file == NULL)
    {
        fclose(file);
        temp = where_is_global_information();
        chdir(temp);
        free(temp);
        file = fopen("configNGLOB.txt", "r");
        if (file == NULL)
        {
            strcpy(output, "NO username");
            fclose(file);
        }
        else
        {
            fgets(line, sizeof(line), file);
            strcpy(output, line);
            fclose(file);
        }
    }
    else
    {
        fgets(line, sizeof(line), file);
        strcpy(output, line);
        fclose(file);
    }
    chdir(firstDirectory);
    return output;
}
char *WHO_EMAIL() ///////////remember to free
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));

    char *output = (char *)malloc(50 * sizeof(char));
    char line[50];
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);
    FILE *file = fopen("configE.txt", "r");
    if (file == NULL)
    {
        fclose(file);
        temp = where_is_global_information();
        chdir(temp);
        free(temp);
        file = fopen("configEGLOB.txt", "r");
        if (file == NULL)
        {
            strcpy(output, "NO useremail");
            fclose(file);
        }
        else
        {
            fgets(line, sizeof(line), file);
            strcpy(output, line);
            fclose(file);
        }
    }
    else
    {
        fgets(line, sizeof(line), file);
        strcpy(output, line);
        fclose(file);
    }
    chdir(firstDirectory);
    return output;
}
void run_set(int argc, char *argv[])
{
    if (argc != 6 || strcmp(argv[2], "-m") != 0 || strcmp(argv[4], "-s") != 0)
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
    else
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        //////////
        FILE *commitmsg = fopen("COMMITMSG.txt", "a");
        fprintf(commitmsg, "%s %s\n", argv[5], argv[3]);
        fclose(commitmsg);
        chdir(firstDirectory);
        printf("\033[32mthe shortcut successfully set\033\n[0m");
    }
}
char *shortcut(char *file_name, char *target) /////////remembe to free
{
    FILE *file = fopen(file_name, "r");
    char line[100];
    char line1[100];
    char line2[100];
    int flag = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        sscanf(line, "%s", line1);
        if (strcmp(line1, target) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\033[31mthrere is no shortcut with given name\033\n[0m");
        return "NO";
    }
    else
    {
        for (int i = strlen(line1); i < strlen(line); i++)
        {
            line2[i - strlen(line1)] = line[i + 1];
        }
        char *output = (char *)malloc(100 * sizeof(char));
        strcpy(output, line2);
        return output;
    }
}
void run_replace(int argc, char *argv[])
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);
    if (argc != 6 || strcmp(argv[2], "-m") != 0 || strcmp(argv[4], "-s") != 0)
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
    else
    {
        FILE *file = fopen("COMMITMSG.txt", "r");
        FILE *temp_file = fopen("temp.txt", "w");
        char line[100];
        char line1[100];
        int flag = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            sscanf(line, "%s", line1);
            if (strcmp(line1, argv[5]) == 0)
            {
                fprintf(temp_file, "%s %s\n", argv[5], argv[3]);
                flag = 1;
                continue;
            }
            fprintf(temp_file, "%s\n", line);
        }
        if (flag == 0)
        {
            fclose(temp_file);
            system("del temp.txt");
            printf("\033[31mthrere is no shortcut with given name\033\n[0m");
            fclose(file);
        }
        else
        {
            fclose(file);
            fclose(temp_file);
            system("del COMMITMSG.txt");
            rename("temp.txt", "COMMITMSG.txt");
            printf("\033[32mthe shortcut successfully replace\033\n[0m");
        }
    }
    chdir(firstDirectory);
}
void run_remove(int argc, char *argv[])
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);
    if (argc != 4 || strcmp(argv[2], "-s") != 0)
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
    else
    {
        FILE *file = fopen("COMMITMSG.txt", "r");
        FILE *temp_file = fopen("temp.txt", "w");
        char line[100];
        char line1[100];
        int flag = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            sscanf(line, "%s", line1);
            if (strcmp(line1, argv[3]) == 0)
            {
                flag = 1;
                continue;
            }
            fprintf(temp_file, "%s\n", line);
        }
        if (flag == 0)
        {
            fclose(temp_file);
            system("del temp.txt");
            printf("\033[31mthrere is no shortcut with given name\033\n[0m");
            fclose(file);
        }
        else
        {
            fclose(file);
            fclose(temp_file);
            system("del COMMITMSG.txt");
            rename("temp.txt", "COMMITMSG.txt");
            printf("\033[32mthe shortcut successfully remove\033\n[0m");
        }
        chdir(firstDirectory);
    }
}
void run_log(int argc, char *argv[])
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);
    if (argc == 2)
    {
        char line[200];
        reverseLines("COMMIT.txt", "temp.txt");
        FILE *file = fopen("temp.txt", "r");
        int i = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            switch (i % 6)
            {
            case 0:
                printf("\033[36mNUMBER OF COMMITED FILES : \033[0m");
                break;
            case 1:
                printf("\033[36mMESSAGE : \033[0m");
                break;
            case 2:
                printf("\033[36mGMAIL : \033[0m");
                break;
            case 3:
                printf("\033[36mNAME : \033[0m");
                break;
            case 4:
                printf("\033[36mBRANCH : \033[0m");
                break;
            case 5:
                printf("\033[36mID : \033[35m%s\033[0m", line);
                printf("\033[36mTIME : \033[35mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n[0m", line[0], line[1], line[2], line[3], line[4], line[5], line[6], line[7], line[8], line[9], line[10], line[11], line[12], line[13]);
                break;
            }
            if (i % 6 != 5)
            {
                printf("\033[35m%s\033[0m", line);
            }
            i++;
        }
        fclose(file);
        system("del temp.txt");
    }
    else if (argc == 4 && strcmp(argv[2], "-n") == 0)
    {
        char line[200];
        reverseLines("COMMIT.txt", "temp.txt");
        FILE *file = fopen("temp.txt", "r");
        int i = 0;
        int A = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            if (A == atoi(argv[3]))
            {
                break;
            }
            switch (i % 6)
            {
            case 0:
                printf("\033[36mNUMBER OF COMMITED FILES : \033[0m");
                break;
            case 1:
                printf("\033[36mMESSAGE : \033[0m");
                break;
            case 2:
                printf("\033[36mGMAIL : \033[0m");
                break;
            case 3:
                printf("\033[36mNAME : \033[0m");
                break;
            case 4:
                printf("\033[36mBRANCH : \033[0m");
                break;
            case 5:
                printf("\033[36mID : \033[35m%s\033[0m", line);
                printf("\033[36mTIME : \033[35mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n[0m", line[0], line[1], line[2], line[3], line[4], line[5], line[6], line[7], line[8], line[9], line[10], line[11], line[12], line[13]);
                A++;
                break;
            }
            if (i % 6 != 5)
            {
                printf("\033[35m%s\033[0m", line);
            }
            i++;
        }
        fclose(file);
        system("del temp.txt");
    }
    else if (argc == 4 && strcmp(argv[2], "-branch") == 0)
    {
        FILE *file = fopen("ALLBRANCHS.txt", "r");
        if (searchInFile(file, argv[3]) == 0)
        {
            printf("\033[31mthere is no branch with given name\033[0m\n");
            fclose(file);
        }
        else
        {
            fclose(file);
            char line0[100];
            char line1[100];
            char line2[100];
            char line3[100];
            char line4[100];
            char line5[100];
            reverseLines("COMMIT.txt", "temp.txt");
            file = fopen("temp.txt", "r");
            while (fgets(line0, sizeof(line0), file) != NULL)
            {
                fgets(line1, sizeof(line1), file);
                fgets(line2, sizeof(line2), file);
                fgets(line3, sizeof(line3), file);
                fgets(line4, sizeof(line4), file);
                fgets(line5, sizeof(line5), file);
                line4[strlen(line4) - 1] = '\0';
                if (strcmp(line4, argv[3]) != 0)
                {
                    continue;
                }
                printf("\033[36mNUMBER OF COMMITED FILES : \033[35m%s\033[0m", line0);
                printf("\033[36mMESSAGE : \033[35m%s\033[0m", line1);
                printf("\033[36mGMAIL : \033[35m%s\033[0m", line2);
                printf("\033[36mNAME : \033[35m%s\033[0m", line3);
                printf("\033[36mBRANCH : \033[35m%s\033\n[0m", line4);
                printf("\033[36mID : \033[35m%s\033[0m", line5);
                printf("\033[36mTIME : \033[35mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n[0m", line5[0], line5[1], line5[2], line5[3], line5[4], line5[5], line5[6], line5[7], line5[8], line5[9], line5[10], line5[11], line5[12], line5[13]);
            }
            fclose(file);
            system("del temp.txt");
        }
    }
    else if (argc == 4 && strcmp(argv[2], "-author") == 0)
    {
        char line0[100];
        char line1[100];
        char line2[100];
        char line3[100];
        char line4[100];
        char line5[100];
        reverseLines("COMMIT.txt", "temp.txt");
        FILE *file = fopen("temp.txt", "r");
        while (fgets(line0, sizeof(line0), file) != NULL)
        {
            fgets(line1, sizeof(line1), file);
            fgets(line2, sizeof(line2), file);
            fgets(line3, sizeof(line3), file);
            fgets(line4, sizeof(line4), file);
            fgets(line5, sizeof(line5), file);
            line3[strlen(line3) - 1] = '\0';
            if (strcmp(line3, argv[3]) != 0)
            {
                continue;
            }
            printf("\033[36mNUMBER OF COMMITED FILES : \033[35m%s\033[0m", line0);
            printf("\033[36mMESSAGE : \033[35m%s\033[0m", line1);
            printf("\033[36mGMAIL : \033[35m%s\033[0m", line2);
            printf("\033[36mNAME : \033[35m%s\033\n[0m", line3);
            printf("\033[36mBRANCH : \033[35m%s\033[0m", line4);
            printf("\033[36mID : \033[35m%s\033[0m", line5);
            printf("\033[36mTIME : \033[35mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n[0m", line5[0], line5[1], line5[2], line5[3], line5[4], line5[5], line5[6], line5[7], line5[8], line5[9], line5[10], line5[11], line5[12], line5[13]);
        }
        fclose(file);
        system("del temp.txt");
    }
    else if (argc == 4 && strcmp(argv[2], "-since") == 0)
    {
        char line0[100];
        char line1[100];
        char line2[100];
        char line3[100];
        char line4[100];
        char line5[100];
        reverseLines("COMMIT.txt", "temp.txt");
        FILE *file = fopen("temp.txt", "r");
        while (fgets(line0, sizeof(line0), file) != NULL)
        {
            fgets(line1, sizeof(line1), file);
            fgets(line2, sizeof(line2), file);
            fgets(line3, sizeof(line3), file);
            fgets(line4, sizeof(line4), file);
            fgets(line5, sizeof(line5), file);
            line5[strlen(line5) - 1] = '\0';
            if (strcmp(line5, argv[3]) < 0)
            {
                break;
            }
            printf("\033[36mNUMBER OF COMMITED FILES : \033[35m%s\033[0m", line0);
            printf("\033[36mMESSAGE : \033[35m%s\033[0m", line1);
            printf("\033[36mGMAIL : \033[35m%s\033[0m", line2);
            printf("\033[36mNAME : \033[35m%s\033[0m", line3);
            printf("\033[36mBRANCH : \033[35m%s\033[0m", line4);
            printf("\033[36mID : \033[35m%s\033[0m\n", line5);
            printf("\033[36mTIME : \033[35mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n[0m", line5[0], line5[1], line5[2], line5[3], line5[4], line5[5], line5[6], line5[7], line5[8], line5[9], line5[10], line5[11], line5[12], line5[13]);
        }
        fclose(file);
        system("del temp.txt");
    }
    else if (argc == 4 && strcmp(argv[2], "-before") == 0)
    {
        char line0[100];
        char line1[100];
        char line2[100];
        char line3[100];
        char line4[100];
        char line5[100];
        reverseLines("COMMIT.txt", "temp.txt");
        FILE *file = fopen("temp.txt", "r");
        while (fgets(line0, sizeof(line0), file) != NULL)
        {
            fgets(line1, sizeof(line1), file);
            fgets(line2, sizeof(line2), file);
            fgets(line3, sizeof(line3), file);
            fgets(line4, sizeof(line4), file);
            fgets(line5, sizeof(line5), file);
            line5[strlen(line5) - 1] = '\0';
            if (strcmp(line5, argv[3]) > 0)
            {
                continue;
            }
            printf("\033[36mNUMBER OF COMMITED FILES : \033[35m%s\033[0m", line0);
            printf("\033[36mMESSAGE : \033[35m%s\033[0m", line1);
            printf("\033[36mGMAIL : \033[35m%s\033[0m", line2);
            printf("\033[36mNAME : \033[35m%s\033[0m", line3);
            printf("\033[36mBRANCH : \033[35m%s\033[0m", line4);
            printf("\033[36mID : \033[35m%s\033[0m\n", line5);
            printf("\033[36mTIME : \033[35mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n[0m", line5[0], line5[1], line5[2], line5[3], line5[4], line5[5], line5[6], line5[7], line5[8], line5[9], line5[10], line5[11], line5[12], line5[13]);
        }
        fclose(file);
        system("del temp.txt");
    }
    else if (strcmp(argv[2], "-search") == 0) //////////////////wild card?
    {
        char line0[100];
        char line1[100];
        char line2[100];
        char line3[100];
        char line4[100];
        char line5[100];
        reverseLines("COMMIT.txt", "temp.txt");
        FILE *file = fopen("temp.txt", "r");
        while (fgets(line0, sizeof(line0), file) != NULL)
        {
            fgets(line1, sizeof(line1), file);
            fgets(line2, sizeof(line2), file);
            fgets(line3, sizeof(line3), file);
            fgets(line4, sizeof(line4), file);
            fgets(line5, sizeof(line5), file);
            line1[strlen(line1) - 1] = '\0';
            int count = 0;
            for (int i = 3; i < argc; i++)
            {
                if (strstr(line1, argv[i]) == NULL)
                {
                    count++;
                }
            }
            if (count == argc - 3)
            {
                continue;
            }
            printf("\033[36mNUMBER OF COMMITED FILES : \033[35m%s\033[0m", line0);
            printf("\033[36mMESSAGE : \033[35m%s\033[0m\n", line1);
            printf("\033[36mGMAIL : \033[35m%s\033[0m", line2);
            printf("\033[36mNAME : \033[35m%s\033[0m", line3);
            printf("\033[36mBRANCH : \033[35m%s\033[0m", line4);
            printf("\033[36mID : \033[35m%s\033[0m", line5);
            printf("\033[36mTIME : \033[35mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n[0m", line5[0], line5[1], line5[2], line5[3], line5[4], line5[5], line5[6], line5[7], line5[8], line5[9], line5[10], line5[11], line5[12], line5[13]);
        }
        fclose(file);
        system("del temp.txt");
    }
    else
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
    chdir(firstDirectory);
}
void reverseLines(char *inputFileName, char *outputFileName)
{
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        perror("error!");
        return;
    }
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL)
    {
        perror("error!");
        fclose(inputFile);
        return;
    }
    char **lines = NULL;
    char buffer[256];
    int lineCount = 0;
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL)
    {
        lines = realloc(lines, (lineCount + 1) * sizeof(char *));
        lines[lineCount] = strdup(buffer);
        lineCount++;
    }
    for (int i = lineCount - 1; i >= 0; i--)
    {
        fprintf(outputFile, "%s", lines[i]);
        free(lines[i]);
    }
    free(lines);
    fclose(inputFile);
    fclose(outputFile);
}
void run_branch(int argc, char *argv[])
{
    if (argc == 2)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        FILE *file = fopen("ALLBRANCHS.txt", "r");
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("\033[36m%s\033[0m", line);
        }
        fclose(file);
        chdir(firstDirectory);
    }
    else if (argc == 3)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);

        FILE *file = fopen("ALLBRANCHS.txt", "r");
        if (searchInFile(file, argv[2]) != 0)
        {
            printf("\033[31mthis branch is already exist\033[0m\n");
            fclose(file);
        }
        else
        {
            fclose(file);
            FILE *file = fopen("ALLBRANCHS.txt", "a");
            fprintf(file, "%s\n", argv[2]);
            fclose(file);
            printf("\033[32mthe branch successfully create\033\n[0m");
        }
        chdir(firstDirectory);
    }
    else
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
}
void run_checkout(int argc, char *argv[])
{
    if (argc == 4 && strcmp(argv[2], "HEAD") == 0)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        char *HASH = HEAD_HASH(atoi(argv[3]));
        char line0[20];
        char line1[30];
        char line2[50];
        char line3[50];
        char line4[75];
        char line5[100];
        // char save[20];
        FILE *file = fopen("COMMIT.txt", "r");
        while (fgets(line0, sizeof(line0), file) != NULL)
        {
            fgets(line1, sizeof(line1), file);
            fgets(line2, sizeof(line2), file);
            fgets(line3, sizeof(line3), file);
            fgets(line4, sizeof(line4), file);
            fgets(line5, sizeof(line5), file);
            line0[strlen(line0) - 1] = '\0';
            line1[strlen(line1) - 1] = '\0';
            chdir(line0);
            FILE *stageaddress = fopen("stageADDRESS.txt", "r");
            char address[100];
            while (fgets(address, sizeof(address), stageaddress) != NULL)
            {
                address[strlen(address) - 1] = '\0';
                if (strcmp(address, "ADD") == 0)
                {
                    continue;
                }
                char *temp = (char *)malloc(100 * sizeof(char));
                strcpy(temp, "del ");
                strcat(temp, address);
                system(temp);
                ///////////////////////////////////////////////////////////////
                free(temp);
            }
            fclose(stageaddress);
            chdir("..");
        }
        fclose(file);

        file = fopen("COMMIT.txt", "r");
        FILE *stagehash;
        FILE *stageaddress;
        while (fgets(line0, sizeof(line0), file) != NULL)
        {
            line0[strlen(line0) - 1] = '\0';
            if (strcmp(line0, HASH) == 1)
            {
                break;
            }
            chdir(line0);
            stagehash = fopen("stageHASH.txt", "r");
            stageaddress = fopen("stageADDRESS.txt", "r");
            char hash[20];
            char address[100];
            while (fgets(hash, sizeof(hash), stagehash) != NULL)
            {
                fgets(address, sizeof(address), stageaddress);
                hash[strlen(hash) - 1] = '\0';
                address[strlen(address) - 1] = '\0';
                if (strcmp(hash, "ADD") == 0)
                {
                    continue;
                }
                char *temp = (char *)malloc(100 * sizeof(char));
                strcpy(temp, "xcopy ..\\");
                strcat(temp, hash);
                strcat(temp, " ");
                strcat(temp, address);
                system(temp);
                free(temp);
            }
            chdir("..");
            fclose(stageaddress);
            fclose(stagehash);
            fgets(line0, sizeof(line0), file);
            fgets(line0, sizeof(line0), file);
            fgets(line0, sizeof(line0), file);
            fgets(line0, sizeof(line0), file);
            fgets(line0, sizeof(line0), file);
        }
        fclose(file);
        if (HEAD_OR_NOT(HASH) == 0)
        {
            FILE *head = fopen("HEAD.txt", "w");
            fprintf(head, "NO");
            fclose(head);
        }
        else
        {
            FILE *head = fopen("HEAD.txt", "w");
            fprintf(head, "YES");
            fclose(head);
        }
        free(HASH);
        chdir(firstDirectory);
    }
    else
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        FILE *file = fopen("stageHASH.txt", "r");
        char character = fgetc(file);
        if (character != EOF && character != 'A')
        {
            printf("\033[31mplease first commit\033[0m\n");
            fclose(file);
        }
        else if (argv[2][0] != '2')
        {
            /////////////////////////////////////////////////////
            fclose(file);
            FILE *allbranchs = fopen("ALLBRANCHS.txt", "r");
            if (searchInFile(allbranchs, argv[2]) == 0)
            {
                printf("\033[31mthere is no branch with given name\033[0m\n");
                fclose(allbranchs);
            }
            else
            {
                fclose(allbranchs);
                FILE *commit = fopen("COMMIT.txt", "r");
                if (searchInFile(commit, argv[2]) == 0)
                {
                    FILE *change_branch = fopen("WHICHBRANCH.txt", "w");
                    fprintf(change_branch, "%s", argv[2]);
                    fclose(commit);
                    fclose(change_branch);
                    FILE *head = fopen("HEAD.txt", "w");
                    fprintf(head, "YES");
                    fclose(head);
                }
                else
                {
                    fclose(commit);
                    char line0[20];
                    char line1[30];
                    char line2[50];
                    char line3[50];
                    char line4[75];
                    char line5[100];
                    char save[20];
                    file = fopen("COMMIT.txt", "r");
                    while (fgets(line0, sizeof(line0), file) != NULL)
                    {
                        fgets(line1, sizeof(line1), file);
                        fgets(line2, sizeof(line2), file);
                        fgets(line3, sizeof(line3), file);
                        fgets(line4, sizeof(line4), file);
                        fgets(line5, sizeof(line5), file);
                        line0[strlen(line0) - 1] = '\0';
                        line1[strlen(line1) - 1] = '\0';
                        chdir(line0);
                        FILE *stageaddress = fopen("stageADDRESS.txt", "r");
                        char address[100];
                        while (fgets(address, sizeof(address), stageaddress) != NULL)
                        {
                            address[strlen(address) - 1] = '\0';
                            if (strcmp(address, "ADD") == 0)
                            {
                                continue;
                            }
                            char *temp = (char *)malloc(100 * sizeof(char));
                            strcpy(temp, "del ");
                            strcat(temp, address);
                            system(temp);
                            free(temp);
                        }
                        fclose(stageaddress);
                        chdir("..");
                        if (strcmp(line1, argv[2]) == 0)
                        {
                            strcpy(save, line0);
                        }
                    }
                    fclose(file);
                    file = fopen("COMMIT.txt", "r");
                    FILE *stagehash;
                    FILE *stageaddress;
                    while (fgets(line0, sizeof(line0), file) != NULL)
                    {
                        line0[strlen(line0) - 1] = '\0';
                        if (strcmp(line0, save) == 1)
                        {
                            break;
                        }
                        chdir(line0);
                        stagehash = fopen("stageHASH.txt", "r");
                        stageaddress = fopen("stageADDRESS.txt", "r");
                        char hash[20];
                        char address[100];
                        while (fgets(hash, sizeof(hash), stagehash) != NULL)
                        {
                            fgets(address, sizeof(address), stageaddress);
                            hash[strlen(hash) - 1] = '\0';
                            address[strlen(address) - 1] = '\0';
                            if (strcmp(hash, "ADD") == 0)
                            {
                                continue;
                            }
                            char *temp = (char *)malloc(100 * sizeof(char));
                            strcpy(temp, "xcopy ..\\");
                            strcat(temp, hash);
                            strcat(temp, " ");
                            strcat(temp, address);
                            system(temp);
                            free(temp);
                        }
                        chdir("..");
                        fclose(stageaddress);
                        fclose(stagehash);
                        fgets(line0, sizeof(line0), file);
                        fgets(line0, sizeof(line0), file);
                        fgets(line0, sizeof(line0), file);
                        fgets(line0, sizeof(line0), file);
                        fgets(line0, sizeof(line0), file);
                    }
                    if (HEAD_OR_NOT(save) == 0)
                    {
                        FILE *head = fopen("HEAD.txt", "w");
                        fprintf(head, "NO");
                        fclose(head);
                    }
                    else
                    {
                        FILE *head = fopen("HEAD.txt", "w");
                        fprintf(head, "YES");
                        fclose(head);
                    }
                    FILE *change_branch = fopen("WHICHBRANCH.txt", "w");
                    fprintf(change_branch, "%s", argv[2]);
                    fclose(change_branch);
                    FILE *change_commit = fopen("NOW.txt", "w");
                    fprintf(change_commit, "%s", save);
                    fclose(change_commit);
                }
                printf("\033[32msuccessfully checkout\033\n[0m");
            }
        }
        else
        {
            fclose(file);
            char line0[20];
            char line1[30];
            char line2[50];
            char line3[50];
            char line4[75];
            char line5[100];
            char save[20];
            file = fopen("COMMIT.txt", "r");
            while (fgets(line0, sizeof(line0), file) != NULL)
            {
                fgets(line1, sizeof(line1), file);
                fgets(line2, sizeof(line2), file);
                fgets(line3, sizeof(line3), file);
                fgets(line4, sizeof(line4), file);
                fgets(line5, sizeof(line5), file);
                line0[strlen(line0) - 1] = '\0';
                line1[strlen(line1) - 1] = '\0';
                chdir(line0);
                FILE *stageaddress = fopen("stageADDRESS.txt", "r");
                char address[100];
                while (fgets(address, sizeof(address), stageaddress) != NULL)
                {
                    address[strlen(address) - 1] = '\0';
                    if (strcmp(address, "ADD") == 0)
                    {
                        continue;
                    }
                    char *temp = (char *)malloc(100 * sizeof(char));
                    strcpy(temp, "del ");
                    strcat(temp, address);
                    system(temp);
                    ///////////////////////////////////////////////////////////////
                    free(temp);
                }
                fclose(stageaddress);
                chdir("..");
                if (strcmp(line0, argv[2]) == 0)
                {
                    strcpy(save, line1);
                }
            }
            fclose(file);
            //////////////////////////////////////////delete
            file = fopen("COMMIT.txt", "r");
            FILE *stagehash;
            FILE *stageaddress;
            while (fgets(line0, sizeof(line0), file) != NULL)
            {
                line0[strlen(line0) - 1] = '\0';
                if (strcmp(line0, argv[2]) == 1)
                {
                    break;
                }
                chdir(line0);
                stagehash = fopen("stageHASH.txt", "r");
                stageaddress = fopen("stageADDRESS.txt", "r");
                char hash[20];
                char address[100];
                while (fgets(hash, sizeof(hash), stagehash) != NULL)
                {
                    fgets(address, sizeof(address), stageaddress);
                    hash[strlen(hash) - 1] = '\0';
                    address[strlen(address) - 1] = '\0';
                    if (strcmp(hash, "ADD") == 0)
                    {
                        continue;
                    }
                    char *temp = (char *)malloc(100 * sizeof(char));
                    strcpy(temp, "xcopy ..\\");
                    strcat(temp, hash);
                    strcat(temp, " ");
                    strcat(temp, address);
                    system(temp);
                    free(temp);
                }
                chdir("..");
                fclose(stageaddress);
                fclose(stagehash);
                fgets(line0, sizeof(line0), file);
                fgets(line0, sizeof(line0), file);
                fgets(line0, sizeof(line0), file);
                fgets(line0, sizeof(line0), file);
                fgets(line0, sizeof(line0), file);
            }
            fclose(file);
            if (HEAD_OR_NOT(argv[2]) == 0)
            {
                FILE *head = fopen("HEAD.txt", "w");
                fprintf(head, "NO");
                fclose(head);
            }
            else
            {
                FILE *head = fopen("HEAD.txt", "w");
                fprintf(head, "YES");
                fclose(head);
            }
            FILE *change_branch = fopen("WHICHBRANCH.txt", "w");
            fprintf(change_branch, "%s", save);
            fclose(change_branch);
            FILE *change_commit = fopen("NOW.txt", "w");
            fprintf(change_commit, "%s", argv[2]);
            fclose(change_commit);
            printf("\033[32msuccessfully checkout\033\n[0m");
        }
        chdir(firstDirectory);
    }
}
int HEAD_OR_NOT(char *hash)
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);
    FILE *file = fopen("COMMIT.txt", "r");
    char line0[20];
    char line1[30];
    char line2[50];
    char line3[50];
    char line4[75];
    char line5[100];
    char save[50];
    while (fgets(line0, sizeof(line0), file) != NULL)
    {
        fgets(line1, sizeof(line1), file);
        fgets(line2, sizeof(line2), file);
        fgets(line3, sizeof(line3), file);
        fgets(line4, sizeof(line4), file);
        fgets(line5, sizeof(line5), file);
        line0[strlen(line0) - 1] = '\0';
        line1[strlen(line1) - 1] = '\0';

        if (strcmp(line0, hash) == 0)
        {
            strcpy(save, line1);
            continue;
        }
        if (strcmp(save, line1) == 0)
        {
            chdir(firstDirectory);
            return 0; //////////////////NOT HEAD
        }
    }
    chdir(firstDirectory);
    return 1;
}
char *HEAD_HASH(int n) ////////////////////remember to free
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);

    FILE *file = fopen("WHICHBRANCH.txt", "r");
    char BRANCH[100];
    fgets(BRANCH, sizeof(BRANCH), file);
    fclose(file);
    /////////////////////
    file = fopen("COMMIT.txt", "r");
    char line0[20];
    char line1[30];
    char line2[50];
    char line3[50];
    char line4[100];
    char line5[10];
    int count_branch = 0;
    while (fgets(line0, sizeof(line0), file) != NULL)
    {
        fgets(line1, sizeof(line1), file);
        fgets(line2, sizeof(line2), file);
        fgets(line3, sizeof(line3), file);
        fgets(line4, sizeof(line4), file);
        fgets(line5, sizeof(line5), file);

        line1[strlen(line1) - 1] = '\0';
        if (strcmp(line1, BRANCH) == 0)
        {
            count_branch++;
        }
    }
    fclose(file);
    ////////////////////////
    int count = 0;
    file = fopen("COMMIT.txt", "r");
    while (fgets(line0, sizeof(line0), file) != NULL)
    {
        fgets(line1, sizeof(line1), file);
        fgets(line2, sizeof(line2), file);
        fgets(line3, sizeof(line3), file);
        fgets(line4, sizeof(line4), file);
        fgets(line5, sizeof(line5), file);

        line1[strlen(line1) - 1] = '\0';
        if (strcmp(line1, BRANCH) == 0)
        {
            count++;
        }
        if (count == count_branch - n)
        {
            line0[strlen(line0) - 1] = '\0';
            break;
        }
    }
    fclose(file);
    char *output = (char *)malloc(100 * sizeof(char));
    strcpy(output, line0);
    return output;
    chdir(firstDirectory);

    return output;
}
void run_tag(int argc, char *argv[])
{
    if (argc == 2)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);

        FILE *file = fopen("TAG.txt", "r");
        char line[50];
        int n = 0;
        char **save = (char **)malloc(10 * sizeof(char *));
        for (int i = 0; i < 10; i++)
        {
            save[i] = (char *)malloc(30 * sizeof(char));
        }
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            strcpy(save[n], line);
            n++;
            fgets(line, sizeof(line), file);
            fgets(line, sizeof(line), file);
            fgets(line, sizeof(line), file);
            fgets(line, sizeof(line), file);
            fgets(line, sizeof(line), file);
        }
        fclose(file);
        int *which_line = organize(save, n);
        char line0[30];
        char line1[20];
        char line2[100];
        char line3[30];
        char line4[40];
        char line5[20];
        int K;
        for (int i = 0; i < n; i++)
        {
            file = fopen("TAG.txt", "r");
            K = 0;
            while (fgets(line0, sizeof(line0), file) != NULL)
            {
                fgets(line1, sizeof(line1), file);
                fgets(line2, sizeof(line2), file);
                fgets(line3, sizeof(line3), file);
                fgets(line4, sizeof(line4), file);
                fgets(line5, sizeof(line5), file);
                if (which_line[i] == K)
                {
                    printf("\033[36mTag name : \033[33m%s", line0);
                    printf("\033[36mCommit hash : \033[32m%s", line1);
                    printf("\033[36mTag message : \033[32m%s", line2);
                    printf("\033[36mName : \033[32m%s", line3);
                    printf("\033[36mGmail : \033[32m%s", line4);
                    printf("\033[36mTime : \033[32mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n\n[0m", line5[0], line5[1], line5[2], line5[3], line5[4], line5[5], line5[6], line5[7], line5[8], line5[9], line5[10], line5[11], line5[12], line5[13]);
                    break;
                }
                K++;
            }
            fclose(file);
        }
        free(save);
        free(which_line);
        chdir(firstDirectory);
    }
    else if (argc == 4 && strcmp(argv[2], "show") == 0)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);

        FILE *file = fopen("TAG.txt", "r");

        char line0[30];
        char line1[20];
        char line2[100];
        char line3[30];
        char line4[40];
        char line5[20];

        while (fgets(line0, sizeof(line0), file) != NULL)
        {
            line0[strlen(line0) - 1] = '\0';
            fgets(line1, sizeof(line1), file);
            fgets(line2, sizeof(line2), file);
            fgets(line3, sizeof(line3), file);
            fgets(line4, sizeof(line4), file);
            fgets(line5, sizeof(line5), file);
            if (strcmp(line0, argv[3]) == 0)
            {
                printf("\033[36mTag name : \033[33m%s\n", line0);
                printf("\033[36mCommit hash : \033[32m%s", line1);
                printf("\033[36mTag message : \033[32m%s", line2);
                printf("\033[36mName : \033[32m%s", line3);
                printf("\033[36mGmail : \033[32m%s", line4);
                printf("\033[36mTime : \033[32mY:%c%c%c%c M:%c%c D:%c%c H:%c%c m:%c%c S:%c%c\033\n\n[0m", line5[0], line5[1], line5[2], line5[3], line5[4], line5[5], line5[6], line5[7], line5[8], line5[9], line5[10], line5[11], line5[12], line5[13]);
                break;
            }
        }

        chdir(firstDirectory);
    }
    else if (strcmp(argv[2], "-a") == 0)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        FILE *file = fopen("TAG.txt", "r");
        int WHICH_LINE = searchInFile(file, argv[3]);
        fclose(file);
        if (WHICH_LINE != 0)
        {
            int flag = 0;
            for (int i = 0; i < argc; i++)
            {
                if (strcmp(argv[i], "-f") == 0)
                {
                    file = fopen("TAG.txt", "r");
                    removeLineFromFile(file, WHICH_LINE, "temp.txt");
                    fclose(file);
                    system("del TAG.txt");
                    rename("temp.txt", "TAG.txt");
                    file = fopen("TAG.txt", "r");
                    removeLineFromFile(file, WHICH_LINE, "temp.txt");
                    fclose(file);
                    system("del TAG.txt");
                    rename("temp.txt", "TAG.txt");
                    file = fopen("TAG.txt", "r");
                    removeLineFromFile(file, WHICH_LINE, "temp.txt");
                    fclose(file);
                    system("del TAG.txt");
                    rename("temp.txt", "TAG.txt");
                    file = fopen("TAG.txt", "r");
                    removeLineFromFile(file, WHICH_LINE, "temp.txt");
                    fclose(file);
                    system("del TAG.txt");
                    rename("temp.txt", "TAG.txt");
                    file = fopen("TAG.txt", "r");
                    removeLineFromFile(file, WHICH_LINE, "temp.txt");
                    fclose(file);
                    system("del TAG.txt");
                    rename("temp.txt", "TAG.txt");
                    file = fopen("TAG.txt", "r");
                    removeLineFromFile(file, WHICH_LINE, "temp.txt");
                    fclose(file);
                    system("del TAG.txt");
                    rename("temp.txt", "TAG.txt");
                    file = fopen("TAG.txt", "a");
                    fprintf(file, "%s\n", argv[3]);
                    fclose(file);
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                printf("\033[31mthe tag is already exist. use -f to overwrite\033[0m\n");
                return;
            }
        }
        else
        {
            file = fopen("TAG.txt", "a");
            fprintf(file, "%s\n", argv[3]);
            fclose(file);
        }
        int flag = 0;
        for (int i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "-c") == 0)
            {
                file = fopen("TAG.txt", "a");
                fprintf(file, "%s\n", argv[i + 1]);
                fclose(file);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            file = fopen("NOW.txt", "r");
            char line[20];
            fgets(line, sizeof(line), file);
            fclose(file);
            file = fopen("TAG.txt", "a");
            fprintf(file, "%s\n", line);
            fclose(file);
        }
        flag = 0;
        for (int i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "-m") == 0)
            {
                file = fopen("TAG.txt", "a");
                fprintf(file, "%s\n", argv[i + 1]);
                fclose(file);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            file = fopen("TAG.txt", "a");
            fprintf(file, "NO\n");
            fclose(file);
        }
        char *name = WHO_NAME();
        char *email = WHO_EMAIL();
        file = fopen("TAG.txt", "a");
        fprintf(file, "%s\n", name);
        fclose(file);
        free(name);
        file = fopen("TAG.txt", "a");
        fprintf(file, "%s\n", email);
        fclose(file);
        free(email);
        char *time = getCurrentTime();
        file = fopen("TAG.txt", "a");
        fprintf(file, "%s\n", time);
        fclose(file);
        free(time);

        chdir(firstDirectory);
    }
    else
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
}
int *organize(char **input, int n)
{
    int *output = (int *)malloc(20 * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        output[i] = i;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (strcmp(input[j], input[j - 1]) == -1)
            {
                output[j - 1] = j;
                output[j] = j - 1;
            }
        }
    }
    return output;
}
void run_diff(int argc, char *argv[])
{
    if (argc == 5 && strcmp(argv[2], "-f") == 0)
    {
        int x = file_line_count(argv[3]);
        int y = file_line_count(argv[4]);
        diff(argv[3], 1, x, argv[4], 1, y); //////?
    }
    else if (argc == 11 && strcmp(argv[2], "-f") == 0 && strcmp(argv[5], "-line1") == 0 && strcmp(argv[8], "-line2") == 0)
    {
        int x = atoi(argv[7]);
        int y = atoi(argv[10]);
        // printf("%d",x);
        if (file_line_count(argv[3]) < x)
        {
            x = file_line_count(argv[3]);
        }
        if (file_line_count(argv[4]) < y)
        {
            y = file_line_count(argv[4]);
        }
        diff(argv[3], atoi(argv[6]), x, argv[4], atoi(argv[9]), y);
    }
    else if (argc == 5 && strcmp(argv[2], "-c") == 0)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);

        chdir(argv[3]);
        all_stage();
        char **save_hash_1 = (char **)malloc(20 * sizeof(char *));
        for (int i = 0; i < 20; i++)
        {
            *(save_hash_1 + i) = (char *)malloc(20 * sizeof(char));
        }
        char **save_address_1 = (char **)malloc(20 * sizeof(char *));
        for (int i = 0; i < 20; i++)
        {
            *(save_address_1 + i) = (char *)malloc(50 * sizeof(char));
        }
        FILE *hash1 = fopen("allHASH.txt", "r");
        FILE *address1 = fopen("allADDRESS.txt", "r");
        int count1 = 0;
        char line[100];
        while (fgets(line, sizeof(line), hash1) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            strcpy(*(save_hash_1 + count1), line);
            fgets(line, sizeof(line), address1);
            line[strlen(line) - 1] = '\0';
            strcpy(*(save_address_1 + count1), line);
            count1++;
        }
        fclose(hash1);
        fclose(address1);
        chdir("..");
        ///////////////
        chdir(argv[4]);
        all_stage();
        char **save_hash_2 = (char **)malloc(20 * sizeof(char *));
        for (int i = 0; i < 20; i++)
        {
            *(save_hash_2 + i) = (char *)malloc(20 * sizeof(char));
        }
        char **save_address_2 = (char **)malloc(20 * sizeof(char *));
        for (int i = 0; i < 20; i++)
        {
            *(save_address_2 + i) = (char *)malloc(50 * sizeof(char));
        }
        FILE *hash2 = fopen("allHASH.txt", "r");
        FILE *address2 = fopen("allADDRESS.txt", "r");
        int count2 = 0;
        while (fgets(line, sizeof(line), hash2) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            strcpy(*(save_hash_2 + count2), line);
            fgets(line, sizeof(line), address2);
            line[strlen(line) - 1] = '\0';
            strcpy(*(save_address_2 + count2), line);
            count2++;
        }
        fclose(hash2);
        fclose(address2);
        chdir("..");
        //////////////////
        for (int i = 0; i < count1; i++)
        {
            int flag = 0;
            for (int j = 0; j < count2; j++)
            {
                if (strcmp(*(save_address_1 + i), *(save_address_2 + j)) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                printf("\033[32m%s\n\033[0m", *(save_address_1 + i));
            }
        }
        for (int i = 0; i < count2; i++)
        {
            int flag = 0;
            for (int j = 0; j < count1; j++)
            {
                if (strcmp(*(save_address_2 + i), *(save_address_1 + j)) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                printf("\033[35m%s\n\033[0m", *(save_address_2 + i));
            }
        }
        for (int i = 0; i < count1; i++)
        {
            int flag = 0;
            int k;
            for (int j = 0; j < count2; j++)
            {
                if (strcmp(*(save_address_1 + i), *(save_address_2 + j)) == 0)
                {
                    flag = 1;
                    k = j;
                    break;
                }
            }
            if (flag == 1)
            {
                char name[100];
                for (int j = strlen(*(save_address_1 + i)) - 1; j >= 0; j--)
                {
                    if (*(*(save_address_1 + i) + j) == '\\')
                    {
                        name[-j - 1 + strlen(*(save_address_1 + i))] = '\0';
                        break;
                    }
                    name[-j - 1 + strlen(*(save_address_1 + i))] = *(*(save_address_1 + i) + j);
                }
                reverseString(name);
                char first[100];
                char second[100];
                strcpy(first, *(save_hash_1 + i));
                strcat(first, "\\");
                strcat(first, name);
                strcpy(second, *(save_hash_2 + k));
                strcat(second, "\\");
                strcat(second, name);
                diff(first, 1, file_line_count(first), second, 1, file_line_count(second));
            }
        }
        chdir(firstDirectory);
    }
    else
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
}
int file_line_count(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\033[31mthere is no file with given name\033[0m\n");
    }
    char line[200];
    int line_counter = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_counter++;
    }
    return line_counter;
}
int ADD_COUNT(char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, "ADD") == 0)
        {
            count++;
        }
    }
    fclose(file);
    return count;
}
void diff(char *file1, int file1_begin, int file1_end, char *file2, int file2_begin, int file2_end)
{
    FILE *file_1 = fopen(file1, "r");
    FILE *file_2 = fopen(file2, "r");
    char line1[100];
    char line2[100];

    for (int i = 0; i < file1_begin; i++)
    {
        fgets(line1, sizeof(line1), file_1);
    }
    for (int i = 0; i < file2_begin; i++)
    {
        fgets(line2, sizeof(line2), file_2);
    }
    int X = file1_begin;
    int Y = file2_begin;
    for (int i = file1_begin + file2_begin; i < file1_end + file2_end; i++)
    {
        // for (int j = file2_begin; j < file2_end; j++)
        //{
        // if (X == file1_end || Y == file2_end)
        //{
        //     break;
        // }
        // line1[strlen(line1) - 1] = '\0';
        // line2[strlen(line2) - 1] = '\0';
        if (check_NULL_space(line1) == 1 && check_NULL_space(line2) == 0)
        {
            fgets(line2, sizeof(line2), file_2);
            Y++;
        }
        else if (check_NULL_space(line1) == 0 && check_NULL_space(line2) == 1)
        {
            fgets(line1, sizeof(line1), file_1);
            X++;
        }
        else if (check_NULL_space(line1) == 0 && check_NULL_space(line2) == 0)
        {
            fgets(line1, sizeof(line1), file_1);
            X++;
            fgets(line2, sizeof(line2), file_2);
            Y++;
        }
        else if (check_NULL_space(line1) == 1 && check_NULL_space(line2) == 1)
        {
            if (strcmp(line1, line2) != 0)
            {
                if (X <= file1_end)
                {
                    printf("\033[32m%s - %d\n%s\n\033[0m", file1, X, line1);
                }
                if (Y <= file2_end)
                {
                    printf("\033[36m%s - %d\n%s\n--------------------\n\033[0m", file2, Y, line2);
                }
                fgets(line1, sizeof(line1), file_1);
                fgets(line2, sizeof(line2), file_2);
            }
            X++;
            Y++;
        }
        //}
        // if (X == file1_end || Y == file2_end)
        //{
        //    break;
        //}
    }
}
int check_NULL_space(char *input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] != '\n' && input[i] != ' ' && input[i] != '\t')
        {
            return 1;
        }
    }
    return 0;
}
void run_merge(int argc, char *argv[])
{
    if (argc == 5 && strcmp(argv[2], "-b") == 0)
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);

        char *branch1 = branch_head_hash(argv[3]);
        char *branch2 = branch_head_hash(argv[4]);
        char line[100];
        chdir(branch1);
        all_stage();
        char **save_hash_1 = (char **)malloc(20 * sizeof(char *));
        for (int i = 0; i < 20; i++)
        {
            *(save_hash_1 + i) = (char *)malloc(20 * sizeof(char));
        }
        char **save_address_1 = (char **)malloc(20 * sizeof(char *));
        for (int i = 0; i < 20; i++)
        {
            *(save_address_1 + i) = (char *)malloc(50 * sizeof(char));
        }
        FILE *hash1 = fopen("allHASH.txt", "r");
        FILE *address1 = fopen("allADDRESS.txt", "r");
        int count1 = 0;
        while (fgets(line, sizeof(line), hash1) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            strcpy(*(save_hash_1 + count1), line);
            fgets(line, sizeof(line), address1);
            line[strlen(line) - 1] = '\0';
            strcpy(*(save_address_1 + count1), line);
            count1++;
        }
        fclose(hash1);
        fclose(address1);
        chdir("..");
        /////////////
        chdir(branch2);
        all_stage();
        char **save_hash_2 = (char **)malloc(20 * sizeof(char *));
        for (int i = 0; i < 20; i++)
        {
            *(save_hash_2 + i) = (char *)malloc(20 * sizeof(char));
        }
        char **save_address_2 = (char **)malloc(20 * sizeof(char *));
        for (int i = 0; i < 20; i++)
        {
            *(save_address_2 + i) = (char *)malloc(50 * sizeof(char));
        }
        FILE *hash2 = fopen("allHASH.txt", "r");
        FILE *address2 = fopen("allADDRESS.txt", "r");
        int count2 = 0;
        while (fgets(line, sizeof(line), hash2) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            strcpy(*(save_hash_2 + count2), line);
            fgets(line, sizeof(line), address2);
            line[strlen(line) - 1] = '\0';
            strcpy(*(save_address_2 + count2), line);
            count2++;
        }
        fclose(hash2);
        fclose(address2);
        chdir("..");
        ////////////////
        for (int i = 0; i < count2; i++)
        {
            int flag = 0;
            int k;
            for (int j = 0; j < count1; j++)
            {
                if (strcmp(*(save_address_2 + i), *(save_address_1 + j)) == 0)
                {
                    k = j;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                copy_folder(*(save_hash_2 + i), *(save_address_2 + i));
            }
            else
            {
                diff(*(save_address_1 + k), 1, file_line_count(*(save_address_1 + k)),
                     *(save_address_2 + i), 1, file_line_count(*(save_address_2 + i)));
                int x;
                scanf("%d", &x);
                if (x == 1)
                {
                    printf("\033[32msuccessfully\033[0m");
                }
                else if (x == 2)
                {
                    copy_folder(*(save_hash_2 + i), *(save_address_2 + i));
                }
            }
        }
        chdir(firstDirectory);
    }
    else
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
}
char *branch_head_hash(char *branch_name) // remember to free
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);
    FILE *file = fopen("COMMIT.txt", "r");
    char line0[20];
    char line1[30];

    char *save = (char *)malloc(20 * sizeof(char));
    while (fgets(line0, sizeof(line0), file) != NULL)
    {
        fgets(line1, sizeof(line1), file);
        line1[strlen(line1) - 1] = '\0';
        if (strcmp(line1, branch_name) == 0)
        {
            line0[strlen(line0) - 1] = '\0';
            strcpy(save, line0);
        }
        fgets(line0, sizeof(line0), file);
        fgets(line0, sizeof(line0), file);
        fgets(line0, sizeof(line0), file);
        fgets(line0, sizeof(line0), file);
    }
    fclose(file);
    chdir(firstDirectory);
    return save;
}
void all_stage()
{
    FILE *stagehash = fopen("stageHASH.txt", "r");
    FILE *stageaddress = fopen("stageADDRESS.txt", "r");

    char **save_hash = (char **)malloc(20 * sizeof(char *));
    for (int i = 0; i < 20; i++)
    {
        *(save_hash + i) = (char *)malloc(20 * sizeof(char));
    }
    char **save_address = (char **)malloc(20 * sizeof(char *));
    for (int i = 0; i < 20; i++)
    {
        *(save_address + i) = (char *)malloc(50 * sizeof(char));
    }
    char hash[20];
    char address[50];
    int X = 0;
    while (fgets(hash, sizeof(hash), stagehash) != NULL)
    {
        fgets(address, sizeof(address), stageaddress);
        hash[strlen(hash) - 1] = '\0';
        address[strlen(address) - 1] = '\0';
        if (strcmp(hash, "ADD") != 0)
        {
            strcpy(*(save_hash + X), hash);
            strcpy(*(save_address + X), address);
            X++;
        }
    }
    fclose(stagehash);
    fclose(stageaddress);
    FILE *all_stage_hash = fopen("allHASH.txt", "w");
    FILE *all_stage_address = fopen("allADDRESS.txt", "w");
    for (int i = X - 1; i >= 0; i--)
    {
        int flag = 0;
        for (int j = X - 1; j > i; j--)
        {
            if (strcmp(*(save_address + i), *(save_address + j)) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            fprintf(all_stage_hash, "%s\n", *(save_hash + i));
            fprintf(all_stage_address, "%s\n", *(save_address + i));
        }
    }
    fclose(all_stage_hash);
    fclose(all_stage_address);
    free(save_address);
    free(save_hash);
}
int check_invalid_alias(char *input)
{
    char temp[100];
    strcpy(temp, input);
    char *token = strtok(temp, " ");
    if (strcmp(token, "neogit") != 0)
    {
        return 0;
    }
    else
    {
        token = strtok(NULL, " ");
        if (strcmp(token, "init") == 0 || strcmp(token, "config") == 0 || strcmp(token, "add") == 0 || strcmp(token, "reset") == 0 || strcmp(token, "status") == 0 || strcmp(token, "commit") == 0 || strcmp(token, "set") == 0 || strcmp(token, "replace") == 0 || strcmp(token, "remove") == 0 || strcmp(token, "log") == 0 || strcmp(token, "branch") == 0 || strcmp(token, "checkout") == 0 || strcmp(token, "tag") == 0 || strcmp(token, "diff") == 0 || strcmp(token, "merge") == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
int run_alias(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 0;
    }
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));

    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);
    FILE *file = fopen("alias.txt", "r");
    char alias[30];
    char command[30];
    chdir(firstDirectory);
    while (fgets(alias, sizeof(alias), file) != NULL)
    {
        fgets(command, sizeof(command), file);
        alias[strlen(alias) - 1] = '\0';
        command[strlen(command) - 1] = '\0';
        if (strcmp(alias, argv[1]) == 0)
        {
            printf("%s", command);
            system(command);
            return 1;
        }
    }
    fclose(file);
    temp = where_is_global_information();
    chdir(temp);
    free(temp);
    file = fopen("aliasGLOB.txt", "r");
    chdir(firstDirectory);
    while (fgets(alias, sizeof(alias), file) != NULL)
    {
        fgets(command, sizeof(command), file);
        alias[strlen(alias) - 1] = '\0';
        command[strlen(command) - 1] = '\0';
        if (strcmp(alias, argv[1]) == 0)
        {
            system(command);
            return 1;
        }
    }
    fclose(file);
    chdir(firstDirectory);
    return 0;
}
void reverseString(char str[])
{
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}
void run_precommit(int argc, char *argv[])
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);

    if (argc == 4 && strcmp(argv[2], "hooks") == 0 && strcmp(argv[3], "list") == 0)
    {
        printf("\033[36mhook-id\n--------------\n\033[0m");
        printf("\033[33mtodo-check\n");
        printf("eof-blank-space\n");
        printf("format-check\n");
        printf("balance-braces\n");
        printf("indentation-check\n");
        printf("static-error-check\n");
        printf("file-size-check\n");
        printf("character-limit\n");
        printf("time-limit\n\033[0m");
    }
    else if (argc == 4 && strcmp(argv[2], "applied") == 0 && strcmp(argv[3], "hooks") == 0)
    {
        FILE *file = fopen("appliedhooks.txt", "r");
        char line[30];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("\033[32m%s\033[0m", line);
        }
        fclose(file);
    }
    else if (argc == 5 && strcmp(argv[2], "add") == 0 && strcmp(argv[3], "hook") == 0)
    {
        FILE *file = fopen("appliedhooks.txt", "a");
        fprintf(file, "%s\n", argv[4]);
        fclose(file);
        printf("\033[32msuccessfully\n\033[0m");
    }
    else if (argc == 5 && strcmp(argv[2], "remove") == 0 && strcmp(argv[3], "hook") == 0)
    {
        FILE *file = fopen("appliedhooks.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            if (strcmp(line, argv[4]) == 0)
            {
                continue;
            }
            fprintf(temp, "%s\n", line);
        }
        fclose(file);
        fclose(temp);
        system("del appliedhooks.txt");
        rename("temp.txt", "appliedhooks.txt");
        printf("\033[32msuccessfully\n\033[0m");
    }
    else if (argc == 2 && strcmp(argv[1], "pre-commit") == 0)
    {
        all_stage();
        FILE *file = fopen("allADDRESS.txt", "r");
        char line[100];
        char hook_line[100];
        int flag = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            FILE *hook = fopen("appliedhooks.txt", "r");
            while (fgets(hook_line, sizeof(hook_line), hook) != NULL)
            {
                hook_line[strlen(hook_line) - 1] = '\0';
                if (strcmp(hook_line, "todo-check") == 0)
                {
                    printf("\033[35m%s\n\033[0m", line);
                    switch (todo_check(line))
                    {
                    case -1:
                        printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                        flag = 1;
                        break;
                    case 0:
                        printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                        break;
                    case 1:
                        printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                        break;
                    }
                }
                else if (strcmp(hook_line, "eof-blank-space") == 0)
                {
                    printf("\033[35m%s\n\033[0m", line);
                    switch (eof_blank_space(line))
                    {
                    case -1:
                        printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                        flag = 1;
                        break;
                    case 0:
                        printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                        break;
                    case 1:
                        printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                        break;
                    }
                }
                else if (strcmp(hook_line, "format-check") == 0)
                {
                    printf("\033[35m%s\n\033[0m", line);
                    switch (format_check(line))
                    {
                    case -1:
                        printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                        flag = 1;
                        break;
                    case 0:
                        printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                        break;
                    case 1:
                        printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                        break;
                    }
                }
                else if (strcmp(hook_line, "balance-braces") == 0)
                {
                    printf("\033[35m%s\n\033[0m", line);
                    switch (balance_braces(line))
                    {
                    case -1:
                        printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                        flag = 1;
                        break;
                    case 0:
                        printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                        break;
                    case 1:
                        printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                        break;
                    }
                }
                else if (strcmp(hook_line, "static-error-check") == 0)
                {
                    printf("\033[35m%s\n\033[0m", line);
                    switch (static_error_check(line))
                    {
                    case -1:
                        printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                        flag = 1;
                        break;
                    case 0:
                        printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                        break;
                    case 1:
                        printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                        break;
                    }
                }
                else if (strcmp(hook_line, "file-size-check") == 0)
                {
                    printf("\033[35m%s\n\033[0m", line);
                    switch (file_size_check(line))
                    {
                    case -1:
                        printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                        flag = 1;
                        break;
                    case 0:
                        printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                        break;
                    case 1:
                        printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                        break;
                    }
                }
                else if (strcmp(hook_line, "character-limit") == 0)
                {
                    printf("\033[35m%s\n\033[0m", line);
                    switch (character_limit(line))
                    {
                    case -1:
                        printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                        flag = 1;
                        break;
                    case 0:
                        printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                        break;
                    case 1:
                        printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                        break;
                    }
                }
            }
            fclose(hook);
        }
        fclose(file);
        system("del allADDRESS.txt");
        system("del allHASH.txt");
        if (flag == 1)
        {
            printf("\033[31mSome hooks failed. be carefull for commit\n\033[0m");
        }
    }
    else if (argc > 3 && strcmp(argv[2], "-f") == 0)
    {
        for (int i = 3; i < argc; i++)
        {
            char *file_path = (char *)malloc(100 * sizeof(char));
            strcpy(file_path, firstDirectory);
            strcat(file_path, "\\");
            strcat(file_path, argv[i]);
            FILE *file = fopen(file_path, "r");
            if (file == NULL)
            {
                fclose(file);
                printf("\033[31mNo such file\n\033[0m");
            }
            else
            {
                fclose(file);
                all_stage();
                file = fopen("allADDRESS.txt", "r");
                if (searchInFile(file, file_path) == 0)
                {
                    printf("\033[31mit is not in stage\n\033[0m");
                    fclose(file);
                }
                else
                {
                    fclose(file);
                    int flag = 0;
                    char hook_line[100];
                    FILE *hook = fopen("appliedhooks.txt", "r");
                    while (fgets(hook_line, sizeof(hook_line), hook) != NULL)
                    {
                        hook_line[strlen(hook_line) - 1] = '\0';
                        if (strcmp(hook_line, "todo-check") == 0)
                        {
                            printf("\033[35m%s\n\033[0m", file_path);
                            switch (todo_check(file_path))
                            {
                            case -1:
                                printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                                flag = 1;
                                break;
                            case 0:
                                printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                                break;
                            case 1:
                                printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                                break;
                            }
                        }
                        else if (strcmp(hook_line, "eof-blank-space") == 0)
                        {
                            printf("\033[35m%s\n\033[0m", file_path);
                            switch (eof_blank_space(file_path))
                            {
                            case -1:
                                printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                                flag = 1;
                                break;
                            case 0:
                                printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                                break;
                            case 1:
                                printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                                break;
                            }
                        }
                        else if (strcmp(hook_line, "format-check") == 0)
                        {
                            printf("\033[35m%s\n\033[0m", file_path);
                            switch (format_check(file_path))
                            {
                            case -1:
                                printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                                flag = 1;
                                break;
                            case 0:
                                printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                                break;
                            case 1:
                                printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                                break;
                            }
                        }
                        else if (strcmp(hook_line, "balance-braces") == 0)
                        {
                            printf("\033[35m%s\n\033[0m", file_path);
                            switch (balance_braces(file_path))
                            {
                            case -1:
                                printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                                flag = 1;
                                break;
                            case 0:
                                printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                                break;
                            case 1:
                                printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                                break;
                            }
                        }
                        else if (strcmp(hook_line, "static-error-check") == 0)
                        {
                            printf("\033[35m%s\n\033[0m", file_path);
                            switch (static_error_check(file_path))
                            {
                            case -1:
                                printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                                flag = 1;
                                break;
                            case 0:
                                printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                                break;
                            case 1:
                                printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                                break;
                            }
                        }
                        else if (strcmp(hook_line, "file-size-check") == 0)
                        {
                            printf("\033[35m%s\n\033[0m", file_path);
                            switch (file_size_check(file_path))
                            {
                            case -1:
                                printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                                flag = 1;
                                break;
                            case 0:
                                printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                                break;
                            case 1:
                                printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                                break;
                            }
                        }
                        else if (strcmp(hook_line, "character-limit") == 0)
                        {
                            printf("\033[35m%s\n\033[0m", file_path);
                            switch (character_limit(file_path))
                            {
                            case -1:
                                printf("\033[36m%s\t\033[31mFAILED\n\033[0m", hook_line);
                                flag = 1;
                                break;
                            case 0:
                                printf("\033[36m%s\t\033[33mSKIPPED\n\033[0m", hook_line);
                                break;
                            case 1:
                                printf("\033[36m%s\t\033[32mPASSSED\n\033[0m", hook_line);
                                break;
                            }
                        }
                    }
                    fclose(hook);
                    if (flag == 1)
                    {
                        printf("\033[31mSome hooks failed. be carefull for commit\n\033[0m");
                    }
                }
                system("del allADDRESS.txt");
                system("del allHASH.txt");
            }
        }
    }

    chdir(firstDirectory);
}
char *what_is_file_format(char *file_path)
{
    char *format = (char *)malloc(50 * sizeof(char));

    for (int i = strlen(file_path) - 1; i >= 0; i--)
    {
        if (file_path[i] == '.')
        {
            format[-i - 1 + strlen(file_path)] = '\0';
            break;
        }
        format[-i - 1 + strlen(file_path)] = file_path[i];
    }
    reverseString(format);
    return format;
}
int todo_check(char *file_path) ///////////////////////need update
{
    if (strcmp(what_is_file_format(file_path), "c") != 0 && strcmp(what_is_file_format(file_path), "cpp") != 0 && strcmp(what_is_file_format(file_path), "txt") != 0)
    {
        return 0;
    }
    else
    {
        char line[256];
        FILE *file = fopen(file_path, "r");
        int flag = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            for (int i = 0; i < strlen(line); i++)
            {
                if (line[0] == ' ' && line[1] == 'T' && line[2] == 'O' && line[3] == 'D' && line[4] == 'O' && line[5] == ' ')
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                return -1;
                break;
            }
        }
        if (flag == 0)
        {
            return 1;
        }
    }
}
int eof_blank_space(char *file_path)
{
    if (strcmp(what_is_file_format(file_path), "c") != 0 && strcmp(what_is_file_format(file_path), "cpp") != 0 && strcmp(what_is_file_format(file_path), "txt") != 0)
    {
        return 0;
    }
    else
    {
        char line[256];
        FILE *file = fopen(file_path, "r");
        int flag;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            if (check_NULL_space(line) == 1)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
        if (flag == 1)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}
int format_check(char *file_path)
{
    char *format = what_is_file_format(file_path);
    if (strcmp(format, "c") != 0 && strcmp(format, "cpp") != 0 && strcmp(format, "txt") != 0 && strcmp(format, "mp3") != 0 &&
        strcmp(format, "mp4") != 0 && strcmp(format, "wav") != 0 && strcmp(format, "pdf") != 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
int balance_braces(char *file_path)
{
    if (strcmp(what_is_file_format(file_path), "c") != 0 && strcmp(what_is_file_format(file_path), "cpp") != 0 && strcmp(what_is_file_format(file_path), "txt") != 0)
    {
        return 0;
    }
    else
    {
        char line[256];
        FILE *file = fopen(file_path, "r");
        int x = 0;
        int X = 0;
        int y = 0;
        int Y = 0;
        int z = 0;
        int Z = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            for (int i = 0; i < strlen(line); i++)
            {
                if (line[i] == '(')
                {
                    x++;
                }
                if (line[i] == ')')
                {
                    X++;
                }
                if (line[i] == '[')
                {
                    y++;
                }
                if (line[i] == ']')
                {
                    Y++;
                }
                if (line[i] == '{')
                {
                    z++;
                }
                if (line[i] == '}')
                {
                    Z++;
                }
            }
        }
        if (x == X && y == Y && z == Z)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}
int getFileSize(char *filename)
{
    FILE *file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);
    return fileSize;
}
int file_size_check(char *file_path)
{
    if (getFileSize(file_path) > 5000000)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
int countCharacters(char *filename)
{
    FILE *file = fopen(filename, "r");
    int charCount = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        charCount++;
    }
    fclose(file);
    return charCount;
}
int character_limit(char *file_path)
{
    if (strcmp(what_is_file_format(file_path), "c") != 0 && strcmp(what_is_file_format(file_path), "cpp") != 0 && strcmp(what_is_file_format(file_path), "txt") != 0)
    {
        return 0;
    }
    else
    {
        if (countCharacters(file_path) > 20000)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
}
int static_error_check(char *file_path)
{
    if (strcmp(what_is_file_format(file_path), "c") == 0)
    {
        char *temp = (char *)malloc(100 * sizeof(char));
        strcpy(temp, file_path);
        temp[strlen(temp) - 1] = '\0'; ///////belabela.
        strcat(temp, "exe");
        char *command = (char *)malloc(100 * sizeof(char));
        strcpy(command, "del ");
        strcat(command, temp);
        free(command);
        strcpy(command, "gcc ");
        strcat(command, file_path);
        strcat(command, " -o ");
        strcat(command, temp);
        system(command);
        FILE *file = fopen(temp, "rb");
        if (file == NULL)
        {
            return -1;
        }
        else
        {
            fclose(file);
            return 1;
        }
    }
    else if (strcmp(what_is_file_format(file_path), "cpp") == 0)
    {
        char *temp = (char *)malloc(100 * sizeof(char));
        strcpy(temp, file_path);
        temp[strlen(temp) - 3] = '\0'; ///////belabela.
        strcat(temp, "exe");
        char *command = (char *)malloc(100 * sizeof(char));
        strcpy(command, "del ");
        strcat(command, temp);
        free(command);
        strcpy(command, "gcc ");
        strcat(command, file_path);
        strcat(command, " -o ");
        strcat(command, temp);
        system(command);
        FILE *file = fopen(temp, "rb");
        if (file == NULL)
        {
            return -1;
        }
        else
        {
            fclose(file);
            return 1;
        }
    }
    else
    {
        return 0;
    }
}
void run_grep(int argc, char *argv[])
{
    char firstDirectory[FILENAME_MAX];
    getcwd(firstDirectory, sizeof(firstDirectory));
    char *temp = where_is_neogit();
    chdir(temp);
    chdir(".neogit");
    free(temp);

    char *file_path = (char *)malloc(100 * sizeof(char));
    strcpy(file_path, firstDirectory);
    strcat(file_path, "\\");
    strcat(file_path, argv[3]);

    if (argc == 6)
    {
        grep_for_filepath(file_path, argv[5], 0);
    }
    else if (argc == 7 && strcmp(argv[6], "-n") == 0)
    {
        grep_for_filepath(file_path, argv[5], 1);
    }
    else if (argc == 8 && strcmp(argv[6], "-c") == 0)
    {
        chdir(argv[7]);
        all_stage();
        char hash[20];
        char address[100];
        FILE *hashfile = fopen("allHASH.txt", "r");
        FILE *addressfile = fopen("allADDRESS.txt", "r");
        while (fgets(hash, sizeof(hash), hashfile) != NULL)
        {
            fgets(address, sizeof(address), addressfile);
            hash[strlen(hash) - 1] = '\0';
            address[strlen(address) - 1] = '\0';
            if (strcmp(file_path, address) == 0)
            {
                break;
            }
        }
        fclose(hashfile);
        fclose(addressfile);
        chdir("..");
        char *path = (char *)malloc(100 * sizeof(char));
        strcpy(path, hash);
        strcat(path, "\\");
        strcat(path, argv[3]);
        grep_for_filepath(path, argv[5], 0);
    }
    else if (argc == 9 && strcmp(argv[6], "-c") == 0 && strcmp(argv[8], "-n") == 0)
    {
        chdir(argv[7]);
        all_stage();
        char hash[20];
        char address[100];
        FILE *hashfile = fopen("allHASH.txt", "r");
        FILE *addressfile = fopen("allADDRESS.txt", "r");
        while (fgets(hash, sizeof(hash), hashfile) != NULL)
        {
            fgets(address, sizeof(address), addressfile);
            hash[strlen(hash) - 1] = '\0';
            address[strlen(address) - 1] = '\0';
            if (strcmp(file_path, address) == 0)
            {
                break;
            }
        }
        fclose(hashfile);
        fclose(addressfile);
        chdir("..");
        char *path = (char *)malloc(100 * sizeof(char));
        strcpy(path, hash);
        strcat(path, "\\");
        strcat(path, argv[3]);
        grep_for_filepath(path, argv[5], 1);
    }
    else
    {
        printf("\033[31mplease enter a valid command\033[0m\n");
    }
    chdir(firstDirectory);
}
void grep_for_filepath(char *file_path, char *word, int yes_or_not)
{
    char line[256];
    FILE *file = fopen(file_path, "r");
    int line_count = 0;
    int flag = 0;
    int FLAG = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_count++;
        line[strlen(line) - 1] = '\0';
        FLAG = 0;
        if (strstr(line, word) != NULL)
        {
            for (int i = 0; i < strlen(line); i++)
            {
                flag = 0;
                for (int j = 0; j < strlen(word); j++)
                {
                    if (line[i + j] != word[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1)
                {
                    printf("%c", line[i]);
                }
                else
                {
                    for (int j = 0; j < strlen(word); j++)
                    {
                        printf("\033[36m%c\033[0m", line[i + j]);
                    }
                    i += strlen(word) - 1;
                    FLAG = 1;
                }
            }
        }
        if (yes_or_not == 1 && FLAG == 1)
        {
            printf("\t%d\n", line_count);
        }
    }
}
