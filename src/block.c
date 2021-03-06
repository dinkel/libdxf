/*!
 * \file block.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF block entity (\c BLOCK).
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


#include "block.h"


/*!
 * \brief Allocate memory for a \c DxfBlock
 * (a DXF \c BLOCK entity).
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfBlock *
dxf_block_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfBlock *block = NULL;
        size_t size;

        size = sizeof (DxfBlock);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((block = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfBlock struct.\n")),
                  __FUNCTION__);
                block = NULL;
        }
        else
        {
                memset (block, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfBlock
 * (a DXF \c BLOCK entity).
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
DxfBlock *
dxf_block_init
(
        DxfBlock *block
                /*!< DXF block entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                block = dxf_block_new ();
        }
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfBlock struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->xref_name = strdup ("");
        block->block_name = strdup ("");
        block->block_name_additional = strdup ("");
        block->id_code = 0;
        block->description = strdup ("");
        block->layer = strdup (DXF_DEFAULT_LAYER);
        block->x0 = 0.0;
        block->y0 = 0.0;
        block->z0 = 0.0;
        block->block_type = 0; /* 0 = invalid type */
        block->dictionary_owner_soft = strdup ("");
        block->endblk = (struct DxfEndblk *) dxf_endblk_new ();
        block->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Read data from a DXF file into a \c DxfBlock
 * (a DXF \c BLOCK entity).
 *
 * The last line read from file contained the string "BLOCK". \n
 * Now follows some data for the \c BLOCK, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_block. \n
 *
 * \return a pointer to \c block.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * \todo After reading information from the \c BLOCK entity up until the
 * closing Group code 0, the pointer to the following \c ENDBLK entity
 * needs to be stored in the current (last) \c DxfBlock struct member
 * \c endblk.
 */
DxfBlock *
dxf_block_read
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        DxfBlock *block
                /*!< DXF block entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char temp_string[DXF_MAX_STRING_LENGTH];

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                block = dxf_block_new ();
                block = dxf_block_init (block);
        }
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
                        /* Now follows a string containing a external
                         * reference name. */
                        fscanf (fp->fp, "%s\n", block->xref_name);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a block name. */
                        fscanf (fp->fp, "%s\n", block->block_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a block name. */
                        fscanf (fp->fp, "%s\n", block->block_name_additional);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing a description. */
                        fscanf (fp->fp, "%s\n", block->description);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        fscanf (fp->fp, "%x\n", &block->id_code);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        fscanf (fp->fp, "%s\n", block->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (block->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        fscanf (fp->fp, "%lf\n", &block->z0);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the block
                         * type value. */
                        fscanf (fp->fp, "%d\n", &block->block_type);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbBlockBegin") != 0)))
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
                        fscanf (fp->fp, "%lf\n", &block->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        fscanf (fp->fp, "%lf\n", &block->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        fscanf (fp->fp, "%lf\n", &block->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner object. */
                        fscanf (fp->fp, "%s\n", block->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
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
        /*!
         * \todo Resolve this quick hack for preventing an empty block
         * name string in a more elegant manner.
         */
        if (strcmp (block->block_name, "") == 0)
        {
                sprintf (block->block_name, "%i", block->id_code);
        }
        if (strcmp (block->layer, "") == 0)
        {
                block->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (block->block_type == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal block type value found while reading from: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                fprintf (stderr,
                  (_("\tblock type value is reset to 1.\n")));
                block->block_type = 1;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Write DXF output for a DXF \c BLOCK entity.
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
dxf_block_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfBlock *block
                /*!< DXF block entity */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("BLOCK");
        DxfEndblk *endblk = NULL;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block->block_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () empty block name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (block->endblk == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () NULL pointer to endblk was passed or the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (((block->xref_name == NULL)
          || (strcmp (block->xref_name, "") == 0))
          && ((block->block_type != 4)
          || (block->block_type != 32)))
        {
                fprintf (stderr,
                  (_("Error in %s () empty xref path name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (block->description == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () NULL pointer to description string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                block->description = strdup ("");
        }
        if (strcmp (block->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0.\n")),
                  dxf_entity_name);
                block->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (block->dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () NULL pointer to soft owner object string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                block->dictionary_owner_soft = strdup ("");
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if ((fp->acad_version_number >= AutoCAD_13)
          && (block->id_code != -1))
        {
                fprintf (fp->fp, "  5\n%x\n", block->id_code);
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
        if ((strcmp (block->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "330\n%s\n", block->dictionary_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        fprintf (fp->fp, "  8\n%s\n", block->layer);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbBlockBegin\n");
        }
        fprintf (fp->fp, "  2\n%s\n", block->block_name);
        fprintf (fp->fp, " 70\n%d\n", block->block_type);
        fprintf (fp->fp, " 10\n%f\n", block->x0);
        fprintf (fp->fp, " 20\n%f\n", block->y0);
        fprintf (fp->fp, " 30\n%f\n", block->z0);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "  3\n%s\n", block->block_name);
        }
        if ((fp->acad_version_number >= AutoCAD_13)
        && ((block->block_type && 4)
        || (block->block_type && 32)))
        {
                fprintf (fp->fp, "  1\n%s\n", block->xref_name);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
        && (strcmp (block->description, "") != 0))
        {
                fprintf (fp->fp, "  4\n%s\n", block->description);
        }
        endblk = (DxfEndblk *) block->endblk;
        dxf_endblk_write (fp, endblk);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a list of block definitions.
 *
 * Appears only in the \c BLOCKS section.\n
 */
int
dxf_block_write_table
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfBlock *blocks_list
                /*!< Pointer to a list of block definitions. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }

        /*! \todo Add code here. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DxfBlock (a \c BLOCK entity)
 * and all it's data fields.
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
dxf_block_free
(
        DxfBlock *block
                /*!< Pointer to the memory occupied by the DXF \c BLOCK
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (block->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfBlock was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (block->xref_name);
        free (block->block_name);
        free (block->block_name_additional);
        free (block->description);
        free (block->layer);
        free (block->dictionary_owner_soft);
        free (block);
        block = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
