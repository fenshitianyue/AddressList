#pragma once
#include<stdio.h>

//获取文件大小（以字节计）
long getFileSize(FILE *fp){
    long fsize;
    fpos_t fpos;  //当前位置
    fgetpos(fp, &fpos);  //获取当前位置
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    fsetpos(fp, &fpos);  //恢复之前的位置

    return fsize;
}

