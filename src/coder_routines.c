/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:09:59 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/06 14:19:36 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models.h"
#include "lib.h"
#include "coder.h"
#include "heap.h"

static void wait_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->lock);
	heap_push(&coder->left_dongle->heap, coder);
	pthread_mutex_lock(&coder->right_dongle->lock);
	heap_push(&coder->right_dongle->heap, coder);
	while(
		((coder->left_dongle->state != unused || coder->right_dongle->state != unused) ||
		(heap_peek(&coder->left_dongle->heap) != coder || heap_peek(&coder->right_dongle->heap) != coder)) &&
		(!*coder->burnout)
	)
	{
		pthread_mutex_unlock(&coder->left_dongle->lock);
		pthread_mutex_unlock(&coder->right_dongle->lock);
		usleep(2);
		pthread_mutex_lock(&coder->left_dongle->lock);
		pthread_mutex_lock(&coder->right_dongle->lock);
	}
	pthread_mutex_unlock(&coder->left_dongle->lock);
	pthread_mutex_unlock(&coder->right_dongle->lock);
}

void    acquire_dongles(t_coder *coder)
{
	wait_dongles(coder);
	acquire_dongle(coder, coder->left_dongle);
	acquire_dongle(coder, coder->right_dongle);
}

void    compile(t_coder *coder)
{
    log_message(coder, "is compiling");
    pthread_mutex_lock(coder->lock);
    (*coder->compile_done)++;
    pthread_mutex_unlock(coder->lock);
    update_compile_time_coder(coder);
    usleep(coder->time_to_compile * 1000);
    update_compile_time_dongle(coder->left_dongle, coder);
    update_compile_time_dongle(coder->right_dongle, coder);
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
