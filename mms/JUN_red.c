typedef struct s_world {
    void       *mlx;  // minilibx特有のやつ
    void       *win;  // minilibxのウィンドウを指すポインタ
    int        screen_width;
    int        screen_height;
    t_dlist *cameras;  // カメラのリスト
    t_list      *objects;  // 物体のリスト
    t_fcolor    ambient;  // 環境光の強度
    t_list      *lights;  // 光源のリスト
}               t_world;

int raytracing(t_world *world)
{
    // 視点位置を表すベクトル
    t_vec3 camera_vec;
    camera_vec = vec3_init(0, 0, -5);  // スクリーンの少し手前な感じ

    // 球の中心座標
    t_vec3 sphere_vec;
    sphere_vec = vec3_init(0, 0, 5);  // スクリーンの少し奥な感じ
    double sphere_r = 1;  // 半径

    for (double y = 0; y < world->screen_height; y++){
        for (double x = 0; x < world->screen_width; x++){
            // スクリーン座標からワールド座標への変換
            // x,yは[-1,1]へ変換する
            // スクリーン上の点の三次元空間における位置を計算する
            t_vec3 screen_vec;
            screen_vec = vec3_init(2 * x / world->screen_width - 1.0, 2 * y / world->screen_height - 1.0, 0);

            // 方向ベクトル
            t_vec3 dir_vec;
            dir_vec = vec3_normalize(vec3_sub(screen_vec, camera_vec));

                        // 
            t_vec3 camera2sphere_vec = vec3_sub(camera_vec, sphere_vec);

            // レイが球に当たったか計算する
            double a = vec3_mag(dir_vec) * vec3_mag(dir_vec);
            double b = 2 * vec3_dot(camera2sphere_vec, dir_vec);
            double c = vec3_dot(camera2sphere_vec, camera2sphere_vec) - sphere_r * sphere_r;
            // 判別式
            double d = b * b - 4 * a * c;
            if (d >= 0)
            {
                my_mlx_pixel_put(&world->img, x, y, rgb2hex(255, 0, 0));
            }
            else
            {
                my_mlx_pixel_put(&world->img, x, y, rgb2hex(0, 0, 255));
            }
        }
    }
    return (0);
}

int main()
{
    int raytracing(t_world *world);
}