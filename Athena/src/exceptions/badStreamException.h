#pragma once
#ifndef BAD_STREAM_EXCEPTION
#define BAD_STREAM_EXCEPTION

#include <exception>
#include <iostream>
namespace athena
{
	namespace exceptions
	{
		class badStreamException : public std::runtime_error
		{
		public:
			badStreamException(const char* error) : std::runtime_error("[athena] a badStream error occured")
			{
				std::cerr << "[Athena] badStream error: " << error << std::endl;
			};
			virtual ~badStreamException() {};

		private:

		};
	}
}
#endif // !BAD_STREAM_EXCEPTION
