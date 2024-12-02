
// parsing version du 01.12.24 pour test
t_manager	*parsing(t_manager *manager, char *line)
{
	int		i;
	char	*word;
	int		type;

	i = 0;
	word = NULL;
	while (line[i])
	{
		type = 0;
		while (line[i] && ft_is_space(line[i]))
			i++;
		if 	(is_operators(manager, line, i) == -1)
			return (NULL);
		else if (is_operators(manager, line, i))
			{
			type = is_operators(manager, line, i);
			i++;
			}

		//if (is_operators(manager, line, i)) //>= 0)
		//{
		//	type = is_operators(manager, line, i);
		//	i++;
		//}
//		else
//			return (NULL);
		if (type == REDIR_APPEND || type == REDIR_HEREDOC)
			i++;
		if (type == DOUBLE_QUOTE || type == SIMPLE_QUOTE)
			i = handle_quote(line, i, type, &word);
		else
			i = regular_word(manager, line, i, &word);
		printf("word : [%s] of type [%d]\n", word, type);
		token_add_back(&(manager->token_first), token_new(word, type));
		free(word);
	}
	printf("display de la liste token\n");
	token_display(manager->token_first);
	return (manager);
}