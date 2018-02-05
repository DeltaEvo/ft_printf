#include "ft_printf.h"
#include "eval.h"
#include "write.h"
#include <unistd.h>

ssize_t	ft_printf(char const *fmt, ...)
{
	va_list	ap;
	ssize_t	r;

	va_start(ap, fmt);
	r = ft_vprintf(fmt, ap);
	va_end(ap);
	return (r);
}

ssize_t	ft_vprintf(char const *fmt, va_list ap)
{
	return (ft_vdprintf(STDOUT_FILENO, fmt, ap));
}

ssize_t	ft_dprintf(int fd, char const *fmt, ...)
{
	va_list	ap;
	ssize_t	r;

	va_start(ap, fmt);
	r = ft_vdprintf(fd, fmt, ap);
	va_end(ap);
	return (r);
}

ssize_t	ft_vdprintf(int fd, char const *fmt, va_list ap)
{
	t_ctx ctx;

	ctx = (t_ctx) {
		.va = (t_va_slist) {
			.idx = 0,
			.lock = 0
		},
		.idx = 0,
		.write = outn,
		.write_data = &fd
	};
	va_copy(ctx.va.ap, ap);
	eval_fmt((char *)fmt, ctx);
	outflush(&ctx);
	return (0);
}

ssize_t	ft_asnprintf(char **out, char const *fmt, ...)
{
	(void)out;
	(void)fmt;
	return (0);
}

ssize_t	ft_vasnprintf(char **out, char const *fmt, va_list ap)
{
	(void)out;
	(void)fmt;
	(void)ap;
	return (0);
}