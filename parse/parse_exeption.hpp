#include <string>
#include <string.h>
#include <memory>
#include <array>
#include <stdexcept>


namespace parse
{

using namespace std;

class SerializeParamExcept : public invalid_argument
{
public:
	SerializeParamExcept() noexcept : invalid_argument("")
	{
	}

	SerializeParamExcept(wstring& message) : invalid_argument(string(message.begin(), message.end()))
	{
	}

	SerializeParamExcept(wstring& message, wstring& phrase) : invalid_argument(string(message.begin(), message.end())), 
		m_phrase_parse(string(phrase.begin(), phrase.end()))
	{
		mass = { invalid_argument::what() , str, m_phrase_parse.what() };
	}

	virtual char const * what() const
	{
		size_t _size = strlen(m_phrase_parse.what());
		if (_size == 1)
		{
			return invalid_argument::what();
		}

		_size += strlen(invalid_argument::what()) + strlen(str) + 1;
		message.reset(new (nothrow) char[_size]);
		if (message.get() == nullptr)
		{
			return invalid_argument::what();
		}

		array<const char*, 3>::const_iterator it = mass.begin();
		for (char *ptr = const_cast<char*>(message.get()), *end = message.get() + _size; ptr < end - 1 && it != mass.end(); ptr += strlen(ptr), it++)
		{
			strcpy_s(ptr, end - ptr, *it);
		}

		return message.get();
	}
private:
	invalid_argument m_phrase_parse { " " };
	mutable unique_ptr<char, default_delete<char[]>> message;
	
	array<const char*, 3> mass;
	const char str[10] = "\n\tParse:\n";
};

} // namespace parse
