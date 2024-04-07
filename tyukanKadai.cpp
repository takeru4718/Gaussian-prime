#include    "cglec.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>
#include    <time.h>
#define _CRT_SECURE_NO_WARNINGS

//ピクセル数 nx × ny のカラー画像用メモリを確保してColorImage構造体を作成する
ColorImage InitColorImage(int nx, int ny)
{
    ColorImage img = { NULL, NULL, NULL, nx, ny };
    img.DataR = (unsigned char*)malloc(sizeof(unsigned char) * nx * ny); //Rプレーン用メモリ
    img.DataG = (unsigned char*)malloc(sizeof(unsigned char) * nx * ny); //Gプレーン用メモリ
    img.DataB = (unsigned char*)malloc(sizeof(unsigned char) * nx * ny); //Bプレーン用メモリ
    if ((img.DataR == NULL) || (img.DataG == NULL) || (img.DataB == NULL))
        img.Nx = 0;     //メモリが一つでも確保できなかったらNxを0にして返す
    return img;
}

//カラー画像imgの全ピクセルにカラー(R, G, B)をセットする
void ColorSetAll(ColorImage img, int R, int G, int B)
{
    Image img0 = { NULL, img.Nx, img.Ny };      //一時的なグレイスケール画像
    img0.Data = img.DataR;  CglSetAll(img0, R); //Rプレーンのデータに明度Rを設定
    img0.Data = img.DataG;  CglSetAll(img0, G); //Gプレーンのデータに明度Gを設定
    img0.Data = img.DataB;  CglSetAll(img0, B); //Bプレーンのデータに明度Bを設定
}

//カラー画像imgをファイル名fnameで保存する
void SaveColorImage(ColorImage img, const char* fname)
{
    Image imgR = { img.DataR, img.Nx, img.Ny }; //グレイスケールのRプレーン
    Image imgG = { img.DataG, img.Nx, img.Ny }; //グレイスケールのGプレーン
    Image imgB = { img.DataB, img.Nx, img.Ny }; //グレイスケールのBプレーン
    CglSaveColorBMP(imgR, imgG, imgB, fname);
}

//カラー画像imgのメモリを開放する
void FreeColorImage(ColorImage img)
{
    free(img.DataR);
    free(img.DataG);
    free(img.DataB);
}


bool prime(int n) {//素数ならtrueを返す関数

    if (n <= 1) {
        return false;
    }

    int n1 = (int)sqrt(n);//nが合成数とすると小さい方の素数は√n以下

    for (int i = 2; i <= n1; i++) {//総当たりで割り切れるか判定する

        if (n % i == 0) {
            return false;
        }
    }

    return true;

}


int main(void)
{
    int N, m, n, R1, R2, G1, G2, G3, G4, G5, G6, a1, a2, a3;
    double r1,r2;

    printf("正方形1辺のピクセル数は？ ");  scanf_s("%d", &N);//正方形のサイズを指定

    ColorImage c = InitColorImage(N, N);
    if (c.Nx == 0)                           //メモリ割当成功か？
    {
        printf("メモリエラー!!"); exit(0);
    } //メモリ割当に失敗したらプログラムを終了する
    ColorSetAll(c, 0, 0, 0);

    srand(time(NULL));
    a1 = rand() % 256;//初期値を乱数により生成
    a2 = rand() % 256;
    a3 = rand() % 256;

    for (m = 0; m < N / 20; m++) {
        r1 = m;
        R1 = (int)(r1 + 0.5);
        G1 = (10 * m+a1) % 256;//mに応じて赤色を変化
        G2 = (10*R1+a2) % 256;//原点からの距離に応じて緑色を変化
        G3 = (10 * m+a3) % 256;//mに応じて青色を変化
       
        if (m % 4 == 3 && prime(m)) {//4で割って3余る素数の場所をプロット
            CglPaintColorCircle(c, N / 2 + 10 * m, N / 2, 6, G1, G2, G3);
            CglPaintColorCircle(c, N / 2 - 10 * m, N / 2, 6, G1, G2, G3);
            CglPaintColorCircle(c, N / 2, N / 2 + 10 * m, 6, G1, G2, G3);
            CglPaintColorCircle(c, N / 2, N / 2 - 10 * m, 6, G1, G2, G3);
        }

        for (n = 0; n < N / 20; n++) {
            r2 = sqrt((double)m * m + (double)n * n);
            R2 = (int)(r2 + 0.5);
            G4 = (10*m+a1)%256 ;//実軸に応じて赤色を変化
            G5 = (10 * R2+a2) % 256;//原点からの距離に応じて緑色を変化
            G6 = (10*n+a3)%256;//虚軸に応じて青色を変化

            if (prime(m * m + n * n)) {//4で割って1余る素数(素数が平方数の和で表される)場所をプロット

                CglPaintColorCircle(c, N / 2 + 10 * m, N / 2 + 10 * n, 6, G4, G5, G6);//第1象限
                CglPaintColorCircle(c, N / 2 - 10 * m, N / 2 + 10 * n, 6, G4, G5, G6);//第2象限
                CglPaintColorCircle(c, N / 2 + 10 * m, N / 2 - 10 * n, 6, G4, G5, G6);//第4象限
                CglPaintColorCircle(c, N / 2 - 10 * m, N / 2 - 10 * n, 6, G4, G5, G6);//第3象限
                
            }
            
        }
        
   }
   
    SaveColorImage(c, "Circles.bmp");
    FreeColorImage(c);

}
