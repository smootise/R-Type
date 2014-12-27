#include "LinDllLoader.h"


LinDllLoader::LinDllLoader()
{
}


LinDllLoader::~LinDllLoader()
{
	//on free les librairies
	for (it_type it = _availlable_libs.begin(); it != _availlable_libs.end(); it++)
	{
		dlclose(it->second);
		std::cout << "Librairie closed : " << it->first << std::endl;
	}
}

void				LinDllLoader::loadfromfile(const std::string &filename)
{
	std::string		line;
	std::ifstream	myfile(filename.c_str());

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		if (line.empty() == false) //si la ligne est valide
		{
			if (_availlable_libs.count(line) <= 0) //si la lib n'est pas déja présente ds la map
			{
				void				*lib = NULL;

				lib = dlopen(line.append(".so").c_str(), RTLD_LAZY); //on load la librairie
				if (lib != NULL)
				{
					_availlable_libs[line] = lib;
					std::cout << "j'ajoute une lib : " << line.append(".so") << std::endl;
				}
				else
					std::cerr << "unable to load lib : " << line.append(".so") << std::endl;
			}
		}
		myfile.close();
	}
	else
		std::cerr << "unable to open the file that contains libs to load" << std::endl;
}

//le nom envoyé doit correspondre a celui qui est dans le fichier a la lettre près !
AMonster	*LinDllLoader::get_instance(const std::string &type, int timing)
{
	AMonster	*(*external_creator)(int);
	std::string	so(type);

	so.append(".so");
	if (_availlable_libs.count(so) > 0)
	{
		external_creator = reinterpret_cast<AMonster* (*)(int)>(dlsym(_availlable_libs[so], "create"));
		AMonster	*ret;

		ret = external_creator(timing);
		return (ret);
	}
	else
		std::cerr << "unable to get instance of lib :" << type << std::endl;
	return (NULL);
}