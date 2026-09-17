/*
练习题
编写一个程序，使用数组指针来处理二维数组（矩阵）：
计算矩阵所有元素的和
计算矩阵的转置
*/
#define COLS 3
#define ROWS 4

//函数声明
void printMatrix(int(* mat)[COLS], int rows);
int matrixSum(int (* mat)[COLS], int rows);
void transposeMatrix(int (* src)[COLS], int (* dst)[ROWS], int rows);

int main(){

    return 0;
}

void printMatrix(int(* mat)[COLS], int rows){
    for(int i=0;i<rows;i++){
        for (int j = 0; j < COLS; j++)
        {
            /* code */
            printf("%d\t",mat[i][j]);
        }
        
    }
}

// 计算矩阵所有元素的和
int matrixSum(int (* mat)[COLS], int rows){
    int sum = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d", mat[i][j]);
            sum += mat[i][j];
        }
        
    }
    return sum;
    
}

//计算矩阵的转置
void transposeMatrix(int (* src)[COLS], int (* dst)[ROWS], int rows){
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {   
            dst[j][i] = src[i][j];
        }
    }
    
}
