/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:09:59 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/10 15:02:02 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models.h"
#include "lib.h"
#include "coder.h"
#include "heap.h"
#include "utils.h"
#include "monitor.h"

void    acquire_dongles(t_coder *coder)
{
	t_dongle *first;
	t_dongle *second;

	if (check_burnout(coder))
		return ;
	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		first = coder->left_dongle;
		second = coder->right_dongle;
	}
	else
	{
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	enqueue(coder, first, second);
	acquire_dongle(coder, first, second);
}

void    compile(t_coder *coder)
{
    log_message(coder, "is compiling");
    pthread_mutex_lock(coder->lock);
    (*coder->compile_done)++;
    pthread_mutex_unlock(coder->lock);
    update_compile_time_coder(coder);
    smart_sleep(coder, coder->time_to_compile);
    update_compile_time_dongle(coder->left_dongle, coder);
    update_compile_time_dongle(coder->right_dongle, coder);
}

void    release_dongles(t_coder *coder)
{
    pthread_mutex_lock(&coder->left_dongle->lock);
    coder->left_dongle->state = cooldown;
    pthread_mutex_unlock(&coder->left_dongle->lock);
    pthread_mutex_lock(&coder->right_dongle->lock);
    coder->right_dongle->state = cooldown;
    pthread_mutex_unlock(&coder->right_dongle->lock);
}

void    debugging(t_coder *coder)
{  
    log_message(coder, "is debugging");
    smart_sleep(coder, coder->time_to_debug);
}

void    refractoring(t_coder *coder)
{
    log_message(coder, "is refractoring");
    smart_sleep(coder, coder->time_to_refractor);
}
