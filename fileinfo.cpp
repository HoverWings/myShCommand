/* FileName:fileinfo.cpp
 * Author:Hover
 * E-Mail:hover@hust.edu.cn
 * GitHub:HoverWings
 */
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

void show_stat_info(char * fname,struct stat *buf);

int main(int argc, char *argv[])
{
    struct stat info;
    if(argc>1)
    {
        if(stat(argv[1],&info)!=-1)
        {
            show_stat_info(argv[1],&info);
        }
    }
    else
    {
        perror(argv[1]);
    }
    return 1;//WHY?
}


void show_stat_info(char * fname,struct stat *buf)
{
    printf("  mode:  %o\n",buf->st_mode);
    printf(" links:  %d\n",buf->st_nlink);
    printf("  user:  %d\n",buf->st_uid);
    printf("  group: %d\n",buf->st_gid);
    printf("   size: %d\n",buf->st_size);
    printf("modtime: %d\n",buf->st_mtime);
    printf("  group: %s\n",fname);
}



/*
struct stat
{
    __dev_t st_dev;                 /* Device.
    __mode_t  st_mode;              /* 文件类型和许可权限
    __nlink_t st_nlink;             /* 文件链接数
    __uid_t   st_uid;               /* 文件属主id
    __gid_t   st_gid;               /* 文件属主所在组的id
    __dev_t   st_rdev;              /* 文件的字节数
    unsigned short int __pad2;      /* 用于填充对齐
    __blkcnt_t  st_blocks;          /* 文件所占的块数

    struct timespec st_atim;        /* 文件最后访问时间 (access time)
    struct timespec st_mtim;        /* 文件最后修改时间 (modification time)
    struct timespec st_ctim;        /* 文件属性/状态最后改变的时间 (change status time)

    ...
}
*/









