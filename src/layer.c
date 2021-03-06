/*!
 * \file layer.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF layer table (\c LAYER).
 *
 * \note Xref-dependent layers are output during DXFOUT.\n
 * For these layers, the associated linetype name in the DXF file is
 * always CONTINUOUS.
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


#include "layer.h"


/*!
 * \brief Allocate memory for a DXF \c LAYER.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLayer *
dxf_layer_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLayer *layer = NULL;
        size_t size;

        size = sizeof (DxfLayer);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((layer = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLayer struct.\n")),
                  __FUNCTION__);
                layer = NULL;
        }
        else
        {
                memset (layer, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LAYER
 * table.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLayer *
dxf_layer_init
(
        DxfLayer *layer
                /*!< DXF LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer = dxf_layer_new ();
        }
        if (layer == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfLayer struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        layer->id_code = 0;
        layer->layer_name = strdup ("");
        layer->linetype = strdup (DXF_DEFAULT_LINETYPE);
        layer->color = DXF_COLOR_BYLAYER;
        layer->flag = 0;
        layer->plotting_flag = 0;
        layer->dictionary_owner_soft = strdup ("");
        layer->material = strdup ("");
        layer->dictionary_owner_hard = strdup ("");
        layer->lineweight = 0;
        layer->plot_style_name = strdup ("");
        layer->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LAYER table.
 *
 * The last line read from file contained the string "LAYER". \n
 * Now follows some data for the \c LAYER, to be terminated with a "  0"
 * string announcing the following table, or the end of the \c TABLE
 * section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c layer. \n
 *
 * \return a pointer to \c layer.
 */
DxfLayer *
dxf_layer_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLayer *layer
                /*!< DXF LAYER table. */
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
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer = dxf_layer_new ();
                layer = dxf_layer_init (layer);
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
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing the layer
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer->layer_name);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing the linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer->linetype);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &layer->color);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &layer->flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTable") != 0)
                        && ((strcmp (temp_string, "AcDbLayerTableRecord") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the plotting
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &layer->plotting_flag);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing the material. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the
                         * lineweight. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &layer->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing the plot style
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer->plot_style_name);
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
        if (strcmp (layer->layer_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () found a bad layer name in: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                fprintf (stderr,
                  (_("\tskipping layer.\n")));
                return (NULL);
        }
        if (strcmp (layer->linetype, "") == 0)
        {
                layer->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Write DXF output for a DXF \c LAYER table.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LAYER");

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
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer->layer_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty layer string for the %s table.\n")),
                  __FUNCTION__, dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s layer\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                layer->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (layer->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", layer->id_code);
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
        if ((strcmp (layer->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", layer->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTable\n");
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbLayerTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", layer->layer_name);
        fprintf (fp->fp, " 70\n%d\n", layer->flag);
        fprintf (fp->fp, " 62\n%d\n", layer->color);
        fprintf (fp->fp, "  6\n%s\n", layer->linetype);
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, "290\n%d\n", layer->plotting_flag);
                fprintf (fp->fp, "370\n%hd\n", layer->lineweight);
                fprintf (fp->fp, "390\n%s\n", layer->plot_style_name);
        }
        if (fp->acad_version_number >= AutoCAD_2007)
        {
                fprintf (fp->fp, "347\n%s\n", layer->material);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LAYER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_free
(
        DxfLayer *layer
                /*!< Pointer to the memory occupied by the DXF \c LAYER
                 * table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (layer->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfLayer was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (layer->layer_name);
        free (layer->linetype);
        free (layer->dictionary_owner_soft);
        free (layer->material);
        free (layer->dictionary_owner_hard);
        free (layer->plot_style_name);
        free (layer);
        layer = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c LAYER
 * tables and all their data fields.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_layer_free_chain
(
        DxfLayer *layers
                /*!< pointer to the chain of DXF \c LAYER tables. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (layers == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (layers != NULL)
        {
                struct DxfLayer *iter = layers->next;
                dxf_layer_free (layers);
                layers = (DxfLayer *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Test if layer is frozen.
 *
 * \return \c TRUE when layer is frozen, or \c FALSE when layer is
 * thawed, or (-1) when an error occurred.
 */
int
dxf_layer_is_frozen
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = ((DXF_CHECK_BIT (layer->flag, 0))
          || (DXF_CHECK_BIT (layer->flag, 1)));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is locked.
 *
 * \return \c TRUE when layer is locked, or \c FALSE when layer is not
 * locked, or (-1) when an error occurred.
 */
int
dxf_layer_is_locked
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (layer->flag, 2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is externally dependent on an xref.
 *
 * \return \c TRUE when layer is externally dependent on an xref,
 * or \c FALSE when layer is not externally dependent on an xref, or
 * (-1) when an error occurred.
 */
int
dxf_layer_is_xreferenced
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (layer->flag, 4);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is externally dependent on a xref and has been
 * successfully resolved.
 *
 * \return \c TRUE when layer is externally dependent on a xref and has
 * been successfully resolved, or \c FALSE when layer is not externally
 * dependent on a xref and has not been successfully resolved, or (-1)
 * when an error occurred.
 */
int
dxf_layer_is_xresolved
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = ((DXF_CHECK_BIT (layer->flag, 4))
          && (DXF_CHECK_BIT (layer->flag, 5)));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is internally referenced by an entity.
 *
 * \return \c TRUE when layer is internally referenced by an entity,
 * or \c FALSE when layer is not internally referenced by an entity, or
 * (-1) when an error occurred.
 */
int
dxf_layer_is_referenced
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (layer->flag, 6);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is off.
 *
 * \return \c TRUE when layer is off, or \c FALSE when layer is on, or
 * (-1) when an error occurred.
 */
int
dxf_layer_is_off
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = (layer->color < 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
