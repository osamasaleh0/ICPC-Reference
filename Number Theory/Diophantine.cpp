int gcd(int a, int b){
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int egcd(int a, int b, int&x, int &y){
	if (b == 0){
		x = 1;
		y = 0;
		return a;
	}
	
	int g, x1, y1;
	g = egcd(b, a % b, x1, y1);
	
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}

pair<int, int> find_solution(int a, int b, int c){
	int x, y, g;
	g = egcd(abs(a), abs(b), x, y);
	
	if (c % g)
		return make_pair(- 1, - 1);
	
	x *= c / g * (a / abs(a));
	y *= c / g * (b / abs(b));
	
	return make_pair(x, y);
}

void shift(int a, int b, int&x, int& y, int times){
	int g = gcd(a, b);
	x += times * b / g;
	y -= times * a / g;
}

void shift_to_minimum(int a, int b, int&x, int &y, int mn_x, int mn_y){
	int g = gcd(a, b);
	int dx = b / g, dy = a / g;
	
	if (x < mn_x)
		shift(a, b, x, y, (mn_x - x + dx - 1) / dx);
	if (y < mn_y)
		shift(a, b, x, y, (mn_y - y + dy - 1) / dy);
		
	shift(a, b, x, y, min((mn_x - x) / dx, (mn_y - y) / dy));
}

void shift_to_maximum(int a, int b, int&x, int&y, int mx_x, int mx_y){
	int g = gcd(a, b);
	int dx = b / g, dy = a / g;
	
	if (x > mx_x)
		shift(a, b, x, y, (x - mx_x + dx - 1) / dx);
	if (y > mx_y)
		shift(a, b, x, y, (y - mx_x + dy - 1) / dy);
		
	shift(a, b, x, y, min((mx_x - x) / dx, (mx_y - y) / dy));
}

int count_solutions(int a, int b, int&x, int &y, int mn_x, int mx_x, int mn_y, int mx_y){
	shift_to_minimum(a, b, x, y, mn_x, mn_y);
	
	if (x > mx_x || y > mx_y)
		return 0;
	
	int res_x = x, g = gcd(a, b);
	shift_to_maximum(a, b, x, y, mx_x, mx_y);
	return (x - res_x) / (b / g) + 1;
}
