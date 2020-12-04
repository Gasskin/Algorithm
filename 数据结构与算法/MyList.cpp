#include "MyList.h"
#include<list>

typedef struct
{
	int x;
	int y;
}Position;

int main()
{
	list<Position> list;
	for (int i = 0; i < 5; i++)
	{
		Position p;
		p.x = i;
		p.y = i + 1;
		list.push_back(p);
	}
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		cout << iter->y << " ";
	}
	return 0;
}