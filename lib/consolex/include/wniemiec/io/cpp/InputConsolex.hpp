/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <iostream>

namespace wniemiec { namespace io { namespace cpp {

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
