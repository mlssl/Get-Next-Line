/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaussel <mlaussel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:45:15 by mlaussel          #+#    #+#             */
/*   Updated: 2024/11/27 15:58:01 by mlaussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// IL FAUT LIRRE DE BUFFER_SIZE EN BUFFER_SIZE ET LE STOCKER.
// ENSUITE ON CHERCHE DANS LE STOCK SI Y A \N

static int	ft_find_end_line(char *str)
{
	int	i;

	i = 0;
	while (i <= BUFFER_SIZE && str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_extract_line(char **rest)
{
	int		i;
	char	*line;
	char	*buf;

	i = 0;
	while (rest[i] != '\n' && rest[i] != '\0' && i <= BUFFER_SIZE)
		i++;
	if (rest[i] == '\n') // ligne se terminant par /n
	{
		line = ft_substr(rest, 0, i + 1); //+1 pour avoir le \n
		if (line == NULL)
			return (NULL);
		buf = ft_strdup(*rest + i + 1); // Reste après '\n'
		if (buf == NULL)
			return (NULL);
		free(*rest);
		*rest = buf;
		return (line);
	}
	if (rest[i] == '\0') // fin du fichier NON PAS FORCEMENT
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	line = ft_strdup(rest); // Copie ce qui reste sinon
	return (line);
}
// rest = chaine de i + 1 (car on ne veut pas le /n) a la taille de la chaine - i

char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		check_read;
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0) // verifie si les conitions sont ok
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)); // prepare le tempon a recevoir BUFFER_SIZE octetc
	if (buffer == NULL)
		return (NULL);
	check_read = 1;
	while (check_read > 0)
	{
		check_read = read(fd, buffer, BUFFER_SIZE);// verifie si la lecture n'a pas eu d'erreurs
		if (check_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[check_read + 1] = '\0'; // ferme correctement la chaine buffer. +1 pour arriver au \0
		rest = ft_strjoin(rest, buffer); // met la suite de la lecture ??
		if (rest == NULL)
		{
			return (NULL);
			free (buffer);
		}
	}
	line = ft_extract_line(rest); // extrait la line, elle sera ecrite si on a un /n, sinon
	if (line = NULL)
		return (NULL);
	free(buffer);
	return (line);
}

//CHECK CE QUE FANNY A ENVOYE

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
