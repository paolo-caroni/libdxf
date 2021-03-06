/*!
 * \file style.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF (text) style entity \c STYLE.
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


#ifndef LIBDXF_SRC_STYLE_H
#define LIBDXF_SRC_STYLE_H


#include "global.h"
#include "file.h"


/*!
 * \brief DXF definition of an AutoCAD (text) style (\c STYLE).
 *
 * A \c STYLE table item can also be used to record shape file \c LOAD
 * requests.\n
 * In this case the first bit (1) is set in the 70 group flags and only the
 * 3 group (shape filename) is meaningful (all the other groups are output).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_style
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *style_name;
                /*!< Style name.\n
                 * Group code = 2. */
        char *primary_font_filename;
                /*!< Primary font file name.\n
                 * Group code = 3. */
        char *big_font_filename;
                /*!< Bigfont file name; blank if none.\n
                 * Group code = 4. */
        double height;
                /*!< Fixed text height; 0 if not fixed.\n
                 * Group code = 40. */
        double width;
                /*!< Width factor.\n
                 * Group code = 41. */
        double last_height;
                /*!< Last height used.\n
                 * Group code = 42. */
        double oblique_angle;
                /*!< Oblique angle.\n
                 * Group code = 50. */
        int flag;
                /*!< Standard flag values.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> Loads a shape file, only
                 * the primary_font_filename (group code = 3) is
                 * relevant.</li>
                 * <li value = "4"> Text is vertical oriented.</li>
                 * <li value = "16"> If set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> If this bit and bit 16 are both
                 * set, the externally dependent Xref has been
                 * successfully resolved.</li>
                 * <li value = "64"> If set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n
                 * Group code = 70. */
        int text_generation_flag;
                /*!< Text generation flags.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "2"> Text is backward (mirrored in X).</li>
                 * <li value = "4"> Text is upside down (mirrored in Y).</li>
                 * </ol>\n
                 * Group code = 71. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        struct DxfStyle *next;
                /*!< Pointer to the next DxfStyle.\n
                 * \c NULL in the last DxfStyle. */
} DxfStyle;
DxfStyle *
dxf_style_new ();
DxfStyle *
dxf_style_init
(
        DxfStyle *style
);
DxfStyle *
dxf_style_read
(
        DxfFile *fp,
        DxfStyle *style
);
int
dxf_style_write
(
        DxfFile *fp,
        DxfStyle *style
);
int
dxf_style_free
(
        DxfStyle *style
);
void
dxf_style_free_chain
(
        DxfStyle *styles
);
int
dxf_style_is_shape_file
(
        DxfStyle *style
);
int
dxf_style_is_text_vertical
(
        DxfStyle *style
);
int
dxf_style_is_xreferenced
(
        DxfStyle *style
);
int
dxf_style_is_xresolved
(
        DxfStyle *style
);
int
dxf_style_is_referenced
(
        DxfStyle *style
);


#endif /* LIBDXF_SRC_STYLE_H */


/* EOF */
