//
// Created by wings on 18-4-22.
//
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH_SIZE 1024
#define BUF_SIZE 1024
int main(int argc, char **argv)
{
    DIR *dir;
    struct dirent *entry;
    FILE *fp;
    char path[MAX_PATH_SIZE];
    char buf[BUF_SIZE];
    char temp[30];
    if ((dir = opendir("/proc")) == NULL)
    {
        perror("fail to open dir");
        exit(-1);
    }
    printf("name:\t\tpid:\n");
    while ((entry = readdir(dir)) != NULL)
    {
        if(entry->d_name[0] == '.') //skip the current path, proce directory does not have a parent directory
            continue;
        if( (entry->d_name[0] <='0' ) || (entry->d_name[0] >= '9'))
            continue;
        sprintf(path, "/proc/%s/task/%s/status", entry->d_name,entry->d_name);
        fp = fopen(path, "r");
        if(fp == NULL)
        {
            perror("fail to open");
            exit(1);
        }
        while(fgets(buf, BUF_SIZE, fp) != NULL)
        {
            if(buf[0] == 'N' && buf[1] == 'a' && buf[2] == 'm' && buf[3] == 'e') //name
            {
                int i=6;
//                while(buf[i]!='\n')
//                {
//                    putc(buf[i],temp);
//
//                    printf("%c", buf[i]);
//                    i++;
//                }
                strcpy(temp,buf+6);
                temp[strlen(temp)-1]=0;
                printf("%-15s",temp);
            }
            if(buf[0] == 'P' && buf[1] == 'i' && buf[2] == 'd')
            {
                printf("\t\t%s", &buf[5]); // output pid then break
                break;
            }
        }
        fclose(fp);
    }
    closedir( dir );
    return 0;
}
