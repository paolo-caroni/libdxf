/*!
 * \file acad_proxy_entity.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF acad_proxy_entity entity
 * (\c ACAD_PROXY_ENTITY).
 *
 * \version The \c ACAD_ZOMBIE_ENTITY entity was introduced in DXF R13.
 * \version The \c ACAD_ZOMBIE_ENTITY entity was renamed to 
 * \c ACAD_PROXY_ENTITY in DXF R14.
 *
 * \warning dxf_acad_proxy_entity_new(), dxf_acad_proxy_entity_init(),
 * dxf_acad_proxy_entity_read() and dxf_acad_proxy_entity_free() are
 * backward compatible with versions R10 .. R12 to allow for reading DXF
 * data generated with other CAD software. \n
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


#include "acad_proxy_entity.h"


/*!
 * \brief Allocate memory for a DXF \c ACAD_PROXY_ENTITY.
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
 * \version According to DXF R2000.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAcadProxyEntity *acad_proxy_entity = NULL;
        size_t size;

        size = sizeof (DxfAcadProxyEntity);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((acad_proxy_entity = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfAcadProxyEntity struct.\n")),
                  __FUNCTION__);
                acad_proxy_entity = NULL;
        }
        else
        {
                memset (acad_proxy_entity, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c ACAD_PROXY_ENTITY
 * table.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_init
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                acad_proxy_entity = dxf_acad_proxy_entity_new ();
        }
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfAcadProxyEntity struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->id_code = 0;
        acad_proxy_entity->linetype = strdup (DXF_DEFAULT_LINETYPE);
        acad_proxy_entity->layer = strdup (DXF_DEFAULT_LAYER);
        acad_proxy_entity->color = DXF_COLOR_BYLAYER;
        acad_proxy_entity->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        acad_proxy_entity->visibility = 0;
        acad_proxy_entity->dictionary_owner_soft = strdup ("");
        acad_proxy_entity->dictionary_owner_hard = strdup ("");
        acad_proxy_entity->original_custom_object_data_format = 1;
        acad_proxy_entity->proxy_entity_class_id = DXF_DEFAULT_PROXY_ENTITY_ID;
        acad_proxy_entity->application_entity_class_id = 0;
        acad_proxy_entity->graphics_data_size = 0;
        acad_proxy_entity->object_drawing_format = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                acad_proxy_entity->binary_graphics_data[i] = strdup ("");
                acad_proxy_entity->object_id[i] = strdup ("");
        }
        acad_proxy_entity->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Read data from a DXF file into a DXF \c ACAD_PROXY_ENTITY
 * entity.
 *
 * The last line read from file contained the string "ACAD_PROXY_ENTITY". \n
 * Now follows some data for the \c ACAD_PROXY_ENTITY, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_acad_proxy_entity. \n
 *
 * \return a pointer to \c acad_proxy_entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY table. */
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
        if (!acad_proxy_entity)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                acad_proxy_entity = dxf_acad_proxy_entity_new ();
                acad_proxy_entity = dxf_acad_proxy_entity_init (acad_proxy_entity);
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
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &acad_proxy_entity->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing the linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", acad_proxy_entity->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing the layer
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", acad_proxy_entity->layer);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &acad_proxy_entity->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the object
                         * visability value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &acad_proxy_entity->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &acad_proxy_entity->color);
                }
                else if ((fp->acad_version_number >= AutoCAD_2000)
                  && (strcmp (temp_string, "70") == 0))
                {
                        /* Now follows a string containing the original
                         * custom object data format value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &acad_proxy_entity->original_custom_object_data_format);
                        if (acad_proxy_entity->original_custom_object_data_format != 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad original custom object data format value in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the proxy
                         * entity ID value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &acad_proxy_entity->proxy_entity_class_id);
                        if (acad_proxy_entity->proxy_entity_class_id != DXF_DEFAULT_PROXY_ENTITY_ID)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad proxy entity class ID in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing the application
                         * entity ID value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &acad_proxy_entity->application_entity_class_id);
                        if (acad_proxy_entity->application_entity_class_id < 500)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad value in application entity class ID in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the graphics
                         * data size value (bytes). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &acad_proxy_entity->graphics_data_size);
                }
                else if (strcmp (temp_string, "93") == 0)
                {
                        /* Now follows a string containing the entity
                         * data size value (bits). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &acad_proxy_entity->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_2000)
                  && (strcmp (temp_string, "95") == 0))
                {
                        /* Now follows a string containing the object
                         * drawing format value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &acad_proxy_entity->object_drawing_format);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                  && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                          && ((strcmp (temp_string, "AcDbZombieEntity") != 0))
                          && ((strcmp (temp_string, "AcDbProxyEntity") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", acad_proxy_entity->binary_graphics_data[i]);
                        i++;
                }
                else if ((strcmp (temp_string, "330") == 0)
                  || (strcmp (temp_string, "340") == 0)
                  || (strcmp (temp_string, "350") == 0)
                  || (strcmp (temp_string, "360") == 0))
                {
                        /* Now follows a string containing an object id. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", acad_proxy_entity->object_id[j]);
                        j++;
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
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Write DXF output for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
int
dxf_acad_proxy_entity_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = NULL;
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
        if (acad_proxy_entity == NULL)
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
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (fp->acad_version_number <= AutoCAD_13)
        {
                dxf_entity_name = strdup ("ACAD_ZOMBIE_ENTITY");
        }
        else if (fp->acad_version_number >= AutoCAD_14)
        {
                dxf_entity_name = strdup ("ACAD_PROXY_ENTITY");
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (acad_proxy_entity->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", acad_proxy_entity->id_code);
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
        if ((strcmp (acad_proxy_entity->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", acad_proxy_entity->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (acad_proxy_entity->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", acad_proxy_entity->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (acad_proxy_entity->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", acad_proxy_entity->layer);
        if (strcmp (acad_proxy_entity->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", acad_proxy_entity->linetype);
        }
        if (acad_proxy_entity->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", acad_proxy_entity->color);
        }
        fprintf (fp->fp, " 48\n%f\n", acad_proxy_entity->linetype_scale);
        fprintf (fp->fp, " 60\n%d\n", acad_proxy_entity->visibility);
        if (fp->acad_version_number == AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbZombieEntity\n");
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbProxyEntity\n");
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 70\n%d\n", acad_proxy_entity->original_custom_object_data_format);
        }
        fprintf (fp->fp, " 90\n%d\n", acad_proxy_entity->proxy_entity_class_id);
        fprintf (fp->fp, " 91\n%d\n", acad_proxy_entity->application_entity_class_id);
        fprintf (fp->fp, " 92\n%d\n", acad_proxy_entity->graphics_data_size);
        i = 0;
        while (strlen (acad_proxy_entity->binary_graphics_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", acad_proxy_entity->binary_graphics_data[i]);
                i++;
        }
        fprintf (fp->fp, " 93\n%d\n", acad_proxy_entity->entity_data_size);
        while (strlen (acad_proxy_entity->binary_graphics_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", acad_proxy_entity->binary_graphics_data[i]);
                i++;
        }
        i = 0;
        while (strlen (acad_proxy_entity->object_id[i]) > 0)
        {
                fprintf (fp->fp, "330\n%s\n", acad_proxy_entity->object_id[i]);
                i++;
        }
        fprintf (fp->fp, " 94\n  0\n");
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 95\n%ld\n", acad_proxy_entity->object_drawing_format);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 70\n%d\n", acad_proxy_entity->original_custom_object_data_format);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ACAD_PROXY_ENTITY and all it's
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
 * \version According to DXF R2000.
 */
int
dxf_acad_proxy_entity_free
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to the memory occupied by the DXF
                 * \c ACAD_PROXY_ENTITY table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (acad_proxy_entity->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfAcadProxyEntity was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (acad_proxy_entity->linetype);
        free (acad_proxy_entity->layer);
        free (acad_proxy_entity->dictionary_owner_soft);
        free (acad_proxy_entity->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (acad_proxy_entity->binary_graphics_data[i]);
                free (acad_proxy_entity->object_id[i]);
        }
        free (acad_proxy_entity);
        acad_proxy_entity = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c ACAD_PROXY_ENTITY
 * entities and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
void
dxf_acad_proxy_entity_free_chain
(
        DxfAcadProxyEntity *acad_proxy_entities
                /*!< a pointer to the chain of DXF ACAD_PROXY_ENTITY entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (acad_proxy_entities == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (acad_proxy_entities != NULL)
        {
                struct DxfAcadProxyEntity *iter = acad_proxy_entities->next;
                dxf_acad_proxy_entity_free (acad_proxy_entities);
                acad_proxy_entities = (DxfAcadProxyEntity *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c ACAD_PROXY_ENTITY entity.
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
dxf_acad_proxy_entity_get_id_code
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = acad_proxy_entity->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_id_code
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
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
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the linetype from a DXF \c ACAD_PROXY_ENTITY entity.
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
dxf_acad_proxy_entity_get_linetype
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (acad_proxy_entity->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_linetype
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the layer from a DXF \c ACAD_PROXY_ENTITY entity.
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
dxf_acad_proxy_entity_get_layer
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (acad_proxy_entity->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the layer for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_layer
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the linetype scale from a DXF \c ACAD_PROXY_ENTITY entity.
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
dxf_acad_proxy_entity_get_linetype_scale
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = acad_proxy_entity->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype scale for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_linetype_scale
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the object visibility from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return object visibility.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int16_t
dxf_acad_proxy_entity_get_visibility
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = acad_proxy_entity->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the visibility for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_visibility
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the color from a DXF \c ACAD_PROXY_ENTITY entity.
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
dxf_acad_proxy_entity_get_color
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = acad_proxy_entity->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_color
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c ACAD_PROXY_ENTITY
 * entity.
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
dxf_acad_proxy_entity_get_paperspace
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (acad_proxy_entity->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = acad_proxy_entity->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the paperspace flag for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_paperspace
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c ACAD_PROXY_ENTITY entity.
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
dxf_acad_proxy_entity_get_dictionary_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (acad_proxy_entity->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_dictionary_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c ACAD_PROXY_ENTITY entity.
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
dxf_acad_proxy_entity_get_dictionary_owner_hard
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (acad_proxy_entity->dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_dictionary_owner_hard
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the original custom object data format value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return original custom object data format value.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_acad_proxy_entity_get_original_custom_object_data_format
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->original_custom_object_data_format < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the original_custom_object_data_format member.\n")),
                  __FUNCTION__);
        }
        if (acad_proxy_entity->original_custom_object_data_format > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the original_custom_object_data_format member.\n")),
                  __FUNCTION__);
        }
        result = acad_proxy_entity->original_custom_object_data_format;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the original custom object data format value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_original_custom_object_data_format
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int original_custom_object_data_format
                /*!< the original custom object data format value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (original_custom_object_data_format < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative original custom object data format value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (original_custom_object_data_format > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range original custom object data format value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->original_custom_object_data_format = original_custom_object_data_format;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the proxy entity class id value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return proxy entity class id value.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_acad_proxy_entity_get_proxy_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->proxy_entity_class_id != 498)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was found in the proxy_entity_class_id member.\n")),
                  __FUNCTION__);
        }
        result = acad_proxy_entity->proxy_entity_class_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the proxy entity class id value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_proxy_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int proxy_entity_class_id
                /*!< the proxy entity class id value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (proxy_entity_class_id != 498)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->proxy_entity_class_id = proxy_entity_class_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the application entity class id value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return application entity class id value.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_acad_proxy_entity_get_application_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->application_entity_class_id < 500)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was found in the proxy_entity_class_id member.\n")),
                  __FUNCTION__);
        }
        result = acad_proxy_entity->application_entity_class_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the application entity class id value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_application_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int application_entity_class_id
                /*!< the application entity class id value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (application_entity_class_id < 500)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->application_entity_class_id = application_entity_class_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the graphics data size value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return graphics data size value.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_acad_proxy_entity_get_graphics_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid graphics data size value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = acad_proxy_entity->graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the graphics data size value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_graphics_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int graphics_data_size
                /*!< the graphics data size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid graphics data size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the entity data size value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return entity data size value.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_acad_proxy_entity_get_entity_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->entity_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid entity data size value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = acad_proxy_entity->entity_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the entity data size value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_entity_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int entity_data_size
                /*!< the entity data size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid graphics data size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->entity_data_size = entity_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the object drawing format value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return object drawing format value.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2000.
 */
ulong
dxf_acad_proxy_entity_get_object_drawing_format
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        ulong result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->object_drawing_format < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid object drawing format value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = acad_proxy_entity->object_drawing_format;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Get the pointer to the next \c ACAD_PROXY_ENTITY entity from a
 * DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return pointer to the next \c ACAD_PROXY_ENTITY entity.
 *
 * \warning No checks are performed on the returned pointer.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_get_next
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAcadProxyEntity *result;

        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfAcadProxyEntity *) acad_proxy_entity->next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the next \c ACAD_PROXY_ENTITY for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_next
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        DxfAcadProxyEntity *next
                /*!< a pointer to the next \c ACAD_PROXY_ENTITY for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->next = (struct DxfAcadProxyEntity *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/* EOF */
