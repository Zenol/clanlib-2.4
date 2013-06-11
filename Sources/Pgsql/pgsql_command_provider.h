/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Jeremy Cochoy
*/

/// \addtogroup clanPgsql_System clanPgsql System
/// \{


#pragma once


#include <libpq-fe.h>
#include "API/Database/db_command_provider.h"

class CL_PgsqlConnectionProvider;

/// \brief Pgsql database command provider.
class CL_PgsqlCommandProvider : public CL_DBCommandProvider
{
/// \name Construction
/// \{
public:
	CL_PgsqlCommandProvider(CL_PgsqlConnectionProvider *connection, const CL_StringRef &text);
	~CL_PgsqlCommandProvider();
/// \}

/// \name Attributes
/// \{
public:
	int get_input_parameter_column(const CL_StringRef &name) const;
	int get_output_last_insert_rowid() const;
/// \}

/// \name Operations
/// \{
public:
	void set_input_parameter_string(int index, const CL_StringRef &value);
	void set_input_parameter_bool(int index, bool value);
	void set_input_parameter_int(int index, int value);
	void set_input_parameter_double(int index, double value);
	void set_input_parameter_datetime(int index, const CL_DateTime &value);
	void set_input_parameter_binary(int index, const CL_DataBuffer &value);
/// \}

/// \name Implementation
/// \{
private:
	void throw_if_failed(int result) const;

	CL_PgsqlConnectionProvider *connection;
	CL_String text;
	int last_insert_rowid;

	friend class CL_PgsqlReaderProvider;
/// \}
};


/// \}
