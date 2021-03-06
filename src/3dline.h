/*!
 * \file 3dline.h
 *
 * \author Copyright (C) 2015 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF 3D line entity (\c 3DLINE).
 *
 * \warning This entity type is used in DXF versions R10 and R11 only,
 * it was obsoleted and removed in DXF version R12.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.\n\n
 * This program is distributed in the hope that it will be useful, but
 * <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
 * <b>MERCHANTABILITY</b> or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.\n
 * See the GNU General Public License for more details.\n\n
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to:\n
 * Free Software Foundation, Inc.,\n
 * 59 Temple Place,\n
 * Suite 330,\n
 * Boston,\n
 * MA 02111 USA.\n
 * \n
 * Drawing eXchange Format (DXF) is a defacto industry standard for the
 * exchange of drawing files between various Computer Aided Drafting
 * programs.\n
 * DXF is an industry standard designed by Autodesk(TM).\n
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_3DLINE_H
#define LIBDXF_SRC_3DLINE_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


/*!
 * \brief DXF definition of an AutoCAD line entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 */
typedef struct
dxf_3dline_struct
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double elevation;
                /*!< Elevation of the 3dline in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0\n
                 * (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the 3dline in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int16_t visibility;
                /*!< Object visibility (optional):
                 * <ol>
                 * <li value = "0"> Visible.</li>
                 * <li value = "1"> Invisible.<.li>
                 * </ol>
                 * Group code = 60. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67. */
        int graphics_data_size;
                /*!< Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).\n
                 * Group code = 92.
                 *
                 * \warning On some 64 bit workstations output is
                 * generated with group code "160", thus omitting group
                 * code "92".
                 */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284. */
        DxfBinaryGraphicsData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390. */
        long color_value;
                /*!< A 24-bit color value that should be dealt with in
                 * terms of bytes with values of 0 to 255.\n
                 * The lowest byte is the blue value, the middle byte is
                 * the green value, and the third byte is the red value.\n
                 * The top byte is always 0.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 420. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430. */
        long transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440. */
        /* Specific members for a DXF line. */
        double x0;
                /*!< group code = 10\n
                 * start point. */
        double y0;
                /*!< group code = 20\n
                 * start point. */
        double z0;
                /*!< group code = 30\n
                 * start point. */
        double x1;
                /*!< group code = 11\n
                 * end point. */
        double y1;
                /*!< group code = 21\n
                 * end point. */
        double z1;
                /*!< group code = 31\n
                 * end point. */
        double extr_x0;
                /*!< group code = 210\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_y0;
                /*!< group code = 220\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_z0;
                /*!< group code = 230\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 1.0. */
        struct Dxf3dline *next;
                /*!< pointer to the next Dxf3dline.\n
                 * \c NULL in the last Dxf3dline. */
} Dxf3dline;


Dxf3dline *
dxf_3dline_new ();
Dxf3dline *
dxf_3dline_init
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_read
(
        DxfFile *fp,
        Dxf3dline *line
);
int
dxf_3dline_write
(
        DxfFile *fp,
        Dxf3dline *line
);
int
dxf_3dline_free
(
        Dxf3dline *line
);
void
dxf_3dline_free_chain
(
        Dxf3dline *lines
);
int
dxf_3dline_get_id_code
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_id_code
(
        Dxf3dline *line,
        int id_code
);
char *
dxf_3dline_get_linetype
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_linetype
(
        Dxf3dline *line,
        char *linetype
);
char *
dxf_3dline_get_layer
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_layer
(
        Dxf3dline *line,
        char *layer
);
double
dxf_3dline_get_elevation
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_elevation
(
        Dxf3dline *line,
        double elevation
);
double
dxf_3dline_get_thickness
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_thickness
(
        Dxf3dline *line,
        double thickness
);
double
dxf_3dline_get_linetype_scale
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_linetype_scale
(
        Dxf3dline *line,
        double linetype_scale
);
int16_t
dxf_3dline_get_visibility
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_visibility
(
        Dxf3dline *line,
        int16_t visibility
);
int
dxf_3dline_get_color
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_color
(
        Dxf3dline *line,
        int color
);
int
dxf_3dline_get_paperspace
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_paperspace
(
        Dxf3dline *line,
        int paperspace
);
int
dxf_3dline_get_graphics_data_size
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_graphics_data_size
(
        Dxf3dline *line,
        int graphics_data_size
);
int16_t
dxf_3dline_get_shadow_mode
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_shadow_mode
(
        Dxf3dline *line,
        int16_t shadow_mode
);
DxfBinaryGraphicsData *
dxf_3dline_get_binary_graphics_data
(
        Dxf3dline *line
);
char *
dxf_3dline_get_dictionary_owner_soft
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_dictionary_owner_soft
(
        Dxf3dline *line,
        char *dictionary_owner_soft
);
char *
dxf_3dline_get_dictionary_owner_hard
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_dictionary_owner_hard
(
        Dxf3dline *line,
        char *dictionary_owner_hard
);
DxfPoint *
dxf_3dline_get_start_point
(
        Dxf3dline *line,
        int id_code,
        int inheritance
);
DxfPoint *
dxf_3dline_get_end_point
(
        Dxf3dline *line,
        int id_code,
        int inheritance
);
DxfPoint *
dxf_3dline_get_mid_point
(
        Dxf3dline *line,
        int id_code,
        int inheritance
);
DxfPoint *
dxf_3dline_get_extrusion_vector_as_point
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_extrusion_vector
(
        Dxf3dline *line,
        double extr_x0,
        double extr_y0,
        double extr_z0
);
double
dxf_3dline_get_length
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_create_from_points
(
        DxfPoint *p1,
        DxfPoint *p2,
        int id_code,
        int inheritance
);
Dxf3dline *
dxf_3dline_get_next
(
        Dxf3dline *line
);
Dxf3dline *
dxf_3dline_set_next
(
        Dxf3dline *line,
        Dxf3dline *next
);


#endif /* LIBDXF_SRC_3DLINE_H */


/* EOF */
