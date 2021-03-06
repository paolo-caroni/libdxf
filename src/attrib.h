/*!
 * \file attrib.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF attribute entity (\c ATTRIB).
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#include "global.h"
#include "point.h"


#ifndef LIBDXF_SRC_ATTRIB_H
#define LIBDXF_SRC_ATTRIB_H


/*!
 * \brief DXF definition of an AutoCAD attribute entity (\c ATTRIB).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_attrib
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
                /*!< Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
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
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        int16_t line_weight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370. */
        /* Specific members for a DXF attrib. */
        char *default_value;
                /*!< Default value (string).\n
                 * Group code = 1. */
        char *tag_value;
                /*!< Attribute tag (string).\n
                 * Group code = 2. */
        char *text_style;
                /*!< Text style name (optional, default = STANDARD).\n
                 * Group code = 7. */
        double x0;
                /*!< X-value of text start point (in OCS).\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of text start point (in OCS).\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of text start point (in OCS).\n
                 * Group code = 30. */
        double x1;
                /*!< X-value of alignment point (in OCS).\n
                 * Present only if 72 or 74 group is present and
                 * nonzero.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of alignment point (in OCS).\n
                 * Present only if 72 or 74 group is present and
                 * nonzero.\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of alignment point (in OCS).\n
                 * Present only if 72 or 74 group is present and
                 * nonzero.\n
                 * Group code = 31. */
        double height;
                /*!< Text height.\n
                 * Group code = 40. */
        double rel_x_scale;
                /*!< Relative X scale factor (width) (optional;
                 * default = 1.0).\n
                 * This value is also adjusted when fit-type text is
                 * used.\n
                 * Group code = 41. */
        double rot_angle;
                /*!< Text rotation (optional; default = 0.0).\n
                 * Group code = 50. */
        double obl_angle;
                /*!< Oblique angle (optional; default = 0.0).\n
                 * Group code = 51. */
        int attr_flags;
                /*!< Attribute flags.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> Attribute is invisible (does not
                 * appear).</li>
                 * <li value = "2"> This is a constant attribute.</li>
                 * <li value = "4"> Verification is required on input of
                 * this attribute.</li>
                 * <li value = "8"> Attribute is preset (no prompt
                 * during insertion).</li>
                 * </ol>
                 * Group code = 70. */
        int text_flags;
                /*!< Text generation flags (optional, default = 0).\n
                 * See \c TEXT.\n
                 * Optional, defaults to 0\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "2"> Text is backward (mirrored in X).</li>
                 * <li value = "4"> Text is upside down (mirrored in Y).</li>
                 * </ol>
                 * Group code = 71. */
        int hor_align;
                /*!< Horizontal text justification type (optional,
                 * default = 0).\n
                 * See \c TEXT.\n
                 * Not bit coded:
                 * <ol>
                 * <li value = "0"> Left.</li>
                 * <li value = "1"> Center.</li>
                 * <li value = "2"> Right.</li>
                 * <li value = "3"> Aligned, only when vert_align = 0.</li>
                 * <li value = "4"> Middle, only when vert_align = 0.</li>
                 * <li value = "5"> Fit, only when vert_align = 0.</li>
                 * </ol>
                 * Group code = 72. */
        int field_length;
                /*!< Field length (optional; default = 0) (not currently
                 * used in DXF R14).\n
                 * Group code = 73. */
        int vert_align;
                /*!< Vertical text justification type (optional,
                 * default = 0).\n
                 * See group code 73 in \c TEXT.\n
                 * Not bit coded:\n
                 * <ol>
                 * <li value = "0"> Baseline.</li>
                 * <li value = "1"> Bottom.</li>
                 * <li value = "2"> Middle.</li>
                 * <li value = "3"> Top.</li>
                 * </ol>
                 * Group code = 74.\n
                 * \version Added in DXF R12. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        struct DxfAttrib *next;
                /*!< Pointer to the next DxfAttrib.\n
                 * \c NULL in the last DxfAttrib. */
} DxfAttrib;


