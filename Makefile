NAME = cub3D

# *** FILES ****************************************************************** #

MAKE_DIR := .make/
BUILD_DIR := $(MAKE_DIR)$(shell git branch --show-current)/

SRCS_DIR = srcs/
SRCS = $(addsuffix .c, $(SRC))

OBJS = $(patsubst %.c,$(BUILD_DIR)%.o,$(SRCS))

DEPS = $(patsubst %.o,%.d,$(OBJS))

SRC = \
	main \
	render \
	update_player \
	get_coords \

# ********** ENV ********** #

SRC += $(addprefix $(INIT_DIR),$(INIT_SRC))

INIT_DIR = env/
INIT_SRC = \
	init_cubenv \
	destroy_scene \
	open_mlx_window \
	destroy_cubenv \
	load_textures \

# ********** PARSING ********** #

SRC += $(addprefix $(PARSING_DIR),$(PARSING_SRC))

PARSING_DIR = parsing/
PARSING_SRC = \
	check_arguments \
	set_texture \
	open_cub_file \
	get_scene_textures \
	get_scene_map \
	convert_map \
	get_player_spawn \
	is_xmp_file \
	is_player_enclosed \

# ********** DRAW ********** #

SRC += $(addprefix $(DRAW_DIR),$(DRAW_SRC))

DRAW_DIR = draw/
DRAW_SRC = \
	draw_v_line \
	floor_and_ceiling \
	get_wall_texture \
	get_tex_x \

# ********** HOOK ********** #

SRC += $(addprefix $(HOOK_DIR),$(HOOK_SRC))

HOOK_DIR = hook/
HOOK_SRC = \
	keydown_hook \
	keyup_hook \

# ******* RAYCASTING ******* #

SRC += $(addprefix $(RAYCASTING_DIR),$(RAYCASTING_SRC))

RAYCASTING_DIR = raycasting/
RAYCASTING_SRC = \
	ft_dda \
	get_line_y \
	ray_calculation \
	raycasting \

# ********** DEBUG ********** #

SRC += $(addprefix $(DEBUG_DIR),$(DEBUG_SRC))

DEBUG_DIR = DEBUG/
DEBUG_SRC = \
	DEBUG_REMOVE \
	DEBUG_PRINT_MAP \

# *** LIBRARIES && INCLUDES  ************************************************* #

LIBS_PATH = \
	libft/libft.a \
	minilibx/libmlx_Linux.a \
		
LIBS = \
	$(patsubst lib%.a,%,$(notdir $(LIBS_PATH))) \
	X11 \
	m \
	z \
	Xext \

INCS_DIR = incs/
INCS = \
	$(INCS_DIR) \
	$(dir $(LIBS_PATH)) \
	$(addsuffix $(INCS_DIR),$(dir $(LIBS_PATH))) \

# *** CONFIG ***************************************************************** #

CFLAGS		=	-Wall -Wextra -Werror $(OFLAGS)
OFLAGS 		=	-O3

CPPFLAGS 	= 	$(addprefix -I, $(INCS)) \
				$(addprefix -D, $(DEFINES)) \
				-MMD -MP \

LDFLAGS		=	$(addprefix -L, $(dir $(LIBS_PATH)))
LDLIBS		=	$(addprefix -l, $(LIBS))

MAKEFLAGS	=	--no-print-directory

# *** COMPILATION MODES ****************************************************** #

MODE_TRACE = $(MAKE_DIR).trace 
LAST_MODE = $(shell cat $(MODE_TRACE) 2>/dev/null)

MODE ?=

ifneq ($(MODE),)
BUILD_DIR := $(BUILD_DIR)$(MODE)/
endif

ifeq ($(MODE),debug)
CFLAGS := $(filter-out $(OFLAGS),$(CFLAGS)) -g3
else ifeq ($(MODE),fsanitize)
CFLAGS := $(filter-out $(OFLAGS),$(CFLAGS)) -g3 -fsanitize=address
else ifneq ($(MODE),)
ERROR = MODE
endif

ifneq ($(LAST_MODE),$(MODE))
$(NAME) : FORCE
endif

# *** MISC ******************************************************************* #

LOGFILE = $(MAKE_DIR).mklog

LOADING_BAR_SIZE = 48

# *** TARGETS **************************************************************** #

.PHONY : all
all : $(NAME)


$(NAME) : $(LIBS_PATH) $(OBJS) | PREMAKE
	@echo "$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)" >> $(LOGFILE)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(MODE)" > $(MODE_TRACE)
	@printf "\n$(BOLD)\n\
 ██████$(RED)╗$(RESET)██$(RED)╗$(RESET)   ██$(RED)╗$(RESET)██████$(RED)╗$(RESET) ██████$(RED)╗$(RESET) ██████$(RED)╗$(RESET) $(RESET)\n\
██$(RED)╔════╝$(RESET)██$(RED)║$(RESET)   ██$(RED)║$(RESET)██$(RED)╔══$(RESET)██$(RED)╗╚════$(RESET)██$(RED)╗$(RESET)██$(RED)╔══$(RESET)██$(RED)╗$(RESET)\n\
██$(RED)║$(RESET)     ██$(RED)║$(RESET)   ██$(RED)║$(RESET)██████$(RED)╔╝$(RESET)█████$(RED)╔╝$(RESET) ██$(RED)║$(RESET)  ██$(RED)║$(RESET)\n\
██$(RED)║$(RESET)     ██$(RED)║$(RESET)   ██$(RED)║$(RESET)██$(RED)╔══$(RESET)██$(RED)╗ ╚═══$(RESET)██$(RED)╗$(RESET)██$(RED)║$(RESET)  ██$(RED)║$(RESET)\n\
$(RED)╚$(RESET)██████$(RED)╗╚$(RESET)██████$(RED)╔╝$(RESET)██████$(RED)╔╝$(RESET)██████$(RED)╔╝$(RESET)██████$(RED)╔╝$(RESET)\n\
 $(RED)╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ $(RESET)\n\
                     @kchillon @ibertran\n"

