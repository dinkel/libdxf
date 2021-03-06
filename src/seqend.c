/*!
 * \file seqend.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF end of sequence marker (\c SEQEND).
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


#include "seqend.h"


/*!
 * \brief Allocate memory for a DXF \c SEQEND.
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
DxfSeqend *
dxf_seqend_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSeqend *dxf_seqend = NULL;
        size_t size;

        size = sizeof (DxfSeqend);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_seqend = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSeqend struct.\n")),
                  __FUNCTION__);
                dxf_seqend = NULL;
        }
        else
        {
                memset (dxf_seqend, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_seqend);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SEQEND
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
DxfSeqend *
dxf_seqend_init
(
        DxfSeqend *dxf_seqend
                /*!< DXF seqend entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_seqend == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_seqend = dxf_seqend_new ();
        }
        if (dxf_seqend == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfSeqend struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_seqend->app_name = strdup ("");
        dxf_seqend->id_code = 0;
        dxf_seqend->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_seqend->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_seqend->elevation = 0.0;
        dxf_seqend->thickness = 0.0;
        dxf_seqend->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_seqend->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_seqend->color = DXF_COLOR_BYLAYER;
        dxf_seqend->paperspace = DXF_MODELSPACE;
        dxf_seqend->dictionary_owner_soft = strdup ("");
        dxf_seqend->dictionary_owner_hard = strdup ("");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_seqend);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SEQEND entity.
 *
 * The last line read from file contained the string "SEQEND". \n
 * Now follows some data for the \c SEQEND, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_seqend. \n
 *
 * \return a pointer to \c dxf_seqend.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfSeqend *
dxf_seqend_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSeqend *dxf_seqend
                /*!< DXF \c SEQEND entity. */
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
        if (dxf_seqend == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_seqend = dxf_seqend_new ();
                dxf_seqend = dxf_seqend_init (dxf_seqend);
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
                        fscanf (fp->fp, "%x\n", &dxf_seqend->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_seqend->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_seqend->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_seqend->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_seqend->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_seqend->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_seqend->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_seqend->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_seqend->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_seqend->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbEntity") != 0)
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
                        fscanf (fp->fp, "%s\n", dxf_seqend->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_seqend->dictionary_owner_hard);
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
        if (strcmp (dxf_seqend->linetype, "") == 0)
        {
                dxf_seqend->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_seqend->layer, "") == 0)
        {
                dxf_seqend->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_seqend);
}


/*!
 * \brief Write DXF output to a file for an end of sequence marker
 * (\c SEQEND).
 *
 * No fields.\n
 * This entity marks the end of vertices (Vertex type name) for a 
 * Polyline (\c POLYLINE), a Light Wight Polyline (\c LWPOLYLINE)
 * or the end of Attribute entities (Attrib type name) for an Insert
 * entity (\c INSERT) that has Attributes (indicated by 66 group present
 * and nonzero).
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
dxf_seqend_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSeqend *dxf_seqend
                /*!< DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SEQEND");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_seqend->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_seqend->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_seqend->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_seqend->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_seqend->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_seqend->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_seqend->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_seqend->id_code);
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
        if ((strcmp (dxf_seqend->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_seqend->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_seqend->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_seqend->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }

        if (dxf_seqend->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_seqend->layer);
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_seqend->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_seqend->elevation);
        }
        if (strcmp (dxf_seqend->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_seqend->linetype);
        }
        if (dxf_seqend->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_seqend->color);
        }
        if (dxf_seqend->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_seqend->linetype_scale);
        }
        if (dxf_seqend->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_seqend->visibility);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SEQEND and all it's
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
dxf_seqend_free
(
        DxfSeqend *dxf_seqend
                /*!< Pointer to the memory occupied by the DXF \c SEQEND
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        free (dxf_seqend->linetype);
        free (dxf_seqend->layer);
        free (dxf_seqend->dictionary_owner_soft);
        free (dxf_seqend->dictionary_owner_hard);
        free (dxf_seqend);
        dxf_seqend = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
