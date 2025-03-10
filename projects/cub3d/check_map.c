/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:07:39 by mmychaly          #+#    #+#             */
/*   Updated: 2025/01/06 05:08:11 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Проверяем формат а так же разрешение на доступ к файлу
bool check_file_format(char *filename)
{
    char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".cub") != 0)
        return false;
    
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return false;
    close(fd);
    return true;
}

bool check_file_access(char *filename, char **error_msg)
{
    int fd;
    
    if (!filename)
    {
        *error_msg = "Filename is NULL";
        return false;
    }
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        if (errno == ENOENT)
            *error_msg = "File does not exist";
        else if (errno == EACCES)
            *error_msg = "Permission denied";
        else
            *error_msg = "Unknown file error";
        return false;
    }
    
    close(fd);
    return true;
}

void flood_fill(char **map, int x, int y, int *error)
{
    // Проверяем границы
    if (y < 0 || x < 0 || !map[y] || !map[y][x])
    {
        *error = 1;
        return;
    }
    
    // Если текущая позиция - стена или уже посещена
    if (map[y][x] == '1' || map[y][x] == 'V')
        return;
        
    // Если обнаружен пробел - карта не замкнута
    if (map[y][x] == ' ')
    {
        *error = 1;
        return;
    }
    
    // Помечаем как посещенную
    map[y][x] = 'V';
    
    // Рекурсивно проверяем соседние клетки
    flood_fill(map, x + 1, y, error);
    flood_fill(map, x - 1, y, error);
    flood_fill(map, x, y + 1, error);
    flood_fill(map, x, y - 1, error);
}

bool validate_map(t_map *map)
{
    bool has_player = false;
    
    // Проверка размеров карты
    if (map->height < 3 || map->width < 3)
        return false;
        
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            char c = map->map[y][x];
            
            // Проверка допустимых символов
            if (c != '0' && c != '1' && c != ' ' && 
                c != 'N' && c != 'S' && c != 'E' && c != 'W')
                return false;
                
            // Проверка позиции игрока
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (has_player) // Уже есть игрок
                    return false;
                has_player = true;
                
                // Проверка, что игрок не на краю карты
                if (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1)
                    return false;
            }
            
            // Проверка пробелов
            if (c == ' ')
            {
                // Проверка соседних клеток
                if (y > 0 && map->map[y-1][x] == '0') return false;
                if (y < map->height-1 && map->map[y+1][x] == '0') return false;
                if (x > 0 && map->map[y][x-1] == '0') return false;
                if (x < map->width-1 && map->map[y][x+1] == '0') return false;
            }
        }
    }
    
    // Проверка, что игрок существует
    if (!has_player)
        return false;
        
    // Проверка текстур и цветов
    if (!validate_textures(map) || !validate_colors(map))
        return false;
        
    return true;
}


bool validate_textures(t_map *map)
{
    // Проверка существования файлов текстур
    if (!map->no_texture || !map->so_texture || 
        !map->we_texture || !map->ea_texture)
        return false;
        
    // Проверка расширения файлов
    if (!check_file_format(map->no_texture) || 
        !check_file_format(map->so_texture) ||
        !check_file_format(map->we_texture) || 
        !check_file_format(map->ea_texture))
        return false;
        
    return true;
}


typedef struct s_player
{
    double pos_x;        // Позиция X на карте
    double pos_y;        // Позиция Y на карте
    double dir_x;        // Вектор направления X
    double dir_y;        // Вектор направления Y
    double plane_x;      // Вектор плоскости камеры X
    double plane_y;      // Вектор плоскости камеры Y
} t_player;

void set_player_position(t_game *game, int x, int y, char direction)
{
    // Сохраняем позицию
    game->player.pos_x = x + 0.5; // + 0.5 чтобы поместить игрока в центр клетки
    game->player.pos_y = y + 0.5;
    
    // Устанавливаем начальное направление взгляда
    init_player_direction(&game->player, direction);
}

void init_player_direction(t_player *player, char direction)
{
    if (direction == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;  // В верхнюю часть карты
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    else if (direction == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;   // В нижнюю часть карты
        player->plane_x = -0.66;
        player->plane_y = 0;
    }
    else if (direction == 'E')
    {
        player->dir_x = 1;   // Вправо
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
    else if (direction == 'W')
    {
        player->dir_x = -1;  // Влево
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
}


//Проверка карты на правильное отображаение пробеллов
bool check_space_surroundings(char **map, int y, int x, int height, int width)
{
    // Массив для проверки всех соседних клеток
    const int dy[] = {-1, 1, 0, 0};  // Смещения по y
    const int dx[] = {0, 0, -1, 1};  // Смещения по x
    
    for (int i = 0; i < 4; i++)
    {
        int new_y = y + dy[i];
        int new_x = x + dx[i];
        
        // Проверяем, что не выходим за границы карты
        if (new_y >= 0 && new_y < height && 
            new_x >= 0 && new_x < width)
        {
            // Если рядом с пробелом находится '0' - ошибка
            if (map[new_y][new_x] == '0')
                return false;
        }
    }
    return true;
}

bool validate_texture_file(char *texture_path)
{
    char *ext = strrchr(texture_path, '.');
    
    // Проверяем расширение (.xpm)
    if (!ext || strcmp(ext, ".xpm") != 0)
        return false;
    
    // Проверяем доступность файла
    int fd = open(texture_path, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Cannot open texture file: %s\n", texture_path);
        return false;
    }
    close(fd);
    
    return true;
}

//Проверка текстур и путей к ним
bool validate_textures(t_map *map)
{
    // Проверяем существование путей
    if (!map->no_texture || !map->so_texture || 
        !map->we_texture || !map->ea_texture)
    {
        printf("Error: Missing texture path\n");
        return false;
    }
    
    // Проверяем каждый файл текстуры
    if (!validate_texture_file(map->no_texture) ||
        !validate_texture_file(map->so_texture) ||
        !validate_texture_file(map->we_texture) ||
        !validate_texture_file(map->ea_texture))
    {
        return false;
    }
    
    return true;
}


//проверка данных по цвету 
bool validate_rgb(char *color_str)
{
    char **values = ft_split(color_str, ',');
    int r, g, b;
    
    if (!values || !values[0] || !values[1] || !values[2] || values[3])
    {
        free_split(values);
        return false;
    }
    
    r = ft_atoi(values[0]);
    g = ft_atoi(values[1]);
    b = ft_atoi(values[2]);
    
    free_split(values);
    
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return false;
        
    return true;
}




//Функции для работы с RGB:
// Преобразование отдельных компонентов в одно число
unsigned int create_rgb(unsigned char r, unsigned char g, unsigned char b)
{
    return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

// Извлечение компонентов из числа
void extract_rgb(unsigned int color, unsigned char *r, unsigned char *g, unsigned char *b)
{
    *r = (color >> 16) & 0xff;
    *g = (color >> 8) & 0xff;
    *b = color & 0xff;
}

// Парсинг строки с RGB
bool parse_rgb_string(char *str, unsigned int *color)
{
    char **values;
    int r, g, b;

    // Разделяем строку по запятым
    values = ft_split(str, ',');
    if (!values || !values[0] || !values[1] || !values[2] || values[3])
    {
        free_split(values);
        return false;
    }

    // Преобразуем строки в числа
    r = ft_atoi(values[0]);
    g = ft_atoi(values[1]);
    b = ft_atoi(values[2]);

    // Проверяем диапазон
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        free_split(values);
        return false;
    }

    // Создаем цвет
    *color = create_rgb(r, g, b);
    free_split(values);
    return true;
}


//Использования RGB для прорисовки 
typedef struct s_game
{
    unsigned int floor_color;   // Цвет пола
    unsigned int ceiling_color; // Цвет потолка
    // ... другие поля
} t_game;

// Пример использования при рендеринге
void draw_vertical_line(t_game *game, int x, int y1, int y2)
{
    int y = 0;
    
    // Рисуем потолок
    while (y < y1)
        put_pixel(game, x, y++, game->ceiling_color);
        
    // Рисуем стену
    while (y < y2)
        put_pixel(game, x, y++, get_texture_color(game));
        
    // Рисуем пол
    while (y < WINDOW_HEIGHT)
        put_pixel(game, x, y++, game->floor_color);
}

//-------------------------------

//Шаг 1: Чтение файла
char *line;
while ((line = get_next_line(fd)) != NULL) {
    // Обработать строку
    free(line);
}


//Шаг 2: Парсинг текстур и цветов
int parse_texture(char *line, t_config *config) {
    if (ft_strncmp(line, "NO ", 3) == 0)
        config->textures[NO] = extract_path(line + 3);
    else if (ft_strncmp(line, "SO ", 3) == 0)
        config->textures[SO] = extract_path(line + 3);
    else if (ft_strncmp(line, "WE ", 3) == 0)
        config->textures[WE] = extract_path(line + 3);
    else if (ft_strncmp(line, "EA ", 3) == 0)
        config->textures[EA] = extract_path(line + 3);
    else
        return (0); // Некорректная строка
    return (1);
}

int parse_color(char *line, t_config *config) {
    if (ft_strncmp(line, "F ", 2) == 0)
        config->floor_color = extract_color(line + 2);
    else if (ft_strncmp(line, "C ", 2) == 0)
        config->ceiling_color = extract_color(line + 2);
    else
        return (0); // Некорректная строка
    return (1);
}

//Шаг 3: Парсинг карты
int parse_map(char *line, t_config *config) {
    if (line_is_empty(line))
        return (0); // Пропуск пустых строк

    // Добавить строку карты
    config->map = append_to_map(config->map, line);
    return (1);
}
//1. Проверка символов
int validate_characters(char **map) {
    for (int i = 0; map[i]; i++) {
        for (int j = 0; map[i][j]; j++) {
            if (!ft_strchr("012NSEW ", map[i][j]))
                return (0); // Некорректный символ
        }
    }
    return (1);
}
//2. Проверка закрытости карты
int is_closed(char **map) {
    for (int i = 0; map[i]; i++) {
        for (int j = 0; map[i][j]; j++) {
            if (map[i][j] == '0' || ft_strchr("NSEW", map[i][j])) {
                if (!is_surrounded_by_walls(map, i, j))
                    return (0); // Проблема с закрытостью
            }
        }
    }
    return (1);
}

int is_surrounded_by_walls(char **map, int i, int j) {
    if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
        return (0); // Граница карты
    if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
        return (0);
    if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
        return (0);
    return (1);
}
//3. Проверка начальной позиции игрока
int validate_player_position(char **map, t_config *config) {
    int count = 0;

    for (int i = 0; map[i]; i++) {
        for (int j = 0; map[i][j]; j++) {
            if (ft_strchr("NSEW", map[i][j])) {
                config->player.x = j;
                config->player.y = i;
                config->player.direction = map[i][j];
                count++;
            }
        }
    }
    return (count == 1); // Должна быть ровно одна начальная позиция
}
//Функция extract_path
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *extract_path(char *line) {
    // Пропустить начальные пробелы
    while (*line && isspace(*line))
        line++;

    // Найти конец строки без завершающих пробелов
    char *end = line + strlen(line) - 1;
    while (end > line && isspace(*end))
        end--;

    // Создать новую строку с очищенным путём
    int length = end - line + 1;
    char *path = malloc(length + 1);
    if (!path)
        return NULL;
    
    strncpy(path, line, length);
    path[length] = '\0';
    return path;
}

//Функция extract_color
#include <stdlib.h>
#include <stdio.h>

int extract_color(char *line) {
    int r, g, b;

    // Удалить пробелы, если есть
    while (*line && isspace(*line))
        line++;

    // Разбить строку на три числа
    if (sscanf(line, "%d,%d,%d", &r, &g, &b) != 3)
        return -1;

    // Проверить диапазон значений
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return -1;

    // Вернуть цвет в формате 0xRRGGBB
    return (r << 16) | (g << 8) | b;
}
//1. Проверка размера карты
#define MAX_MAP_HEIGHT 100
#define MAX_MAP_WIDTH 100

int validate_map_size(char **map) {
    int height = 0;

    for (int i = 0; map[i]; i++) {
        height++;
        // Проверяем длину строки
        if ((int)strlen(map[i]) > MAX_MAP_WIDTH)
            return 0; // Карта слишком широкая
    }

    // Проверяем высоту карты
    if (height > MAX_MAP_HEIGHT)
        return 0; // Карта слишком высокая

    return 1; // Размер карты корректный
}
//Проверка внешних символов карты
int validate_map_borders(char **map) {
    int height = 0;

    // Считаем количество строк карты
    while (map[height])
        height++;

    // Проверяем первую строку
    for (int j = 0; map[0][j]; j++) {
        if (map[0][j] != '1' && map[0][j] != ' ')
            return 0; // Ошибка: некорректный символ в первой строке
    }

    // Проверяем последнюю строку
    for (int j = 0; map[height - 1][j]; j++) {
        if (map[height - 1][j] != '1' && map[height - 1][j] != ' ')
            return 0; // Ошибка: некорректный символ в последней строке
    }

    // Проверяем остальные строки
    for (int i = 1; i < height - 1; i++) {
        int len = strlen(map[i]);

        // Первый символ строки
        if (len > 0 && map[i][0] != '1' && map[i][0] != ' ')
            return 0; // Ошибка: некорректный символ в первой колонке

        // Последний символ строки
        if (len > 1 && map[i][len - 1] != '1' && map[i][len - 1] != ' ')
            return 0; // Ошибка: некорректный символ в последней колонке

        // Символы за пределами строки автоматически считаются пробелами
    }

    return 1; // Карта корректно замкнута
}
