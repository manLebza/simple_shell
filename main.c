#ifndef MAIN_H
#define MAIN_H

int putchar(char c);
int sizeof_string(char *str);
int builtin_functions(char *cmd, char envp[]);
int _strcmp(char *s1, char *s2);
int execution_handler(char *raw_cmd, char *env[], char *argv1);
int contains(char *str, char *keyword);
int print_env(char *envp[]);
int change_directory(char **parsed_cmd, char *envp[]);
void free_2d_array(char **);
char *find_path(char *env[]);
char *str_concat(char *s1, char *s2);
char **cmd_parser(char *cmd_to_parse);
char *strcpy(char *dest, char *src);
char *find _home_dir(char *envp[]);

#endif /* MAIN_H */
