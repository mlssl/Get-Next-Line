/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaussel <mlaussel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:45:15 by mlaussel          #+#    #+#             */
/*   Updated: 2024/11/26 15:53:57 by mlaussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*extrait la ligne jusqu`au \n et la renvoie*/
char	*ft_extract_line(char *buffer, int *index)
{
	char	*line;

	while (buffer[*index] != '\n' && buffer[*index] != '\0')
		(*index)++;
	if (buffer[index] == '\n')
		(*index)++;
	line = ft_substr(buffer, 0, *index);
	if (line == NULL)
		return (NULL);
	return (line);
}

/*lis le fichier et le stock dans un buffer*/
char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;
	int		index;
	int	count;
	int	check_read;

	count = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	if (read(fd, buffer, BUFFER_SIZE) < 0)
			return (-1);
	while (buffer != '\0')
	{
		line = ft_extract_line(buffer, &index);
		buffer = (buffer + index + 1);
		count++;
	}
	free(buffer);
	return (line);
}

/*
ssize_t version signe de size_t
ssize_t	read(int fd, void *buf, size_t count);
Paramètres :

fd : Le descripteur de fichier (file descriptor) qui
identifie la source d'entrée (obtenu, par exemple,
avec open ou des descripteurs prédéfinis comme STDIN_FILENO).
buf : Un pointeur vers un buffer (tableau) où les données lues seront stockées.
count : Le nombre maximal d'octets à lire.
Valeur de retour :

Le nombre d'octets réellement lus (peut être inférieur à count).
0 si la fin du fichier (EOF) est atteinte.
-1 en cas d'erreur, avec la variable globale errno définissant l'erreur.
*/

// substr renvoie une sous chaine en prenant
//le start d`une chaine et le nombre de commentaire
