/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_ray_intersect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:41:32 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/18 20:12:46 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_instersection_lst	allocte_intersect_data(int obj_id, double *t, t_ray *ray)
{
	t_instersection_lst		lst;
	int						hit_index;

	lst = (t_instersection_lst){0};
	if (t[0] > t[1])
		hit_index = 0;
	else
		hit_index = 1;
	lst.t = malloc (2 * sizeof(double));
	if (!lst.t)
		return (perror(MALL_ERR), (t_instersection_lst){0});
	lst.t[0] = t[0];
	lst.t[1] = t[1];
	lst.next = NULL;
	lst.points_lst = ray_sphere_points(ray->ray_origin,
			ray->ray_direction, t);
	lst.object_id = obj_id;
	lst.hit = t[hit_index];
	lst.hit_points = lst.points_lst[hit_index];
	return (lst);
}

t_instersection_lst	*append_intersect_arr(int obj_id, double *t,
	t_instersection_lst *lst, t_ray *ray)
{


}

t_ray	construct_ray(double *ray_origin, double *ray_direction
	, t_objects *obj_lst)
{
	t_ray	ray;

	ray = (t_ray){0};
	ray.ray_origin = ray_origin;
	ray.ray_direction = ray_direction;
	while (obj_lst)
	{
		if (obj_lst->object_type == SPHERE)
			ray.intersection_lst->t = ray_sphere_intersection(ray_origin,
					ray_direction, obj_lst->u_obj.sphere->center);
		if (!ray.intersection_lst->t)
		{
			if (obj_lst->object_type == CYLINDER)
				//CYlinder hit function
		}
		if (!ray.intersection_lst->t)
		{
			if (obj_lst->object_type == PLANE)
				/// plane hit function ;
		}
		if (ray.intersection_lst->)
			//append function to the intersection lst ;;
		obj_lst = obj_lst -> next;
	}
}
