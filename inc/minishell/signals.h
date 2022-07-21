#ifndef SIGNALS_H
# define SIGNALS_H

# define SIG_ERROR 130

void	manage_signal(void);
void	signal_heredoc(void);
void	signal_child(void);
void	signal_ignore(void);

void	free_all(void);

#endif
