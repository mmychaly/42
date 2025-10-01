#ifndef VECT_HPP
# define VECT_HPP

#include iostream
#include vector


class Vect
{
	public:
		Vect();
		Vect(int nb_1, int nb_2);
		Vect(const Vect& src);
		~Vect();

		int		get_element(int index) const;

		Vect	operator+(int nb) const;
		Vect	operator+(const Vect src) const;
		Vect&	operator++(void);//pre
		Vect	operator++(int);//post

		Vect operator-(int nb) const;

	private:
		std::vector _cont;
};

#endif