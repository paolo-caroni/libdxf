/*!
 * \file 3dline.c
 *
 * \author Copyright (C) 2015 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF 3D line entity (\c 3DLINE).
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


#include "3dline.h"


/*!
 * \brief Allocate memory for a DXF \c 3DLINE entity.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        Dxf3dline *line = NULL;
        size_t size;

        size = sizeof (Dxf3dline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((line = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a Dxf3dline struct.\n")),
                  __FUNCTION__);
                line = NULL;
        }
        else
        {
                memset (line, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c 3DLINE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_init
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                line = dxf_3dline_new ();
        }
        if (line == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a Dxf3dline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        line->id_code = 0;
        line->linetype = strdup (DXF_DEFAULT_LINETYPE);
        line->layer = strdup (DXF_DEFAULT_LAYER);
        line->x0 = 0.0;
        line->y0 = 0.0;
        line->z0 = 0.0;
        line->x1 = 0.0;
        line->y1 = 0.0;
        line->z1 = 0.0;
        line->extr_x0 = 0.0;
        line->extr_y0 = 0.0;
        line->extr_z0 = 0.0;
        line->elevation = 0.0;
        line->thickness = 0.0;
        line->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        line->visibility = DXF_DEFAULT_VISIBILITY;
        line->color = DXF_COLOR_BYLAYER;
        line->paperspace = DXF_MODELSPACE;
        line->dictionary_owner_soft = strdup ("");
        line->dictionary_owner_hard = strdup ("");
        line->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Read data from a DXF file into a DXF \c 3DLINE entity.
 *
 * The last line read from file contained the string "3DLINE". \n
 * Now follows some data for the \c 3DLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c line.
 *
 * \return a pointer to \c line.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

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
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                line = dxf_3dline_new ();
                line = dxf_3dline_init (line);
        }
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
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &line->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", line->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", line->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (line->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &line->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &line->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &line->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbLine") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", line->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", line->dictionary_owner_hard);
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
        if (strcmp (line->linetype, "") == 0)
        {
                line->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (line->layer, "") == 0)
        {
                line->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Write DXF output to a file (or a device) for a DXF \c 3DLINE
 * entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occured.
 *
 * \note For DXF version R12 and later, a DXF \c LINE entity is written
 * to file (or device).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
int
dxf_3dline_write
(
        DxfFile *fp,
                /*!< a DXF file pointer to an output file (or device). */
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("3DLINE");

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
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((line->x0 == line->x1)
                && (line->y0 == line->y1)
                && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () start point and end point are identical for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, line->id_code);
                dxf_entity_skip (dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (line->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, line->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                line->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (fp->acad_version_number > AutoCAD_11)
        {
                dxf_entity_name = strdup ("LINE");
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (line->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", line->id_code);
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
        if ((strcmp (line->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", line->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (line->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", line->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if ((line->paperspace == DXF_PAPERSPACE)
          && (fp->acad_version_number >= AutoCAD_13))
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", line->layer);
        if (strcmp (line->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", line->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (line->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", line->elevation);
        }
        if (line->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", line->color);
        }
        if ((line->linetype_scale != 1.0)
          && (fp->acad_version_number >= AutoCAD_13))
        {
                fprintf (fp->fp, " 48\n%f\n", line->linetype_scale);
        }
        if ((line->visibility != 0)
          && (fp->acad_version_number >= AutoCAD_13))
        {
                fprintf (fp->fp, " 60\n%d\n", line->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbLine\n");
        }
        if (line->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", line->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", line->x0);
        fprintf (fp->fp, " 20\n%f\n", line->y0);
        fprintf (fp->fp, " 30\n%f\n", line->z0);
        fprintf (fp->fp, " 11\n%f\n", line->x1);
        fprintf (fp->fp, " 21\n%f\n", line->y1);
        fprintf (fp->fp, " 31\n%f\n", line->z1);
        if ((fp->acad_version_number >= AutoCAD_12)
                && (line->extr_x0 != 0.0)
                && (line->extr_y0 != 0.0)
                && (line->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", line->extr_x0);
                fprintf (fp->fp, "220\n%f\n", line->extr_y0);
                fprintf (fp->fp, "230\n%f\n", line->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c 3DLINE entity and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
int
dxf_3dline_free
(
        Dxf3dline *line
                /*!< a pointer to the memory occupied by the DXF \c 3DLINE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (line->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next Dxf3dline was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (line->linetype);
        free (line->layer);
        free (line->dictionary_owner_soft);
        free (line->dictionary_owner_hard);
        free (line);
        line = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c 3DLINE
 * entities and all their data fields.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
void
dxf_3dline_free_chain
(
        Dxf3dline *lines
                /*!< a pointer to the chain of DXF 3DLINE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (lines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (lines != NULL)
        {
                struct Dxf3dline *iter = (struct Dxf3dline *) lines->next;
                dxf_3dline_free (lines);
                lines = (Dxf3dline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c 3DLINE entity.
 *
 * \return ID code.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
int
dxf_3dline_get_id_code
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_id_code
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the linetype from a DXF \c 3DLINE entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
char *
dxf_3dline_get_linetype
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_linetype
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the layer from a DXF \c 3DLINE entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
char *
dxf_3dline_get_layer
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->layer));
}


/*!
 * \brief Set the layer for a DXF \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_layer
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the elevation from a DXF \c 3DLINE entity.
 *
 * \return elevation.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
double
dxf_3dline_get_elevation
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_elevation
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the thickness from a DXF \c 3DLINE entity.
 *
 * \return thickness.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
double
dxf_3dline_get_thickness
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_thickness
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the linetype scale from a DXF \c 3DLINE entity.
 *
 * \return linetype scale.
 *
 * \note The linetype scale was added in DXF R13 and is included for
 * forward compatibility.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
double
dxf_3dline_get_linetype_scale
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c 3DLINE entity.
 *
 * \note The linetype scale was added in DXF R13 and is included for
 * forward compatibility.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_linetype_scale
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the visibility from a DXF \c 3DLINE entity.
 *
 * \return visibility.
 *
 * \note The visibility was added in DXF R13 and is included for
 * forward compatibility.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
int16_t
dxf_3dline_get_visibility
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c 3DLINE entity.
 *
 * \note The visibility was added in DXF R13 and is included for
 * forward compatibility.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_visibility
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the color from a DXF \c 3DLINE entity.
 *
 * \return color.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
int
dxf_3dline_get_color
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->color);
}


/*!
 * \brief Set the color for a DXF \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_color
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        line->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c 3DLINE entity.
 *
 * \return paperspace flag value.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
int
dxf_3dline_get_paperspace
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (line->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c 3DLINE entity.
 *
 * \note the paperpspace flag was added in DXF R13 and is included for
 * forward compatibility.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_paperspace
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c 3DLINE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_3dline_get_graphics_data_size
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        if (line->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c 3DLINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dline *
dxf_3dline_set_graphics_data_size
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a zero graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c 3DLINE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_3dline_get_shadow_mode
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c 3DLINE entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dline *
dxf_3dline_set_shadow_mode
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the binary graphics data from a DXF 
 * \c 3DLINE entity.
 *
 * \return pointer to the binary graphics data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_3dline_get_binary_graphics_data
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the binary_graphics_data member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) line->binary_graphics_data);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c 3DLINE entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
char *
dxf_3dline_get_dictionary_owner_soft
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_dictionary_owner_soft
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c 3DLINE entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
char *
dxf_3dline_get_dictionary_owner_hard
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_set_dictionary_owner_hard
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the start point of a DXF \c 3DLINE entity.
 *
 * \return the start point.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
DxfPoint *
dxf_3dline_get_start_point
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c 3DLINE.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () a 3DLINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = line->x0;
        p1->y0 = line->y0;
        p1->z0 = line->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (line->linetype != NULL)
                        {
                                p1->linetype = strdup (line->linetype);
                        }
                        if (line->layer != NULL)
                        {
                                p1->layer = strdup (line->layer);
                        }
                        p1->thickness = line->thickness;
                        p1->linetype_scale = line->linetype_scale;
                        p1->visibility = line->visibility;
                        p1->color = line->color;
                        p1->paperspace = line->paperspace;
                        if (line->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (line->dictionary_owner_soft);
                        }
                        if (line->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (line->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Get the end point of a DXF \c 3DLINE entity.
 *
 * \return the end point.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
DxfPoint *
dxf_3dline_get_end_point
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c 3DLINE.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p2 = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () a 3DLINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p2 = dxf_point_init (p2);
        if (p2 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        p2->id_code = id_code;
        p2->x0 = line->x0;
        p2->y0 = line->y0;
        p2->z0 = line->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (line->linetype != NULL)
                        {
                                p2->linetype = strdup (line->linetype);
                        }
                        if (line->layer != NULL)
                        {
                                p2->layer = strdup (line->layer);
                        }
                        p2->thickness = line->thickness;
                        p2->linetype_scale = line->linetype_scale;
                        p2->visibility = line->visibility;
                        p2->color = line->color;
                        p2->paperspace = line->paperspace;
                        if (line->dictionary_owner_soft != NULL)
                        {
                                p2->dictionary_owner_soft = strdup (line->dictionary_owner_soft);
                        }
                        if (line->dictionary_owner_hard != NULL)
                        {
                                p2->dictionary_owner_hard = strdup (line->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p2);
}


/*!
 * \brief Get the mid point of a DXF \c 3DLINE entity.
 *
 * \return the mid point.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
DxfPoint *
dxf_3dline_get_mid_point
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c 3DLINE.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () a 3DLINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point = dxf_point_init (point);
        if (point == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        point->id_code = id_code;
        point->x0 = (line->x0 + line->x1) / 2;
        point->y0 = (line->y0 + line->y1) / 2;
        point->z0 = (line->z0 + line->z1) / 2;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (line->linetype != NULL)
                        {
                                point->linetype = strdup (line->linetype);
                        }
                        if (line->layer != NULL)
                        {
                                point->layer = strdup (line->layer);
                        }
                        point->thickness = line->thickness;
                        point->linetype_scale = line->linetype_scale;
                        point->visibility = line->visibility;
                        point->color = line->color;
                        point->paperspace = line->paperspace;
                        if (line->dictionary_owner_soft != NULL)
                        {
                                point->dictionary_owner_soft = strdup (line->dictionary_owner_soft);
                        }
                        if (line->dictionary_owner_hard != NULL)
                        {
                                point->dictionary_owner_hard = strdup (line->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c 3DLINE entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_3dline_get_extrusion_vector_as_point
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () a 3DLINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point = dxf_point_init (point);
        if (point == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        point->x0 = line->extr_x0;
        point->y0 = line->extr_y0;
        point->z0 = line->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector for a DXF \c 3DLINE entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dline *
dxf_3dline_set_extrusion_vector
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        double extr_x0,
                /*!<  X-value of the extrusion direction. */
        double extr_y0,
                /*!<  Y-value of the extrusion direction. */
        double extr_z0
                /*!<  Z-value of the extrusion direction. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->extr_x0 = extr_x0;
        line->extr_y0 = extr_y0;
        line->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the length of a DXF \c 3DLINE (straight distance between
 * start point and end point).
 *
 * \return the length of the \c line in drawing units.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
double
dxf_3dline_get_length
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (0.0);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () endpoints with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (0.0);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sqrt (
                       ((line->x1 - line->x0) * (line->x1 - line->x0))
                     + ((line->y1 - line->y0) * (line->y1 - line->y0))
                     + ((line->z1 - line->z0) * (line->z1 - line->z0))
                     )
               );
}


/*!
 * \brief Create a DXF \c 3DLINE by means of two DXF \c POINT entities.
 *
 * \return \c NULL when failed, a pointer to the DXF \c 3DLINE entity
 * when successful.
 *
 * \warning Both DXF \c POINT entities need to be freed by the caller.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
 */
Dxf3dline *
dxf_3dline_create_from_points
(
        DxfPoint *p1,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfPoint *p2,
                /*!< a pointer to a DXF \c POINT entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> Point 1.</li>
                 * <li value = "2"> Point 2.</li>
                 * </ol>
                 */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        Dxf3dline *line = NULL;

        /* Do some basic checks. */
        if ((p1 == NULL) || (p2 == NULL))
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((p1->x0 == p2->x0) && (p1->y0 == p2->y0) && (p1->z0 == p2->z0))
        {
                fprintf (stderr,
                  (_("Error in %s () points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((inheritance < 0) || (inheritance > 2))
        {
                fprintf (stderr,
                  (_("Error in %s () an illegal inherit value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line = dxf_3dline_init (line);
        if (line == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a Dxf3dline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        line->id_code = id_code;
        line->x0 = p1->x0;
        line->y0 = p1->y0;
        line->z0 = p1->z0;
        line->x1 = p2->x0;
        line->y1 = p2->y0;
        line->z1 = p2->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (p1->linetype != NULL)
                        {
                                line->linetype = p1->linetype;
                        }
                        if (p1->layer != NULL)
                        {
                                line->layer = p1->layer;
                        }
                        line->thickness = p1->thickness;
                        line->linetype_scale = p1->linetype_scale;
                        line->visibility = p1->visibility;
                        line->color = p1->color;
                        line->paperspace = p1->paperspace;
                        if (p1->dictionary_owner_soft != NULL)
                        {
                                line->dictionary_owner_soft = strdup (p1->dictionary_owner_soft);
                        }
                        if (p1->dictionary_owner_hard != NULL)
                        {
                                line->dictionary_owner_hard = strdup (p1->dictionary_owner_hard);
                        }
                        break;
                case 2:
                        if (p2->linetype != NULL)
                        {
                                line->linetype = p2->linetype;
                        }
                        if (p2->layer != NULL)
                        {
                                line->layer = p2->layer;
                        }
                        line->thickness = p2->thickness;
                        line->linetype_scale = p2->linetype_scale;
                        line->visibility = p2->visibility;
                        line->color = p2->color;
                        line->paperspace = p2->paperspace;
                        if (p2->dictionary_owner_soft != NULL)
                        {
                                line->dictionary_owner_soft = strdup (p2->dictionary_owner_soft);
                        }
                        if (p2->dictionary_owner_hard != NULL)
                        {
                                line->dictionary_owner_hard = strdup (p2->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the next \c 3DLINE entity from a DXF 
 * \c 3DLINE entity.
 *
 * \return pointer to the next \c 3DLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dline *
dxf_3dline_get_next
(
        Dxf3dline *line
                /*!< a pointer to a DXF \c 3DLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((Dxf3dline *) line->next);
}


/*!
 * \brief Set the pointer to the next \c 3DLINE for a DXF \c 3DLINE
 * entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dline *
dxf_3dline_set_next
(
        Dxf3dline *line,
                /*!< a pointer to a DXF \c 3DLINE entity. */
        Dxf3dline *next
                /*!< a pointer to the next \c 3DLINE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->next = (struct Dxf3dline *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/* EOF */
