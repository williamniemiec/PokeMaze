#pragma once

#include <iostream>

namespace wniemiec {namespace io {namespace consolex
{
	/**
	 * Responsible for console input.
	 */
	class InputConsolex
	{
	//-------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------
	public:
		std::string read_line();
	};
}}}
