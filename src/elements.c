/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   elements.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: showard <showard@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 15:45:03 by showard       #+#    #+#                 */
/*   Updated: 2025/07/01 15:32:13 by showard       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	validate_rgb(char *str, t_data *data, int *colour_arr)
{
	int	i;
	int	counter;
	int	num;

	i = 1;
	counter = 0;
	num = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0' && counter < 3)
	{
		if (str[i] == '-' || !ft_isdigit(str[i]))
			werror("RGB values incorrectly formatted\n", data);
		num = atoi_overflow(&str[i], data);
		colour_arr[counter] = num;
		while (ft_isdigit(str[i]))
			i++;
		counter++;
		if ((counter != 3 && str[i++] != ',') || (num < 0 || num > 255))
    		werror("RGB values incorrectly formatted.\n", data);
	}
	while (str[i] == ' ')
		i++;
	if (counter < 3 || str[i] != '\0')
		werror("RGB values incorrectly formatted.\n", data);
}

static char	*copy_path(const char *s, t_data *data)
{
	int		length;
	int		i;
	char	*str;

	length = 0;
	i = 0;
	while (s[length] && s[length] != ' ')
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
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			werror("Invalid element line found in file.", data);
		i++;
	}
	return (str);
}

static void	init_tex_path(char *map, t_data *data, char **path)
{
	int	i;

	i = 0;
	while (map[i] == ' ')
		i++;
	*path = copy_path(&map[i], data);
}

static bool	check_element(char *element, t_data *data)
{
	int	i;

	i = 0;
	if (element[i] == 'N' && (element[i + 1] == 'O') && data->n_tex == NULL)
		init_tex_path(&element[i + 2], data, &data->n_tex);
	else if (element[i] == 'S' && (element[i + 1] == 'O')
		&& data->s_tex == NULL)
		init_tex_path(&element[i + 2], data, &data->s_tex);
	else if (element[i] == 'W' && (element[i + 1] == 'E')
		&& data->w_tex == NULL)
		init_tex_path(&element[i + 2], data, &data->w_tex);
	else if (element[i] == 'E' && (element[i + 1] == 'A')
		&& data->e_tex == NULL)
		init_tex_path(&element[i + 2], data, &data->e_tex);
	else if (element[i] == 'F' && data->floor[0] == -1)
		validate_rgb(&element[i], data, data->floor);
	else if (element[i] == 'C' && data->ceiling[0] == -1)
		validate_rgb(&element[i], data, data->ceiling);
	else
		return (false);
	return (true);
}

int	validate_elements(char **map, t_data *data)
{
	int	i;
	int	j;
	int	element_count;

	i = 0;
	element_count = 0;
	data->floor[0] = -1;
	data->ceiling[0] = -1;
	while (map[i] != NULL && element_count != 6)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (check_element(&map[i][j], data) == false)
		{
			if (map[i][j] != '\0')
				werror("Invalid element line found in file.", data);
		}
		else
			element_count++;
		i++;
	}
	if (element_count != 6)
		werror("Couldn't find all required elements.", data);
	return (i);
}
