/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 14:22:54 by imarakho          #+#    #+#             */
/*   Updated: 2017/02/26 17:43:42 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 128
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

int					get_next_line(const int fd, char **line);

typedef struct		s_chain
{
	char			*ln;
	int				fd;
	struct s_chain	*next;
}					t_chain;

#endif
