/*!
 * \file mline.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mline entity (\c MLINE).
 *
 * \version The \c MLINE entity was introduced in DXF R13.
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


#include "mline.h"


/*!
 * \brief Allocate memory for a \c DxfMline.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfMline *
dxf_mline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMline *mline = NULL;
        size_t size;

        size = sizeof (DxfMline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfMline struct.\n")),
                  __FUNCTION__);
                mline = NULL;
        }
        else
        {
                memset (mline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c MLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfMline *
dxf_mline_init
(
        DxfMline *mline
                /*!< DXF mline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mline = dxf_mline_new ();
        }
        if (mline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfMline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        mline->id_code = 0;
        mline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mline->layer = strdup (DXF_DEFAULT_LAYER);
        mline->elevation = 0.0;
        mline->thickness = 0.0;
        mline->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        mline->visibility = DXF_DEFAULT_VISIBILITY;
        mline->color = DXF_COLOR_BYLAYER;
        mline->paperspace = DXF_MODELSPACE;
        mline->dictionary_owner_soft = strdup ("");
        mline->dictionary_owner_hard = strdup ("");
        mline->style_name = strdup ("");
        mline->x0 = 0.0;
        mline->y0 = 0.0;
        mline->z0 = 0.0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                mline->x1[i] = 0.0;
                mline->y1[i] = 0.0;
                mline->z1[i] = 0.0;
                mline->x2[i] = 0.0;
                mline->y2[i] = 0.0;
                mline->z2[i] = 0.0;
                mline->x3[i] = 0.0;
                mline->y3[i] = 0.0;
                mline->z3[i] = 0.0;
                mline->element_parameters[i] = 0.0;
                mline->area_fill_parameters[i] = 0.0;
        }
        mline->scale_factor = 1.0;
        mline->justification = 0;
        mline->flags = 0;
        mline->number_of_vertices = 0;
        mline->number_of_elements = 0;
        mline->number_of_area_fill_parameters = 0;
        mline->extr_x0 = 0.0;
        mline->extr_y0 = 0.0;
        mline->extr_z0 = 1.0;
        mline->mlinestyle_dictionary = strdup ("");
        mline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Read data from a DXF file into an \c MLINE entity.
 *
 * The last line read from file contained the string "MLINE". \n
 * Now follows some data for the \c MLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c mline.
 *
 * \return a pointer to \c mline.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfMline *
dxf_mline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfMline *mline
                /*!< DXF mline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int j;
        int k;
        int l;
        int m;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mline = dxf_mline_new ();
                mline = dxf_mline_init (mline);
        }
        i = 0;
        j = 0;
        k = 0;
        l = 0;
        m = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a string of
                         * up to 32 characters with the name of the
                         * style used for this mline. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mline->style_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &mline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the vertex coordinates (multiple
                         * entries; one entry for each vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->x1[i]);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the vertex coordinates (multiple
                         * entries; one entry for each vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->y1[i]);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the vertex coordinates (multiple
                         * entries; one entry for each vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->z1[i]);
                        i++;
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the direction vector of segment
                         * starting at this vertex (multiple
                         * entries; one entry for each vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->x2[j]);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the direction vector of segment
                         * starting at this vertex (multiple
                         * entries; one entry for each vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->y2[j]);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the direction vector of segment
                         * starting at this vertex (multiple
                         * entries; one entry for each vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->z2[j]);
                        j++;
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the direction vector of miter at
                         * this vertex (multiple entries: one for each
                         * vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->x3[k]);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the direction vector of miter at
                         * this vertex (multiple entries: one for each
                         * vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->y3[k]);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the direction vector of miter at
                         * this vertex (multiple entries: one for each
                         * vertex). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->z3[k]);
                        j++;
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the scale
                         * factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->scale_factor);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the element
                         * parameters (repeats based on previous code 74). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->element_parameters[l]);
                        l++;
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the area fill
                         * parameters (repeats based on previous code 75). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->area_fill_parameters[m]);
                        m++;
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * justification value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->justification);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the flags
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the number of
                         * vertices value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->number_of_vertices);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the number of
                         * elements in MLINESTYLE definition. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->number_of_elements);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the number of
                         * parameters for this element (repeats for each
                         * element in segment). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->number_of_parameters);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the number of
                         * area fill parameters for this element
                         * (repeats for each element in segment). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->number_of_area_fill_parameters);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbMline") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the extrusion direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the extrusion direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the extrusion direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a
                         * Pointer-handle/ID of MLINESTYLE dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mline->mlinestyle_dictionary);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mline->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (mline->linetype, "") == 0)
        {
                mline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (mline->layer, "") == 0)
        {
                mline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Write DXF output to fp for a mline entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occured.
 *
 * \warning This entity requires AutoCAD version R13 or higher.
 * When the \c follow_strict_version_rules flag is set to \c TRUE in the
 * \c DxfFile struct, this entity will be skipped from file.
 * When the \c follow_strict_version_rules flag is set to \c FALSE in the
 * \c DxfFile struct, libdxf will write this entity to file and report
 * with a warning message to \c stderr.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_mline_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfMline *mline
                /*!< DXF mline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("MLINE");
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((fp->acad_version_number < AutoCAD_13)
          && (fp->follow_strict_version_rules))
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, mline->id_code);
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, mline->id_code);
        }
        if (strcmp (mline->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, mline->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                mline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (mline->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, mline->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                mline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (mline->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", mline->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (mline->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", mline->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (mline->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", mline->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (mline->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", mline->layer);
        if (strcmp (mline->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", mline->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (mline->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", mline->elevation);
        }
        if (mline->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", mline->color);
        }
        if (mline->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", mline->linetype_scale);
        }
        if (mline->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", mline->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbMline\n");
        }
        if (mline->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", mline->thickness);
        }
        fprintf (fp->fp, "  2\n%s\n", mline->style_name);
        fprintf (fp->fp, "340\n%s\n", mline->mlinestyle_dictionary);
        fprintf (fp->fp, " 40\n%f\n", mline->scale_factor);
        fprintf (fp->fp, " 70\n%d\n", mline->justification);
        fprintf (fp->fp, " 71\n%d\n", mline->flags);
        /*! \todo Check for correct number of vertices (prevent overrun of array/index). */
        fprintf (fp->fp, " 72\n%d\n", mline->number_of_vertices);
        /*! \todo Check for correct number of elements (prevent overrun of array/index). */
        fprintf (fp->fp, " 73\n%d\n", mline->number_of_elements);
        fprintf (fp->fp, " 10\n%f\n", mline->x0);
        fprintf (fp->fp, " 20\n%f\n", mline->y0);
        fprintf (fp->fp, " 30\n%f\n", mline->z0);
        if ((fp->acad_version_number >= AutoCAD_12)
                && (mline->extr_x0 != 0.0)
                && (mline->extr_y0 != 0.0)
                && (mline->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", mline->extr_x0);
                fprintf (fp->fp, "220\n%f\n", mline->extr_y0);
                fprintf (fp->fp, "230\n%f\n", mline->extr_z0);
        }
        for (i = 0; i < mline->number_of_vertices; i++)
        {
                fprintf (fp->fp, " 11\n%f\n", mline->x1[i]);
                fprintf (fp->fp, " 21\n%f\n", mline->y1[i]);
                fprintf (fp->fp, " 31\n%f\n", mline->z1[i]);
        }
        for (i = 0; i < mline->number_of_vertices; i++)
        {
                fprintf (fp->fp, " 12\n%f\n", mline->x2[i]);
                fprintf (fp->fp, " 22\n%f\n", mline->y2[i]);
                fprintf (fp->fp, " 32\n%f\n", mline->z2[i]);
        }
        for (i = 0; i < mline->number_of_vertices; i++)
        {
                fprintf (fp->fp, " 13\n%f\n", mline->x3[i]);
                fprintf (fp->fp, " 23\n%f\n", mline->y3[i]);
                fprintf (fp->fp, " 33\n%f\n", mline->z3[i]);
        }
        /*! \todo Check for correct number of parameters (prevent overrun of array/index). */
        fprintf (fp->fp, " 74\n%d\n", mline->number_of_parameters);
        for (i = 0; i < mline->number_of_parameters; i++)
        {
                fprintf (fp->fp, " 41\n%f\n", mline->element_parameters[i]);
        }
        /*! \todo Check for correct number of area fill parameters (prevent overrun of array/index). */
        fprintf (fp->fp, " 75\n%d\n", mline->number_of_area_fill_parameters);
        for (i = 0; i < mline->number_of_area_fill_parameters; i++)
        {
                fprintf (fp->fp, " 42\n%f\n", mline->area_fill_parameters[i]);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c MLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_mline_free
(
        DxfMline *mline
                /*!< Pointer to the memory occupied by the DXF \c MLINE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfMline was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (mline->linetype);
        free (mline->layer);
        free (mline->dictionary_owner_soft);
        free (mline->dictionary_owner_hard);
        free (mline->style_name);
        free (mline->mlinestyle_dictionary);
        free (mline);
        mline = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c MLINE
 * entities and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_mline_free_chain
(
        DxfMline *mlines
                /*!< a pointer to the chain of DXF \c MLINE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (mlines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (mlines != NULL)
        {
                struct DxfMline *iter = mlines->next;
                dxf_mline_free (mlines);
                mlines = (DxfMline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/* EOF */
