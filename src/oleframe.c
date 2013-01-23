/*!
 * \file oleframe.c
 *
 * \author Copyright (C) 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF oleframe entity (\c OLEFRAME).
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


#include "oleframe.h"


/*!
 * \brief Allocate memory for a \c DxfOleFrame.
 *
 * Fill the memory contents with zeros.
 */
DxfOleFrame *
dxf_oleframe_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_oleframe_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfOleFrame *dxf_oleframe = NULL;
        size_t size;

        size = sizeof (DxfOleFrame);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_oleframe = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_oleframe_new () could not allocate memory for a DxfOleFrame struct.\n");
                dxf_oleframe = NULL;
        }
        else
        {
                memset (dxf_oleframe, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_oleframe_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_oleframe);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c OLEFRAME
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfOleFrame *
dxf_oleframe_init
(
        DxfOleFrame *dxf_oleframe
                /*!< DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_oleframe_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        dxf_oleframe = dxf_oleframe_new ();
        if (dxf_oleframe == NULL)
        {
              fprintf (stderr, "ERROR in dxf_oleframe_init () could not allocate memory for a DxfOleFrame struct.\n");
              return (NULL);
        }
        dxf_oleframe->id_code = 0;
        dxf_oleframe->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_oleframe->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_oleframe->thickness = 0.0;
        dxf_oleframe->color = DXF_COLOR_BYLAYER;
        dxf_oleframe->paperspace = DXF_MODELSPACE;
        dxf_oleframe->ole_version_number = 1;
        dxf_oleframe->length = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_oleframe->binary_data[i] = strdup ("");
        }
        dxf_oleframe->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_oleframe_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_oleframe);
}


/*!
 * \brief Read data from a DXF file into a DXF \c OLEFRAME entity.
 *
 * The last line read from file contained the string "OLEFRAME". \n
 * Now follows some data for the \c OLEFRAME, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_oleframe. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_oleframe_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfOleFrame *dxf_oleframe
                /*!< DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_oleframe_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;
        int i;

        if (!dxf_oleframe)
        {
                dxf_oleframe = dxf_oleframe_new ();
        }
        i = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr, "Error in dxf_oleframe_read () while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a End of Ole
                         * data marker. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "OLE") != 0)
                        {
                                fprintf (stderr, "Error in dxf_oleframe_read () found a bad End of Ole data marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_oleframe->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_oleframe->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_oleframe->layer);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_oleframe->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_oleframe->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_oleframe->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the ole
                         * version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_oleframe->ole_version_number);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the length of
                         * binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &dxf_oleframe->length);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbOleFrame") != 0)))
                        {
                                fprintf (stderr, "Error in dxf_oleframe_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_oleframe->binary_data[i]);
                        i++;
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
                        fprintf (stderr, "Warning: in dxf_oleframe_read () unknown string tag found while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_oleframe_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c OLEFRAME entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_oleframe_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfOleFrame *dxf_oleframe
                /*!< DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_oleframe_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("OLEFRAME");
        int i;

        if (strcmp (dxf_oleframe->layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_oleframe_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_oleframe->id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_oleframe->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_oleframe->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_oleframe->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
                fprintf (fp->fp, "100\nAcDbOleFrame\n");
        }
        if (strcmp (dxf_oleframe->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_oleframe->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_oleframe->layer);
        if (dxf_oleframe->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_oleframe->thickness);
        }
        if (dxf_oleframe->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_oleframe->color);
        }
        if (dxf_oleframe->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, " 70\n%d\n", dxf_oleframe->ole_version_number);
        fprintf (fp->fp, " 90\n%ld\n", dxf_oleframe->length);
        i = 0;
        while (strlen (dxf_oleframe->binary_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", dxf_oleframe->binary_data[i]);
                i++;
        }
        fprintf (fp->fp, "  1\nOLE\n");
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_oleframe_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c OLEFRAME and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_oleframe_free
(
        DxfOleFrame *dxf_oleframe
                /*!< Pointer to the memory occupied by the DXF
                 * \c OLEFRAME entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_oleframe_free () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        if (dxf_oleframe->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_oleframe_free () pointer to next DxfOleFrame was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_oleframe->linetype);
        free (dxf_oleframe->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_oleframe->binary_data[i]);
        }
        free (dxf_oleframe);
        dxf_oleframe = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_oleframe_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */