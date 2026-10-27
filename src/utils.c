/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:43:22 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/27 12:38:01 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

void	print_error(char *message)
{
	printf("%s", message);

}
void    acquire_dongle(t_coder *coder, t_dongle *dongle)
{
    pthread_mutex_lock(coder->lock);
    while (dongle->state != unused)
        pthread_cond_wait(coder->cond, coder->lock);
    dongle->state = used;
    pthread_mutex_unlock(coder->lock);
}
