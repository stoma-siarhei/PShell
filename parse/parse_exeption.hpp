#include <string>
#include <stdexcept>


namespace parse
{

using namespace std;

class SerializeParamExcept : public invalid_argument
{
public:
	SerializeParamExcept() : invalid_argument("")
	{
	}

	SerializeParamExcept(wstring& message) : invalid_argument(string(message.begin(), message.end()))
	{
	}
};

} // namespace parse
