#include "ft_select.h"

int terminfo_exec(char *cmd, int col, int line)
{
	char	*cmdinfo;
	char	*gotostr;

	cmdinfo = tgetstr(cmd, NULL);
	if (!cmdinfo)
	{
		ft_error("error: tgetstr\n");
		return (1);
	}
	if (col != -1 && line != -1)
	{
		gotostr = tgoto(cmdinfo, col, line);
		cmdinfo = NULL;
		cmdinfo = gotostr;
	}
	if (tputs(cmdinfo, 1, ft_putchar_select) == -1)
	{
		ft_error("error: tputs\n");
		return (1);
	}
	return (0);
}

int read_inputs(t_select *s)
{
	char tab[8];
	int nb;
	int input;

	while (1)
	{
		ft_bzero(tab, 8);
		nb = read(s->fd, tab, 8);
		input = identify_input(tab, nb);
		if (s->count <= 0 || key_pressed(s, input) == 1)
			break ;
		if (print_elems(s))
			return (1);
	}
	return (0);
}

int init_terminal(t_select *s)
{
	char *path;
	char *termname;

	if (isatty(0) == 0)
	{
		ft_error("Can't execute ft_select in a pipe.\n");
		return (1);
	}
	path = ttyname(0);
	if (!path)
	{
		ft_error("error: ttyname(0)\n");
		return (1);
	}
	s->fd = open(path, O_RDWR);
	if (s->fd == -1)
	{
		ft_error("error: open()\n");
		return (1);
	}
	if (tcgetattr(s->fd, &s->orig)==-1)
	{
		ft_error("error: tcgetattr()\n");
		return (1);
	}
	termname = getenv("TERM");
	if (!termname)
	{
		ft_error("error: getenv. No environment found.\n");
		return (1);
	}
	if (tgetent(NULL, termname) != 1)
	{
		ft_error("error: tgetent\n");
		return (1);
	}
	if (terminfo_exec("vi", -1, -1))
		return (1);
	if (terminfo_exec("ti", -1, -1))
		return (1);
	s->raw = s->orig;
	s->raw.c_lflag &= ~(ICANON | ECHO);
	s->raw.c_cc[VMIN] = 1;
	s->raw.c_cc[VTIME] = 0;
	tcsetattr(s->fd, TCSANOW, &s->raw);
	s->term_ready = 1;
	return (0);
}

void check_cursor(t_select *s)
{
	if (s->cursor >= s->count)
		s->cursor = 0;
	if (s->cursor < 0)
		s->cursor = s->count - 1;
}

void	restore_terminal(t_select *s)
{
	terminfo_exec("ve", -1, -1);
	terminfo_exec("te", -1, -1);
	tcsetattr(s->fd, TCSANOW, &s->orig);
}