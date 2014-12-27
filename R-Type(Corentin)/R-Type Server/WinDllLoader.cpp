#include "WinDllLoader.h"


WinDllLoader::WinDllLoader()
{

}


WinDllLoader::~WinDllLoader()
{
	//on free les librairies
	for (it_type it = _availlable_libs.begin(); it != _availlable_libs.end(); it++)
	{
		FreeLibrary(it->second);
		std::cout << "Librairie closed : " << it->first << std::endl;
	}
}

void				WinDllLoader::loadfromfile(const std::string &filename)
{
	std::string		line;
	std::ifstream	myfile(filename);

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		if (line.empty() == false) //si la ligne est valide
		{
			if (_availlable_libs.count(line) <= 0) //si la lib n'est pas déja présente ds la map
			{
				HINSTANCE				lib = NULL;

				lib = LoadLibrary(TEXT(line.c_str())); //on load la librairie
				if (lib != NULL)
				{
					_availlable_libs[line] = lib;
					std::cout << "j'ajoute une lib : " << line.append(".dll") << std::endl;
				}
				else
					std::cerr << "unable to load lib : " << line.append(".dll") << std::endl;
			}
		}
		myfile.close();
	}
	else
		std::cerr << "unable to open the file that contains libs to load" << std::endl;
}

//le nom envoyé doit correspondre a celui qui est dans le fichier a la lettre près !
AMonster	*WinDllLoader::get_instance(const std::string &type, int timing, int id)
{
	AMonster	*(*external_creator)(int, int);

	if (_availlable_libs.count(type) > 0)
	{
		external_creator = reinterpret_cast<AMonster* (*)(int, int)>(GetProcAddress(_availlable_libs[type], "create"));
		AMonster	*ret;

		ret = external_creator(timing, id);
		return (ret);
	}
	else
		std::cerr << "unable to get instance of lib :" << type << std::endl;
	return (NULL);
}