DxfAttrib *
dxf_attrib_new ();
DxfAttrib *
dxf_attrib_init
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_read
(
        DxfFile *fp,
        DxfAttrib *attrib
);
int
dxf_attrib_write
(
        DxfFile *fp,
        DxfAttrib *attrib
);
int
dxf_attrib_free
(
        DxfAttrib *attrib
);
void
dxf_attrib_free_chain
(
        DxfAttrib *attribs
);
int
dxf_attrib_get_id_code
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_id_code
(
        DxfAttrib *attrib,
        int id_code
);
char *
dxf_attrib_get_linetype
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_linetype
(
        DxfAttrib *attrib,
        char *linetype
);
char *
dxf_attrib_get_layer
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_layer
(
        DxfAttrib *attrib,
        char *layer
);
double
dxf_attrib_get_elevation
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_elevation
(
        DxfAttrib *attrib,
        double elevation
);
double
dxf_attrib_get_thickness
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_thickness
(
        DxfAttrib *attrib,
        double thickness
);
double
dxf_attrib_get_linetype_scale
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_linetype_scale
(
        DxfAttrib *attrib,
        double linetype_scale
);
int16_t
dxf_attrib_get_visibility
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_visibility
(
        DxfAttrib *attrib,
        int16_t visibility
);
int
dxf_attrib_get_color
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_color
(
        DxfAttrib *attrib,
        int color
);
int
dxf_attrib_get_paperspace
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_paperspace
(
        DxfAttrib *attrib,
        int paperspace
);
char *
dxf_attrib_get_dictionary_owner_soft
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_dictionary_owner_soft
(
        DxfAttrib *attrib,
        char *dictionary_owner_soft
);
char *
dxf_attrib_get_dictionary_owner_hard
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_dictionary_owner_hard
(
        DxfAttrib *attrib,
        char *dictionary_owner_hard
);
char *
dxf_attrib_get_default_value
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_default_value
(
        DxfAttrib *attrib,
        char *default_value
);
char *
dxf_attrib_get_tag_value
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_tag_value
(
        DxfAttrib *attrib,
        char *tag_value
);
char *
dxf_attrib_get_text_style
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_text_style
(
        DxfAttrib *attrib,
        char *text_style
);
DxfPoint *
dxf_attrib_get_start_point
(
        DxfAttrib *attrib,
        int id_code,
        int inheritance
);
DxfAttrib *
dxf_attrib_set_start_point
(
        DxfAttrib *attrib,
        DxfPoint *point
);
DxfPoint *
dxf_attrib_get_alignment_point
(
        DxfAttrib *attrib,
        int id_code,
        int inheritance
);
DxfAttrib *
dxf_attrib_set_alignment_point
(
        DxfAttrib *attrib,
        DxfPoint *point
);
double
dxf_attrib_get_height
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_height
(
        DxfAttrib *attrib,
        double height
);
double
dxf_attrib_get_rel_x_scale
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_rel_x_scale
(
        DxfAttrib *attrib,
        double rel_x_scale
);
double
dxf_attrib_get_rot_angle
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_rot_angle
(
        DxfAttrib *attrib,
        double rot_angle
);
double
dxf_attrib_get_obl_angle
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_obl_angle
(
        DxfAttrib *attrib,
        double obl_angle
);
int
dxf_attrib_get_attr_flags
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_attr_flags
(
        DxfAttrib *attrib,
        int attr_flags
);
int
dxf_attrib_is_invisible
(
        DxfAttrib *attrib
);
int
dxf_attrib_is_constant
(
        DxfAttrib *attrib
);
int
dxf_attrib_is_verification_required
(
        DxfAttrib *attrib
);
int
dxf_attrib_is_preset
(
        DxfAttrib *attrib
);
int
dxf_attrib_get_text_flags
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_text_flags
(
        DxfAttrib *attrib,
        int text_flags
);
int
dxf_attrib_get_hor_align
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_hor_align
(
        DxfAttrib *attrib,
        int hor_align
);
int
dxf_attrib_get_field_length
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_field_length
(
        DxfAttrib *attrib,
        int field_length
);
int
dxf_attrib_get_vert_align
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_vert_align
(
        DxfAttrib *attrib,
        int vert_align
);
DxfPoint *
dxf_attrib_get_extrusion_vector_as_point
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_extrusion_vector
(
        DxfAttrib *attrib,
        double extr_x0,
        double extr_y0,
        double extr_z0
);
DxfAttrib *
dxf_attrib_get_next
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_set_next
(
        DxfAttrib *attrib,
        DxfAttrib *next
);


#endif /* LIBDXF_SRC_ATTRIB_H */


/* EOF */
