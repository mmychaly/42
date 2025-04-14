#include "Serializer.hpp"
#include "Data.hpp"

int main(void)
{
	Data x = {42};
	uintptr_t raw = Serializer::serialize(&x);
	Data *ptr = Serializer::deserialize(raw);

	std::cout << "Original pointer: " << &x << std::endl;
	std::cout << "Deserialized pointer: " << ptr << std::endl;
	std::cout << "Data value: " << ptr->x << std::endl;

	if (&x == ptr)
		std::cout << "Success: Conversion match!" << std::endl;
	else
		std::cout << "Failure: Conversion do not match!" << std::endl;
	return (0);
}