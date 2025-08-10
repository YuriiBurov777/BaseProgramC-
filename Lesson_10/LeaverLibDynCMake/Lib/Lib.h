

#ifndef LEAVERLIBDYN_H
#define LEAVERLIBDYN_H

#ifdef LEAVERLIBDYN_EXPORTS 
#define LEAVERLIBDYN_API __declspec (dllexport)
#else
#define LEAVERLIBDYN_API __declspec (dllimport)
#endif // !LEAVERLIBDYN_EXPORTS 

#include<iostream>

namespace  LeaverNMS
{
	class  Leave
	{
	public:
		Leave(std::string Name) : Name( Name) {}

		LEAVERLIBDYN_API  std::string getName() const;


	private:

		std::string Name;
	};


}
#endif // !LEAVERLIBDYN_H