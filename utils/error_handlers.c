/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abergman <abergman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:53:50 by abergman          #+#    #+#             */
/*   Updated: 2024/10/18 17:12:58 by abergman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_error_message(char *error_msg, char *description, int quotes)
{
	char *message;
	
	message = ft_strdup("minishell: ");
	// message = 
}

int	ft_standart_error(int res)
{
	ft_putstr_fd("Error\nTry again.", 2);
	return (res);
}
