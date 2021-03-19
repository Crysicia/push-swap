int		main(int argc, char *argv[])
{
	t_push_swap push_swap;

	init_push_swap(&push_swap);
	if (argc == 1)
		return (0);
	while (argc > 1)
	{
		if (is_duplicate(argv, argc)
			|| !parse_arguments(&push_swap.stacks, argv[argc - 1]))
			ft_error(&push_swap);
		argc--;
	}
	if (!parse_statements(&push_swap))
		ft_error(&push_swap);
	execute_statements(&push_swap);
	if (are_stacks_sorted(&push_swap.stacks))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_push_swap(&push_swap);
	return (0);
}