$(BUILD_DIR)%.o : $(SRCS_DIR)%.c | count PREMAKE
	@true || echo "$(NAME)_object"
	$(eval COUNT_DONE := $(shell echo $$(($(COUNT_DONE) + 1))))
	$(eval LOADING_COMPLETED := $(shell echo "$(COUNT_DONE) * $(LOADING_BAR_SIZE) / $(COUNT_TOTAL)" | bc 2> /dev/null))
	@mkdir -p $(@D)
	@echo "$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@" >> $(LOGFILE)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BOLD)$(CC) $(BLUE)$(CFLAGS) $(YELLOW)$(patsubst $(MAKE_DIR)%, %, $(basename $@)) $(RESET)\n"
	@printf "🔧 $(BOLD)$(CYAN)Compiling sources: $(WHITE)["
	@for i in $(shell seq 1 $(LOADING_COMPLETED)); do printf "="; done 
	@for i in $(shell seq 1 $(shell echo "$(LOADING_BAR_SIZE) - $(LOADING_COMPLETED)" | bc 2> /dev/null)); do printf " "; done
	@printf "] $(shell echo "$(COUNT_DONE) * 100 / $(COUNT_TOTAL)" | bc 2> /dev/null)%%$(RESET)"

$(LIBS_PATH): FORCE | PREMAKE
	@$(MAKE) -C $(@D)

.PHONY : bonus
bonus :
	$(MAKE) MODE=bonus

.PHONY : debug
debug :
	$(MAKE) MODE=debug

.PHONY : fsanitize
fsanitize :
	$(MAKE) MODE=fsanitize

.PHONY : print
print :
	$(MAKE) MODE=debug DEFINES=PRINT

.PHONY : clean
clean :
	-for f in $(dir $(LIBS_PATH)); do $(MAKE) -s -C $$f $@; done
	rm -rf $(BUILD_DIR)
	@printf "🚮 $(BOLD)$(RED)$(NAME) building files removed!$(RESET)\n"

.PHONY : fclean
fclean :
	-for f in $(dir $(LIBS_PATH)); do $(MAKE) -s -C $$f $@; done
	rm -rf $(MAKE_DIR) $(NAME)
	@printf "🚮 $(BOLD)$(RED)$(NAME) files removed!$(RESET)\n"

.PHONY : re
re : fclean
	$(MAKE)

NORM_LOG = $(MAKE_DIR)norminette.log

.PHONY : norminette
norminette :
	-for f in $(dir $(LIBS_PATH)); do $(MAKE) -s -C $$f $@; done
	mkdir -p $(dir $(NORM_LOG))
	norminette $(INCS_DIR) $(SRCS_DIR) > $(NORM_LOG) || true
	if [ $$(< $(NORM_LOG) grep Error | wc -l) -eq 0 ]; \
		then echo "$(NAME): \e[32;49;1mOK!\e[0m"; \
		else echo "$(NAME): \e[31;49;1mKO!\e[0m" \
			&& < $(NORM_LOG) grep Error; fi
	$(RM) $(NORM_LOG)

.PHONY : print%
print% :
	@echo $(patsubst print%,%,$@)=
	@echo $($(patsubst print%,%,$@))

.PHONY : count
count :
ifneq ($(AS_COUNTED),TRUE)
	$(eval COUNT_TOTAL := $(shell $(MAKE) -j -n MODE=$(MODE) AS_COUNTED=TRUE | grep "$(NAME)_object" | wc -l))
	$(eval COUNT_DONE := 0)
endif

.PHONY : run
run : $(NAME)
	./$(NAME)

VALGRIND = \
	valgrind \
	--suppressions=.valgrindignore.txt \
	--leak-check=full \
	--trace-children=yes \
	--track-fds=yes \
	--show-leak-kinds=all \

.PHONY : valgrind
valgrind : debug
	$(VALGRIND) ./$(NAME)

CALLGRIND = \
	valgrind \
	--tool=callgrind \

.PHONY : callgrind
callgrind : debug
	$(CALLGRIND) ./$(NAME)

# *** SPECIAL TARGETS ******************************************************** #

-include $(DEPS)

.DEFAULT_GOAL := all

.SILENT : bonus clean fclean re debug %debug fsanitize norminette

.PHONY : FORCE
FORCE :

.PHONY : PREMAKE
PREMAKE :
ifneq ($(MODE),)
	@printf "🔨 $(BOLD)Building $(NAME)($(MODE))...$(RESET)\n"
else
	@printf "🔨 $(BOLD)Building $(NAME)...$(RESET)\n"
endif
	@rm -f $(LOGFILE)
ifeq ($(ERROR),MODE)
	$(error Invalid mode: $(MODE))
endif

# *** FANCY STUFF ************************************************************ #

RESET	=	\e[0m
ERASE	=	\033[2K\r
BOLD	=	\033[1m
UNDER	=	\033[4m
SUR		=	\033[7m
GREY	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m
C12	=	\033[39m
C13	=	\033[43m

# **************************************************************************** #