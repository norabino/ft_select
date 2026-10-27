#include "ft_select.h"

int	ft_putchar_select(int c)
{
	t_select *s;

	s = get_sel();
	ft_putchar_fd(c, s->fd);	
	return (0);
}

int clear_term()
{
	char	*cmdinfo;

	cmdinfo = tgetstr("cl", NULL);
	if (!cmdinfo)
	{
		ft_error("error: tgetstr\n");
		return (1);
	}
	if (tputs(cmdinfo, 1, ft_putchar_select) == -1)
	{
		ft_error("error: tputs\n");
		return (1);
	}
	return (0);
}

int identify_input(char *tab, int nb)
{
	if (nb <= 0)
	{
		return(ESCAPE);
	}
	if (nb == 1)
	{
		if (!ft_strncmp(tab, " ", nb))
			return(SPACE);
		else if (!ft_strncmp(tab, "\n", nb))
			return(ENTER);
		else if (!ft_strncmp(tab, "\033", nb))
			return(ESCAPE);
		else if (!ft_strncmp(tab, "\177", nb))
			return(BACKSPACE);
	}
	if (nb == 3)
	{
		if (!ft_strncmp(tab, "\033[A", nb))
			return(ARROW_UP);
		else if (!ft_strncmp(tab, "\033[B", nb))
			return(DOWN);
		else if (!ft_strncmp(tab, "\033[C", nb))
			return(RIGHT);
		else if (!ft_strncmp(tab, "\033[D", nb))
			return(LEFT);
	}
	if (nb == 4)
	{
		if (!ft_strncmp(tab, "\033[3~", nb))
			return(SUPPR);
	}
	return (-1);
}

int key_pressed(int input)
{
	if (input == SPACE)
		ft_printf("space\n");
	else if (input == ENTER)
	{
		ft_printf("enter\n");
		return (1);
	}
	else if (input == ESCAPE)
	{
		ft_printf("escape\n");
		return (1);
	}
	else if (input == BACKSPACE)
		ft_printf("backspace\n");
	else if (input == ARROW_UP)
		ft_printf("up\n");
	else if (input == DOWN)
		ft_printf("down\n");
	else if (input == RIGHT)
		ft_printf("right\n");
	else if (input == LEFT)
		ft_printf("left\n");
	else if (input == SUPPR)
		ft_printf("suppr\n");
	else
		ft_printf("other\n");
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
		if (key_pressed(input) == 1)
			break;
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
		ft_error("error: getenv\n");
		return (1);
	}
	if (tgetent(NULL, termname) != 1)
	{
		ft_error("error: tgetent\n");
		return (1);
	}
	if (clear_term())
		return (1);
	s->raw = s->orig;
	s->raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(s->fd, TCSANOW, &s->raw);	
	return (0);
}
