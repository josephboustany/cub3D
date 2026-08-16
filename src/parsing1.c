/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 23:09:08 by nassaf            #+#    #+#             */
/*   Updated: 2026/02/22 20:07:00 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	cub_size(char *cub_name)
{
	int		fd;
	int		total_bytes;
	char	temp;

	fd = open(cub_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	total_bytes = 0;
	while (read(fd, &temp, 1) > 0)
		total_bytes++;
	close(fd);
	return (total_bytes);
}

char	*cub_to_str(char *cub_name)
{
	int		fd;
	int		total_bytes;
	int		read_bytes;
	char	*str;

	total_bytes = cub_size(cub_name);
	if (total_bytes < 0)
		error_exit("Failed to open file in read_cub function");
	str = malloc(sizeof(char) * (total_bytes + 1));
	if (!str)
		error_exit("Malloc failed in read_cub function");
	fd = open(cub_name, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file in read_cub function");
	read_bytes = read(fd, str, total_bytes);
	if (read_bytes < 0)
		error_exit("Read error in read_cub function");
	str[total_bytes] = '\0';
	close(fd);
	return (str);
}

int	count_lines(char *str)
{
	int		i;
	int		lines;

	i = 0;
	lines = 0;
	if (!str || str[0] == '\0')
		error_exit("Empty .cub file");
	lines = 1;
	while (str[i])
	{
		if (str[i] == '\n')
			lines++;
		i++;
	}
	return (lines);
}

char	**allocate_array(int lines)
{
	char	**array;

	array = malloc(sizeof(char *) * (lines + 1));
	if (!array)
		error_exit("Malloc failed in alloc_cub_array");
	return (array);
}

char	*get_line(char *str, int i)
{
	int		j;
	int		k;
	char	*line;

	j = 0;
	k = 0;
	while (str[i + j] && str[i + j] != '\n')
		j++;
	line = malloc(sizeof(char) * (j + 1));
	if (!line)
		error_exit("Malloc failed in get_line function");
	while (k < j)
	{
		line[k] = str[i + k];
		k++;
	}
	line[k] = '\0';
	return (line);
}
