# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 19:28:31 by ibertran          #+#    #+#              #
#    Updated: 2024/05/01 20:00:45 by ibertran         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# This script will try to

make -C ../..

MAPS=*.cub

for map in $MAPS
do
	echo $map
	cat $map
	echo
	echo ------------------------------------------------
	echo ../../cub3D $map
	echo
	 valgrind -q ../../cub3D $map
	echo ------------------------------------------------
done