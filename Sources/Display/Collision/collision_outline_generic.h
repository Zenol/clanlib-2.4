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
**    Harry Storbacka
**    Magnus Norddahl
**    Emanuel Greisen
*/

#pragma once


#include "API/Display/Collision/collision_outline.h"
#include "API/Display/Collision/contour.h"
#include "API/Display/Collision/outline_circle.h"
#include "API/Display/Collision/outline_accuracy.h"
#include "API/Core/IOData/virtual_directory.h"

class CL_OutlineProvider;

class CL_CollisionOutline_Generic
{
/// \name Construction
/// \{

public:
	CL_CollisionOutline_Generic();
	CL_CollisionOutline_Generic( CL_OutlineProvider *provider, CL_OutlineAccuracy accuracy );

	~CL_CollisionOutline_Generic();


/// \}
/// \name Attributes
/// \{

public:
	std::vector<CL_Contour> contours;
	bool do_inside_test;

	int width, height;
	float angle;
	/** float radius;*/
	CL_Circlef minimum_enclosing_disc;

	CL_Pointf position;
	CL_Pointf scale_factor;
	CL_Pointf translation_offset;
	CL_Origin translation_origin;
	CL_Pointf rotation_hotspot;
	CL_Origin rotation_origin;

	bool collision_info_points;
	bool collision_info_normals;
	bool collision_info_meta;
	bool collision_info_pen_depth;
	///< points || normals || meta (quick way of seeing if any info is collected)
	bool collision_info_collect;

	std::vector<CL_CollidingContours> collision_info;


/// \}
/// \name Operations
/// \{

 public:
	void set_translation(float x, float y, bool offset_points=false);
	void set_scale(float sx, float sy);
	void set_angle(const CL_Angle &angle);
	void rotate(const CL_Angle &angle);

	void optimize(unsigned char check_distance, float corner_angle);
	void save(CL_IODevice &file) const;

	bool collide( const CL_CollisionOutline &outline, bool remove_old_collision_info);
	bool point_inside( const CL_Pointf &point ) const;
	static bool point_inside_contour( const CL_Pointf &point, const CL_Contour &contour);
	bool contours_collide(const CL_Contour &contour1, const CL_Contour &contour2, bool do_subcirle_test=true);
	static void calculate_penetration_depth(std::vector<CL_CollidingContours> &collision_info);

	void calculate_radius();
	void calculate_sub_circles(float radius_multiplier=3.5f);
	void calculate_smallest_enclosing_discs();
	void calculate_convex_hulls();

	inline bool line_bounding_box_overlap( const std::vector<CL_Pointf> &rect1, const std::vector<CL_Pointf> &rect2, int i, int j, int i2, int j2 ) const;

/// \}

/// \}
/// \name Implementation
/// \{
	CL_OutlineProvider *provider;

/// \}
};

