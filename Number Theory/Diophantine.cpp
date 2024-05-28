//complexity: O(log2(max(a, b, c)))
//practice problem: https://lightoj.com/problem/solutions-to-an-equation
//special cases: a = 0, b = 0 or a = b = 0

int64 gcd(int64 a, int64 b){
	if (b == 0)
		return a;
	return gcd(b, a % b);
}
	
int64 egcd(int64 a, int64 b, int64 &x, int64 &y){
	if (b == 0){
		x = 1, y = 0;
		return a;
	}
		
	int64 x1, y1, g;
	g = egcd(b, a % b, x1, y1);
	x = y1, y = x1 - (a / b) * y1;
	return g;
}

void shift(int64 a, int64 b, int64 &x, int64 &y, int64 times){
	int64 g = gcd(a, b);
	x += times * (b / g);
	y -= times * (a / g);
}

void shift_to_larger(int64 a, int64 b, int64 &x, int64 &y, int64 limit){
	int64 g = gcd(a, b);
	int64 dx = b / g;
	if (x < limit)
		shift(a, b, x, y, ((limit - x + abs(dx) - 1) / dx));
	shift(a, b, x, y, ((limit - x) / dx));
}

void shift_to_smaller(int64 a, int64 b, int64 &x, int64 &y, int64 limit){
	int64 g = gcd(a, b);
	int64 dx = b / g;
	if (x > limit)
		shift(a, b, x, y, (limit - x - abs(dx) + 1) / dx);
	shift(a, b, x, y, (limit - x) / dx);
}

int64 count_solutions(int64 a, int64 b, int64 c, int64 mn_x, int64 mx_x, int64 mn_y, int64 mx_y){
	int64 x, y, g;
	g = egcd(abs(a), abs(b), x, y);
	
	if (c % g)
		return 0;
	
	x = x * (c / g) * (a / abs(a));
	y = y * (c / g) * (b / abs(b));
	
	shift_to_larger(a, b, x, y, mn_x);
	if (y < mn_y)
		shift_to_larger(b, a, y, x, mn_y);
	if (y > mx_y)
		shift_to_smaller(b, a, y, x, mx_y);
	if (x < mn_x || x > mx_x || y < mn_y || y > mx_y)
		return 0;
	
	int64 res_x = x;
	
	shift_to_smaller(a, b, x, y, mx_x);
	if (y < mn_y)
		shift_to_larger(b, a, y, x, mn_y);
	if (y > mx_y)
		shift_to_smaller(b, a, y, x, mx_y);
		
	return abs((x - res_x) / (b / g)) + 1;
}
