#ifndef CUB3D_h
#define CUB3D_h

typedef struct s_map_data {
    int width;      // Максимальная ширина
    int height;     // Количество строк
    char **map;     // Сама карта
} t_map_data;

// Пример структуры для хранения данных карты
typedef struct s_map {
    char **map;
    int width;
    int height;
    char *no_texture;  // Путь к северной текстуре
    char *so_texture;  // Путь к южной текстуре
    char *we_texture;  // Путь к западной текстуре
    char *ea_texture;  // Путь к восточной текстуре
    int floor_color;   // RGB цвет пола
    int ceiling_color; // RGB цвет потолка
} t_map;

// Вариант 1: Структура для RGB
typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_player
{
    double pos_x;        // Позиция X на карте
    double pos_y;        // Позиция Y на карте
    double dir_x;        // Вектор направления X
    double dir_y;        // Вектор направления Y
    double plane_x;      // Вектор плоскости камеры X
    double plane_y;      // Вектор плоскости камеры Y
} t_player;


#endif