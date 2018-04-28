MK_DIR=		./mk/

include $(MK_DIR)color.mk $(MK_DIR)def.mk $(MK_DIR)local_def.mk

SRC_DIR=	./srv/src/

SRC_FILES=	main.c			\
			logger.c		\
			response.c		\
			utils.c			\
			utils_port.c	\
			commands.c		\
			cmd/abor.c		\
            cmd/cwd.c		\
            cmd/default.c	\
            cmd/delete.c	\
            cmd/list.c		\
            cmd/mkdir.c		\
            cmd/noop.c		\
            cmd/pass.c		\
            cmd/pasv.c		\
            cmd/pwd.c		\
            cmd/quit.c		\
            cmd/retr.c		\
            cmd/rmd.c		\
            cmd/size.c		\
            cmd/stor.c		\
            cmd/type.c		\
            cmd/user.c

BONUS_DIR=	./bonus/

BONUS_FILES=

SRC=		$(addprefix $(SRC_DIR), $(SRC_FILES))	\
		$(addprefix $(BONUS_DIR), $(BONUS_FILES))

include $(MK_DIR)rules.mk
