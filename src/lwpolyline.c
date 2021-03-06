/*!
 * \file lwpolyline.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF light weight polyline entity (\c LWPOLYLINE).
 *
 * \warning This entity requires AutoCAD version R14 or higher.
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


#include "lwpolyline.h"


/*!
 * \brief Allocate memory for a \c DxfLWPolyline.
 *
 * Fill the memory contents with zeros.
 */
DxfLWPolyline *
dxf_lwpolyline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLWPolyline *dxf_lwpolyline = NULL;
        size_t size;

        size = sizeof (DxfLWPolyline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_lwpolyline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLWPolyline struct.\n")),
                  __FUNCTION__);
                dxf_lwpolyline = NULL;
        }
        else
        {
                memset (dxf_lwpolyline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_lwpolyline);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c LWPOLYLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLWPolyline *
dxf_lwpolyline_init
(
        DxfLWPolyline *dxf_lwpolyline
                /*!< DXF light weight polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_lwpolyline = dxf_lwpolyline_new ();
        }
        if (dxf_lwpolyline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfLWPolyline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_lwpolyline->id_code = 0;
        dxf_lwpolyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_lwpolyline->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_lwpolyline->elevation = 0.0;
        dxf_lwpolyline->thickness = 0.0;
        dxf_lwpolyline->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_lwpolyline->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_lwpolyline->constant_width = 0.0;
        dxf_lwpolyline->color = DXF_COLOR_BYLAYER;
        dxf_lwpolyline->paperspace = DXF_MODELSPACE;
        dxf_lwpolyline->flag = 0;
        dxf_lwpolyline->number_vertices = 0;
        dxf_lwpolyline->extr_x0 = 0.0;
        dxf_lwpolyline->extr_y0 = 0.0;
        dxf_lwpolyline->extr_z0 = 0.0;
        dxf_lwpolyline->dictionary_owner_soft = strdup ("");
        dxf_lwpolyline->dictionary_owner_hard = strdup ("");
        dxf_lwpolyline->vertices = (struct DxfVertex *) dxf_vertex_new ();
        dxf_lwpolyline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_lwpolyline);
}


/*!
 * \brief Read data from a DXF file into an \c LWPOLYLINE entity.
 *
 * The last line read from file contained the string "LWPOLYLINE". \n
 * Now follows some data for the \c LWPOLYLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_lwpolyline. \n
 *
 * \return a pointer to \c dxf_lwpolyline.
 */
DxfLWPolyline *
dxf_lwpolyline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLWPolyline *dxf_lwpolyline
                /*!< DXF light weight polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfVertex *iter = NULL;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dxf_lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_lwpolyline = dxf_lwpolyline_new ();
                dxf_lwpolyline = dxf_lwpolyline_init (dxf_lwpolyline);
        }
        iter = (DxfVertex *) dxf_lwpolyline->vertices;
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
                        fscanf (fp->fp, "%x\n", &dxf_lwpolyline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_lwpolyline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_lwpolyline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                        * X-coordinate of a vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                        * Y-coordinate of a vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->y0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_lwpolyline->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_lwpolyline->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_lwpolyline->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * start width of the vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->start_width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * start width of the vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->end_width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the bulge of
                         * the vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->bulge);
                        /* The last member of the vertex is read.\n */
                        /*! \todo The pointer administration needs to be checked for functionality. */
                         /* Increment iter to next DxfVertex. */
                        iter->next = (struct DxfVertex *) dxf_vertex_new ();
                        iter = (DxfVertex *) iter->next;
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * constant width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_lwpolyline->constant_width);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_lwpolyline->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_lwpolyline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_lwpolyline->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_lwpolyline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_lwpolyline->flag);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the number
                         * of following vertices. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_lwpolyline->number_vertices);
                }
                else if ((fp->acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_lwpolyline->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_lwpolyline->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_lwpolyline->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_lwpolyline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_lwpolyline->dictionary_owner_hard);
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
        /*! \todo Free memory to the last (unused) vertex in the linked list. */

        /* Set the pointer to the last (unused) vertex in the linked list to NULL. */
        iter->next = NULL;
        /* Handle omitted members and/or illegal values. */
        if (strcmp (dxf_lwpolyline->linetype, "") == 0)
        {
                dxf_lwpolyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_lwpolyline->layer, "") == 0)
        {
                dxf_lwpolyline->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_lwpolyline);
}


/*!
 * \brief Write DXF output to fp for a light weight polyline entity.
 *
 * \warning This entity requires AutoCAD version 2004 or higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLWPolyline *dxf_lwpolyline
                /*!< DXF polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LWPOLYLINE");
        DxfVertex *iter = NULL;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_lwpolyline->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_lwpolyline->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_lwpolyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_lwpolyline->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_lwpolyline->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                dxf_lwpolyline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_lwpolyline->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_lwpolyline->id_code);
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
        if ((strcmp (dxf_lwpolyline->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_lwpolyline->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_lwpolyline->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_lwpolyline->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_lwpolyline->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_lwpolyline->layer);
        if (strcmp (dxf_lwpolyline->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_lwpolyline->linetype);
        }
        if (dxf_lwpolyline->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_lwpolyline->color);
        }
        if (dxf_lwpolyline->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_lwpolyline->linetype_scale);
        }
        if (dxf_lwpolyline->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_lwpolyline->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbPolyline\n");
        }
        fprintf (fp->fp, " 90\n%d\n", dxf_lwpolyline->number_vertices);
        fprintf (fp->fp, " 70\n%d\n", dxf_lwpolyline->flag);
        fprintf (fp->fp, " 43\n%f\n", dxf_lwpolyline->constant_width);
        if (dxf_lwpolyline->elevation != 0.0)
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_lwpolyline->elevation);
        }
        if (dxf_lwpolyline->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_lwpolyline->thickness);
        }
        /* Start of writing (multiple) vertices. */
        iter = (DxfVertex *) dxf_lwpolyline->vertices;
        while (iter != NULL)
        {
                fprintf (fp->fp, " 10\n%f\n", iter->x0);
                fprintf (fp->fp, " 20\n%f\n", iter->y0);
                if ((iter->start_width != dxf_lwpolyline->constant_width)
                  || (iter->end_width != dxf_lwpolyline->constant_width))
                {
                        fprintf (fp->fp, " 40\n%f\n", iter->start_width);
                        fprintf (fp->fp, " 41\n%f\n", iter->end_width);
                }
                fprintf (fp->fp, " 42\n%f\n", iter->bulge);
                iter = (DxfVertex *) iter->next;
        }
        /* End of writing (multiple) vertices. */
        if (fp->acad_version_number >= AutoCAD_12)
        {
                fprintf (fp->fp, "210\n%f\n", dxf_lwpolyline->extr_x0);
                fprintf (fp->fp, "220\n%f\n", dxf_lwpolyline->extr_y0);
                fprintf (fp->fp, "230\n%f\n", dxf_lwpolyline->extr_z0);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LWPOLYLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_free
(
        DxfLWPolyline *dxf_lwpolyline
                /*!< Pointer to the memory occupied by the DXF \c LWPOLYLINE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_lwpolyline->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfLWPolyline was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_lwpolyline->linetype);
        free (dxf_lwpolyline->layer);
        free (dxf_lwpolyline);
        dxf_lwpolyline = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
