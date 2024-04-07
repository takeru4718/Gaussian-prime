#include    "cglec.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>
#include    <time.h>
#define _CRT_SECURE_NO_WARNINGS

//�s�N�Z���� nx �~ ny �̃J���[�摜�p���������m�ۂ���ColorImage�\���̂��쐬����
ColorImage InitColorImage(int nx, int ny)
{
    ColorImage img = { NULL, NULL, NULL, nx, ny };
    img.DataR = (unsigned char*)malloc(sizeof(unsigned char) * nx * ny); //R�v���[���p������
    img.DataG = (unsigned char*)malloc(sizeof(unsigned char) * nx * ny); //G�v���[���p������
    img.DataB = (unsigned char*)malloc(sizeof(unsigned char) * nx * ny); //B�v���[���p������
    if ((img.DataR == NULL) || (img.DataG == NULL) || (img.DataB == NULL))
        img.Nx = 0;     //����������ł��m�ۂł��Ȃ�������Nx��0�ɂ��ĕԂ�
    return img;
}

//�J���[�摜img�̑S�s�N�Z���ɃJ���[(R, G, B)���Z�b�g����
void ColorSetAll(ColorImage img, int R, int G, int B)
{
    Image img0 = { NULL, img.Nx, img.Ny };      //�ꎞ�I�ȃO���C�X�P�[���摜
    img0.Data = img.DataR;  CglSetAll(img0, R); //R�v���[���̃f�[�^�ɖ��xR��ݒ�
    img0.Data = img.DataG;  CglSetAll(img0, G); //G�v���[���̃f�[�^�ɖ��xG��ݒ�
    img0.Data = img.DataB;  CglSetAll(img0, B); //B�v���[���̃f�[�^�ɖ��xB��ݒ�
}

//�J���[�摜img���t�@�C����fname�ŕۑ�����
void SaveColorImage(ColorImage img, const char* fname)
{
    Image imgR = { img.DataR, img.Nx, img.Ny }; //�O���C�X�P�[����R�v���[��
    Image imgG = { img.DataG, img.Nx, img.Ny }; //�O���C�X�P�[����G�v���[��
    Image imgB = { img.DataB, img.Nx, img.Ny }; //�O���C�X�P�[����B�v���[��
    CglSaveColorBMP(imgR, imgG, imgB, fname);
}

//�J���[�摜img�̃��������J������
void FreeColorImage(ColorImage img)
{
    free(img.DataR);
    free(img.DataG);
    free(img.DataB);
}


bool prime(int n) {//�f���Ȃ�true��Ԃ��֐�

    if (n <= 1) {
        return false;
    }

    int n1 = (int)sqrt(n);//n���������Ƃ���Ə��������̑f���́�n�ȉ�

    for (int i = 2; i <= n1; i++) {//��������Ŋ���؂�邩���肷��

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

    printf("�����`1�ӂ̃s�N�Z�����́H ");  scanf_s("%d", &N);//�����`�̃T�C�Y���w��

    ColorImage c = InitColorImage(N, N);
    if (c.Nx == 0)                           //�����������������H
    {
        printf("�������G���[!!"); exit(0);
    } //�����������Ɏ��s������v���O�������I������
    ColorSetAll(c, 0, 0, 0);

    srand(time(NULL));
    a1 = rand() % 256;//�����l�𗐐��ɂ�萶��
    a2 = rand() % 256;
    a3 = rand() % 256;

    for (m = 0; m < N / 20; m++) {
        r1 = m;
        R1 = (int)(r1 + 0.5);
        G1 = (10 * m+a1) % 256;//m�ɉ����ĐԐF��ω�
        G2 = (10*R1+a2) % 256;//���_����̋����ɉ����ėΐF��ω�
        G3 = (10 * m+a3) % 256;//m�ɉ����ĐF��ω�
       
        if (m % 4 == 3 && prime(m)) {//4�Ŋ�����3�]��f���̏ꏊ���v���b�g
            CglPaintColorCircle(c, N / 2 + 10 * m, N / 2, 6, G1, G2, G3);
            CglPaintColorCircle(c, N / 2 - 10 * m, N / 2, 6, G1, G2, G3);
            CglPaintColorCircle(c, N / 2, N / 2 + 10 * m, 6, G1, G2, G3);
            CglPaintColorCircle(c, N / 2, N / 2 - 10 * m, 6, G1, G2, G3);
        }

        for (n = 0; n < N / 20; n++) {
            r2 = sqrt((double)m * m + (double)n * n);
            R2 = (int)(r2 + 0.5);
            G4 = (10*m+a1)%256 ;//�����ɉ����ĐԐF��ω�
            G5 = (10 * R2+a2) % 256;//���_����̋����ɉ����ėΐF��ω�
            G6 = (10*n+a3)%256;//�����ɉ����ĐF��ω�

            if (prime(m * m + n * n)) {//4�Ŋ�����1�]��f��(�f�����������̘a�ŕ\�����)�ꏊ���v���b�g

                CglPaintColorCircle(c, N / 2 + 10 * m, N / 2 + 10 * n, 6, G4, G5, G6);//��1�ی�
                CglPaintColorCircle(c, N / 2 - 10 * m, N / 2 + 10 * n, 6, G4, G5, G6);//��2�ی�
                CglPaintColorCircle(c, N / 2 + 10 * m, N / 2 - 10 * n, 6, G4, G5, G6);//��4�ی�
                CglPaintColorCircle(c, N / 2 - 10 * m, N / 2 - 10 * n, 6, G4, G5, G6);//��3�ی�
                
            }
            
        }
        
   }
   
    SaveColorImage(c, "Circles.bmp");
    FreeColorImage(c);

}
