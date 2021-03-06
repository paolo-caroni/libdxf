/*!
 * \file 3dsolid.c
 *
 * \author Copyright (C) 2012 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF 3D solid entity (\c 3DSOLID).
 *
 * \version The \c 3DSOLID entity was introduced in DXF R13.
 *
 * \warning dxf_3dsolid_new(), dxf_3dsolid_init(), dxf_3dsolid_read()
 * and dxf_3dsolid_free() are backward compatible with versions
 * R10 .. R12 to allow for reading DXF data generated with other CAD
 * software. \n
 * When writing DXF data to file with versions before DXF R13 a warning
 * message is given.
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


#include "3dsolid.h"


/*!
 * \brief Allocate memory for a DXF \c 3DSOLID.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        Dxf3dsolid *solid = NULL;
        size_t size;

        size = sizeof (Dxf3dsolid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((solid = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a Dxf3dsolid struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                memset (solid, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c 3DSOLID
 * entity.
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
Dxf3dsolid *
dxf_3dsolid_init
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                solid = dxf_3dsolid_new ();
        }
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a Dxf3dsolid struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->modeler_format_version_number = 0;
        solid->id_code = 0;
        solid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        solid->layer = strdup (DXF_DEFAULT_LAYER);
        solid->elevation = 0.0;
        solid->thickness = 0.0;
        solid->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        solid->visibility = DXF_DEFAULT_VISIBILITY;
        solid->color = DXF_COLOR_BYLAYER;
        solid->paperspace = DXF_MODELSPACE;
        solid->modeler_format_version_number = 1;
        solid->history = strdup ("");
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                solid->proprietary_data[i] = strdup ("");
                solid->additional_proprietary_data[i] = strdup ("");
        }
        solid->dictionary_owner_soft = strdup ("");
        solid->dictionary_owner_hard = strdup ("");
        solid->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Read data from a DXF file into a DXF \c 3DSOLID entity.
 *
 * The last line read from file contained the string "3DSOLID". \n
 * Now follows some data for the \c 3DSOLID, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c solid. \n
 *
 * \return \c a pointer to \c solid.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int j;

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
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                solid = dxf_3dsolid_new ();
                solid = dxf_3dsolid_init (solid);
        }
        i = 0;
        j = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "  1") == 0)
                {
                        /* Now follows a string containing proprietary
                         * data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->proprietary_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->additional_proprietary_data[j]);
                        j++;
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &solid->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                  && DXF_FLATLAND
                  && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &solid->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "70") == 0))
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->modeler_format_version_number);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbModelerGeometry") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if ((fp->acad_version_number >= AutoCAD_2008)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDb3dSolid") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->dictionary_owner_soft);
                }
                else if ((fp->acad_version_number >= AutoCAD_2008)
                        && (strcmp (temp_string, "350") == 0))
                {
                        /* Now follows a string containing a handle to a
                         * history object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->history);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (solid->linetype, "") == 0)
        {
                solid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (solid->layer, "") == 0)
        {
                solid->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Write DXF output to a file for a DXF \c 3DSOLID entity.
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
dxf_3dsolid_write
(
        DxfFile *fp,
                /*!< a DXF file pointer to an output file (or device). */
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("3DSOLID");
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
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, solid->id_code);
        }
        if (strcmp (solid->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, solid->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                solid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (solid->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, solid->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                solid->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (solid->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", solid->id_code);
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
        if ((strcmp (solid->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", solid->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (solid->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", solid->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (solid->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", solid->layer);
        if (strcmp (solid->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", solid->linetype);
        }
        if (solid->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", solid->color);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (solid->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", solid->elevation);
        }
        if (solid->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", solid->thickness);
        }
        if (solid->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", solid->linetype_scale);
        }
        if (solid->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", solid->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbModelerGeometry\n");
        }
        if (fp->acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp->fp, "100\nAcDb3dSolid\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, " 70\n%d\n", solid->modeler_format_version_number);
        }
        i = 0;
        while (strlen (solid->proprietary_data[i]) > 0)
        {
                fprintf (fp->fp, "  1\n%s\n", solid->proprietary_data[i]);
                i++;
        }
        i = 0;
        while (strlen (solid->additional_proprietary_data[i]) > 0)
        {
                fprintf (fp->fp, "  3\n%s\n", solid->additional_proprietary_data[i]);
                i++;
        }
        if (fp->acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp->fp, "350\n%s\n", solid->history);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c 3DSOLID and all it's
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
dxf_3dsolid_free
(
        Dxf3dsolid *solid
                /*!< a pointer to the memory occupied by the DXF
                 * \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (solid->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next Dxf3dsolid was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (solid->linetype);
        free (solid->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (solid->proprietary_data[i]);
                free (solid->additional_proprietary_data[i]);
        }
        free (solid->dictionary_owner_soft);
        free (solid->dictionary_owner_hard);
        free (solid);
        solid = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c 3DSOLID
 * entities and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_3dsolid_free_chain
(
        Dxf3dsolid *solids
                /*!< a pointer to the chain of DXF \c 3DSOLID entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (solids == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (solids != NULL)
        {
                struct Dxf3dsolid *iter = solids->next;
                dxf_3dsolid_free (solids);
                solids = (Dxf3dsolid *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c 3DSOLID entity.
 *
 * \return ID code.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_3dsolid_get_id_code
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = solid->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_id_code
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
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
        if (solid == NULL)
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
        solid->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the linetype from a DXF \c 3DSOLID entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_3dsolid_get_linetype
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (solid->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_linetype
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the layer from a DXF \c 3DSOLID entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_3dsolid_get_layer
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (solid->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the layer for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_layer
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the elevation from a DXF \c 3DSOLID entity.
 *
 * \return elevation.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_3dsolid_get_elevation
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = solid->elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the elevation for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_elevation
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the thickness from a DXF \c 3DSOLID entity.
 *
 * \return thickness.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_3dsolid_get_thickness
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = solid->thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the thickness for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_thickness
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the linetype scale from a DXF \c 3DSOLID entity.
 *
 * \return linetype scale.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_3dsolid_get_linetype_scale
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = solid->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype scale for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_linetype_scale
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the visibility from a DXF \c 3DSOLID entity.
 *
 * \return visibility.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int16_t
dxf_3dsolid_get_visibility
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = solid->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the visibility for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_visibility
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the color from a DXF \c 3DSOLID entity.
 *
 * \return color.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_3dsolid_get_color
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = solid->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_color
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c 3DSOLID entity.
 *
 * \return paperspace flag value.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_3dsolid_get_paperspace
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (solid->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = solid->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the paperspace flag for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_paperspace
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c 3DSOLID entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_3dsolid_get_dictionary_owner_soft
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (solid->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_dictionary_owner_soft
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c 3DSOLID entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_3dsolid_get_dictionary_owner_hard
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (solid->dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_dictionary_owner_hard
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the modeler format version number from a DXF \c 3DSOLID
 * entity.
 *
 * \return the modeler format version number.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_3dsolid_get_modeler_format_version_number
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->modeler_format_version_number < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the modeler_format_version_number member.\n")),
                  __FUNCTION__);
        }
        if (solid->modeler_format_version_number > DXF_MODELER_FORMAT_CURRENT_VERSION)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the modeler_format_version_number member.\n")),
                  __FUNCTION__);
        }
        result = solid->modeler_format_version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the modeler format version number for a DXF \c 3DSOLID
 * entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_modeler_format_version_number
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int modeler_format_version_number
                /*!< the modeler format version number to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (modeler_format_version_number < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative modeler_format_version_number value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (modeler_format_version_number > DXF_MODELER_FORMAT_CURRENT_VERSION)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->modeler_format_version_number = modeler_format_version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the history from a DXF \c 3DSOLID entity.
 *
 * \return soft pointer to the history.
 *
 * \warning No checks are performed on the returned pointer (string).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_3dsolid_get_history
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->history ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (solid->history);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the history for a DXF \c 3DSOLID entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_history
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *history
                /*!< a string containing the pointer to the history for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (history == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->history = strdup (history);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the next \c 3DSOLID entity from a DXF 
 * \c 3DSOLID entity.
 *
 * \return pointer to the next \c 3DSOLID entity.
 *
 * \warning No checks are performed on the returned pointer.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_get_next
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        Dxf3dsolid *result;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (Dxf3dsolid *) solid->next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the next \c 3DSOLID for a DXF \c 3DSOLID
 * entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dsolid *
dxf_3dsolid_set_next
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3SOLID entity. */
        Dxf3dsolid *next
                /*!< a pointer to the next \c 3DSOLID for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->next = (struct Dxf3dsolid *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/* EOF */
