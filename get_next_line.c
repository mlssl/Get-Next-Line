/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathildelaussel <mathildelaussel@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:45:15 by mlaussel          #+#    #+#             */
/*   Updated: 2024/12/01 15:28:59 by mathildelau      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	print_debug_info(char *message)
{
    write(1, message, ft_strlen(message));
    write(1, "\n", 1);
}

static int	ft_find_end_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
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

	if (*rest == NULL)
		return (NULL);
	i = ft_find_end_line(*rest);
	if (i >= 0)
	{
		line = ft_substr(*rest, 0, i + 1);
		if (line == NULL)
			return (NULL);
		buf = ft_strdup(*rest + i + 1);
		if (buf == NULL)
		{
			free(line);
			return (NULL);
		}
		free(*rest);
		*rest = buf;
		return (line);
	}
	else if ((*rest)[i] != '\0')
	{
		line = ft_strdup(*rest);
		if (line == NULL)
		{
			free (line);
			return (NULL);
		}
		free(*rest);
		*rest = NULL;
		return (line);
	}
	free(*rest);
	*rest = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		check_read;
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
		
	print_debug_info("Début de la lecture...");
	
	check_read = 1;
	while (check_read > 0)
	{
		check_read = read(fd, buffer, BUFFER_SIZE);
		print_debug_info("Après lecture...");
		if (check_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[check_read] = '\0';
		rest = ft_strjoin(rest, buffer); 
		if (rest == NULL)
		{
			free (buffer);
			return (NULL);
		}
		print_debug_info("Contenu actuel du reste : ");
		print_debug_info(rest); // Afficher ce qui 
		if (ft_find_end_line(rest) >= 0)
            break ;
	}
	free(buffer);
	line = ft_extract_line(&rest);
	
	print_debug_info("Ligne extraite : ");
	print_debug_info(line); // Afficher la ligne extraite

	return (line);
}

//CHECK CE QUE FANNY A ENVOYE

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY); // Ouvrir le fichier
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	print_debug_info("Fichier ouvert avec succès");

	// Lire et afficher chaque ligne du fichier
	while ((line = get_next_line(fd)) != NULL)
	{
		print_debug_info("Affichage de la ligne...");
		printf("%s", line);
		free(line); // Libérer la mémoire allouée pour chaque ligne
	}
	close(fd); // Fermer le fichier
	return (0);
}