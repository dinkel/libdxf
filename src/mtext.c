/*!
 * \file mtext.c
 *
 * \author Copyright (C) 2012 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mtext entity (\c MTEXT).
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


#include "mtext.h"


/*!
 * \brief Allocate memory for a \c DxfMtext.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfMtext *
dxf_mtext_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMtext *dxf_mtext = NULL;
        size_t size;

        size = sizeof (DxfMtext);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_mtext = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfMtext struct.\n")),
                  __FUNCTION__);
                dxf_mtext = NULL;
        }
        else
        {
                memset (dxf_mtext, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_mtext);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c MTEXT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfMtext *
dxf_mtext_init
(
        DxfMtext *dxf_mtext
                /*!< DXF mtext entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (dxf_mtext == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_mtext = dxf_mtext_new ();
        }
        if (dxf_mtext == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfMtext struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_mtext->id_code = 0;
        dxf_mtext->text_value = strdup ("");
        for (i = 1; i < DXF_MAX_PARAM; i++)
        {
                dxf_mtext->text_additional_value[i] = strdup ("");
        }
        dxf_mtext->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_mtext->text_style = strdup ("");
        dxf_mtext->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_mtext->x0 = 0.0;
        dxf_mtext->y0 = 0.0;
        dxf_mtext->z0 = 0.0;
        dxf_mtext->x1 = 0.0;
        dxf_mtext->y1 = 0.0;
        dxf_mtext->z1 = 0.0;
        dxf_mtext->height = 0.0;
        dxf_mtext->rectangle_width = 0.0;
        dxf_mtext->horizontal_width = 0.0;
        dxf_mtext->rectangle_height = 0.0;
        dxf_mtext->spacing_factor = 0.0;
        dxf_mtext->box_scale = 0.0;
        dxf_mtext->column_width = 0.0;
        dxf_mtext->column_gutter = 0.0;
        dxf_mtext->column_heights = 0.0;
        dxf_mtext->rot_angle = 0.0;
        dxf_mtext->color = DXF_COLOR_BYLAYER;
        dxf_mtext->background_color = 0;
        dxf_mtext->paperspace = DXF_MODELSPACE;
        dxf_mtext->attachment_point = 0;
        dxf_mtext->drawing_direction = 0;
        dxf_mtext->spacing_style = 0;
        dxf_mtext->column_type = 0;
        dxf_mtext->column_count = 0;
        dxf_mtext->column_flow = 0;
        dxf_mtext->column_autoheight = 0;
        dxf_mtext->background_fill = 0;
        dxf_mtext->extr_x0 = 0.0;
        dxf_mtext->extr_y0 = 0.0;
        dxf_mtext->extr_z0 = 0.0;
        dxf_mtext->background_color_rgb = 0;
        dxf_mtext->background_color_name = strdup ("");
        dxf_mtext->background_transparency = 0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_mtext);
}


/*!
 * \brief Read data from a DXF file into a \c MTEXT entity.
 *
 * The last line read from file contained the string "MTEXT". \n
 * Now follows some data for the \c MTEXT, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_mtext. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfMtext *
dxf_mtext_read
(
        DxfFile *fp,
                /*!< DXF filepointer to the input file (or device). */
        DxfMtext *dxf_mtext
                /*!< DXF mtext entity. */
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
                return (NULL);
        }
        if (dxf_mtext == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_mtext = dxf_mtext_new ();
                dxf_mtext = dxf_mtext_init (dxf_mtext);
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
                        return (NULL);
                }
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a text value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_mtext->text_value);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a text value. */
                        (fp->line_number)++;
                        //fscanf (fp->fp, "%s\n", dxf_mtext->text_additional_value[number_additional]);
                        //number_additional++;
                }
                /*!< I'm not sure this number_additional is correct.*/
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_mtext->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_mtext->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_mtext->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_mtext->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->z0);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * reference rectangle width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->rectangle_width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal width of the characters. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->horizontal_width);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * vertical rectangle height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->rectangle_height);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the
                         * text line spacing factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->spacing_factor);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing the
                         * fill box scale (border around text). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->box_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the
                         * column width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->column_width);
                }
                else if (strcmp (temp_string, "49") == 0)
                {
                        /* Now follows a string containing the
                         * column gutter. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->column_gutter);
                }
                else if ((fp->acad_version_number <= AutoCAD_2006)
                        && (strcmp (temp_string, "50") == 0))
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->rot_angle);
                }
                else if ((fp->acad_version_number >= AutoCAD_2007)
                        && (strcmp (temp_string, "50") == 0))
                {
                        /* Can follows a string containing the
                         * rotation angle or column heights. */
                        (fp->line_number)++;
                /*!< Add more code here, I'm stop because the double use of group code 50*/
                }
                else if (strcmp (temp_string, "63") == 0)
                {
                        /* Now follows a string containing the
                         * color to use for background fill. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->background_color);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * attachment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->attachment_point);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * drawing direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->drawing_direction);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * mtext line spacing style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->spacing_style);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the
                         * column type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->column_type);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing the
                         * column count. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->column_count);
                }
                else if (strcmp (temp_string, "78") == 0)
                {
                        /* Now follows a string containing the
                         * column flow reverse. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->column_flow);
                }
                else if (strcmp (temp_string, "79") == 0)
                {
                        /* Now follows a string containing the
                         * column autoheight. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->column_autoheight);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * background fill setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_mtext->background_fill);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbMText") != 0)))
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
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_mtext->extr_z0);
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
        if (strcmp (dxf_mtext->linetype, "") == 0)
        {
                dxf_mtext->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_mtext->layer, "") == 0)
        {
                dxf_mtext->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a DXF \c ARC entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_mtext_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfMtext *dxf_mtext
                /*!< DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("MTEXT");
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_mtext->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_mtext->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_mtext->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_mtext->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_mtext->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_mtext->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_mtext->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_mtext->id_code);
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
        if ((strcmp (dxf_mtext->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_mtext->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_mtext->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_mtext->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_mtext->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_mtext->layer);
        if (strcmp (dxf_mtext->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_mtext->linetype);
        }
        if (dxf_mtext->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_mtext->color);
        }
        if (dxf_mtext->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_mtext->linetype_scale);
        }
        if (dxf_mtext->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_mtext->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbMText\n");
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_mtext->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_mtext->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_mtext->z0);
        fprintf (fp->fp, " 40\n%f\n", dxf_mtext->height);
        fprintf (fp->fp, " 41\n%f\n", dxf_mtext->rectangle_width);
        fprintf (fp->fp, " 71\n%d\n", dxf_mtext->attachment_point);
        fprintf (fp->fp, " 72\n%d\n", dxf_mtext->drawing_direction);
        fprintf (fp->fp, "  1\n%s\n", dxf_mtext->text_value);
        i = 0;
        while (strlen (dxf_mtext->text_additional_value[i]) > 0)
        {
                fprintf (fp->fp, "  3\n%s\n", dxf_mtext->text_additional_value[i]);
                i++;
        }
        fprintf (fp->fp, "  7\n%s\n", dxf_mtext->text_style);

        if ((fp->acad_version_number >= AutoCAD_12)
                && (dxf_mtext->extr_x0 != 0.0)
                && (dxf_mtext->extr_y0 != 0.0)
                && (dxf_mtext->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", dxf_mtext->extr_x0);
                fprintf (fp->fp, "220\n%f\n", dxf_mtext->extr_y0);
                fprintf (fp->fp, "230\n%f\n", dxf_mtext->extr_z0);
        }
        fprintf (fp->fp, " 11\n%f\n", dxf_mtext->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_mtext->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_mtext->z1);
        fprintf (fp->fp, " 42\n%f\n", dxf_mtext->horizontal_width);
        fprintf (fp->fp, " 43\n%f\n", dxf_mtext->rectangle_height);
        fprintf (fp->fp, " 50\n%f\n", dxf_mtext->rot_angle);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c MTEXT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_mtext_free
(
        DxfMtext *dxf_mtext
                /*!< DXF mtext entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_mtext->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfMtext was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_mtext->linetype);
        free (dxf_mtext->layer);
        free (dxf_mtext->text_value);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_mtext->text_additional_value[i]);
        }
        free (dxf_mtext->text_style);
        free (dxf_mtext->dictionary_owner_soft);
        free (dxf_mtext->dictionary_owner_hard);
        free (dxf_mtext->background_color_name);
        free (dxf_mtext);
        dxf_mtext = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
