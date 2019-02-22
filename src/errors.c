/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:44:58 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/22 06:06:36 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

const char	*str_to_error(t_error err_id)
{
	if (err_id == ERR_UNEXPECTED)
		return ("Unexpected error");
	else if (err_id == ERR_NOCHAMPNAME)
		return ("No champion name");
	else if (err_id == ERR_OPTCONFLICT)
		return ("Please check your options carefully it seems that there is a "
				"conflict in it");
	else if (err_id == ERR_WRONGNOPT)
		return ("Champion number should be between 0 and 2147483647");
	else if (err_id == ERR_WRONGDUMPOPT)
		return ("Dump option number should be between 0 and 2147483647");
	else if (err_id == ERR_WRONGDEBUGOPT)
		return ("Wrong debug level");
	else if (err_id == ERR_NOCHAMPS)
		return ("Please load champions");
	else if (err_id == ERR_TOOMANYCHAMPS)
		return ("There is too many champions");
	else
		return ("Unknown error");
}
