#pragma once
struct Coordinates
{
	int x;
	int y;
	Coordinates(int x,int y):x{x},y{y}
	{

	}
	Coordinates()
	{
		x = 0;
		y = 0;
	}
	

	bool operator!=(const Coordinates& compared) const
	{
		if (x == compared.x and y == compared.y)
		{
			return false;
		}
		return true;
	}

	bool operator==(const Coordinates& compared) const
	{
		if (x != compared.x or y != compared.y)
		{
			return false;
		}
		return true;
	}
};