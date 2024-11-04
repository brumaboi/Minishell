/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:24:03 by marvin            #+#    #+#             */
/*   Updated: 2024/10/08 17:24:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void generate_dot(t_ast *node, FILE *file, int *node_count) {
//     if (node == NULL) return;

//     int current_id = (*node_count)++;
//     fprintf(file, "  node%d [label=\"", current_id);

//     // Print the current node type
//     switch (node->type) {
//         case N_COMMAND: fprintf(file, "COMMAND: %s", node->cmd_args ? node->cmd_args[0] : "NULL"); break;
//         case N_PIPE: fprintf(file, "PIPE"); break;
//         case N_AND: fprintf(file, "AND"); break;
//         case N_OR: fprintf(file, "OR"); break;
//         case N_GREAT: fprintf(file, "REDIRECT OUT: %s", node->file); break;
//         case N_DGREAT: fprintf(file, "APPEND: %s", node->file); break;
//         case N_LESS: fprintf(file, "REDIRECT IN: %s", node->file); break;
//         case N_DLESS: fprintf(file, "HEREDOC: %s", node->file); break;
//         default: fprintf(file, "UNKNOWN NODE"); break;
//     }

//     fprintf(file, "\"];\n");

//     if (node->left) {
//         int left_id = *node_count;
//         generate_dot(node->left, file, node_count);
//         fprintf(file, "  node%d -> node%d;\n", current_id, left_id);
//     }

//     if (node->right) {
//         int right_id = *node_count;
//         generate_dot(node->right, file, node_count);
//         fprintf(file, "  node%d -> node%d;\n", current_id, right_id);
//     }
// }

// void write_ast_to_dot(t_ast *ast, const char *filename) {
//     FILE *file = fopen(filename, "w");
//     if (!file) {
//         perror("Failed to open file");
//         return;
//     }

//     fprintf(file, "digraph AST {\n");
//     int node_count = 0;
//     generate_dot(ast, file, &node_count);
//     fprintf(file, "}\n");

//     fclose(file);
// }

void process_input(t_data *data)
{
    t_token *tokens;
    char *input;
    t_ast *ast;
    int  count;
    char **split_result;

    tokens = NULL;
    input = NULL;
    ast = NULL;
    split_result = NULL;
    count = 0;
    input = get_input(data);
    if (!input)
        return ;
    split_result = split_input(input, &count, &tokens);
    if (!split_result || !tokens)
    {
        free(input);
        return;
    }
    ast = build_ast(tokens);
    if (!ast)
    {
        free_tokens(tokens);
        free_split(split_result);
        free(input);
        return ;
    }
    // if (ast)
    // {
    //     write_ast_to_dot(ast, "ast.dot");
    //     printf("AST written to ast.dot. Use Graphviz to visualize.\n");
    // } else {
    //     printf("Failed to build AST\n");
    // }
    execute_asts(ast, data);
    free_ast(ast);
    free_tokens(tokens);
    free_split(split_result);
    free(input);
}

void free_env_vars(t_var *env)
{
    t_var *tmp;
    while (env) {
        tmp = env;
        env = env->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
    }
}

int main(int argc, char **argv, char **env)
{
    t_data data;

    (void)argc;
    (void)argv;
    init_data(&data, env);  //initialize env and exp linked lists
    init_signals(); //set up signal handlers
    while(1)
    {
        process_input(&data);
    }
    free_env_vars(data.env);
    free_env_vars(data.exp);
    return (0);
}
