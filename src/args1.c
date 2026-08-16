/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassaf <nassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:38:04 by nassaf            #+#    #+#             */
/*   Updated: 2025/12/03 01:37:14 by nassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_num_of_args(int argc)
{
	if (argc != 2)
		return (1);
	return (0);
}

int	check_if_cub(char *argv)
{
	int	len;

	if (!argv)
		return (1);
	len = ft_strlen(argv);
	if (len < 4)
		return (1);
	if (argv[len -1] != 'b'
		|| argv[len - 2] != 'u'
		|| argv[len -3] != 'c'
		|| argv[len - 4] != '.' )
		return (1);
	return (0);
}

void	validate_args(int argc, char **argv)
{
	if (check_num_of_args(argc))
		error_exit("Arguments: only a map should be provided");
	if (check_if_cub(argv[1]))
		error_exit("Provided Map should be .cub format");
}
