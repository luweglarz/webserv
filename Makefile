# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 19:56:36 by lucocozz          #+#    #+#              #
#    Updated: 2022/04/30 16:03:24 by lucocozz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := webserv

CONFIG_FILE_NAME := "webserv.conf"
WEBSERV_PATH := "$(HOME)/.config/webserv/"
DEFAULT_PORT := "8080"
DEFAULT_ROOT := "/tmp/www/"

DEF := CONFIG_FILE_NAME WEBSERV_PATH DEFAULT_PORT DEFAULT_ROOT

DEFINES = $(addprefix -D ,$(foreach tmp,$(DEF),$(tmp)='$($(tmp))'))

SRC := 	main.cpp					\
		serverCore.cpp				\
		handleInput.cpp				\
		handleOutput.cpp			\
		handleConnection.cpp		\
		handleDeconnection.cpp		\
		handleSignal.cpp			\
		createServers.cpp			\
		closeServers.cpp			\
		eventLoop.cpp				\
		statusCode.cpp				\
		configData.cpp				\
		fileRelated.cpp				\
		locationRelated.cpp			\
		pathRelated.cpp				\
		stringRelated.cpp			\
		URLRelated.cpp

MAKE = make
MAKEFLAGS += --no-print-directory
CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -MMD -std=c++98 -Wpedantic -g3
BUILD_DIR := .build
INCLUDES_DIR := $(shell find includes -type d)
SOURCE_DIR := sources
DEP := $(SRC:%.cpp=$(BUILD_DIR)/%.d)
OBJ := $(DEP:.d=.o)

vpath %.cpp ./ $(shell find $(SOURCE_DIR) -type d)



all: $(NAME) config

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

config:
	mkdir -p $(WEBSERV_PATH)
	mkdir -p $(DEFAULT_ROOT)
	cp -r config/* $(WEBSERV_PATH)
	cp -r sites $(DEFAULT_ROOT)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(DEFINES) $(CXXFLAGS) $(INCLUDES_DIR:%=-I %) -c $< -o $@

.PHONY: all clean fclean re test config

-include $(DEP)
