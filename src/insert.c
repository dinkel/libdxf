/*!
 * \file insert.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF insert entity (\c INSERT).
 *
 * A DXF \c INSERT entity is an insertion for a (external) \c BLOCK entity.\n
 * Whilst a \c BLOCK only resides in the block table only once as a
 * definition, an \c INSERT entity can insert blocks as singlular entities
 * and also as [rectanglar, polar] arrays in the drawing.
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


#include "insert.h"


/*!
 * \brief Allocate memory for a \c DxfInsert.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfInsert *
dxf_insert_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfInsert *dxf_insert = NULL;
        size_t size;

        size = sizeof (DxfInsert);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_insert = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfInsert struct.\n")),
                  __FUNCTION__);
                dxf_insert = NULL;
        }
        else
        {
                memset (dxf_insert, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_insert);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c INSERT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfInsert *
dxf_insert_init
(
        DxfInsert *dxf_insert
                /*!< DXF insert entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_insert == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_insert = dxf_insert_new ();
        }
        if (dxf_insert == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfInsert struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_insert->block_name = strdup ("");
        dxf_insert->id_code = 0;
        dxf_insert->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_insert->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_insert->x0 = 0.0;
        dxf_insert->y0 = 0.0;
        dxf_insert->z0 = 0.0;
        dxf_insert->elevation = 0.0;
        dxf_insert->thickness = 0.0;
        dxf_insert->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_insert->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_insert->rel_x_scale = 1.0;
        dxf_insert->rel_y_scale = 1.0;
        dxf_insert->rel_z_scale = 1.0;
        dxf_insert->column_spacing = 0.0;
        dxf_insert->row_spacing = 0.0;
        dxf_insert->rot_angle = 0.0;
        dxf_insert->color = DXF_COLOR_BYLAYER;
        dxf_insert->paperspace = DXF_MODELSPACE;
        dxf_insert->attributes_follow = 0;
        dxf_insert->columns = 0;
        dxf_insert->rows = 0;
        dxf_insert->extr_x0 = 0.0;
        dxf_insert->extr_y0 = 0.0;
        dxf_insert->extr_z0 = 0.0;
        dxf_insert->dictionary_owner_soft = strdup ("");
        dxf_insert->dictionary_owner_hard = strdup ("");
        dxf_insert->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_insert);
}


/*!
 * \brief Read data from a DXF file into an \c INSERT entity.
 *
 * The last line read from file contained the string "INSERT". \n
 * Now follows some data for the \c INSERT, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_insert. \n
 *
 * \return a pointer to \c dxf_insert.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfInsert *
dxf_insert_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfInsert *dxf_insert
                /*!< DXF insert entity. */
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
        if (dxf_insert == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_insert = dxf_insert_new ();
                dxf_insert = dxf_insert_init (dxf_insert);
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
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a block name
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_insert->block_name);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_insert->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_insert->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_insert->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_insert->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->thickness);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->rel_x_scale);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * relative Y-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->rel_y_scale);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * relative Z-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->rel_z_scale);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the
                         * column spacing. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->column_spacing);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing the
                         * row spacing. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->row_spacing);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->rot_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_insert->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_insert->color);
                }
                else if (strcmp (temp_string, "66") == 0)
                {
                        /* Now follows a string containing the
                         * attributes follow flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_insert->attributes_follow);
                        /*!
                         * \todo After a set attributes_follow flag is
                         * detected, parsing of following entities should
                         * be implemented until the end of sequence
                         * marker (\c SEQEND) is encountered. */
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_insert->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * number of columns. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_insert->columns);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * number of rows. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_insert->rows);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbBlockReference") != 0))
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
                        fscanf (fp->fp, "%lf\n", &dxf_insert->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_insert->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_insert->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_insert->dictionary_owner_hard);
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
        if (strcmp (dxf_insert->linetype, "") == 0)
        {
                dxf_insert->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_insert->layer, "") == 0)
        {
                dxf_insert->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_insert);
}


