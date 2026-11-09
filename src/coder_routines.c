/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:09:59 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/09 13:50:41 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models.h"
#include "lib.h"
#include "coder.h"
#include "heap.h"
#include "utils.h"

void    acquire_dongles(t_coder *coder)
{
    if (!*coder->burnout)
    {
        enqueue(coder, coder->left_dongle, coder->right_dongle);
        if (coder->id % 2 == 0)
            acquire_dongle(coder, coder->right_dongle, coder->left_dongle);
        else
            acquire_dongle(coder, coder->left_dongle, coder->right_dongle);
    }
}

void    compile(t_coder *coder)
{
    log_message(coder, "is compiling");
    pthread_mutex_lock(coder->lock);
    (*coder->compile_done)++;
    pthread_mutex_unlock(coder->lock);
    update_compile_time_coder(coder);
    // smart_sleep(coder, coder->time_to_compile);
    usleep(coder->time_to_compile * 1000);
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
    // release_dongle(coder->right_dongle);
    pthread_mutex_unlock(&coder->right_dongle->lock);
}

void    debugging(t_coder *coder)
{  
    log_message(coder, "is debugging");
    // smart_sleep(coder, coder->time_to_debug);
    usleep(coder->time_to_debug * 1000);
}

void    refractoring(t_coder *coder)
{
    log_message(coder, "is refractoring");
    // smart_sleep(coder, coder->time_to_refractor);
    usleep(coder->time_to_refractor * 1000);
}
