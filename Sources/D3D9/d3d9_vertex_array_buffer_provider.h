/*
**  ClanLib SDK
**  Copyright (c) 1997-2010 The ClanLib Team
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
**    Magnus Norddahl
*/

#pragma once


#include "API/Display/TargetProviders/vertex_array_buffer_provider.h"
#include "API/Core/System/comptr.h"
#include <d3d9.h>

class CL_D3D9DisplayWindowProvider;

class CL_D3D9VertexArrayBufferProvider : public CL_VertexArrayBufferProvider
{
/// \name Construction
/// \{

public:
	CL_D3D9VertexArrayBufferProvider(CL_D3D9DisplayWindowProvider *window);

	~CL_D3D9VertexArrayBufferProvider();

	void create(int size, CL_BufferUsage usage);

	void create(void *data, int size, CL_BufferUsage usage);

	void destroy();


/// \}
/// \name Attributes
/// \{

public:
	void *get_data();

	const CL_ComPtr<IDirect3DVertexBuffer9> &get_buffer() const { return vertex_buffer; }

/// \}
/// \name Operations
/// \{

public:
	void lock(CL_BufferAccess access);

	void unlock();

	void upload_data(int offset, void *data, int size);


/// \}
/// \name Implementation
/// \{

private:
	CL_D3D9DisplayWindowProvider *window;

	CL_ComPtr<IDirect3DVertexBuffer9> vertex_buffer;

	void *data_ptr;
/// \}
};


