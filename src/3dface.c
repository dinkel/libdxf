/*!
 * \file 3dface.c
 *
 * \author Copyright (C) 2010 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF 3D face entity (\c 3DFACE).
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


#include "3dface.h"


/*!
 * \brief Allocate memory for a DXF \c 3DFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dface *
dxf_3dface_new ()
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        Dxf3dface *face = NULL;
        size_t size;

        size = sizeof (Dxf3dface);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((face = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a Dxf3dface struct.\n")),
                  __FUNCTION__);
                face = NULL;
        }
        else
        {
                memset (face, 0, size);
        }
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c 3DFACE
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
Dxf3dface *
dxf_3dface_init
(
        Dxf3dface *face
                /*!< DXF 3dface entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                face = dxf_3dface_new ();
        }
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a Dxf3dface struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->id_code = 0;
        face->linetype = strdup (DXF_DEFAULT_LINETYPE);
        face->layer = strdup (DXF_DEFAULT_LAYER);
        face->x0 = 0.0;
        face->y0 = 0.0;
        face->z0 = 0.0;
        face->x1 = 0.0;
        face->y1 = 0.0;
        face->z1 = 0.0;
        face->x2 = 0.0;
        face->y2 = 0.0;
        face->z2 = 0.0;
        face->x3 = 0.0;
        face->y3 = 0.0;
        face->z3 = 0.0;
        face->elevation = 0.0;
        face->thickness = 0.0;
        face->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        face->visibility = DXF_DEFAULT_VISIBILITY;
        face->color = DXF_COLOR_BYLAYER;
        face->paperspace = DXF_MODELSPACE;
        face->flag = 0;
        face->dictionary_owner_soft = strdup ("");
        face->dictionary_owner_hard = strdup ("");
        face->next = NULL;
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Read data from a DXF file into a DXF \c 3DFACE entity.
 *
 * The last line read from file contained the string "3DFACE". \n
 * Now follows some data for the \c 3DFACE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 *
 * \return a pointer to \c face.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dface *
dxf_3dface_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        Dxf3dface *face
                /*!< DXF 3dface entity. */
)
{
#ifdef DEBUG
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
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                face = dxf_3dface_new ();
                face = dxf_3dface_init (face);
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
                        fscanf (fp->fp, "%x\n", &face->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the first point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the first point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of first the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->z3);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                  && DXF_FLATLAND
                  && (strcmp (temp_string, "38") == 0)
                  && (face->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &face->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &face->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &face->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbFace") != 0))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * value of edge visibility flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &face->flag);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->dictionary_owner_hard);
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
        if (strcmp (face->linetype, "") == 0)
        {
                face->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (face->layer, "") == 0)
        {
                face->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Write DXF output to a file for a DXF \c 3DFACE entity.
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
dxf_3dface_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        Dxf3dface *face
                /*!< DXF 3D face entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("3DFACE");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (face->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, face->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                face->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (face->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, face->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                face->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (face->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", face->id_code);
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
        if ((strcmp (face->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", face->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (face->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", face->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (face->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", face->layer);
        if (strcmp (face->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", face->linetype);
        }
        if (face->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", face->color);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (face->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", face->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (face->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", face->thickness);
        }
        if (face->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", face->linetype_scale);
        }
        if (face->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", face->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbFace\n");
        }
        fprintf (fp->fp, " 10\n%f\n", face->x0);
        fprintf (fp->fp, " 20\n%f\n", face->y0);
        fprintf (fp->fp, " 30\n%f\n", face->z0);
        fprintf (fp->fp, " 11\n%f\n", face->x1);
        fprintf (fp->fp, " 21\n%f\n", face->y1);
        fprintf (fp->fp, " 31\n%f\n", face->z1);
        fprintf (fp->fp, " 12\n%f\n", face->x2);
        fprintf (fp->fp, " 22\n%f\n", face->y2);
        fprintf (fp->fp, " 32\n%f\n", face->z2);
        fprintf (fp->fp, " 13\n%f\n", face->x3);
        fprintf (fp->fp, " 23\n%f\n", face->y3);
        fprintf (fp->fp, " 33\n%f\n", face->z3);
        fprintf (fp->fp, " 70\n%d\n", face->flag);
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c 3DFACE and all it's
 * data fields.
 *
 * \return \c NULL when successful, or pointer to \c face when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
Dxf3dface *
dxf_3dface_free
(
        Dxf3dface *face
                /*!< Pointer to the memory occupied by the DXF \c 3DFACE
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (face->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next Dxf3dface was not NULL.\n")),
                __FUNCTION__);
              return (face);
        }
        free (face->linetype);
        free (face->layer);
        free (face->dictionary_owner_soft);
        free (face->dictionary_owner_hard);
        free (face);
        face = NULL;
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Test if the first edge of the DXF \c 3DFACE is invisible.
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge is
 * visible.
 */
int
dxf_3dface_is_first_edge_invisible
(
        Dxf3dface *face
                /*!< DXF 3dface entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = (DXF_CHECK_BIT (face->flag, 0));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the second edge of the DXF \c 3DFACE is invisible.
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge is
 * visible.
 */
int
dxf_3dface_is_second_edge_invisible
(
        Dxf3dface *face
                /*!< DXF 3dface entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = (DXF_CHECK_BIT (face->flag, 1));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the third edge of the DXF \c 3DFACE is invisible.
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge is
 * visible.
 */
int
dxf_3dface_is_third_edge_invisible
(
        Dxf3dface *face
                /*!< DXF 3dface entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = (DXF_CHECK_BIT (face->flag, 2));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the fourth edge of the DXF \c 3DFACE is invisible.
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge is
 * visible.
 */
int
dxf_3dface_is_fourth_edge_invisible
(
        Dxf3dface *face
                /*!< DXF 3dface entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = (DXF_CHECK_BIT (face->flag, 3));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
