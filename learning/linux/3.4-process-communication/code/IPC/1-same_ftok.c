// ftok to generate same key
// same key: same pathname, same proj_id
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, const char * argv[]){

    if(argc != 2){
        printf("input arguments count wrong \n");
        printf("usage: ./a.out pathname \n");
        return -1;
    }

    key_t key_1, key_2;
    key_1 = ftok(argv[1], 1);
    key_2 = ftok(argv[1], 1);

    printf("key_1 value: %d\nkey_2 value: %d \n", key_1, key_2);
    return 0;
}