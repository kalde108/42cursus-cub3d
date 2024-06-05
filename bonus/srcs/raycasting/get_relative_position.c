/*
Input : f1, f2 (facing directions)

	    2
	_________
	|		|
1	|		| 3
	|		|
	---------
	    0


Output : relative position of f2 from f1

0 : same face
1 : left face
2 : opposite face
3 : right face
*/

int	get_relative_position(int f1, int f2)
{
	static const int	relative_positions[4][4] = {
	{0, 1, 2, 3},
	{3, 0, 1, 2},
	{2, 3, 0, 1},
	{1, 2, 3, 0}
	};

	return (relative_positions[f1][f2]);
}
