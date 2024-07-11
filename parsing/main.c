#include "parse.h"

void ft_putendl_fd_color(char *s, int fd, char *color)
{
    write(fd, color, 5);
    ft_putendl_fd(s, fd);
    write(fd, "\033[0m", 4);
}
char *two_char(char *line)
{
    int i = 0;
    int j = 0;
    char *re_line = malloc(3);
    if (!re_line)
        ft_putendl_fd_color("Error\nmalloc failure", 2, RED);
    while (line[i] && line[i] == ' ')
        i++;
    while (j < 2 && line[i])
        re_line[j++] = line[i++];
    re_line[j] = '\0';
    return (re_line);
}
char *remove_new_line(char *line)
{
    int i;
    i = 0;
    char *new_ret;
    while (line[i] && line[i] != '\n')
        i++;
    new_ret = (char *)malloc(i + 1);
    if (!new_ret)
        return (NULL);
    i = 0;
    while (line[i] && line[i] != '\n')
    {
        new_ret[i] = line[i];
        i++;
    }
    new_ret[i] = '\0';
    return (new_ret);
}
bool check_dirs(char *line, char *to_find)
{
    if (ft_strcmp(two_char(line), to_find))
        return (false);
    return (true);
}

void set_map(t_data *data)
{
    int i = 0;
    int fd = open("map.cub", O_RDWR, 0666);
    char *line = get_next_line(fd);
    while (line)
    {
        line = get_next_line(fd);
        i++;
    }
    data->map = (char **)malloc(sizeof(char *) * (i + 1));
    if (!data->map)
        return;
    close(fd);
    fd = open("map.cub", O_RDWR, 0666);

    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        data->map[i] = remove_new_line(line);
        line = get_next_line(fd);
        i++;
    }
    data->map[i] = NULL;
}
void check_space(char *line)
{
    int i;
    i = 0;
    while (line[i] && line[i] == ' ')
        i++;
    if (line[i + 2] != ' ')
        ft_putendl_fd_color("Error\nInvalid directions", 2, RED);
}
void validate_dirs(t_data *data, char *to_find)
{
    bool check = false;
    int count = 0;
    int i = 0;
    while (data->map[i])
    {
        if (check_dirs(data->map[i], to_find))
        {
            check_space(data->map[i]);
            count++;
        }
        i++;
    }
    if (count != 1)
        ft_putendl_fd_color("Error\nInvalid directions", 2, RED);
}
void validate_all_dirs(t_data *data)
{
    validate_dirs(data, "NO");
    validate_dirs(data, "SO");
    validate_dirs(data, "WE");
    validate_dirs(data, "EA");
}
char *first_char(t_data *data)
{
    int i;
    int j;
    char *new_ret;

    j = 0;
    new_ret = (char *)malloc(sizeof(char) * 2);
    if (!new_ret)
        ft_putendl_fd_color("Error\nmalloc failure", 2, RED);
    i = 0;
    while (data->map[i] && data->map[] == ' ')
        i++;
    new_ret[0] = data->map[i];
    new_ret[1] = '\0';
    return (new_ret);
}
// void find_line_color(t_data *data, char *to_find)
// {
//     int i;

//     i = 0;
//     while (data->map[i])
//     {
//         if (ft_strcmp(data->map[i], to_find))
//     }
// }
int main()
{
    t_data data;

    set_map(&data);
    validate_all_dirs(&data);
    // find_line_color(&data);
    // printf("%s\n", first_char(&data));
    // validate_colors(&data);
}