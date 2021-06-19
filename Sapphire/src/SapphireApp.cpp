#include <Gemstone.h>

class Sapphire : public Gemstone::Application
{
public:
	Sapphire()
	{

	}

	~Sapphire()
	{

	}
};

Gemstone::Application* Gemstone::CreateApplication()
{
	return new Sapphire();
}