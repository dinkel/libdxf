/*!
 * \file appid.c
 *
 * \author Copyright (C) 2009 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF application identity symbol table entry
 * (\c APPID).
 *
 * \version The \c APPID table was introduced in DXF R12.
 *
 * A DXF \c APPID entity contains data concerning the application registered
 * with the drawing involved.\n
 * It is a table entry in the \c TABLES section of the DXF file.\n
 * These table entries maintain a set of names for all applications
 * registered with a drawing.
 *
 * \warning dxf_appid_new(), dxf_appid_init(), dxf_appid_read() and
 * dxf_appid_free() are backward compatible with versions R10 and R11 to
 * allow for reading DXF data generated with other CAD software. \n
 * When writing DXF data to file with versions before DXF R12 a warning
 * message is given.
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


#include "appid.h"


/*!
 * \brief Allocate memory for a DXF \c APPID symbol table entry.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAppid *
dxf_appid_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAppid *appid = NULL;
        size_t size;

        size = sizeof (DxfAppid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((appid = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfAppid struct.\n")),
                  __FUNCTION__);
                appid = NULL;
        }
        else
        {
                memset (appid, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c APPID
 * symbol table entry.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAppid *
dxf_appid_init
(
        DxfAppid *appid
                /*!< DXF application id symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                appid = dxf_appid_new ();
        }
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfAppid struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        appid->id_code = 0;
        appid->application_name = strdup ("");
        appid->flag = 0;
        appid->dictionary_owner_soft = strdup ("");
        appid->dictionary_owner_hard = strdup ("");
        appid->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Read data from a DXF file into a DXF \c APPID symbol table
 * entry.
 *
 * The last line read from file contained the string "APPID". \n
 * Now follows some data for the \c APPID, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c appid. \n
 *
 * \return a pointer to \c appid.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfAppid *
dxf_appid_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAppid *appid
                /*!< DXF appid symbol table entry. */
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
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                appid = dxf_appid_new ();
                appid = dxf_appid_init (appid);
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
                        fscanf (fp->fp, "%x\n", &appid->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing an application
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", appid->application_name);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &appid->flag);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", appid->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", appid->dictionary_owner_hard);
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
        return (appid);
}


/*!
 * \brief Write DXF output to a file for a DXF \c APPID symbol table
 * entry.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_appid_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfAppid *appid
                /*!< DXF APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("APPID");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((appid->application_name == NULL)
          || (strcmp (appid->application_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s empty block name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, appid->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_12)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (appid->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", appid->id_code);
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
        if ((strcmp (appid->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", appid->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (appid->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", appid->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbRegAppTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", appid->application_name);
        fprintf (fp->fp, " 70\n%d\n", appid->flag);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c APPID and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_appid_free
(
        DxfAppid *appid
                /*!< DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (appid->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfAppid was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (appid->application_name);
        free (appid->dictionary_owner_soft);
        free (appid->dictionary_owner_hard);
        free (appid);
        appid = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Test if xdata associated with this DXF \c APPID is not to be
 * written when \c SAVEASR12 is performed.
 *
 * \return \c TRUE when not to be written,
 * or \c FALSE when to be written.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_appid_is_no_save_xdata
(
        DxfAppid *appid
                /*!< DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (appid->flag, 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if this DXF \c APPID is externally dependent on an xref.
 *
 * \return \c TRUE when \c APPID is externally dependent on an xref,
 * or \c FALSE when \c APPID is not externally dependent on an xref.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_appid_is_xreferenced
(
        DxfAppid *appid
                /*!< DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (appid->flag, 4);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if this DXF \c APPID is externally dependent on a xref
 * and has been successfully resolved.
 *
 * \return \c TRUE when \c APPID is externally dependent on a xref and
 * has been successfully resolved, or \c FALSE when \c APPID is not
 * externally dependent on a xref and has not been successfully resolved.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_appid_is_xresolved
(
        DxfAppid *appid
                /*!< DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ((DXF_CHECK_BIT (appid->flag, 4))
          && (DXF_CHECK_BIT (appid->flag, 5)));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if this DXF \c APPID is internally referenced by an
 * entity.
 *
 * \return \c TRUE when \c APPID is internally referenced by an entity,
 * or \c FALSE when \c APPID is not internally referenced by an entity.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_appid_is_referenced
(
        DxfAppid *appid
                /*!< DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (appid->flag, 6);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF*/
