/*!
 * \file view.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF view symbol table entry (\c VIEW).
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

#ifndef LIBDXF_SRC_VIEW_H
#define LIBDXF_SRC_VIEW_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD view symbol table entry (\c VIEW).
 *
 * See chapter 2 of the "AutoLISP Programmer's Reference" for
 * information on DCS, the Display Coordinate System.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_view
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *view_name;
                /*!< Name of view.\n
                 * Group code = 2. */
        double x_view;
                /*!< View center point, in Display Coordinate System.\n
                 * Group code = 10. */
        double y_view;
                /*!< View center point, in Display Coordinate System.\n
                 * Group code = 20. */
        double x_direction;
                /*!< View direction from target, in World Coordinate
                 * System.\n
                 * Group code = 11. */
        double y_direction;
                /*!< View direction from target, in World Coordinate
                 * System.\n
                 * Group code = 21. */
        double z_direction;
                /*!< View direction from target, in World Coordinate
                 * System.\n
                 * Group code = 31. */
        double x_target;
                /*!< Target point, in WCS.\n
                 * Group code = 12. */
        double y_target;
                /*!< Target point, in WCS.\n
                 * Group code = 22. */
        double z_target;
                /*!< Target point, in WCS.\n
                 * Group code = 32. */
        double view_height;
                /*!< View height in DCS.\n
                 * Group code = 40. */
        double view_width;
                /*!< View width in DCS.\n
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
        double view_twist_angle;
                /*!< Twist angle.\n
                 * Group code = 50. */
        int flag;
                /*!< \n
                 * bit coded:\n
                 * <ol>
                 * <li value ="1"> If set, view is in paperspace.</li>
                 * <li value ="16"> If set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> If this bit and bit 16 are both set,
                 * the externally dependent Xref has been successfully
                 * resolved.</li>
                 * <li value ="64"> If set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n
                 * Group code = 70. */
        int view_mode;
                /*!< View mode (see \c VIEWMODE system variable).\n
                 * Group code = 71. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
        struct DxfView *next;
                /*!< Pointer to the next DxfView.\n
                 * \c NULL in the last DxfView. */
} DxfView;


DxfView *
dxf_view_new ();
DxfView *
dxf_view_init
(
        DxfView *view
);
DxfView *
dxf_view_read
(
        DxfFile *fp,
        DxfView *view
);
int
dxf_view_write
(
        DxfFile *fp,
        DxfView *view
);
int
dxf_view_free
(
        DxfView *view
);
void
dxf_view_free_chain
(
        DxfView *views
);


#endif /* LIBDXF_SRC_VIEW_H */


/* EOF */
