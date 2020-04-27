#include "comb.h"

void	print_depth(t_num *parent)
{
	int		*res;
	int		step;
	t_num	*tmp;
	t_num	*tmp2;
	t_num	*tmp3;
	t_num	*tmp4;
	t_num	*tmp5;

	for (int i = 0; i < parent->son_count; i++)
	{
		tmp = parent->sons[i];
		// printf("%d\n", tmp->value);
		for (int j = 0; j < tmp->son_count; j++)
		{
			tmp2 = tmp->sons[j];
			// printf("%d%d\n", tmp->value, tmp2->value);
			for (int k = 0; k < tmp2->son_count; k++)
			{
				tmp3 = tmp2->sons[k];
				// printf("%d%d%d\n",tmp->value, tmp2->value, tmp3->value);
				for (int l = 0; l < tmp3->son_count; l++)
				{
					tmp4 = tmp3->sons[l];
					// printf("%d%d%d%d\n",tmp->value, tmp2->value, tmp3->value, tmp4->value);
					for (int m = 0; m < tmp4->son_count; m++)
					{
						tmp5 = tmp4->sons[m];
						// printf("%d%d%d%d%d\n",tmp->value, tmp2->value, tmp3->value, tmp4->value, tmp5->value);
					}
				}
			}
		}
	}
}

void	print_width_2(int *tab, int range)
{
	int	i, j;

	i = 0;
	while (i < range)
	{
		j = i + 1;
		while (j < range)
		{
			printf("%d%d ", tab[i], tab[j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	print_width_3(int *tab, int range)
{
	int	i, j, k;

	i = 0;
	while (i < range)
	{
		j = i + 1;
		while (j < range)
		{
			k = j + 1;
			while (k < range)
			{
				printf("%d%d%d ", tab[i], tab[j], tab[k]);
				k++;
			}
			printf("\n");
			j++;
		}
		i++;
	}
}

void	print_width_4(int *tab, int range)
{
	int	i, j, k, l;

	i = 0;
	while (i < range)
	{
		j = i + 1;
		while (j < range)
		{
			k = j + 1;
			while (k < range)
			{
				l = k + 1;
				while (l < range)
				{
					printf("%d%d%d%d ", tab[i], tab[j], tab[k], tab[l]);
					l++;
				}
				printf("\n");
				k++;
			}
			j++;
		}
		i++;
	}
}

void	print_width_5(int *tab, int range)
{
	int	i, j, k, l, m;

	i = 0;
	while (i < range)
	{
		j = i + 1;
		while (j < range)
		{
			k = j + 1;
			while (k < range)
			{
				l = k + 1;
				while (l < range)
				{
					m = l + 1;
					while (m < range)
					{
						printf("%d%d%d%d%d ", tab[i], tab[j], tab[k], tab[l], tab[m]);
						m++;
					}
					l++;
					printf("\n");
				}
				k++;
			}
			j++;
		}
		i++;
	}
}
