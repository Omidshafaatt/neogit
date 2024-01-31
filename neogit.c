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
        int flag = 0;
        int WHICH_LINE = 1;
        char *temp = modification_time(input);
        while (fgets(line1, sizeof(line1), stagehash) != NULL)
        {
            line1[strlen(line1) - 1] = '\0';
            if (strcmp(line1, "ADD") == 0)
            {
                flag++;
            }
            if (flag == HOW_MANY_ADD - 1 && strcmp(temp, line1) == 0)
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
                strcat(temp_rmdir, line1);
                system(temp_rmdir);
                free(temp_rmdir);
                break;
            }
            WHICH_LINE++;
        }
        free(temp);
        // fclose(stagehash);
        // fclose(stageaddress);
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
        printf("\033[31mplease enter a valid command\033\n[0m");
    }
    else
    {
        char firstDirectory[FILENAME_MAX];
        getcwd(firstDirectory, sizeof(firstDirectory));
        char *temp = where_is_neogit();
        chdir(temp);
        chdir(".neogit");
        free(temp);
        FILE *all = fopen("ALL.txt", "w");
        listFilesRecursively("..", all);
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
            if (searchInFile(stagehash, temp) == 0)
            {
                printf("\033[32m+\033[0m\n");
            }
            else
            {
                printf("-");
                if (searchInFile(stageaddress, line) == 0)
                {
                    printf("M\n");
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
