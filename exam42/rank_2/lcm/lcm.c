unsigned int    lcm(unsigned int a, unsigned int b)
{
	int nb;

	if (a == 0 || b == 0)
		return (0);
	if (a > b)
		nb = a;
	else
		nb = b;
	while (1)
	{
		if (nb % a == 0 && nb % b == 0)
			return (nb);
		nb++;
	}
}