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
**    Mark Page
*/

#include "precomp.h"
#include "model.h"
#include "graphic_store.h"

class Model_Impl
{
public:
	Model_Impl();

	void Load(const char *filename, std::vector<CL_Collada_Image> &library_images);
	void Load(CL_DomDocument &doc, const char *geometry_name, std::vector<CL_Collada_Image> &library_images);

	void Draw(CL_GraphicContext &gc, GraphicStore *gs, const CL_Mat4f &modelview_matrix, bool is_draw_shadow);
	void SetMaterial(float new_material_shininess, const CL_Vec4f &new_material_emission, const CL_Vec4f &new_material_ambient, const CL_Vec4f &new_material_specular);

private:
	void invert_uvmap(CL_Vec2f *points_ptr, int size);
	void insert_object(CL_Collada &object, const CL_String &geometry_name, std::vector<CL_Collada_Image> &library_images, const CL_Angle &smooth_threshold);

	std::vector<CL_Collada_Triangles> positions_surface_list;
	std::vector<CL_Vec3f> object_positions;
	std::vector<CL_Vec3f> object_normals;

	std::vector<CL_Collada_Triangles> texcoord_surface_list;
	std::vector<CL_Vec2f> object_texcoords;

	ShaderDepth *shader_depth_ptr;

	float material_shininess;
	CL_Vec4f material_emission;
	CL_Vec4f material_ambient;
	CL_Vec4f material_specular;

};


Model::Model()
{
}

Model::Model(const char *filename, std::vector<CL_Collada_Image> &library_images): impl(new Model_Impl())
{
	impl->Load(filename, library_images);
}

Model::Model(CL_DomDocument &doc, const char *geometry_name, std::vector<CL_Collada_Image> &library_images): impl(new Model_Impl())
{
	impl->Load(doc, geometry_name, library_images);
}

bool Model::is_null()
{
	return impl.is_null();
}

void Model::Draw(CL_GraphicContext &gc, GraphicStore *gs, const CL_Mat4f &modelview_matrix, bool is_draw_shadow)
{
	impl->Draw(gc, gs, modelview_matrix, is_draw_shadow);
}

Model_Impl::Model_Impl()
{
	material_shininess = 64.0f;
	material_emission = CL_Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	material_ambient =  CL_Vec4f(0.9f, 0.2f, 0.2f, 1.0f);
	material_specular = CL_Vec4f(0.0f, 0.0f, 0.0f, 1.0f);

}

void Model::SetMaterial(float new_material_shininess, const CL_Vec4f &new_material_emission, const CL_Vec4f &new_material_ambient, const CL_Vec4f &new_material_specular)
{
	impl->SetMaterial(new_material_shininess, new_material_emission, new_material_ambient, new_material_specular);
}

void Model_Impl::SetMaterial(float new_material_shininess, const CL_Vec4f &new_material_emission, const CL_Vec4f &new_material_ambient, const CL_Vec4f &new_material_specular)
{
	material_shininess = new_material_shininess;
	material_emission = new_material_emission;
	material_ambient = new_material_ambient;
	material_specular = new_material_specular;
}

void Model_Impl::Load(const char *filename, std::vector<CL_Collada_Image> &library_images)
{
	CL_File file;
	CL_DomDocument doc;

	file = CL_File(filename);
	doc = CL_DomDocument(file);

	Load(doc, "Mesh_Object", library_images);
}

void Model_Impl::Load(CL_DomDocument &doc, const char *geometry_name, std::vector<CL_Collada_Image> &library_images)
{
	CL_Collada object;
	object = CL_Collada(doc, library_images);
	insert_object(object, geometry_name, library_images, CL_Angle(89.53f, cl_degrees));
}

void Model_Impl::insert_object(CL_Collada &object, const CL_String &geometry_name, std::vector<CL_Collada_Image> &library_images, const CL_Angle &smooth_threshold)
{
	CL_Collada_Geometry &geometry = object.get_geometry(geometry_name);
	CL_Collada_Mesh &mesh = geometry.get_mesh();

	unsigned int dest_positions_offset = object_positions.size();
	unsigned int dest_texcoords_offset = object_texcoords.size();
	unsigned int dest_normals_offset = object_normals.size();

	int vertex_count_positions = mesh.get_triangle_count("VERTEX") * 3;
	if (!vertex_count_positions)
		return;		// Return now, if not vertices were found - maybe throw an exception instead?

	int vertex_count_texcoord = mesh.get_triangle_count("TEXCOORD") * 3;

	object_positions.resize(dest_positions_offset + vertex_count_positions);
	object_texcoords.resize(dest_texcoords_offset + vertex_count_texcoord);
	object_normals.resize(dest_normals_offset + vertex_count_positions);

	mesh.create_vertices(&object_positions[dest_positions_offset], 0, "VERTEX", positions_surface_list);
	mesh.create_vertices_normal(&object_normals[dest_normals_offset], 0, "VERTEX", smooth_threshold);

	if (vertex_count_texcoord)
	{
		mesh.create_vertices(&object_texcoords[dest_texcoords_offset], 0, "TEXCOORD", texcoord_surface_list);
		// Invert uvmap positions for clanlib
		invert_uvmap(&object_texcoords[dest_texcoords_offset], vertex_count_texcoord);
	}
}

void Model_Impl::invert_uvmap(CL_Vec2f *points_ptr, int size)
{
	for (; size > 0; --size, points_ptr++)
	{
		points_ptr->y = 1.0f - points_ptr->y;
	}
}

void Model_Impl::Draw(CL_GraphicContext &gc, GraphicStore *gs, const CL_Mat4f &modelview_matrix, bool is_draw_shadow)
{
	gc.set_modelview(modelview_matrix);

	CL_PrimitivesArray prim_array(gc);

	prim_array.set_attributes(0, &object_positions[0]);
	prim_array.set_attributes(1, &object_normals[0]);

	if (is_draw_shadow)
	{
		gs->shader_depth.Use(gc);
		gc.draw_primitives(cl_triangles, object_positions.size(), prim_array);
	}
	else
	{
		if (object_texcoords.size())
		{
			prim_array.set_attributes(2, &object_texcoords[0]);
			gs->shader_texture.SetShadowMatrix(gs->shadow_matrix);
			gc.set_texture(0, gs->texture_brick);
			gc.set_texture(1, gs->texture_shadow);
			gs->shader_texture.SetMaterial(material_shininess, material_emission, material_ambient, material_specular);
			gs->shader_texture.Use(gc);
		}
		else
		{
			gs->shader_color.SetMaterial(material_shininess, material_emission, material_ambient, material_specular);
			gs->shader_color.Use(gc);
		}

		gc.draw_primitives(cl_triangles, object_positions.size(), prim_array);

		if (object_texcoords.size())
		{
			gc.reset_texture(0);
			gc.reset_texture(1);
		}
	}
}