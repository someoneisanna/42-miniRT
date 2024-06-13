#include "minirt.h"
#include "error.h"

static int	ft_validchar(char c)
{
	if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) ||
		(c >= '0' && c <= '9') || (c >= '+' && c <= '.') ||
		c == ' ' || c == '\n')
		return (1);
	return (0);
}

/*scene_line_split, a variável info_qty é usada para armazenar o número 
 	esperado de elementos em uma linha para cada tipo de elemento da cena. 
 Esta matriz estática é inicializada com os números corretos para cada tipo 
 	de elemento, onde cada índice corresponde ao ID do elemento na cena.*/

static void scene_line_split(t_scene *scene, int id)
{
	static int	info_qty[9] = {3, 4, 4, 4, 4, 6, 6, 5, 5};
	int			i;

	i = 0;
	while (scene->line[i])
	{
		if (ft_validchar(scene->line[i] == 0))
			ft_msg_error(scene, LINE);
		if (ft_isspace(scene->line[i]))
			scene->line[i] = ' ';
		i++;
	}
	scene->split = ft_split(scene->line, ' ');
	if (ft_strlen_2(scene->split) != (size_t)info_qty[id])
		ft_msg_error(scene, "err_id");	
}

static void get_scene(t_scene *scene, int id)
{
	static t_arr_sc ft_scene[9] = {get_1_amb, get_2_cam, get_3_light , get_4_sp, 
			get_5_pl , get_6_cy, get_7_co, get_8_cb, get_9_tr};

	if (id < 3)
	{
		if (scene->qtys[id] > 0)
			ft_msg_error(scene, ID);
	}
	scene_line_split(scene, id);
	ft_scene[id](scene);
	if (id > 2)
		ft_add_shapes(&scene->objects, scene->new);
	ft_split_free(scene->split);
	scene->qtys[id]++;
}

void	ft_scene_check(t_scene *scene, int fd)
{
	if (close(fd) < 0)
		return (ft_error(FILE_NF, scene));
	if (scene->msg_error)
		ft_error(scene->msg_error, scene);
	if (scene->qtys[0] == 0 || scene->qtys[1] == 0)
		ft_error(INFO_SCENE, scene);
}

void	open_file(char *file, t_scene *scene)
{
	static char	*s[9] = {"A ", "C ", "L ", "sp", "pl", "cy", "co", "cb", "tr"};
	int		fd;
	char	*ret;
	int		id;

	if (ft_strnrcmp(file, ".rt", 3) != 0)
		ft_error(RT_FILE, scene);
	ft_bzero(scene, sizeof(t_scene));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_error(FILE_NF, scene));
	ret = get_next_line(fd, NO);
	while (ret)
	{
		id = 0;	
		while (id < 9 && ft_strncmp(ret, s[id], 2))
			id++;
		scene->line = ft_strdup(ret);
		if (id < 9)
			get_scene(scene, id);
		free(scene->line);
		free(ret);
		ret = get_next_line(fd, NO);
	}
	ft_scene_check(scene, fd);
}
