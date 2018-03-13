/* FileName:myls.cpp
 * Author:Hover
 * E-Mail:hover@hust.edu.cn
 * GitHub:HoverWings
 * Reference:《UNIX环境高级编程》
 */
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

void do_ls(char[]);

int main(int argc,char *argv[])
{
    if(argc==1)
    {
        do_ls(".");
    }
    else
    {
        while(argc--)
        {
            printf("%s:\n",*++argv);
            do_ls(*argv);
        }
    }
}

/*
  struct dirent
  {
    ino_t          d_ino;        //inode number
    off_t          d_off;        //offset to the next dirent
    unsigned short d_reclen;     //length of this record
    unsigned char  d_type;       //type of file; not supportedby all file system types
    char           d_name[256];  //filename
    };
*/



void do_ls(char dirName[])
{
    DIR *dir_ptr;
    struct dirent *direntp;

    if((dir_ptr=opendir(dirName))==NULL)
    {
        fprintf(stderr,"myShCommand:cannot open %s\n",dirName);
    }
    else
    {
        while((direntp=readdir(dir_ptr))!=NULL)
        {
            printf("%s\n",direntp->d_name);
        }
        closedir(dir_ptr);
    }
}
















































