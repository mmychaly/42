#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Error: Faults number of arguments\nFilename, s1, s2"<< std::endl;
		return (1);
	}

	std::string s1 = argv[2];
	std::string s2 = argv[3];
	std::string file_out_name = argv[1];
	file_out_name.append(".replace");
	std::stringstream buffer;

	std::ifstream file_in(argv[1]);
	if (file_in)
		buffer << file_in.rdbuf();
	else
	{
		std::cerr << "Error: Opening input file" << std::endl;
		return (1);
	}
	file_in.close();

	std::string text = buffer.str();
	size_t pos = 0;
	while ((pos = text.find(s1, pos)) != std::string::npos)
	{
		text = text.substr(0, pos) + s2 + text.substr(pos + s1.size());
		pos += s2.size();
	}

	std::ofstream file_out(file_out_name);
	if (file_out)
		file_out << text;
	else 
	{
		std::cerr << "Error: Opening output file" << std::endl;
		return (1);
	}
	file_out.close();
	return (0);	
}