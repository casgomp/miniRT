/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:02:40 by aabdella          #+#    #+#             */
/*   Updated: 2026/03/17 20:48:15 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static const char	*object_type_to_string(t_OBJECT_TYP type)
{
	if (type == SPHERE)
		return ("SPHERE");
	else if (type == CYLINDER)
		return ("CYLINDER");
	else if (type == PLANE)
		return ("PLANE");
	else if (type == CAMERA)
		return ("CAMERA");
	else if (type == LIGHT)
		return ("LIGHT");
	else if (type == AMBIENT_LIGHT)
		return ("AMBIENT_LIGHT");
	return ("UNKNOWN");
}

void	print_object_list(t_object *lst)
{
	while (lst)
	{
		printf("--------------- OBJECT ---------------\n");
		printf("ID: %d\n", lst->object_id);
		printf("Type: %s\n", object_type_to_string(lst->object_type));
		printf("RGB: ");
		if (lst->rgb)
			printf("%f %f %f\n", lst->rgb[0], lst->rgb[1], lst->rgb[2]);
		else
			printf("(null)\n");
		printf("Transform matrix:\n");
		if (lst->scale)
			printf("scale: %f, %f, %f, \n", lst->scale[0],
				lst->scale[1], lst->scale[2]);
		print_grid(lst->transform);
		printf("Inverse matrix:\n");
		print_grid(lst->inverse);
		printf("--------------------------------------\n\n");
		lst = lst->next;
	}
}

void	print_light_lst(t_light *lst)
{
	while (lst)
	{
		printf("--------------- LIGHT ---------------\n");
		printf("ID: %d\n", lst->id);
		printf("Type: %s\n", object_type_to_string(lst->type));
		printf("RGB: ");
		if (lst->rgb)
			printf("%f %f %f\n", lst->rgb[0], lst->rgb[1], lst->rgb[2]);
		else
			printf("(null)\n");
		if (lst->intensity)
			printf("Brightness: %f, %f, %f\n", lst->intensity[0],
				lst->intensity[1], lst->intensity[2]);
		if (lst->position)
			printf("light position: %f, %f, %f\n", lst->position[0],
				lst->position[1], lst->position[2]);
		printf("--------------------------------------\n\n");
		lst = lst->next;
	}
}

void	print_cam_lst(t_camera *lst)
{
	while (lst)
	{
		printf("--------------- CAMERA ---------------\n");
		printf("ID: %d\n", lst->id);
		printf("Type: %s\n", object_type_to_string(lst->type));
		printf("hsize: %f\n", lst->hsize);
		printf("vsize: %f\n", lst->vsize);
		printf("field of view : %f\n", lst->field_of_view);
		printf("Pixel size : %f\n", lst->pixel_size);
		printf("half width : %f\n", lst->half_width);
		printf("half height : %f\n", lst->half_height);
		printf("Transform matrix:\n");
		if (lst->transform)
			print_grid(lst->transform);
		printf("Inverse matrix:\n");
		if (lst->inverse)
			print_grid(lst->inverse);
		printf("--------------------------------------\n\n");
		lst = lst->next;
	}
}

void	print_world(t_world *world)
{
	print_cam_lst(world->camera);
	print_light_lst(world->light);
	print_object_list(world->object);
}
