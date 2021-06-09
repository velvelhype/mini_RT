#include "mms/mlx.h"
#include <math.h>
#include <stdio.h>
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

typedef struct s_triangle
{
    t_point a;
    t_point b;
    t_point c;
}   t_triangle;

void is_contact()
{
    
}

void draw_line(t_point a, t_point b, void *mlx, void *mlx_win)
{
    printf("a.x %d a.y %d\n",a.x,a.y);
    printf("b.x %d b.y %d\n",b.x,b.y);

    double buff = ((double)a.y - (double)b.y)/((double)a.x - (double)b.x);
    printf("buff is %f %d %d\n",buff, b.y - a.y, b.x - a.x);
    
    double ori = a.x;
    while(a.x != b.x)
    {
        a.x = a.x + 1;
		mlx_pixel_put(mlx, mlx_win, a.x, a.y+(a.x - ori)*buff, 10000000);
    }
}

double what_is_pi(double deg)
{
    double rad = deg*PI/180.0;
    return(rad);
}

void dsotm(void *mlx, void *mlx_win)
{
    double rad = what_is_pi(60);
    double len = 2;

    double x = len * cos(rad);
    double y = len * sin(rad);
    printf("x=%f y=%f\n",x,y);

    printf("rad is %f\n",rad);
    t_triangle triangle = {{145,200},{145+110*cos(rad), 200-110*sin(rad)},{255,200}};
   printf("%d tri\n", triangle.a.x);
   draw_line(triangle.a, triangle.b, mlx, mlx_win);
   draw_line(triangle.b, triangle.c, mlx, mlx_win);
   draw_line(triangle.a, triangle.c, mlx, mlx_win);
    t_point bend_one = {0, 200};
    t_point bend_two = {400, 70};
   draw_line(bend_one, bend_two, mlx, mlx_win);
}

int main()
{
    void *mlx;//スクリーン接続識別子
    void *mlx_win;//ウィンドウ識別子
    int i;
    int j;
    int width = 400; //ウィンドウのサイズ
    int height = 400; 
	//t_data img;

    mlx = mlx_init();//fileopenの時のfd的な？
    mlx_win = mlx_new_window(mlx, width, height,"test");
	// mlx_win = mlx_new_window(スクリーン識別子, width, height,"test");
	//座標は左上が原点、矢印はx軸が右、y軸が下向きになる
	//でも与えられる図形の座標は一般的な向きの座標のためあとで座標変換が必要となる
   	i= 0;
	while (i < width)
	{
			j = 0;
			// while (j < height)
			while (j < height)
			{
					mlx_pixel_put(mlx, mlx_win, i, j, 0);
					j++;
			}
			i++;
          //  pow(x, 2) + pow(y, 2) + pow(z, 2) = 16; 
	}
    dsotm(mlx, mlx_win);

    
    mlx_loop(mlx);
    
    //無限ループを作り、その間ウィンドウを表示させ続ける
    //最初のうちはcntl+Cで強制終了すればおk
    //クリックした時に終了させるなどのプログラムはゆくゆく書く必要がある
    return (1);
}
