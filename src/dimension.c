/*!
 * \file dimension.c
 *
 * \author Copyright (C) 2012 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dimension entity (\c DIMENSION).
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


#include "dimension.h"


/*!
 * \brief Allocate memory for a DXF \c DIMENSION.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
DxfDimension *
dxf_dimension_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDimension *dxf_dimension = NULL;
        size_t size;

        size = sizeof (DxfDimension);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_dimension = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDimension struct.\n")),
                  __FUNCTION__);
                dxf_dimension = NULL;
        }
        else
        {
                memset (dxf_dimension, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_dimension);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c
 * DIMENSION entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
DxfDimension *
dxf_dimension_init
(
        DxfDimension *dxf_dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_dimension == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_dimension = dxf_dimension_new ();
        }
        if (dxf_dimension == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfDimension struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_dimension->id_code = 0;
        dxf_dimension->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_dimension->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_dimension->elevation = 0.0;
        dxf_dimension->thickness = 0.0;
        dxf_dimension->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_dimension->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_dimension->color = DXF_COLOR_BYLAYER;
        dxf_dimension->paperspace = DXF_PAPERSPACE;
        dxf_dimension->dim_text = strdup ("");
        dxf_dimension->dimblock_name = strdup ("");
        dxf_dimension->dimstyle_name = strdup ("");
        dxf_dimension->x0 = 0.0;
        dxf_dimension->y0 = 0.0;
        dxf_dimension->z0 = 0.0;
        dxf_dimension->x1 = 0.0;
        dxf_dimension->y1 = 0.0;
        dxf_dimension->z1 = 0.0;
        dxf_dimension->x2 = 0.0;
        dxf_dimension->y2 = 0.0;
        dxf_dimension->z2 = 0.0;
        dxf_dimension->x3 = 0.0;
        dxf_dimension->y3 = 0.0;
        dxf_dimension->z3 = 0.0;
        dxf_dimension->x4 = 0.0;
        dxf_dimension->y4 = 0.0;
        dxf_dimension->z4 = 0.0;
        dxf_dimension->x5 = 0.0;
        dxf_dimension->y5 = 0.0;
        dxf_dimension->z5 = 0.0;
        dxf_dimension->x6 = 0.0;
        dxf_dimension->y6 = 0.0;
        dxf_dimension->z6 = 0.0;
        dxf_dimension->leader_length = 0.0;
        dxf_dimension->text_line_spacing_factor = 0.0;
        dxf_dimension->actual_measurement = 0.0;
        dxf_dimension->angle = 0.0;
        dxf_dimension->hor_dir = 0.0;
        dxf_dimension->obl_angle = 0.0;
        dxf_dimension->text_angle = 0.0;
        dxf_dimension->flag = 0;
        dxf_dimension->attachment_point = 0;
        dxf_dimension->text_line_spacing = 0;
        dxf_dimension->extr_x0 = 0.0;
        dxf_dimension->extr_y0 = 0.0;
        dxf_dimension->extr_z0 = 0.0;
        dxf_dimension->dictionary_owner_soft = strdup ("");
        dxf_dimension->dictionary_owner_hard = strdup ("");
        dxf_dimension->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_dimension);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DIMENSION entity.
 *
 * The last line read from file contained the string "DIMENSION". \n
 * Now follows some data for the \c DIMENSION, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 *
 * \return a pointer to \c dxf_dimension.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
DxfDimension *
dxf_dimension_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDimension *dxf_dimension
                /*!< DXF \c DIMENSION entity. */
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
        if (dxf_dimension == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_dimension = dxf_dimension_new ();
                dxf_dimension = dxf_dimension_init (dxf_dimension);
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
                        /* Now follows a string containing a dimension
                         * text string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimension->dim_text);
                }
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a dimension
                         * block name string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimension->dimblock_name);
                }
                if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a dimension
                         * style name string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimension->dimstyle_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_dimension->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimension->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimension->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->z3);
                }
                else if (strcmp (temp_string, "14") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->x4);
                }
                else if (strcmp (temp_string, "24") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->y4);
                }
                else if (strcmp (temp_string, "34") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->z4);
                }
                else if (strcmp (temp_string, "15") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->x5);
                }
                else if (strcmp (temp_string, "25") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->y5);
                }
                else if (strcmp (temp_string, "35") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->z5);
                }
                else if (strcmp (temp_string, "16") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->x6);
                }
                else if (strcmp (temp_string, "26") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->y6);
                }
                else if (strcmp (temp_string, "36") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->z5);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_dimension->elevation = 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the leader
                         * length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->leader_length);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the text line
                         * spacing factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->text_line_spacing_factor);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the actual
                         * measurement. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->actual_measurement);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the angle of
                         * rotated, horizontal, or vertical linear
                         * dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the horizontal
                         * direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->hor_dir);
                }
                else if (strcmp (temp_string, "52") == 0)
                {
                        /* Now follows a string containing the oblique
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->obl_angle);
                }
                else if (strcmp (temp_string, "53") == 0)
                {
                        /* Now follows a string containing the text
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->text_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_dimension->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimension->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimension->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing a flag
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimension->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the attachment
                         * point value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimension->attachment_point);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the text line
                         * spacing value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimension->text_line_spacing);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                          && (strcmp (temp_string, "AcDbDimension") != 0)
                          && (strcmp (temp_string, "AcDbAlignedDimension") != 0)
                          && (strcmp (temp_string, "AcDbRotatedDimension") != 0)
                          && (strcmp (temp_string, "AcDb3PointAngularDimension") != 0)
                          && (strcmp (temp_string, "AcDbDiametricDimension") != 0)
                          && (strcmp (temp_string, "AcDbRadialDimension") != 0)
                          && (strcmp (temp_string, "AcDbOrdinateDimension") != 0))
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
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimension->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimension->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimension->dictionary_owner_hard);
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
        if (strcmp (dxf_dimension->linetype, "") == 0)
        {
                dxf_dimension->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_dimension->layer, "") == 0)
        {
                dxf_dimension->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_dimension);
}


/*!
 * \brief Write DXF output for a DXF \c DIMENSION entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
int
dxf_dimension_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDimension *dxf_dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("DIMENSION");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_dimension == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_dimension->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_dimension->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_dimension->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_dimension->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_dimension->id_code);
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
        if ((strcmp (dxf_dimension->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_dimension->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_dimension->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_dimension->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_dimension->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_dimension->layer);
        if (strcmp (dxf_dimension->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_dimension->linetype);
        }
        if (dxf_dimension->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_dimension->color);
        }
        if (dxf_dimension->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_dimension->linetype_scale);
        }
        if (dxf_dimension->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_dimension->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbDimension\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_dimension->dimblock_name);
        fprintf (fp->fp, " 10\n%f\n", dxf_dimension->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_dimension->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_dimension->z0);
        fprintf (fp->fp, " 11\n%f\n", dxf_dimension->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_dimension->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_dimension->z1);
        fprintf (fp->fp, " 70\n%d\n", dxf_dimension->flag);
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 71\n%d\n", dxf_dimension->attachment_point);
                fprintf (fp->fp, " 72\n%d\n", dxf_dimension->text_line_spacing);
                fprintf (fp->fp, " 41\n%f\n", dxf_dimension->text_line_spacing_factor);
                fprintf (fp->fp, " 42\n%f\n", dxf_dimension->actual_measurement);
        }
        fprintf (fp->fp, "  1\n%s\n", dxf_dimension->dim_text);
        fprintf (fp->fp, " 53\n%f\n", dxf_dimension->text_angle);
        fprintf (fp->fp, " 51\n%f\n", dxf_dimension->hor_dir);
        fprintf (fp->fp, "210\n%fn", dxf_dimension->extr_x0);
        fprintf (fp->fp, "220\n%fn", dxf_dimension->extr_y0);
        fprintf (fp->fp, "230\n%fn", dxf_dimension->extr_z0);
        fprintf (fp->fp, "  3\n%s\n", dxf_dimension->dimstyle_name);
        /* Rotated, horizontal, or vertical dimension. */
        if (dxf_dimension->flag == 0)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbAlignedDimension\n");
                }
                fprintf (fp->fp, " 12\n%f\n", dxf_dimension->x2);
                fprintf (fp->fp, " 22\n%f\n", dxf_dimension->y2);
                fprintf (fp->fp, " 32\n%f\n", dxf_dimension->z2);
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
                fprintf (fp->fp, " 50\n%f\n", dxf_dimension->angle);
                fprintf (fp->fp, " 52\n%f\n", dxf_dimension->obl_angle);
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbRotatedDimension\n");
                }
        }
        /* Aligned dimension. */
        if (dxf_dimension->flag == 1)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbAlignedDimension\n");
                }
                fprintf (fp->fp, " 12\n%f\n", dxf_dimension->x2);
                fprintf (fp->fp, " 22\n%f\n", dxf_dimension->y2);
                fprintf (fp->fp, " 32\n%f\n", dxf_dimension->z2);
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
                fprintf (fp->fp, " 50\n%f\n", dxf_dimension->angle);
        }
        /* Angular dimension. */
        if (dxf_dimension->flag == 2)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDb3PointAngularDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
                fprintf (fp->fp, " 15\n%f\n", dxf_dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dxf_dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dxf_dimension->z5);
                fprintf (fp->fp, " 16\n%f\n", dxf_dimension->x6);
                fprintf (fp->fp, " 26\n%f\n", dxf_dimension->y6);
                fprintf (fp->fp, " 36\n%f\n", dxf_dimension->z6);
        }
        /* Diameter dimension. */
        if (dxf_dimension->flag == 3)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbDiametricDimension\n");
                }
                fprintf (fp->fp, " 15\n%f\n", dxf_dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dxf_dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dxf_dimension->z5);
                fprintf (fp->fp, " 40\n%f\n", dxf_dimension->leader_length);
        }
        /* Radius dimension. */
        if (dxf_dimension->flag == 4)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbRadialDimension\n");
                }
                fprintf (fp->fp, " 15\n%f\n", dxf_dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dxf_dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dxf_dimension->z5);
                fprintf (fp->fp, " 40\n%f\n", dxf_dimension->leader_length);
        }
        /* Angular 3-point dimension. */
        if (dxf_dimension->flag == 5)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDb3PointAngularDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
                fprintf (fp->fp, " 15\n%f\n", dxf_dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dxf_dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dxf_dimension->z5);
                fprintf (fp->fp, " 16\n%f\n", dxf_dimension->x6);
                fprintf (fp->fp, " 26\n%f\n", dxf_dimension->y6);
                fprintf (fp->fp, " 36\n%f\n", dxf_dimension->z6);
        }
        /* Ordinate dimension. */
        if (dxf_dimension->flag == 6)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbOrdinateDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
        }
        if (dxf_dimension->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_dimension->thickness);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c DIMENSION and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
int
dxf_dimension_free
(
        DxfDimension *dxf_dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_dimension->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfDimension was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_dimension->linetype);
        free (dxf_dimension->layer);
        free (dxf_dimension->dim_text);
        free (dxf_dimension->dimblock_name);
        free (dxf_dimension->dimstyle_name);
        free (dxf_dimension->dictionary_owner_soft);
        free (dxf_dimension->dictionary_owner_hard);
        free (dxf_dimension);
        dxf_dimension = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
