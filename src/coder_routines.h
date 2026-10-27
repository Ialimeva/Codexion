/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routines.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:39:32 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/27 11:58:42 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_ROUTINES_H
#define CODER_ROUTINES_H

#include "models.h"

void    acquire_dongles(t_coder *coder);
void    compile(t_coder *coder);
void    release_dongles(t_coder *coder);
void    debugging(t_coder *coder);
void    refractoring(t_coder *coder);

#endif