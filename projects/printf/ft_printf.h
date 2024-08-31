/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 07:03:51 by mmychaly          #+#    #+#             */
/*   Updated: 2024/06/09 07:03:56 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
void	ft_put_symb(char symb, int *len);
void	ft_put_nbr(int nbr, int *len);
void	ft_put_str(char *str, int *len);
void	ft_put_unsigned_nbr(unsigned int nbr, int *len);
void	ft_put_hexadecimal(unsigned int nbr, char symb, int *len);
void	ft_put_ptr(void *ptr, int *len);

#endif