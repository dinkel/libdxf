/*!
 * \file view.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF View symbol table entry (\c VIEW).
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


#include "view.h"


/*!
 * \brief Allocate memory for a DXF \c VIEW.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfView *
dxf_view_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfView *dxf_view = NULL;
        size_t size;

        size = sizeof (DxfView);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_view = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfView struct.\n")),
                  __FUNCTION__);
                dxf_view = NULL;
        }
        else
        {
                memset (dxf_view, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_view);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c VIEW
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfView *
dxf_view_init
(
        DxfView *dxf_view
                /*!< DXF View entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_view == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_view = dxf_view_new ();
        }
        if (dxf_view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfView struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_view->id_code = 0;
        dxf_view->view_name = strdup ("");
        dxf_view->x_view = 0.0;
        dxf_view->y_view = 0.0;
        dxf_view->x_direction = 0.0;
        dxf_view->y_direction = 0.0;
        dxf_view->z_direction = 0.0;
        dxf_view->x_target = 0.0;
        dxf_view->y_target = 0.0;
        dxf_view->z_target = 0.0;
        dxf_view->view_height = 0.0;
        dxf_view->view_width = 0.0;
        dxf_view->lens_length = 0.0;
        dxf_view->front_plane_offset = 0.0;
        dxf_view->back_plane_offset = 0.0;
        dxf_view->view_twist_angle = 0.0;
        dxf_view->flag = 0;
        dxf_view->view_mode = 0;
        dxf_view->dictionary_owner_soft = strdup ("");
        dxf_view->dictionary_owner_hard = strdup ("");
        dxf_view->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_view);
}


/*!
 * \brief Read data from a DXF file into a DXF \c VIEW entity.
 *
 * The last line read from file contained the string "VIEW". \n
 * Now follows some data for the \c VIEW, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c dxf_view. \n
 *
 * \return a pointer to \c dxf_view.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfView *
dxf_view_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfView *dxf_view
                /*!< DXF VIEW entity. */
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
        if (dxf_view == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_view = dxf_view_new ();
                dxf_view = dxf_view_init (dxf_view);
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
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_view->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a view
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_view->view_name);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the View center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->x_view);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the View center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->y_view);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the View direction from
                         * target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->x_direction);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the View direction from
                         * target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->y_direction);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the View direction from
                         * target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->z_direction);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the Target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->x_target);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the Target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->y_target);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the Target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->z_target);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the view
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->view_height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the view
                         * width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->view_width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the lens
                         * length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->lens_length);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the Front
                         * clipping plane - offset from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->front_plane_offset);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the Back
                         * clipping plane - offset from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->back_plane_offset);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the view
                         * twist angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_view->view_twist_angle);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_view->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the view mode
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_view->view_mode);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTableRecord") != 0)
                        && ((strcmp (temp_string, "AcDbViewTableRecord") != 0)))
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
                        fscanf (fp->fp, "%s\n", dxf_view->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_view->dictionary_owner_hard);
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_view);
}


/*!
 * \brief Write DXF output to a file for a DXF \c VIEW entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_view_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfView *dxf_view
                /*!< DXF VIEW entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("VIEW");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((dxf_view->view_name == NULL)
          || (strcmp (dxf_view->view_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty UCS name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_view->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_view->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_view->id_code);
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
        if ((strcmp (dxf_view->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_view->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_view->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_view->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbViewTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_view->view_name);
        fprintf (fp->fp, " 40\n%f\n", dxf_view->view_height);
        fprintf (fp->fp, " 70\n%d\n", dxf_view->flag);
        fprintf (fp->fp, " 10\n%f\n", dxf_view->x_view);
        fprintf (fp->fp, " 20\n%f\n", dxf_view->y_view);
        fprintf (fp->fp, " 41\n%f\n", dxf_view->view_width);
        fprintf (fp->fp, " 11\n%f\n", dxf_view->x_direction);
        fprintf (fp->fp, " 21\n%f\n", dxf_view->y_direction);
        fprintf (fp->fp, " 31\n%f\n", dxf_view->z_direction);
        fprintf (fp->fp, " 12\n%f\n", dxf_view->x_target);
        fprintf (fp->fp, " 22\n%f\n", dxf_view->y_target);
        fprintf (fp->fp, " 32\n%f\n", dxf_view->z_target);
        fprintf (fp->fp, " 42\n%f\n", dxf_view->lens_length);
        fprintf (fp->fp, " 43\n%f\n", dxf_view->front_plane_offset);
        fprintf (fp->fp, " 44\n%f\n", dxf_view->back_plane_offset);
        fprintf (fp->fp, " 50\n%f\n", dxf_view->view_twist_angle);
        fprintf (fp->fp, " 71\n%d\n", dxf_view->view_mode);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c VIEW and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_view_free
(
        DxfView *dxf_view
                /*!< Pointer to the memory occupied by the DXF \c VIEW
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_view->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfView was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_view->view_name);
        free (dxf_view->dictionary_owner_soft);
        free (dxf_view->dictionary_owner_hard);
        free (dxf_view);
        dxf_view = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
