/*!
 * \file vport.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF Viewport symbol table entry (\c VPORT).
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


#ifndef LIBDXF_SRC_VPORT_H
#define LIBDXF_SRC_VPORT_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD viewport entity.
 *
 * The VPORT table is unique in that it may contain several entries with the
 * same name (indicating a multiple-viewport configuration).\n
 * The entries corresponding to the active viewport configuration all have
 * the name *ACTIVE.\n
 * The first such entry describes the current viewport.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_vport
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *viewport_name;
                /*!< Group code = 2. */
        double x_min;
                /*!< X value of the lower-left corner of viewport.\n
                 * Group code = 10. */
        double y_min;
                /*!< Y value of the lower-left corner of viewport.\n
                 * Group code = 20. */
        double x_max;
                /*!< X value of the upper-right corner.\n
                 * Group code = 11. */
        double y_max;
                /*!< Y value of the upper-right corner.\n
                 * Group code = 21. */
        double x_center;
                /*!< X value of the view center point, in World
                 * Coordinate System.\n
                 * Group code = 12. */
        double y_center;
                /*!< Y value of the view center point, in World
                 * Coordinate System.\n
                 * Group code = 22. */
        double x_snap_base;
                /*!< X value of the snap base point.\n
                 * Group code = 13. */
        double y_snap_base;
                /*!< Y value of the snap base point.\n
                 * Group code = 23. */
        double x_snap_spacing;
                /*!< X value of snap spacing X and Y.\n
                 * Group code = 14. */
        double y_snap_spacing;
                /*!< Y value of snap spacing X and Y.\n
                 * Group code = 24. */
        double x_grid_spacing;
                /*!< X value of grid spacing X and Y.\n
                 * Group code = 15. */
        double y_grid_spacing;
                /*!< Y value of grid spacing X and Y.\n
                 * Group code = 25. */
        double x_direction;
                /*!< X value of the view direction from target point.\n
                 * Group code = 16. */
        double y_direction;
                /*!< Y value of the view direction from target point.\n
                 * Group code = 26. */
        double z_direction;
                /*!< Z value of the view direction from target point.\n
                 * Group code = 36. */
        double x_target;
                /*!< X value of the view target point.\n
                 * Group code = 17. */
        double y_target;
                /*!< Y value of the view target point.\n
                 * Group code = 27. */
        double z_target;
                /*!< Z value of the view target point.\n
                 * Group code = 37. */
        double view_height;
                /*!< View height.\n
                 * Group code = 40. */
        double viewport_aspect_ratio;
                /*!< Viewport aspect ratio.\n
                 * Group code = 41. */
        double lens_length;
                /*!< Lens length.\n
                 * Group code = 42. */
        double front_plane_offset;
                /*!< Front clipping plane - offset from target point.\n
                 * Group code = 43. */
        double back_plane_offset;
                /*!< Back clipping plane - offset from target point.\n
                 * Group code = 44. */
        double snap_rotation_angle;
                /*!< Snap rotation angle.\n
                 * Group code = 50. */
        double view_twist_angle;
                /*!< View twist angle.\n
                 * Group code = 51. */
        int status_field;
                /*!< Status field (never saved in DXF).\n
                 * Group code = 68. */
        int id;
                /*!< ID (never saved in DXF).\n
                 * Group code = 69. */
        int standard_flag;
                /*!< Standard flag values (See "Common Group Codes for
                 * Symbol Table Entries.").\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "16"> If set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> If this bit and bit 16 are both
                 * set, the externally dependent Xref has been
                 * successfully resolved.</li>
                 * <li value = "64"> If set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * This flag is for the benefit of AutoCAD commands; it can
                 * be ignored by most programs that read DXF files, and need
                 * not be set by programs that write DXF files.\n
                 * Group code = 70. */
        int view_mode;
                /*!< See VIEWMODE system variable in appendix A.\n
                 * Group code = 71. */
        int circle_zoom_percent;
                /*!< Circle zoom percent.\n
                 * Group code = 72. */
        int fast_zoom_setting;
                /*!< Fast zoom setting.\n
                 * Group code = 73. */
        int UCSICON_setting;
                /*!< UCSICON setting.\n
                 * Group code = 74. */
        int snap_on;
                /*!< Snap on/off.\n
                 * Group code = 75. */
        int grid_on;
                /*!< Grid on/off.\n
                 * Group code = 76. */
        int snap_style;
                /*!< Snap style.\n
                 * Group code = 77. */
        int snap_isopair;
                /*!< Snap isopair.\n
                 * Group code = 78. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
        struct DxfVPort *next;
                /*!< Pointer to the next DxfVPort.\n
                 * \c NULL in the last DxfVPort. */
} DxfVPort;


DxfVPort *
dxf_vport_new ();
DxfVPort *
dxf_vport_init
(
        DxfVPort *vport
);
DxfVPort *
dxf_vport_read
(
        DxfFile *fp,
        DxfVPort *vport
);
int
dxf_vport_write
(
        DxfFile *fp,
        DxfVPort *vport
);
int
dxf_vport_free
(
        DxfVPort *vport
);
void
dxf_vport_free_chain
(
        DxfVPort *vports
);


#endif /* LIBDXF_SRC_VPORT_H */


/* EOF */
