#include "minirt.h"

void	ft_msg_error(t_scene *scene, char *code)
{
	if (!scene->msg_error)
		scene->msg_error = code;
}

void	*malloc_ver(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		ft_error("System error\n", NULL);
	return (ptr);
}

void	ft_error(char *msg, t_scene *scene)
{
	(void)scene;
	ft_putstr_fd("\033[1m\033[38;5;199mError\033[0m\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	//free_scene(scene);
	exit(EXIT_FAILURE);
}



size_t	ft_strlen_2(char **s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}

int	ft_strnrcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (n == 0)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	while (s1[--i] == s2[--j])
	{
		n--;
		if (n == 0)
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[j]));
}

void	ft_split_free(char **s)
{
	size_t	i;
	size_t	len;

	if (!s || !*s)
		return ;
	len = ft_strlen_2(s);
	i = 0;
	while (i < len)
	{
		free(s[i++]);
	}
	free(s);
}