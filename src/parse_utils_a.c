/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils_a.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbank <dbank@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 15:44:55 by showard       #+#    #+#                 */
/*   Updated: 2025/08/06 14:12:00 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_lstdelcontent(void *content)
{
	free(content);
	content = NULL;
}

char	**lst_to_2darray(t_data *data)
{
	char	**map;
	int		lines;
	t_list	*current;
	int		i;

	i = 0;
	current = data->l_map;
	lines = count_list(data->l_map);
	map = (char **)malloc((lines + 1) * sizeof(char **));
	if (map == NULL)
		werror("Malloc failure in map initialization", data);
	while (current)
	{
		map[i] = ft_strdup_nonl((char *)current->content);
		if (map[i] == NULL)
			werror("Malloc failure in map initialization", data);
		current = current->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	atoi_overflow(const char *nptr, t_data *data)
{
	int		sign;
	long	value;
	int		digit;

	sign = 1;
	value = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		digit = *nptr - '0';
		if (sign == 1 && (value > (INT_MAX - digit) / 10))
			werror("Integer overflow detected.", data);
		if (sign == -1 && (-value < (INT_MIN + digit) / 10))
			werror("Integer underflow detected.", data);
		value = value * 10 + digit;
		nptr++;
	}
	return (value * sign);
}

char	*ft_strdup_nonl(const char *s)
{
	int		length;
	int		i;
	char	*str;

	length = 0;
	i = 0;
	while (s[length] && s[length] != '\n')
		length++;
	str = (char *)malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < length)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	map_trim(t_data *data, char **start_line)
{
	int		line_count;
	char	**trimmed_map;
	int		i;

	i = 0;
	line_count = 0;
	if (start_line == NULL)
		werror("Reached end of file before finding map start", data);
	while (start_line[line_count] != NULL)
		line_count++;
	trimmed_map = (char **)malloc((line_count + 1) * sizeof(char *));
	if (trimmed_map == NULL)
		werror("Malloc failure", data);
	while (i < line_count)
	{
		trimmed_map[i] = ft_strdup(start_line[i]);
		i++;
	}
	trimmed_map[i] = NULL;
	free_2d(data->map);
	data->map = trimmed_map;
}
