
#include <stdlib.h>
#include <stdio.h>

char	*ft_itoa(int nbr)
{
	int nb_s;
	long nb_temp; //Лонг что бы ихбежать оверфлоу
	long temp_2;
	char *str;

	nb_s = 0;
	nb_temp = nbr;
	if (nb_temp < 0) //Если значение негативное то добавляем место под символ и преводим в позитовное 
	{
		nb_s++;
		nb_temp = -nb_temp;
	}
	temp_2 = nb_temp; //Инициализируем другую переменную так как его значение уйдет в ноль
	while (temp_2 > 0) //Вычеляем количестово сомволов в числе  //при этом если число 0 то цикл не сработает 
	{
		temp_2 /= 10;
		nb_s += 1;
	}
	if (nbr == 0) //Прорабатываем если число 0
		nb_s++;
	str = malloc(sizeof(char) * (nb_s + 1));
	if (str == NULL)
		return (0);
	str[nb_s] = '\0'; //Сразу символ конца строки 
	if (nbr == 0) //Размещаем 0 если число 0 
		str[0] = '0';
	if (nbr < 0) //Если число было негативное размещаем -
		str[0] = '-';
	while (nb_temp > 0) //Достаем символ каждого числа и вводим в строку 
	{
		str[nb_s - 1] = (nb_temp % 10) + '0';
		nb_temp /= 10;
		nb_s--;
	}
	return (str);
}
int main(void)
{
	char *str;

	str = ft_itoa(0);
	printf("str %s\n", str);
	return (0);
}