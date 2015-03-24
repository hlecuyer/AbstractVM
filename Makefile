NAME				=		avm

SRC_DIR				=		srcs
INCLUDE_DIR			=		includes
BOOST_DIR			=		~/.brew/Cellar/boost/1.57.0/include
OBJ_DIR				=		objs

PCH					=		$(INCLUDE_DIR)/misc.hpp
PCH_SUFFIX			=		.gch
PCH_DIR				=		$(OBJ_DIR)/pch
PCH_TARGET			=		$(PCH_DIR)$(PCH_SUFFIX)/pch
PCH_FLAG			=		-include $(PCH_DIR)

COMPILER			=		/Volumes/Data/nfs/zfs-student-2/users/2013/hlecuyer/.brew/Cellar/gcc/4.9.2_1/bin/g++-4.9
CFLAGS				=		-std=c++1y -g3 -Wall -Wextra -Werror -c \
							-I$(INCLUDE_DIR) -I $(BOOST_DIR)
LFLAGS				=		-o

SRC					=		main.cpp		\
							parser.cpp		\
							VirtualMachine.cpp \
							OperandFactory.cpp

OBJ					=		$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILER) $(LFLAGS) $@ $^

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(PCH_TARGET)
	$(COMPILER) $(CFLAGS) $(PCH_FLAG) $< -o $@

$(PCH_TARGET): $(PCH)
	$(MAKE) $(OBJ_DIR)
	mkdir -p $(PCH_DIR)$(PCH_SUFFIX)
	@echo "precompiling headers"
	$(COMPILER) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
