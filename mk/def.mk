# Commands definitions
RM=		rm -f
ECHO=		echo -ne
CP=		cp
CHDIR=		cd
IGNORE=		2> /dev/null ||:

INSTALL_DIR=	bin/
INSTALL_PATH=	$(ROOT_DIR)/$(INSTALL_DIR)

# Compilation and link definitions
CC=		gcc


# Debug Infos
ifeq ($(DEBUG), yes)
CFLAGS+=	-g -DDEBUG -fomit-frame-pointer 	\
		-fstack-protector			\
		-Wformat-security			\
		$(LOCAL_DEBUG_FLAGS)
ASFLAGS+=	-g
LDFLAGS+=	-g
else
CFLAGS+=	-DNDEBUG
LDFLAGS+=
endif

CFLAGS+=	$(INC_DIR)				\
		$(LOCAL_COMP_FLAGS)			\
		-W 					\
		-Wall 					\
		-Wextra	\
		-g

LDFLAGS+=	$(LOCAL_LINK_FLAGS)
