#include <stdio.h>

int main(const int argc, char * argv[]){
    if(argc != 3){
        printf("参数个数不对,请重新输入参数执行 \n");
        return -1;
    }

    char * source_path = argv[1];
    char * dest_path = argv[2];
    FILE * source_fp = NULL;
    FILE * dest_fp = NULL;
    if(NULL == (source_fp = fopen(source_path, "r"))){
        printf("文件: %s,打开失败 \n", source_path);
        return -1;
    }
    if(NULL == (dest_fp = fopen(dest_path, "w"))){
        printf("文件写入失败\n");
        return -1;
    }
    int c = 0;
    while (EOF != (c=fgetc(source_fp)))
    {
        if(EOF == fputc(c, dest_fp)){
            printf("文件写入失败 \n");
            return -1;
        }
    }
    if(ferror(source_fp)){
        perror("读取文件报错:");
        return -1;
    }

    printf("文件复制成功\n");
    fclose(source_fp);
    fclose(dest_fp);

    return 0;
}