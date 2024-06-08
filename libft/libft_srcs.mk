# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_srcs.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kchillon <kchillon@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 06:32:49 by ibertran          #+#    #+#              #
#    Updated: 2024/06/07 19:14:39 by kchillon         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = srcs/
SRCS = \
	$(addprefix $(SRCS_DIR),$(SRC))	

# *** CHAR ******************************************************************* #

SRC += $(addprefix $(CHAR_DIR)ft_, $(addsuffix .c, $(CHAR_SRC))) \

CHAR_DIR = char/
CHAR_SRC = \
	isalnum \
	isalpha \
	isascii \
	ischarset \
	isdigit \
	isprint \
	isspace \
	tolower \
	toupper \

# *** STRING ***************************************************************** #

SRC += $(addprefix $(STR_DIR)ft_, $(addsuffix .c, $(STR_SRC)))

STR_DIR = str/
STR_SRC = \
	countwords \
	generate_rand_str \
	isnumber \
	replace_char \
	split \
	str_in_array \
	strchr \
	strcmp \
	strcpy \
	strdup \
	striteri \
	strjoin \
	strjoin2 \
	strlcat \
	strlcpy \
	strlen \
	strmapi \
	strncmp \
	strndup \
	strnstr \
	strpbrk \
	strrchr \
	strtok \
	strtrim \
	substr \

# *** INTERGER *************************************************************** #

SRC += $(addprefix $(INT_DIR)ft_, $(addsuffix .c, $(INT_SRC)))

INT_DIR = int/
INT_SRC = \
	abs \
	atoi \
	fabs \
	isrange \
	itoa \
	itoalen \
	strtoi \
	strtol \

# *** MATH ******************************************************************* #

SRC += $(addprefix $(MATH_DIR)ft_, $(addsuffix .c, $(MATH_SRC)))

MATH_DIR = math/
MATH_SRC = \
	euclidean_dist \
	rotate_v1 \
	rotate_v2 \
	rotate_v2_around \

# *** MEMORY ***************************************************************** #

SRC += $(addprefix $(MEM_DIR)ft_, $(addsuffix .c, $(MEM_SRC)))

MEM_DIR = mem/
MEM_SRC = \
	bzero \
	calloc \
	fmalloc \
	memchr \
	memcmp \
	memcpy \
	memcpy2 \
	memmove \
	memset \

# *** VECTOR ***************************************************************** #

SRC += $(addprefix $(VECTOR_DIR)ft_,$(addsuffix .c, $(VECTOR_SRC)))

VECTOR_DIR = vector/
VECTOR_SRC = \
	vector_add \
	vector_add_ptr \
	vector_alloc \
	vector_dealloc \
	vector_delete \
	vector_deleten \
	vector_free \
	vector_get \
	vector_init \
	vector_insert \
	vector_insert_ptr \
	vector_insertn \
	vector_join \
	vector_merge \
	vector_print \
	vector_replace \
	vector_resize \
	vector_search \
	vector_set \
	vector_set_ptr \
	vector_setn \
	vector_split \
	vector_strncat \
	vector_trim \
	vector_unlink \
	vector_sort \

SRC += $(addprefix $(VUTILS_DIR)ft_,$(addsuffix .c, $(VUTILS_SRC)))

VUTILS_DIR = $(VECTOR_DIR)utility/
VUTILS_SRC = \
	vclose \
	vfree \
	vprint_char \
	vprint_int \
	vprint_vchar \
	vprint_str \
	vvector_free \
	vsort_int_ascend \
	vsort_str_ascend

# *** LINKED LIST ************************************************************ #

SRC += $(addprefix $(LST_DIR)ft_, $(addsuffix .c, $(LST_SRC)))

LST_DIR = lst/
LST_SRC = \
	lstadd_back \
	lstadd_front \
	lstclear \
	lstdelone \
	lstiter \
	lstlast \
	lstmap \
	lstnew \
	lstsize \

# *** GET_NEXT_LINE ********************************************************** #

SRC += $(addprefix $(GNL_DIR), $(addsuffix .c, $(GNL_SRC)))

GNL_DIR = get_next_line/
GNL_SRC = \
	get_next_line \

# *** GET_FD_CONTENT ********************************************************* #

SRC += $(addprefix $(GFC_DIR), $(addsuffix .c, $(GFC_SRC)))

GFC_DIR = get_fd_content/
GFC_SRC = \
	get_fd_content \

# *** FT_PRINTF ************************************************************** #

SRC += $(addprefix $(PRINTF_DIR)ft_, $(addsuffix .c, $(PRINTF_SRC)))

PRINTF_DIR = ft_printf/
PRINTF_SRC = \
	converter/convert_char \
	converter/convert_hexlow \
	converter/convert_hexup \
	converter/convert_int \
	converter/convert_percent \
	converter/convert_string \
	converter/convert_uint \
	addconversion \
	dprintf \
	pf_build_buffer \
	pf_print_buffer \
	sprintf \

# *** MISCELLANEOUS ********************************************************** #

SRC += $(addprefix $(MISC_DIR)ft_, $(addsuffix .c, $(MISC_SRC)))

MISC_DIR = misc/
MISC_SRC = \
	close \
	free_array \
	free_2darray_char \
	tmp_file \
