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
	void *mlx;	   //スクリーン接続識別子
	void *mlx_win; //ウィンドウ識別子
	float x;
	float y;
	float width = 512; //ウィンドウのサイズ
	float height = 512;

	vector_t eye_pos = {0, 0, -5};
	vector_t sphere_pos = {0, 0, 5};
	float spehere_r = 1;
	vector_t pw;

	float k_amb = 0.01;
	float k_dif = 0.69;
	float k_spe = 0.3;
	float shininess = 8;

	vector_t light_pos = {-5, 5, -5};
	float ilum_amb = 0.1;
	float ilum_direct = 1.0;

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
			t_color color = {100, 149, 237};
			float t = -1;
			if (D == 0)
				t = -B / (2 * A);
			else if (D > 0)
			{
				float t1 = (-B + sqrt(D)) / (2 * A);
				float t2 = (-B - sqrt(D)) / (2 * A);

				if (t1 > 0)
					t = t1;
				if (t2 > 0 && t2 < t)
					t = t2;
			}
			if (t > 0)
			{
				vector_t int_pos;
				vector_t light_dir;
				vector_t sphere_n;

				float lum_amb;
				float lum_dif;
				float lum_spe;
				float lum_ref;

				float nl_dot;

				lum_amb = k_amb * ilum_amb;

				int_pos = mult(&eye_dir, t);
				int_pos = add(&int_pos, &eye_pos);

				light_dir = sub(&light_pos, &int_pos);
				normalize(&light_dir);
				sphere_n = sub(&int_pos, &sphere_pos);
				normalize(&sphere_n);

				nl_dot = dot(&sphere_n, &light_dir);
				nl_dot = CLAMP(nl_dot, 0, 1);
				//printf("dot is %f\n", nl_dot);
				lum_dif = nl_dot * ilum_direct * k_dif;
				lum_spe = 0;
				if (nl_dot > 0)
				{
					vector_t ref_dir;
					vector_t inv_eye_dir;
					float vr_dot;

					ref_dir = mult(&sphere_n, nl_dot * 2);
					ref_dir = sub(&ref_dir, &light_dir);
					normalize(&ref_dir);

					inv_eye_dir = mult(&eye_dir, -1);
					normalize(&inv_eye_dir);

					vr_dot = dot(&inv_eye_dir, &ref_dir);
					vr_dot = CLAMP(vr_dot, 0, 1);
					lum_spe = k_spe * ilum_direct * pow(vr_dot, shininess);
				}

				lum_ref = lum_spe + lum_dif + lum_amb;
				lum_ref = CLAMP(lum_ref, 0, 1);

				color.red = color.green = color.blue = 255 * lum_ref;
			}
			mlx_pixel_put(mlx, mlx_win, x, y, trinity(color));
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
