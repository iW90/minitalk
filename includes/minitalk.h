/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:41:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/04/19 22:12:54 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "../ft_printf/includes/ft_printf.h"

int		ft_atoi(const char *str);
int		ft_isalldigit(char *str);
void	ft_putstr_fd(char *str, int fd);
void	exit_program(int ret, char *msg, int fd);

#endif