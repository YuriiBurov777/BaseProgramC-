
#ifndef STATICLIB_H
#define STATICLIB_H
#include <iostream>

namespace GreeteNMS
{
	class Greete
	{
	public:
		Greete(std::string Name) : Name(Name) {}

		std::string getNam() const;

	private:

		std::string Name;
	};


}
#endif
