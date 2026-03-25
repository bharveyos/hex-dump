SRC_DIR := ./src

hex-dump:
	$(CC) $(SRC_DIR)/main.c -Wall -O0 -Werror -o hex-dump