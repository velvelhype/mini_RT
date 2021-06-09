#include "mms/mlx.h"
#include "vector_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592

typedef struct s_color
{
    int red;
    int green;
    int blue;
} t_color;

int trinity(t_color color)
{
    int ret;
    ret = 0;
    //printf("rgb %d %d %d\n",color.red, color.green, color.blue);
    ret += color.red * 256 * 256;
    ret += color.green * 256;
    ret += color.blue;

    printf("ret is ret %d\n",ret);
    return (ret);
}

typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

typedef struct s_point
{
    int x;
    int y;
} t_point;

int main()
{
    void *mlx;     //スクリーン接続識別子
    void *mlx_win; //ウィンドウ識別子
    float x;
    float y;
    float width = 512; //ウィンドウのサイズ
    float height = 512;

    vector_t eye_pos = {0, 0, -5};
    vector_t sphere_pos = {0, 0, 5};
    vector_t light_pos = {-5, 5, -5};
    float spehere_r = 1;
    vector_t pw;

    pw.z = 0;

    mlx = mlx_init(); //fileopenの時のfd的な？
    mlx_win = mlx_new_window(mlx, width, height, "test");
    // mlx_win = mlx_new_window(スクリーン識別子, width, height,"test");
    //座標は左上が原点、矢印はx軸が右、y軸が下向きになる
    //でも与えられる図形の座標は一般的な向きの座標のためあとで座標変換が必要となる
    y = 0;
    while (y < height)
    {
        pw.y = -(2 * y) / (width - 1) + 1;
        x = 0;
        while (x < width)
        {
            pw.x = (2 * x) / (height - 1) - 1;
            vector_t eye_dir = sub(&pw, &eye_pos);
            vector_t s_c = sub(&eye_pos, &sphere_pos);

            float A, B, C, D;
            A = squared_norm(&eye_dir);
            B = 2 * dot(&eye_dir, &s_c);
            C = squared_norm(&s_c) - SQR(spehere_r);
            D = SQR(B) - 4 * A * C;
            t_color color = {0, 0, 0};
            t_color back = {100, 149, 237};
            if (D >= 0)
                mlx_pixel_put(mlx, mlx_win, x, y, trinity(color));
            else
                mlx_pixel_put(mlx, mlx_win, x, y, trinity(back));
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
