NAME = cub3D

# *** FILES ****************************************************************** #

MAKE_DIR := .make/
BUILD_DIR := $(MAKE_DIR)$(shell git branch --show-current)/

SRCS_DIR = srcs/
SRCS = $(addsuffix .c, $(SRC))

OBJS = $(patsubst %.c,$(BUILD_DIR)%.o,$(SRCS))

DEPS = $(patsubst %.o,%.d,$(OBJS))

SRC = \
	get_keyindex \
	main \
	render \

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
	convert_map \
	generate_map_charset \
	get_cell_value \
	get_cubscene \
	get_entities \
	get_player_spawn \
	get_portals \
	get_scene_map \
	get_scene_textures \
	is_player_enclosed \
	read_texture_directory \
	set_texture \

# ********** TEXTURES ********** #

SRC += $(addprefix $(TEXTURES_DIR),$(TEXTURES_SRC))

TEXTURES_DIR = textures/
TEXTURES_SRC = \
	init_attributes \
	get_attributes \
	get_average_color \
	set_animation_attr \
	set_frametime_attr \
	set_framestart_attr \

# ********** DRAW ********** #

SRC += $(addprefix $(DRAW_DIR),$(DRAW_SRC))

DRAW_DIR = draw/
DRAW_SRC = \
	draw_wall \
	draw_portal \
	draw_line \
	draw_line_minimap \
	draw_triangle \
	put_pixel \
	put_pixel_alpha \
	draw_rectangle \

# ********** HOOK ********** #

SRC += $(addprefix $(HOOK_DIR),$(HOOK_SRC))

HOOK_DIR = hook/
HOOK_SRC = \
	focusout_hook \
	keydown_hook \
	keyup_hook \
	mouse_hooks \

# ********** HUD ********** #

SRC += $(addprefix $(HUD_DIR),$(HUD_SRC))

HUD_DIR = hud/
HUD_SRC = \
	display_fps \
	crosshair \
	interaction_cooldown \
	hud \

#	# ****** MINIMAP ******* #

SRC += $(addprefix $(MINIMAP_DIR),$(MINIMAP_SRC))

MINIMAP_DIR = $(HUD_DIR)minimap/
MINIMAP_SRC = \
	minimap \
	is_on_minimap \
	player_angle \
	get_tile_color \
	mini_scene \
	mini_player \
	mini_view_cone \
	view_cone_x \

# ******** OPTIONS ********* #

SRC += $(addprefix $(OPTIONS_DIR),$(OPTIONS_SRC))

OPTIONS_DIR = options/
OPTIONS_SRC = \
	cub_options \
	op_fps \
	op_minimap_enable \
	op_minimap_lock \
	op_minimap_pos \
	op_minimap_size \
	op_minimap_view \
	op_minimap_zoom \

# ******* RAYCASTING ******* #

SRC += $(addprefix $(RAYCASTING_DIR),$(RAYCASTING_SRC))

RAYCASTING_DIR = raycasting/
RAYCASTING_SRC = \
	camera_rotation \
	ft_dda \
	get_line_y \
	get_relative_position \
	get_tex_x \
	get_wall_texture \
	ray_calculation \
	portal_hit_move \
	portal_hit \
	screen_raycast \
	single_raycast \

# ******* RENDERING ******** #

SRC += $(addprefix $(RENDERING_DIR),$(RENDERING_SRC))

RENDERING_DIR = rendering/
RENDERING_SRC = \
	background_row \
	render_background \
	render_wall \

# ********** TIME ********** #

SRC += $(addprefix $(TIME_DIR),$(TIME_SRC))

TIME_DIR = time/
TIME_SRC = \
	get_elapsed_time \
	get_time \
	init_timer \
	start_timer \
	timer_is_over \

# ********* UPDATE ********* #

SRC += $(addprefix $(UPDATE_DIR),$(UPDATE_SRC))

UPDATE_DIR = update/
UPDATE_SRC = \
	interaction	\
	update_frames \
	update_mouse \
	update_portal_frames \
	update_portal_status \
	updates \

#	# *** UPDATE_PLAYER **** #

SRC += $(addprefix $(UPDATE_PLAYER_DIR),$(UPDATE_PLAYER_SRC))       

UPDATE_PLAYER_DIR = $(UPDATE_DIR)update_player/
UPDATE_PLAYER_SRC = \
	rotate_player \
	update_player \
	player_mouvement \
	player_rotation \
	x_mouvement \
	y_mouvement \

# *** LIBRARIES && INCLUDES  ************************************************* #

LIBS_PATH = \
	../libft/libft.a \
	../minilibx/libmlx_Linux.a \
		
LIBS = \
	$(patsubst lib%.a,%,$(notdir $(LIBS_PATH))) \
	X11 \
	m \
	z \
	Xext \
	pthread \

INCS_DIR = incs/
INCS = \
	$(INCS_DIR) \
	$(dir $(LIBS_PATH)) \
	$(addsuffix $(INCS_DIR),$(dir $(LIBS_PATH))) \

# *** CONFIG ***************************************************************** #

CFLAGS		=	-Wall -Wextra -Werror $(OFLAGS)
OFLAGS 		=	-O3

DEFINES		=	CPUCORES=$(shell cat /proc/cpuinfo | grep cores | wc -l)

CPPFLAGS 	=	$(addprefix -I, $(INCS)) \
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
else ifeq ($(MODE),4K)
DEFINES += RES_4K=1
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

.PHONY : 4K
4K :
	$(MAKE) MODE=4K

.PHONY : debug
debug :
	$(MAKE) MODE=debug

.PHONY : fsanitize
fsanitize :
	$(MAKE) MODE=fsanitize

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

.PHONY : print-%
print-% :
	@echo $(patsubst print-%,%,$@)=
	@echo $($(patsubst print-%,%,$@))

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

MAP = maps/hub.cub

.PHONY : callgrind
callgrind : debug
	$(CALLGRIND) ./$(NAME) $(MAP)

# *** SPECIAL TARGETS ******************************************************** #

-include $(DEPS)

.DEFAULT_GOAL := all

.SILENT : clean fclean re debug fsanitize norminette

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