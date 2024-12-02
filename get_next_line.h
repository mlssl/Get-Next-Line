/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaussel <mlaussel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:36:30 by mlaussel          #+#    #+#             */
/*   Updated: 2024/12/02 13:25:17 by mlaussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

char			*get_next_line(int fd);
size_t			ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *s);
char			*ft_substr(char *s, unsigned int start, size_t len);

#endif
