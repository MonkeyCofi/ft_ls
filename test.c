/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:42:30 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/22 12:19:10 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void exec(char **av, char **envp)
{
	char *cmd = "/bin/ls";

	__asm__("mov rax, 59;\n"
		"mov rdi, %[cmd]\n"
		"mov rsi, %[argv]\n"
		"mov rdx, %[envp]\n"
		"syscall\n"
		:
		: [cmd] "r" (cmd), [argv] "r" (av), [envp] "r" (envp)
		: "rax", "rdi", "rsi"
		);
}

int	main(int ac, char **av, char **envp)
{
	exec(av, envp);
}
