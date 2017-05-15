#include "ListOfAdjacency.h"



//void ListOfAdjacency::fillingList(Grid grid)
//{
//	int n = grid.n, m = grid.m;
//	list.resize(m * n);
//	for (int j = 0; j < m; ++j)
//	{
//		for (int i = 0; i < n; ++i)
//		{
//			int k = grid.calculatePosistion(i, j);
//			for (int j1 = -2; j1 < 1; ++j1)
//			{
//				for (int i1 = -2; i1 < 3; ++i1)
//				{
//					int ii = i + i1, jj = j + j1;
//					int k1 = grid.calculatePosistion(ii, jj);
//					if (k1 != -1 && k1 < k)
//					{
//						list[k].push_back(k1);
//					}
//				}
//			}
//		}
//	}
//}

void ListOfAdjacency::fillingList(Grid grid)
{
	int n = grid.n, m = grid.m;
	int j1, i1, comparsionI, comparsionJ = 1;
	list.resize(m * n);
	for (int j = 0; j < m; ++j)
	{
		for (int i = 0; i < n; ++i)
		{
			int k = grid.calculatePosistion(i, j);
			if (j % 2 == 0)
			{
				j1 = -2;
			}
			else
			{
				j1 = -1;
			}
			for (;j1 < comparsionJ; ++j1)
			{
				if (i % 2 == 0)
				{
					i1 = -2;
					comparsionI = 3;
				}
				else
				{
					i1 = -1;
					comparsionI = 2;
				}
				for (;i1 < comparsionI; ++i1)
				{
					int ii = i + i1, jj = j + j1;
					int k1 = grid.calculatePosistion(ii, jj);
					if (k1 != -1 && k1 < k)
					{
						list[k].push_back(k1);
					}
				}
			}
		}
	}
}