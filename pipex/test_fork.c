/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:38:58 by niabraha          #+#    #+#             */
/*   Updated: 2024/04/08 16:53:37 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    printf("Fork ici.\n");
    pid = fork();
    if (pid == -1)
        return (-1);
    printf("\nFork reussi !\n");
    if (pid == 0)
        printf("Fils: %d.\n", pid);
    else
        printf("Pere: %d.\n", pid);
    return(0);
}