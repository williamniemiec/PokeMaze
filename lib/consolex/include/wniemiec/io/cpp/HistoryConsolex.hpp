/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <iostream>
#include <vector>

namespace wniemiec { namespace io { namespace cpp {

	/**
	 * Responsible for managing console history.
	 */
	class HistoryConsolex
	{
	//-------------------------------------------------------------------------
	//		Attributes
	//-------------------------------------------------------------------------
	private:
		static const int BUFFER_SIZE;
		std::vector<std::string> buffer;


	//-------------------------------------------------------------------------
	//		Constructor
	//-------------------------------------------------------------------------
	public:
		HistoryConsolex();


	//-------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------
	public:
		void add(std::string content);
		void free_buffer();
		void clear();
		void dump_to(std::string output);


		//-------------------------------------------------------------------------
		//		Getters
		//-------------------------------------------------------------------------
	public:
		std::vector<std::string> get_history();
	};
}}}
