/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbank <dbank@student.codam.nl>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:48:50 by showard           #+#    #+#             */
/*   Updated: 2025/07/31 13:49:39 by dbank            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define RED 0
# define GREEN 1
# define BLUE 2
# include "game.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>

void	map_trim(t_data *data, char **start_line);
char	*ft_strdup_nonl(const char *s);
int		atoi_overflow(const char *nptr, t_data *data);
char	**lst_to_2darray(t_data *data);
void	werror(char *error_msg, t_data *data);
int		count_list(t_list *lst);
int		validate_elements(char **map, t_data *data);
bool	input_check(char *str, t_data *data);
void	validate_chars(t_data *data, char **map);
char	**find_start_line(char **map, int start_line);
void	flood_map(t_data *data, char **map, int x, int y);
void	map_init(t_data *data);
void	ft_lstdelcontent(void *content);

#endif