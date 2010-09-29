/*!
 * \file block.c
 * \author Copyright (C) 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF block entity (\c BLOCK).
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
 * \brief Allocate memory for a \c DxfBlock.
 *
 * Fill the memory contents with zeros.
 */
DxfBlock *
dxf_block_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfBlock *dxf_block = NULL;
        size_t size;

        size = sizeof (DxfBlock);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_block = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_block_new () could not allocate memory for a DxfBlock struct.\n");
                dxf_block = NULL;
        }
        else
        {
                memset (dxf_block, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_block);
}


/*!
 * \brief Write DXF output to a file for a block entity.
 */
int
dxf_block_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *xref_name,
                /*!< group code = 1. */
        char *block_name,
                /*!< group code = 2 and 3. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, if omitted defaults to BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * base point. */
        double y0,
                /*!< group code = 20\n
                 * base point. */
        double z0,
                /*!< group code = 30\n
                 * base point. */
        double thickness,
                /*!< group code = 39\n
                 * optional, if omitted defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, if omitted defaults to BYLAYER. */
        int paperspace,
                /*!< group code = 67\n
                 * optional, if omitted defaults to 0 (modelspace). */
        int block_type
                /*!< group code = 70\n
                 * bit codes:\n
                 * 1 = this is an anonymous Block generated by hatching,
                 *     associative dimensioning, other internal operations,
                 *     or an application\n
                 * 2 = this Block has Attributes\n
                 * 4 = this Block is an external reference (Xref)\n
                 * 8 = not used\n
                 * 16 = this Block is externally dependent\n
                 * 32 = this is a resolved external reference, or dependent
                 *      of an external reference\n
                 * 64 = this definition is referenced. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_block () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("BLOCK");
        if (block_name == NULL)
        {
                fprintf (stderr, "Warning: empty block name string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n", dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (xref_name == NULL)
        {
                fprintf (stderr, "Warning: empty xref name string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n", dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0.\n", dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if ((block_type && 4) || (block_type && 32))
        {
                fprintf (fp, "  1\n%s\n", xref_name);
        }
        fprintf (fp, "  2\n%s\n", block_name);
        fprintf (fp, "  3\n%s\n", block_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", block_type);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_block () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a block entity.
 */
int
dxf_block_write
(
        FILE *fp,
                /*!< file pointer to output device */
        DxfBlock dxf_block
                /*!< block entity */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_block2 () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("BLOCK");
        if (dxf_block.block_name == NULL)
        {
                fprintf (stderr, "Warning: empty block name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_block.common.id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_block.xref_name == NULL)
        {
                fprintf (stderr, "Warning: empty xref name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_block.common.id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_block.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_block.common.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0.\n",
                        dxf_entity_name);
                dxf_block.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if ((dxf_block.block_type && 4) || (dxf_block.block_type && 32))
        {
                fprintf (fp, "  1\n%s\n", dxf_block.xref_name);
        }
        if ((dxf_block.block_type && 4) || (dxf_block.block_type && 32))
        {
                fprintf (fp, "  1\n%s\n", dxf_block.xref_name);
        }
        fprintf (fp, "  2\n%s\n", dxf_block.block_name);
        fprintf (fp, "  3\n%s\n", dxf_block.block_name);
        if (dxf_block.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_block.common.id_code);
        }
        if (strcmp (dxf_block.common.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_block.common.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_block.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_block.x0);
        fprintf (fp, " 20\n%f\n", dxf_block.y0);
        fprintf (fp, " 30\n%f\n", dxf_block.z0);
        if (dxf_block.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_block.common.thickness);
        }
        if (dxf_block.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_block.common.color);
        }
        if (dxf_block.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", dxf_block.block_type);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_block2 () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an end of block marker.
 *
 * Appears only in \c BLOCKS section.\n
 * Contains no other group codes than "0".
 */
int
dxf_block_write_endblk (FILE *fp)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_endblk () function.\n", __FILE__, __LINE__);
#endif
        fprintf (fp, "  0\nENDBLK\n");
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_endblk () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a table of blocks.
 *
 * Appears only in \c TABLES section.\n
 */
int
dxf_blocks_write_table
(
        char *dxf_blocks_list, 
        int acad_version_number
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_blocks () function.\n", __FILE__, __LINE__);
#endif
        /*! \todo Add code here. */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_blocks () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
