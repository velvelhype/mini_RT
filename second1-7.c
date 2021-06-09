#include "mms/mlx.h"
#include "vector_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_point
{
    int x;
    int y;
}   t_point;

int main()
{
    void *mlx;//スクリーン接続識別子
    void *mlx_win;//ウィンドウ識別子
    float x;
    float y;
    float width = 512; //ウィンドウのサイズ
    float height = 512; 
	//t_data img;



    vector_t eye_pos = {0, 0, -5};
    vector_t sphere_pos = {0, 0, -5};
    float spehere_r = 1;
    vector_t pw = { -0.4, 0, 0};
    x = 234;
    y = 128;
    pw.x = (2 * x) / (height - 1) - 1;
    pw.y = -(2 * y) / (width - 1) + 1;
    pw.z = 0;
    printf("%f %f\n",pw.x, pw.y);


    vector_t eye_dir = sub(&pw, &eye_pos);
    vector_t s_c = sub(&eye_pos, &sphere_pos);
    float A,B,C,D;
    
    A = squared_norm(&eye_dir);
    B = 2 * dot(&eye_dir, &s_c);
    C = squared_norm(&s_c) - SQR(1);
    D = SQR(B) - 4 * A * C;
    //printf("D is %f\n",D);

    if (D >= 0)
        printf("yes!!\n");
    else
        printf("NOOOO\n");

    mlx = mlx_init();//fileopenの時のfd的な？
    mlx_win = mlx_new_window(mlx, width, height,"test");
	// mlx_win = mlx_new_window(スクリーン識別子, width, height,"test");
	//座標は左上が原点、矢印はx軸が右、y軸が下向きになる
	//でも与えられる図形の座標は一般的な向きの座標のためあとで座標変換が必要となる
   	y = 0;
	while (y < height)
	{
			x = 0;
			while (x < width)
			{
					mlx_pixel_put(mlx, mlx_win, x, y, 22222);
					x++;
			}
			y++;
	}

    
    mlx_loop(mlx);
    
    //無限ループを作り、その間ウィンドウを表示させ続ける
    //最初のうちはcntl+Cで強制終了すればおk
    //クリックした時に終了させるなどのプログラムはゆくゆく書く必要がある
    return (1);
}
