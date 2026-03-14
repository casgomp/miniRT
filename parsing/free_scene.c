/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:59:44 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/14 16:09:39 by pecastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_object_list(t_object *lst)
{
	t_object	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->transform)
			free_grid(lst->transform);
		if (lst->inverse)
			free_grid(lst->inverse);
		if (lst->rgb)
			free(lst->rgb);
		if (lst->scale)
			free(lst->scale);
		if (lst->material)
			free(lst->material);
		free(lst);
		lst = tmp;
	}
}

static void	free_light_list(t_light *lst)
{
	t_light		*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->position)
			free(lst->position);
		if (lst->rgb)
			free(lst->rgb);
		if (lst->intensity)
			free(lst->intensity);
		free(lst);
		lst = tmp;
	}
}

static void	free_cam_list(t_camera *lst)
{
	t_camera		*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->transform)
			free_grid(lst->transform);
		if (lst->inverse)
			free_grid(lst->inverse);
		free(lst);
		lst = tmp;
	}
}

void	free_world(t_world *scene)
{
	free_cam_list(scene->camera);
	free_light_list(scene->light);
	free_light_list(scene->ambient);
	free_object_list(scene->object);
	free(scene);
}