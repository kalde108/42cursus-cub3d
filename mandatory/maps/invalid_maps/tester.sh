# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 19:28:31 by ibertran          #+#    #+#              #
#    Updated: 2024/06/10 21:54:34 by ibertran         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# This script will try to

make -C ../..
chmod 000 assets/no_permissions.xpm

MAPS=*.cub
VALGRIND_LOG="valgrind.log"
VALGRIND_CMD="valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$VALGRIND_LOG"

cp ../../cub3D .
for map in $MAPS
do
	echo "\e[44m FILE: \e[0m $map \e[34m"
	echo
	cat $map
	echo "\e[0m"
	echo "\e[0m------------------------------------------------"
	echo ../../cub3D $map
	echo "\e[41m OUTPUT \e[0m\e[31m"
	echo
	$VALGRIND_CMD ./cub3D $map
	echo "\e[0m------------------------------------------------"
	VAR=`cat $VALGRIND_LOG | wc -l`
	if [ $VAR -gt 0 ]
	then
		exit 1
	fi
	rm $VALGRIND_LOG	
done
rm cub3D