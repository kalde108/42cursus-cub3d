int	get_relative_position(int f1, int f2)
{
	// int	diff;
	// int	relative_position;
	static int	relative_positions[4][4] = {
		{0, 1, 2, 3},
		{3, 0, 1, 2},
		{2, 3, 0, 1},
		{1, 2, 3, 0}
	};

	// diff = (f2 - f1) % 4;
	// relative_position = (diff + 4) % 4;
	// return (relative_position);
	return (relative_positions[f1][f2]);
}
