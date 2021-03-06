#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "./include/myshlib.h"
#define MAX_DIR_DEPTH (256)

char *dir_stack[MAX_DIR_DEPTH];
unsigned current_depth = 0;

char* my_getcwd(char * buf, size_t size);
char *find_name_byino(ino_t ino);
ino_t get_ino_byname(char *filename);

int main(int argc, char **argv)
{
    char buf[1024];
    char *cwd = my_getcwd(buf, sizeof(buf));
    if (NULL == cwd)
    {
        perror("Get current working directory fail.\n");
        exit(-1);
    }
    else
    {
        printf("%s\n", cwd);
    }
    return 0;
}

// "." and ".." is special filename can be used to get current inode_num and parent inode_num
char* my_getcwd(char * buf, size_t size)
{
    while(1)
    {
        ino_t current_ino = get_ino_byname(".");
        ino_t parent_ino = get_ino_byname("..");

        if (current_ino == parent_ino) // reach the root dir
            break;

        chdir("..");
        dir_stack[current_depth++] = find_name_byino(current_ino);
        if (current_depth >= MAX_DIR_DEPTH) //set MAX_DIR_DEPTH to prevent stack overflow
        {
            fprintf(stderr, "Directory tree is too deep.\n");
            exit(-1);
        }
    }
//    int i = current_depth-1;
//    for (i = current_depth-1; i>=0; i--)
//    {
//        fprintf(stdout, "/%s", dir_stack[i]);
//    }
//    fprintf(stdout, "%s\n", current_depth==0?"/":"");
    int i = current_depth-1;
    int offset=0;
    char* pre=buf;
    for (i = current_depth-1; i>=0; i--)
    {
        offset=strlen(dir_stack[i]);
        strcpy(pre,"/");
        pre+=1;
        strcpy(pre,dir_stack[i]);
        pre+=offset;
    }
    if(current_depth==0)
    {
        strcpy(pre,"/\n");
    }
    else
    {
        strcpy(pre,"\n");
    }
    return buf;
}


// get inode-num by name
ino_t get_ino_byname(char *filename)
{
    struct stat file_stat;
    if (0 != stat(filename, &file_stat))
    {
        perror("stat");
        exit(-1);
    }
    return file_stat.st_ino;
}


char *find_name_byino(ino_t ino)
{
    DIR *dp = NULL;
    struct dirent *dptr = NULL;
    char *filename = NULL;
    if (NULL == (dp = opendir(".")))
    {
        fprintf(stderr, "Can not open Current Directory\n");
        exit(-1);
    }
    else
    {
        while (NULL != (dptr = readdir(dp)))
        {
            if (dptr->d_ino == ino)
            {
                filename = strdup(dptr->d_name); // strdup is like strcpy but called malloc in it
                break;
            }
        }
        closedir(dp);
    }
    return filename;
}

