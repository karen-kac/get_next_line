/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:40:01 by myokono           #+#    #+#             */
/*   Updated: 2023/11/17 11:31:03 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

char	*get_next_line(int fd);

//size_t	ft_strlen(const char *str);


#endif