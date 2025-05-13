#include <iostream>
#include <stdlib.h>
#include "bmp.h"

using namespace std;

int R[MaxBMPSizeX][MaxBMPSizeY]; 
int G[MaxBMPSizeX][MaxBMPSizeY];
int B[MaxBMPSizeX][MaxBMPSizeY];
int r[MaxBMPSizeX][MaxBMPSizeY];
int g[MaxBMPSizeX][MaxBMPSizeY];
int b[MaxBMPSizeX][MaxBMPSizeY];

// 低通濾波函式
void lowPassFilter(int inputR[][MaxBMPSizeY], int inputG[][MaxBMPSizeY], int inputB[][MaxBMPSizeY], int outputR[][MaxBMPSizeY], int outputG[][MaxBMPSizeY], int outputB[][MaxBMPSizeY], int width, int height)
{
    // 定義低通濾波器遮罩
    int mask[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    // 圖像的每個像素
    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            int count = 0;

            // 在遮罩範圍內計算像素值總和
            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {
                    sumR += inputR[i + x][j + y] * mask[x + 1][y + 1];
                    sumG += inputG[i + x][j + y] * mask[x + 1][y + 1];
                    sumB += inputB[i + x][j + y] * mask[x + 1][y + 1];
                    count += mask[x + 1][y + 1];
                }
            }

            // 將相加結果除以遮罩內非零數值的個數
            outputR[i][j] = sumR / count;
            outputG[i][j] = sumG / count;
            outputB[i][j] = sumB / count;
        }
    }
}

int main(int argc, char* argv[])
{
    int width, height;
    int i, j;

    // 開啟並讀取全彩(24bits)bmp 影像圖檔
    open_bmp("lena.bmp", R, G, B, width, height);

    // 執行低通濾波處理
    lowPassFilter(R, G, B, r, g, b, width, height);

    // 儲存處理結果至新的圖檔中
    save_bmp("lenna_new1.bmp", r, g, b);

    printf("Job Finished!\n");

    // 關閉 bmp 影像圖檔
    close_bmp();

    system("pause"); 
    return 0;
}