/*!
 * \brief Write DXF output for a DXF \c INSERT entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_insert_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfInsert *dxf_insert
                /*!< DXF insert entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("INSERT");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_insert->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_insert->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_insert->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_insert->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_insert->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0.\n")),
                  dxf_entity_name);
                dxf_insert->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_insert->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_insert->id_code);
                fprintf (stderr,
                  (_("\tdefault relative X-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_insert->rel_x_scale = 1.0;
        }
        if (dxf_insert->rel_y_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative Y-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_insert->id_code);
                fprintf (stderr,
                  (_("\tdefault relative Y-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_insert->rel_y_scale = 1.0;
        }
        if (dxf_insert->rel_z_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative Z-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_insert->id_code);
                fprintf (stderr,
                  (_("\tdefault relative Z-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_insert->rel_z_scale = 1.0;
        }
        if ((dxf_insert->columns > 1) && (dxf_insert->column_spacing == 0.0))
        {
                fprintf (stderr,
                  (_("Warning in %s () number of columns is greater than 1 and the column spacing has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_insert->id_code);
                fprintf (stderr,
                  (_("\tdefault number of columns value of 1 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_insert->columns = 1;
        }
        if ((dxf_insert->rows > 1) && (dxf_insert->row_spacing == 0.0))
        {
                fprintf (stderr,
                  (_("Warning in %s () number of rows is greater than 1 and the row spacing has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_insert->id_code);
                fprintf (stderr,
                  (_("\tdefault number of rows value of 1 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_insert->rows = 1;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_insert->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_insert->id_code);
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
        if ((strcmp (dxf_insert->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_insert->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_insert->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_insert->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_insert->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_insert->layer);
        if (strcmp (dxf_insert->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_insert->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_insert->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_insert->elevation);
        }
        if (dxf_insert->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_insert->thickness);
        }
        if (dxf_insert->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_insert->color);
        }
        if (dxf_insert->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_insert->linetype_scale);
        }
        if (dxf_insert->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_insert->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbBlockReference\n");
        }
        if (dxf_insert->attributes_follow != 0)
        {
                fprintf (fp->fp, " 66\n%d\n", dxf_insert->attributes_follow);
                /*!
                 * \todo After a set attributes_follow flag is
                 * detected, the writing of following entities should
                 * be implemented and an end of sequence
                 * marker (\c SEQEND) written. */
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_insert->block_name);
        fprintf (fp->fp, " 10\n%f\n", dxf_insert->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_insert->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_insert->z0);
        if (dxf_insert->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", dxf_insert->rel_x_scale);
        }
        if (dxf_insert->rel_y_scale != 1.0)
        {
                fprintf (fp->fp, " 42\n%f\n", dxf_insert->rel_y_scale);
        }
        if (dxf_insert->rel_z_scale != 1.0)
        {
                fprintf (fp->fp, " 43\n%f\n", dxf_insert->rel_z_scale);
        }
        if (dxf_insert->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", dxf_insert->rot_angle);
        }
        if (dxf_insert->columns > 1)
        {
                fprintf (fp->fp, " 70\n%d\n", dxf_insert->columns);
        }
        if (dxf_insert->rows > 1)
        {
                fprintf (fp->fp, " 71\n%d\n", dxf_insert->rows);
        }
        if ((dxf_insert->columns > 1) && (dxf_insert->column_spacing > 0.0))
        {
                fprintf (fp->fp, " 44\n%f\n", dxf_insert->column_spacing);
        }
        if ((dxf_insert->rows > 1) && (dxf_insert->row_spacing > 0.0))
        {
                fprintf (fp->fp, " 45\n%f\n", dxf_insert->row_spacing);
        }
        if (fp->acad_version_number >= AutoCAD_12)
        {
                fprintf (fp->fp, "210\n%f\n", dxf_insert->extr_x0);
                fprintf (fp->fp, "220\n%f\n", dxf_insert->extr_y0);
                fprintf (fp->fp, "230\n%f\n", dxf_insert->extr_z0);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c INSERT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_insert_free
(
        DxfInsert *dxf_insert
                /*!< Pointer to the memory occupied by the DXF \c INSERT
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_insert->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfInsert was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_insert->linetype);
        free (dxf_insert->layer);
        free (dxf_insert->block_name);
        free (dxf_insert->dictionary_owner_soft);
        free (dxf_insert->dictionary_owner_hard);
        free (dxf_insert);
        dxf_insert = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
