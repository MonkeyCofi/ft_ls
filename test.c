/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:42:30 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/22 12:59:22 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	exec(char **av, char **envp)
{
	char	*cmd;

	cmd = "/bin/ls";
	__asm__("mov rax, 59;\n"
		"mov rdi, %[cmd]\n"
		"mov rsi, %[argv]\n"
		"mov rdx, %[envp]\n"
		"syscall\n"
		:
		: [cmd] "r" (cmd), [argv] "r" (av), [envp] "r" (envp)
		: "rax", "rdi", "rsi", "rdx"
		);
}

int	main(int ac, char **av, char **envp)
{
	exec(av, envp);
}
