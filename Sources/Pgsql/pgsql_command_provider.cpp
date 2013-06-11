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

#include "Pgsql/precomp.h"
#include "Pgsql/pg_type.h"
#include "pgsql_command_provider.h"
#include "pgsql_connection_provider.h"
#include "pgsql_reader_provider.h"
#include "API/Core/System/databuffer.h"
#include "API/Core/Text/string_help.h"
#include "API/Database/db_command_provider.h"

#include <libpq-fe.h>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// CL_PgsqlCommandProvider Construction:

CL_PgsqlCommandProvider::CL_PgsqlCommandProvider(CL_PgsqlConnectionProvider *connection, const CL_StringRef &user_text)
: connection(connection), last_insert_rowid(-1)
{
	text = compute_command(user_text, arguments_count);
	arguments.resize(arguments_count);
}

CL_PgsqlCommandProvider::~CL_PgsqlCommandProvider()
{
}

/////////////////////////////////////////////////////////////////////////////
// CL_PgsqlCommandProvider Attributes:

int CL_PgsqlCommandProvider::get_input_parameter_column(const CL_StringRef &name) const
{
	throw CL_Exception("get_input_parameter_column not yet implemented for PostgreSQL");
}

int CL_PgsqlCommandProvider::get_output_last_insert_rowid() const
{
	return last_insert_rowid;
}

/////////////////////////////////////////////////////////////////////////////
// CL_PgsqlCommandProvider Operations:

void CL_PgsqlCommandProvider::set_input_parameter_string(int index, const CL_StringRef &value)
{
	put(index, CL_String(value));
}

void CL_PgsqlCommandProvider::set_input_parameter_bool(int index, bool value)
{
	put(index, CL_StringHelp::bool_to_text(value));
}

void CL_PgsqlCommandProvider::set_input_parameter_int(int index, int value)
{
	put(index, CL_StringHelp::int_to_text(value));
}

void CL_PgsqlCommandProvider::set_input_parameter_double(int index, double value)
{
	put(index, CL_StringHelp::double_to_text(value));
}

void CL_PgsqlCommandProvider::set_input_parameter_datetime(int index, const CL_DateTime &value)
{
	put(index, CL_PgsqlConnectionProvider::to_sql_datetime(value));
}

void CL_PgsqlCommandProvider::set_input_parameter_binary(int index, const CL_DataBuffer &value)
{
	put(index, value);
}

/////////////////////////////////////////////////////////////////////////////
// CL_PgsqlCommandProvider Implementation:
inline
void CL_PgsqlCommandProvider::put(int index, const CL_String &value)
{
	if (index > arguments_count)
		throw CL_Exception("Index out of range");
	arguments[index] = value;
	bin_arguments.erase(index);
}

inline
void CL_PgsqlCommandProvider::put(int index, const CL_DataBuffer &value)
{
	if (index > arguments_count)
		throw CL_Exception("Index out of range");
	arguments[index] = "";
	bin_arguments[index] = value;
}

CL_String CL_PgsqlCommandProvider::compute_command(CL_String text, int &arguments_count) const
{
	std::ostringstream oss;
	int arguments = 0;
	for (auto c : text)
	{
		if (c == '?')
			oss << '$' << ++arguments;
		else
			oss << c;
	}
	arguments_count = arguments;
	return CL_String(oss.str());
}
