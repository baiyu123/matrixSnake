#include "matrixUtility.h"
void multiplyMat(std::vector<std::vector<int> >& mat1,
              std::vector<std::vector<int> >& mat2,
              std::vector<std::vector<int> >& res)
{
    int i, j, k;
    int mat1Height = mat1.size();
    int mat1Width = mat1[0].size();
    int mat2Width = mat2[0].size();
    for (i = 0; i < mat1Height; i++)
    {
        for (j = 0; j < mat2Width; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < mat1Width; k++)
                res[i][j] += mat1[i][k] *
                mat2[k][j];
        }
    }
}
