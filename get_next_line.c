/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaussel <mlaussel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:45:15 by mlaussel          #+#    #+#             */
/*   Updated: 2024/12/02 15:50:58 by mlaussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static int	ft_find_end_line(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_free(char *str)
{
	if (str != NULL)
		free(str);
	return (NULL);
}

static char	*ft_extract_rest(char *rest, char *buffer, int fd)
{
	int		check_read;
	char	*temp;

	check_read = 1;
	while (check_read > 0)
	{
		check_read = read(fd, buffer, BUFFER_SIZE);
		if (check_read < 0)
			return (NULL);
		if (check_read == 0)
			break ;
		buffer[check_read] = '\0';
		if (rest == NULL)
			rest = ft_strdup("");
		temp = rest;
		rest = ft_strjoin(rest, buffer);
		free(temp);
		temp = NULL;
		if (ft_find_end_line(rest) >= 0)
			break ;
	}
	return (rest);
}

static char	*ft_extract_line(char **rest)
{
	int		i;
	char	*line;
	char	*buf;

	if (*rest == NULL)
		return (NULL);
	i = ft_find_end_line(*rest);
	if (i >= 0)
	{
		line = ft_substr(*rest, 0, i + 1);
		buf = ft_substr(*rest, i + 1, ft_strlen(*rest) - i);
		free(*rest);
		*rest = buf;
		return (line);
	}
	else
	{
		line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
		return (line);
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	rest = ft_extract_rest(rest, buffer, fd);
	free (buffer);
	line = ft_extract_line(&rest);
	return (line);
}

//CHECK CE QUE FANNY A ENVOYE

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY); // Ouvrir le fichier
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}

// 	// Lire et afficher chaque ligne du fichier
// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line); // Libérer la mémoire allouée pour chaque ligne

// 	// }
// 	close(fd); // Fermer le fichier
// 	return (0);
// }
