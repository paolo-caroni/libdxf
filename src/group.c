/*!
 * \file group.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF group object (\c GROUP).
 *
 * \version The \c GROUP object was introduced in DXF R13.
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


#include "group.h"


/*!
 * \brief Allocate memory for a \c DxfGroup.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfGroup *
dxf_group_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfGroup *group = NULL;
        size_t size;

        size = sizeof (DxfGroup);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((group = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfGroup struct.\n")),
                  __FUNCTION__);
                group = NULL;
        }
        else
        {
                memset (group, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c GROUP
 * object.
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
DxfGroup *
dxf_group_init
(
        DxfGroup *group
                /*!< DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                group = dxf_group_new ();
        }
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfGroup struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        group->id_code = 0;
        group->description = strdup ("");
        group->handle_entity_in_group = strdup ("");
        group->unnamed_flag = 0;
        group->selectability_flag = 0;
        group->dictionary_owner_soft = strdup ("");
        group->dictionary_owner_hard = strdup ("");
        group->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Read data from a DXF file into a DXF \c GROUP object.
 *
 * The last line read from file contained the string "GROUP". \n
 * Now follows some data for the \c GROUP object, to be terminated
 * with a "  0" string announcing the following object. \n
 * While parsing the DXF file store data in \c group. \n
 *
 * \return \c a pointer to \c group object.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfGroup *
dxf_group_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfGroup *group
                /*!< DXF \c GROUP object. */
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
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                group = dxf_group_new ();
                group = dxf_group_init (group);
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
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &group->id_code);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * unnamed flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &group->unnamed_flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * selectability flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &group->selectability_flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbGroup") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "300") == 0)
                {
                        /* Now follows a string containing a description. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", group->description);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", group->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a handle to an
                         * entry in group object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", group->handle_entity_in_group);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", group->dictionary_owner_hard);
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
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Write DXF output to a file for a DXF \c GROUP object.
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
dxf_group_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfGroup *group
                /*!< DXF \c Group object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("GROUP");

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
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (group->description, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty description string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, group->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (group->handle_entity_in_group, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty string for handle entity in group for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, group->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, group->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (group->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", group->id_code);
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
        if ((strcmp (group->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", group->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (group->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", group->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbGroup\n");
        }
        fprintf (fp->fp, "300\n%s\n", group->description);
        fprintf (fp->fp, " 70\n%d\n", group->unnamed_flag);
        fprintf (fp->fp, " 71\n%d\n", group->selectability_flag);
        fprintf (fp->fp, "340\n%s\n", group->handle_entity_in_group);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c GROUP and all it's
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
dxf_group_free
(
        DxfGroup *group
                /*!< Pointer to the memory occupied by the DXF
                 * \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfGroup was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (group->dictionary_owner_soft);
        free (group->dictionary_owner_hard);
        free (group->description);
        free (group->handle_entity_in_group);
        free (group);
        group = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/