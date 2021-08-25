CLIENT		= ./client/client

SERVER		= ./server/server

SRC_CLIENT	=	./client/client.c \
				./utils/utils.c

SRC_SERVER	=	./server/server.c \
				./utils/utils.c

OBJ_SERVER	= $(SRC_SERVER:.c=.o)

OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)

CC		= gcc

CFLAGS	= #-Werror -Wall -Wextra

RM		= rm -f

all:		$(CLIENT) $(SERVER)

$(SERVER):	$(OBJ_SERVER)
		$(CC) -o $(SERVER) $(OBJ_SERVER)

$(CLIENT):	$(OBJ_CLIENT)
		$(CC) -o $(CLIENT) $(OBJ_CLIENT)

clean:
		$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean:		clean
		$(RM) $(SERVER) $(CLIENT)

re:		fclean all