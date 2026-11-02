/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:09:59 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/02 15:20:30 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models.h"
#include "lib.h"
#include "coder.h"

void    acquire_dongles(t_coder *coder)
{
    if (coder->id % 2 == 0)
    {
        acquire_dongle(coder, coder->right_dongle);
        acquire_dongle(coder, coder->left_dongle);
    }
    else
    {
        acquire_dongle(coder, coder->left_dongle);
        acquire_dongle(coder, coder->right_dongle);
    }
}

void    compile(t_coder *coder)
{
    log_message(coder, "is compiling");
    pthread_mutex_lock(coder->lock);
    (*coder->compile_done)++;
    pthread_mutex_unlock(coder->lock);
    usleep(coder->time_to_compile * 1000);
    update_compile_time(coder->left_dongle, coder);
    update_compile_time(coder->right_dongle, coder);
}

void    release_dongles(t_coder *coder)
{
    release_dongle(coder->left_dongle);
    release_dongle(coder->right_dongle);
}

void    debugging(t_coder *coder)
{  
    log_message(coder, "is debugging");
    usleep(coder->time_to_debug * 1000);
}

void    refractoring(t_coder *coder)
{
    log_message(coder, "is refractoring");
    usleep(coder->time_to_refractor * 1000);
}
