/*!
 * \file header.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF header section.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.\n\n
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

#include <stdarg.h>
#include <time.h>
#include "global.h"
#include "file.h"
#include "header.h"
#include "section.h"
#include "util.h"


/*!
 * \brief Allocate memory for a \c DxfHeader.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfHeader *
dxf_header_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHeader *header = NULL;
        size_t size;

        size = sizeof (DxfHeader);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((header = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHeader struct.\n")),
                  __FUNCTION__);
                header = NULL;
        }
        else
        {
                memset (header, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (header);
}


static char *acad_version_string (int version_number)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        switch (version_number)
        {
                case AC1006: return "AC1006";
                case AC1009: return "AC1009";
                case AC1012: return "AC1012";
                case AC1014: return "AC1014";
                case AC1015: return "AC1015";
                case AC1016: return "AC1016";
                case AC1017: return "AC1017";
                case AC1018: return "AC1018";
                case AC1021: return "AC1021";
                case AC1024: return "AC1024";
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return NULL;
}

/*!
 * \brief converts a version string the version number.
 *
 */
static int acad_version_from_string
(
        const char * version_string
                /*!< Pointer to the version string. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (strcmp ("AC1006", version_string) == 0)
                return AC1006;
        if (strcmp ("AC1009", version_string) == 0)
                return AC1009;
        if (strcmp ("AC1012", version_string) == 0)
                return AC1012;
        if (strcmp ("AC1014", version_string) == 0)
                return AC1014;
        if (strcmp ("AC1015", version_string) == 0)
                return AC1015;
        if (strcmp ("AC1016", version_string) == 0)
                return AC1016;
        if (strcmp ("AC1017", version_string) == 0)
                return AC1017;
        if (strcmp ("AC1018", version_string) == 0)
                return AC1018;
        if (strcmp ("AC1021", version_string) == 0)
                return AC1021;
        if (strcmp ("AC1024", version_string) == 0)
                return AC1024;
        /* in the case that it is an invalid version */
#if DEBUG
        DXF_DEBUG_END
#endif
        return 0;
}


/*! * \brief Initialize a dxf header.
 *
 * Only initialize members which are valid for the given AutoCAD version.\n
 */
int
dxf_header_init
(
        DxfHeader header,
                /*!< DXF header to be initialized.\n */
        int acad_version_number
                /*!< AutoCAD version number.\n */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        header.AcadVer = acad_version_string (acad_version_number);
        switch (acad_version_number)
        {
                case AC1009: /* AutoCAD 12 */
                {
                        header.DragMode = 2;
                        header.OSMode = 125;
                        header.BlipMode = 0;
                        header.Coords = 2;
                        header.AttDia = 0;
                        header.AttReq = 1;
                        header.Handling = 1;
                        header.HandSeed = strdup ("233");

                }
                case AC1012: /* AutoCAD 13 */
                {
                        header.DWGCodePage = strdup ("ANSI_1252");
                        header.DragMode = 2;
                        header.OSMode = 125;
                        header.CELTScale = 1.0;
                        header.DispSilH = 0;
                        header.DelObj = 1;
                        header.DimJUST = 0;
                        header.DimSD1 = 0;
                        header.DimSD2 = 0;
                        header.DimTOLJ = 1;
                        header.DimTZIN = 0;
                        header.DimALTZ = 0;
                        header.DimALTTZ = 0;
                        header.DimFIT = 3;
                        header.DimUPT = 0;
                        header.DimUNIT = 2;
                        header.DimDEC = 4;
                        header.DimTDEC = 4;
                        header.DimALTU = 2;
                        header.DimALTTD = 2;
                        header.DimTXSTY = strdup ("STANDARD");
                        header.DimAUNIT = 0;
                        header.BlipMode = 0;
                        header.ChamferC = 10.0;
                        header.ChamferD = 10.0;
                        header.Coords = 2;
                        header.AttDia = 0;
                        header.AttReq = 1;
                        header.Handling = 1;
                        header.HandSeed = strdup ("233");
                        header.TreeDepth = 3020;
                        header.PickStyle = 1;
                        header.CMLStyle = strdup ("STANDARD");
                        header.CMLJust = 0;
                        header.CMLScale = 1.0;
                        header.SaveImages = 1;
                }
                case AC1014: /* AutoCAD 14 */
                {
                        header.AcadMaintVer = 0;
                        header.DWGCodePage = strdup ("ANSI_1252");
                        header.DragMode = 2;
                        header.OSMode = 125;
                        header.CELTScale = 1.0;
                        header.DispSilH = 0;
                        header.DelObj = 1;
                        header.DimJUST = 0;
                        header.DimSD1 = 0;
                        header.DimSD2 = 0;
                        header.DimTOLJ = 1;
                        header.DimTZIN = 0;
                        header.DimALTZ = 0;
                        header.DimALTTZ = 0;
                        header.DimFIT = 3;
                        header.DimUPT = 0;
                        header.DimUNIT = 0;
                        header.DimDEC = 4;
                        header.DimTDEC = 4;
                        header.DimALTU = 2;
                        header.DimALTTD = 2;
                        header.DimTXSTY = strdup ("STANDARD");
                        header.DimAUNIT = 0;
                        header.BlipMode = 0;
                        header.ChamferC = 10.0;
                        header.ChamferD = 10.0;
                        header.Coords = 2;
                        header.AttDia = 0;
                        header.AttReq = 1;
                        header.Handling = 1;
                        header.HandSeed = strdup ("262");
                        header.TreeDepth = 3020;
                        header.PickStyle = 1;
                        header.CMLStyle = strdup ("STANDARD");
                        header.CMLJust = 0;
                        header.CMLScale = 1.0;
                        header.ProxyGraphics = 1;
                        header.Measurement = 0;
                }
                case AC1015: /* AutoCAD 2000 */
                {
                        header.AcadMaintVer = 20;
                        header.DWGCodePage = strdup ("ANSI_1252");
                        header.CELTScale = 1.0;
                        header.DispSilH = 0;
                        header.DimJUST = 0;
                        header.DimSD1 = 0;
                        header.DimSD2 = 0;
                        header.DimTOLJ = 1;
                        header.DimTZIN = 0;
                        header.DimALTZ = 0;
                        header.DimALTTZ = 0;
                        header.DimUPT = 0;
                        header.DimDEC = 4;
                        header.DimTDEC = 4;
                        header.DimALTU = 2;
                        header.DimALTTD = 2;
                        header.DimTXSTY = strdup ("STANDARD");
                        header.DimAUNIT = 0;
                        header.DimADEC = 0;
                        header.DimALTRND = 0.0;
                        header.DimAZIN = 0;
                        header.DimDSEP = 46;
                        header.DimATFIT = 3;
                        header.DimFRAC = 0;
                        header.DimLDRBLK = strdup ("");
                        header.DimLUNIT = 2;
                        header.DimLWD = -2;
                        header.DimLWE = -2;
                        header.DimTMOVE = 0;
                        header.ChamferC = 10.0;
                        header.ChamferD = 10.0;
                        header.TDUCreate = 0.0;
                        header.TDUUpdate = 0.0;
                        header.HandSeed = strdup ("274");
                        header.UCSBase = strdup ("");
                        header.UCSOrthoRef = strdup ("");
                        header.UCSOrthoView = 0;
                        header.UCSOrgTop.x0 = 0.0;
                        header.UCSOrgTop.y0 = 0.0;
                        header.UCSOrgTop.z0 = 0.0;
                        header.UCSOrgBottom.x0 = 0.0;
                        header.UCSOrgBottom.y0 = 0.0;
                        header.UCSOrgBottom.z0 = 0.0;
                        header.UCSOrgLeft.x0 = 0.0;
                        header.UCSOrgLeft.y0 = 0.0;
                        header.UCSOrgLeft.z0 = 0.0;
                        header.UCSOrgRight.x0 = 0.0;
                        header.UCSOrgRight.y0 = 0.0;
                        header.UCSOrgRight.z0 = 0.0;
                        header.UCSOrgFront.x0 = 0.0;
                        header.UCSOrgFront.y0 = 0.0;
                        header.UCSOrgFront.z0 = 0.0;
                        header.UCSOrgBack.x0 = 0.0;
                        header.UCSOrgBack.y0 = 0.0;
                        header.UCSOrgBack.z0 = 0.0;
                        header.PUCSBase = strdup ("");
                        header.PUCSOrthoRef = strdup ("");
                        header.PUCSOrthoView = 0;
                        header.PUCSOrgTop.x0 = 0.0;
                        header.PUCSOrgTop.y0 = 0.0;
                        header.PUCSOrgTop.z0 = 0.0;
                        header.PUCSOrgBottom.x0 = 0.0;
                        header.PUCSOrgBottom.y0 = 0.0;
                        header.PUCSOrgBottom.z0 = 0.0;
                        header.PUCSOrgLeft.x0 = 0.0;
                        header.PUCSOrgLeft.y0 = 0.0;
                        header.PUCSOrgLeft.z0 = 0.0;
                        header.PUCSOrgRight.x0 = 0.0;
                        header.PUCSOrgRight.y0 = 0.0;
                        header.PUCSOrgRight.z0 = 0.0;
                        header.PUCSOrgFront.x0 = 0.0;
                        header.PUCSOrgFront.y0 = 0.0;
                        header.PUCSOrgFront.z0 = 0.0;
                        header.PUCSOrgBack.x0 = 0.0;
                        header.PUCSOrgBack.y0 = 0.0;
                        header.PUCSOrgBack.z0 = 0.0;
                        header.TreeDepth = 3020;
                        header.CMLStyle = strdup ("STANDARD");
                        header.CMLJust = 0;
                        header.CMLScale = 1.0;
                        header.ProxyGraphics = 1;
                        header.Measurement = 0;
                        header.CELWeight = -1;
                        header.EndCaps = 0;
                        header.JoinStyle = 0;
                        header.LWDisplay = 0;
                        header.InsUnits = 0;
                        header.HyperLinkBase = strdup ("");
                        header.StyleSheet = strdup ("");
                        header.XEdit = 1;
                        header.CEPSNType = 0;
                        header.PStyleMode = 1;
                        header.FingerPrintGUID = strdup ("");
                        header.VersionGUID = strdup ("");
                        header.ExtNames = 0;
                        header.PSVPScale = 0.0;
                        header.OLEStartUp = 0;
                }
                case AC1018: /* AutoCAD 2004 */
                {
                        header.AcadMaintVer = 0;
                        header.DWGCodePage = strdup ("ANSI_1252");
                        header.CELTScale = 1.0;
                        header.DispSilH = 0;
                        header.DimJUST = 0;
                        header.DimSD1 = 0;
                        header.DimSD2 = 0;
                        header.DimTOLJ = 1;
                        header.DimTZIN = 0;
                        header.DimALTZ = 0;
                        header.DimALTTZ = 0;
                        header.DimUPT = 0;
                        header.DimDEC = 4;
                        header.DimTDEC = 4;
                        header.DimALTU = 2;
                        header.DimALTTD = 2;
                        header.DimTXSTY = strdup ("STANDARD");
                        header.DimAUNIT = 0;
                        header.DimADEC = 0;
                        header.DimALTRND = 0.0;
                        header.DimAZIN = 0;
                        header.DimDSEP = 46;
                        header.DimATFIT = 3;
                        header.DimFRAC = 0;
                        header.DimLDRBLK = strdup ("");
                        header.DimLUNIT = 2;
                        header.DimLWD = -2;
                        header.DimLWE = -2;
                        header.DimTMOVE = 0;
                        header.ChamferC = 10.0;
                        header.ChamferD = 10.0;
                        header.TDUCreate = 0.0;
                        header.TDUUpdate = 0.0;
                        header.HandSeed = strdup ("26A");
                        header.UCSBase = strdup ("");
                        header.UCSOrthoRef = strdup ("");
                        header.UCSOrthoView = 0;
                        header.UCSOrgTop.x0 = 0.0;
                        header.UCSOrgTop.y0 = 0.0;
                        header.UCSOrgTop.z0 = 0.0;
                        header.UCSOrgBottom.x0 = 0.0;
                        header.UCSOrgBottom.y0 = 0.0;
                        header.UCSOrgBottom.z0 = 0.0;
                        header.UCSOrgLeft.x0 = 0.0;
                        header.UCSOrgLeft.y0 = 0.0;
                        header.UCSOrgLeft.z0 = 0.0;
                        header.UCSOrgRight.x0 = 0.0;
                        header.UCSOrgRight.y0 = 0.0;
                        header.UCSOrgRight.z0 = 0.0;
                        header.UCSOrgFront.x0 = 0.0;
                        header.UCSOrgFront.y0 = 0.0;
                        header.UCSOrgFront.z0 = 0.0;
                        header.UCSOrgBack.x0 = 0.0;
                        header.UCSOrgBack.y0 = 0.0;
                        header.UCSOrgBack.z0 = 0.0;
                        header.PUCSBase = strdup ("");
                        header.PUCSOrthoRef = strdup ("");
                        header.PUCSOrthoView = 0;
                        header.PUCSOrgTop.x0 = 0.0;
                        header.PUCSOrgTop.y0 = 0.0;
                        header.PUCSOrgTop.z0 = 0.0;
                        header.PUCSOrgBottom.x0 = 0.0;
                        header.PUCSOrgBottom.y0 = 0.0;
                        header.PUCSOrgBottom.z0 = 0.0;
                        header.PUCSOrgLeft.x0 = 0.0;
                        header.PUCSOrgLeft.y0 = 0.0;
                        header.PUCSOrgLeft.z0 = 0.0;
                        header.PUCSOrgRight.x0 = 0.0;
                        header.PUCSOrgRight.y0 = 0.0;
                        header.PUCSOrgRight.z0 = 0.0;
                        header.PUCSOrgFront.x0 = 0.0;
                        header.PUCSOrgFront.y0 = 0.0;
                        header.PUCSOrgFront.z0 = 0.0;
                        header.PUCSOrgBack.x0 = 0.0;
                        header.PUCSOrgBack.y0 = 0.0;
                        header.PUCSOrgBack.z0 = 0.0;
                        header.TreeDepth = 3020;
                        header.CMLStyle = strdup ("STANDARD");
                        header.CMLJust = 0;
                        header.CMLScale = 1.0;
                        header.ProxyGraphics = 1;
                        header.Measurement = 0;
                        header.CELWeight = -1;
                        header.EndCaps = 0;
                        header.JoinStyle = 0;
                        header.LWDisplay = 0;
                        header.InsUnits = 0;
                        header.HyperLinkBase = strdup ("");
                        header.StyleSheet = strdup ("");
                        header.XEdit = 1;
                        header.CEPSNType = 0;
                        header.PStyleMode = 1;
                        header.FingerPrintGUID = strdup ("");
                        header.VersionGUID = strdup ("");
                        header.ExtNames = 0;
                        header.PSVPScale = 0.0;
                        header.OLEStartUp = 0;
                        header.SortEnts = 127;
                        header.IndexCtl = 0;
                        header.HideText = 0;
                        header.XClipFrame = 0;
                        header.HaloGap = 0;
                        header.ObsColor = 257;
                        header.ObsLType = 0;
                        header.InterSectionDisplay = 0;
                        header.InterSectionColor = 257;
                        header.DimASSOC = 1;
                        header.ProjectName = strdup ("");
                }
        }
        header.AcadVer = strdup (acad_version_string (acad_version_number));
        header.InsBase.x0 = 0.0;
        header.InsBase.y0 = 0.0;
        header.InsBase.z0 = 0.0;
        header.ExtMin.x0 = 0.0;
        header.ExtMin.y0 = 0.0;
        header.ExtMin.z0 = 0.0;
        header.ExtMax.x0 = 0.0;
        header.ExtMax.y0 = 0.0;
        header.ExtMax.z0 = 0.0;
        header.LimMin.x0 = 0.0;
        header.LimMin.y0 = 0.0;
        header.LimMax.x0 = 0.0;
        header.LimMax.y0 = 0.0;
        header.OrthoMode = 0;
        header.RegenMode = 0;
        header.FillMode = 1;
        header.QTextMode = 0;
        header.MirrText = 1;
        header.LTScale = 1.0;
        header.AttMode = 1;
        header.TextSize = 2.5;
        header.TraceWid = 1.0;
        header.TextStyle = strdup ("STANDARD");
        header.CELType = strdup ("BYLAYER");
        header.CLayer = strdup ("0");
        header.CEColor = 256;
        header.DimSCALE = 1.0;
        header.DimASZ = 2.5;
        header.DimEXO = 0.625;
        header.DimDLI = 3.75;
        header.DimRND = 0.0;
        header.DimDLE = 0.0;
        header.DimEXE = 1.25;
        header.DimTP = 0.0;
        header.DimTM = 0.0;
        header.DimTXT = 2.5;
        header.DimCEN = 2.5;
        header.DimTSZ = 0.0;
        header.DimTOL = 0;
        header.DimLIM = 0;
        header.DimTIH = 0;
        header.DimTOH = 0;
        header.DimSE1 = 0;
        header.DimSE2 = 0;
        header.DimTAD = 1;
        header.DimZIN = 8;
        header.DimBLK = strdup ("");
        header.DimASO = 1;
        header.DimSHO = 1;
        header.DimPOST = strdup ("");
        header.DimAPOST = strdup ("");
        header.DimALT = 0;
        header.DimALTD = 4;
        header.DimALTF = 0.0394;
        header.DimLFAC = 1.0;
        header.DimTOFL = 1;
        header.DimTVP = 0.0;
        header.DimTIX = 0;
        header.DimSOXD = 0;
        header.DimSAH = 0;
        header.DimBLK1 = strdup ("");
        header.DimBLK2 = strdup ("");
        header.DimCLRD = 0;
        header.DimCLRE = 0;
        header.DimCLRT = 0;
        header.DimTFAC = 1.0;
        header.DimGAP = 0.625;
        header.LUnits = 2;
        header.LUPrec = 4;
        header.Sketchinc = 1.0;
        header.FilletRad = 1.0;
        header.AUnits = 0;
        header.AUPrec = 0;
        header.Menu = strdup (".");
        header.Elevation = 0.0;
        header.PElevation = 0.0;
        header.Thickness = 0.0;
        header.LimCheck = 0;
        header.ChamferA = 10.0;
        header.ChamferB = 10.0;
        header.SKPoly = 0;
        header.TDCreate = 0.0;
        header.TDUpdate = 0.0;
        header.TDInDWG = 0.0;
        header.TDUSRTimer = 0.0;
        header.USRTimer = 1;
        header.AngBase = 0.0;
        header.AngDir = 0;
        header.PDMode = 98;
        header.PDSize = 0.0;
        header.PLineWid = 0.0;
        header.SPLFrame = 0;
        header.SPLineType = 6;
        header.SPLineSegs = 8;
        header.SurfTab1 = 6;
        header.SurfTab2 = 6;
        header.SurfType = 6;
        header.SurfU = 6;
        header.SurfV = 6;
        header.UCSName = strdup ("");
        header.UCSOrg.x0 = 0.0;
        header.UCSOrg.y0 = 0.0;
        header.UCSOrg.z0 = 0.0;
        header.UCSXDir.x0 = 0.0;
        header.UCSXDir.y0 = 0.0;
        header.UCSXDir.z0 = 0.0;
        header.UCSYDir.x0 = 0.0;
        header.UCSYDir.y0 = 0.0;
        header.UCSYDir.z0 = 0.0;
        header.PUCSName = strdup ("");
        header.PUCSOrg.x0 = 0.0;
        header.PUCSOrg.y0 = 0.0;
        header.PUCSOrg.z0 = 0.0;
        header.PUCSXDir.x0 = 0.0;
        header.PUCSXDir.y0 = 0.0;
        header.PUCSXDir.z0 = 0.0;
        header.PUCSYDir.x0 = 0.0;
        header.PUCSYDir.y0 = 0.0;
        header.PUCSYDir.z0 = 0.0;
        header.UserI1 = 0;
        header.UserI2 = 0;
        header.UserI3 = 0;
        header.UserI4 = 0;
        header.UserI5 = 0;
        header.UserR1 = 0.0;
        header.UserR2 = 0.0;
        header.UserR3 = 0.0;
        header.UserR4 = 0.0;
        header.UserR5 = 0.0;
        header.WorldView = 0;
        header.ShadEdge = 3;
        header.ShadeDif = 70;
        header.TileMode = 1;
        header.MaxActVP = 48;
        header.PInsBase.x0 = 0.0;
        header.PInsBase.y0 = 0.0;
        header.PInsBase.z0 = 0.0;
        header.PLimCheck = 0;
        header.PExtMin.x0 = 0.0;
        header.PExtMin.y0 = 0.0;
        header.PExtMin.z0 = 0.0;
        header.PExtMax.x0 = 0.0;
        header.PExtMax.y0 = 0.0;
        header.PExtMax.z0 = 0.0;
        header.PLimMin.x0 = 0.0;
        header.PLimMin.y0 = 0.0;
        header.PLimMax.x0 = 0.0;
        header.PLimMax.y0 = 0.0;
        header.UnitMode = 0;
        header.VisRetain = 1;
        header.PLineGen = 0;
        header.PSLTScale = 1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a metric DXF header.
 *
 * Fall back for a situation where no default metric header file exists.\n
 * Basically this function writes down a DXF header based on metric values.\n
 * Included are:\n
 * <ul>
 *   <li>HEADER
 *   <li>CLASSES
 *   <li>TABLES
 *   <ul>
 *     <li>VPORT
 *     <li>LTYPE
 *     <li>LAYER
 *     <li>STYLE
 *     <li>VIEW
 *     <li>UCS
 *     <li>APPID
 *     <li>DIMSTYLE
 *   </ul>
 * </ul>
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_header_write_metric_new
(
        DxfFile *fp
                /*!< file pointer to output file (or device) */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int JD;
        float fraction_day;
        fprintf (fp->fp, "  0\nSECTION\n");
        fprintf (fp->fp, "  2\nHEADER\n");
        fprintf (fp->fp, "  9\n$ACADVER\n  1\nAC1014\n");
        fprintf (fp->fp, "  9\n$ACADMAINTVER\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DWGCODEPAGE\n  3\nANSI_1252\n");
        fprintf (fp->fp, "  9\n$INSBASE\n 10\n0.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$EXTMIN\n 10\n-0.012816\n 20\n-0.009063\n 30\n-0.001526\n");
        fprintf (fp->fp, "  9\n$EXTMAX\n 10\n88.01056\n 20\n35.022217\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$LIMMIN\n 10\n0.0\n 20\n0.0\n");
        fprintf (fp->fp, "  9\n$LIMMAX\n 10\n420.0\n 20\n297.0\n");
        fprintf (fp->fp, "  9\n$ORTHOMODE\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$REGENMODE\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$FILLMODE\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$QTEXTMODE\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$MIRRTEXT\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$DRAGMODE\n 70\n     2\n");
        fprintf (fp->fp, "  9\n$LTSCALE\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$OSMODE\n 70\n   125\n");
        fprintf (fp->fp, "  9\n$ATTMODE\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$TEXTSIZE\n 40\n2.5\n");
        fprintf (fp->fp, "  9\n$TRACEWID\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$TEXTSTYLE\n  7\nSTANDARD\n");
        fprintf (fp->fp, "  9\n$CLAYER\n  8\n0\n");
        fprintf (fp->fp, "  9\n$CELTYPE\n  6\nBYLAYER\n");
        fprintf (fp->fp, "  9\n$CECOLOR\n 62\n   256\n");
        fprintf (fp->fp, "  9\n$CELTSCALE\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$DELOBJ\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$DISPSILH\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMSCALE\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$DIMASZ\n 40\n2.5\n");
        fprintf (fp->fp, "  9\n$DIMEXO\n 40\n0.625\n");
        fprintf (fp->fp, "  9\n$DIMDLI\n 40\n3.75\n");
        fprintf (fp->fp, "  9\n$DIMRND\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$DIMDLE\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$DIMEXE\n 40\n1.25\n");
        fprintf (fp->fp, "  9\n$DIMTP\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$DIMTM\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$DIMTXT\n 40\n2.5\n");
        fprintf (fp->fp, "  9\n$DIMCEN\n 40\n2.5\n");
        fprintf (fp->fp, "  9\n$DIMTSZ\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$DIMTOL\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMLIM\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMTIH\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMTOH\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMSE1\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMSE2\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMTAD\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$DIMZIN\n 70\n     8\n");
        fprintf (fp->fp, "  9\n$DIMBLK\n  1\n\n");
        fprintf (fp->fp, "  9\n$DIMASO\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$DIMSHO\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$DIMPOST\n  1\n\n");
        fprintf (fp->fp, "  9\n$DIMAPOST\n  1\n\n");
        fprintf (fp->fp, "  9\n$DIMALT\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMALTD\n 70\n     4\n");
        fprintf (fp->fp, "  9\n$DIMALTF\n 40\n0.0394\n");
        fprintf (fp->fp, "  9\n$DIMLFAC\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$DIMTOFL\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$DIMTVP\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$DIMTIX\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMSOXD\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMSAH\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMBLK1\n  1\n\n");
        fprintf (fp->fp, "  9\n$DIMBLK2\n  1\n\n");
        fprintf (fp->fp, "  9\n$DIMSTYLE\n  2\nSTANDARD\n");
        fprintf (fp->fp, "  9\n$DIMCLRD\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMCLRE\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMCLRT\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMTFAC\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$DIMGAP\n 40\n0.625\n");
        fprintf (fp->fp, "  9\n$DIMJUST\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMSD1\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMSD2\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMTOLJ\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$DIMTZIN\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMALTZ\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMALTTZ\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMFIT\n 70\n     3\n");
        fprintf (fp->fp, "  9\n$DIMUPT\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$DIMUNIT\n 70\n     2\n");
        fprintf (fp->fp, "  9\n$DIMDEC\n 70\n     4\n");
        fprintf (fp->fp, "  9\n$DIMTDEC\n 70\n     4\n");
        fprintf (fp->fp, "  9\n$DIMALTU\n 70\n     2\n");
        fprintf (fp->fp, "  9\n$DIMALTTD\n 70\n     2\n");
        fprintf (fp->fp, "  9\n$DIMTXSTY\n  7\nSTANDARD\n");
        fprintf (fp->fp, "  9\n$DIMAUNIT\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$LUNITS\n 70\n     2\n");
        fprintf (fp->fp, "  9\n$LUPREC\n 70\n     4\n");
        fprintf (fp->fp, "  9\n$SKETCHINC\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$FILLETRAD\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$AUNITS\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$AUPREC\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$MENU\n  1\n.\n");
        fprintf (fp->fp, "  9\n$ELEVATION\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$PELEVATION\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$THICKNESS\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$LIMCHECK\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$BLIPMODE\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$CHAMFERA\n 40\n10.0\n");
        fprintf (fp->fp, "  9\n$CHAMFERB\n 40\n10.0\n");
        fprintf (fp->fp, "  9\n$CHAMFERC\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$CHAMFERD\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$SKPOLY\n 70\n     0\n");
        time_t now;
        if (time(&now) != (time_t)(-1))
        {
            struct tm *current_time = localtime(&now);

            JD=current_time->tm_mday-32075+1461*(current_time->tm_year+6700+(current_time->tm_mon-13)/12)/4+367*(current_time->tm_mon-1-(current_time->tm_mon-13)/12*12)/12-3*((current_time->tm_year+6800+(current_time->tm_mon-13)/12)/100)/4;
            /* Transforms the current local gregorian date in a julian date.*/

            fraction_day=(current_time->tm_hour+(current_time->tm_min/60.0)+(current_time->tm_sec/3600.0))/24.0;
            /* Transforms the current local clock time in fraction of day.*/

            fprintf (fp->fp, "  9\n$TDCREATE\n 40\n%7.9f\n", JD+fraction_day);
            fprintf (fp->fp, "  9\n$TDUPDATE\n 40\n%7.9f\n", JD+fraction_day);
        }
        fprintf (fp->fp, "  9\n$TDINDWG\n 40\n0.0000000000\n");
        fprintf (fp->fp, "  9\n$TDUSRTIMER\n 40\n0.0000000000\n");
        /* In a new DXF file, $TDINDWG and $TDUSERTIMER are always 0, can change the decimal precision in according to the DXF version.*/
        fprintf (fp->fp, "  9\n$USRTIMER\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$ANGBASE\n 50\n0.0\n");
        fprintf (fp->fp, "  9\n$ANGDIR\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$PDMODE\n 70\n    98\n");
        fprintf (fp->fp, "  9\n$PDSIZE\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$PLINEWID\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$COORDS\n 70\n     2\n");
        fprintf (fp->fp, "  9\n$SPLFRAME\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$SPLINETYPE\n 70\n     6\n");
        fprintf (fp->fp, "  9\n$SPLINESEGS\n 70\n     8\n");
        fprintf (fp->fp, "  9\n$ATTDIA\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$ATTREQ\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$HANDLING\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$HANDSEED\n  5\n262\n");
        fprintf (fp->fp, "  9\n$SURFTAB1\n 70\n     6\n");
        fprintf (fp->fp, "  9\n$SURFTAB2\n 70\n     6\n");
        fprintf (fp->fp, "  9\n$SURFTYPE\n 70\n     6\n");
        fprintf (fp->fp, "  9\n$SURFU\n 70\n     6\n");
        fprintf (fp->fp, "  9\n$SURFV\n 70\n     6\n");
        fprintf (fp->fp, "  9\n$UCSNAME\n  2\n\n");
        fprintf (fp->fp, "  9\n$UCSORG\n 10\n0.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$UCSXDIR\n 10\n1.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$UCSYDIR\n 10\n0.0\n 20\n1.0\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$PUCSNAME\n  2\n\n");
        fprintf (fp->fp, "  9\n$PUCSORG\n 10\n0.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$PUCSXDIR\n 10\n1.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$PUCSYDIR\n 10\n0.0\n 20\n1.0\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$USERI1\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$USERI2\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$USERI3\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$USERI4\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$USERI5\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$USERR1\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$USERR2\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$USERR3\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$USERR4\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$USERR5\n 40\n0.0\n");
        fprintf (fp->fp, "  9\n$WORLDVIEW\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$SHADEDGE\n 70\n     3\n");
        fprintf (fp->fp, "  9\n$SHADEDIF\n 70\n    70\n");
        fprintf (fp->fp, "  9\n$TILEMODE\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$MAXACTVP\n 70\n    48\n");
        fprintf (fp->fp, "  9\n$PINSBASE\n 10\n0.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp->fp, "  9\n$PLIMCHECK\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$PEXTMIN\n 10\n1.000000E+20\n 20\n1.000000E+20\n 30\n1.000000E+20\n");
        fprintf (fp->fp, "  9\n$PEXTMAX\n 10\n-1.000000E+20\n 20\n-1.000000E+20\n 30\n-1.000000E+20\n");
        fprintf (fp->fp, "  9\n$PLIMMIN\n 10\n0.0\n 20\n0.0\n");
        fprintf (fp->fp, "  9\n$PLIMMAX\n 10\n420.0\n 20\n297.0");
        fprintf (fp->fp, "  9\n$UNITMODE\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$VISRETAIN\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$PLINEGEN\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$PSLTSCALE\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$TREEDEPTH\n 70\n  3020\n");
        fprintf (fp->fp, "  9\n$PICKSTYLE\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$CMLSTYLE\n  2\nSTANDARD\n");
        fprintf (fp->fp, "  9\n$CMLJUST\n 70\n     0\n");
        fprintf (fp->fp, "  9\n$CMLSCALE\n 40\n1.0\n");
        fprintf (fp->fp, "  9\n$PROXYGRAPHICS\n 70\n     1\n");
        fprintf (fp->fp, "  9\n$MEASUREMENT\n 70\n     0\n");
        fprintf (fp->fp, "  0\nENDSEC\n");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a dxf header.
 */
int
dxf_header_write
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        DxfHeader header
                /*!< DXF header entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("HEADER");

        dxf_section_write (fp, dxf_entity_name);
        fprintf (fp->fp, "  9\n$ACADVER\n  1\n%s\n", header.AcadVer);
        if (fp->acad_version_number >= AC1014) fprintf (fp->fp, "  9\n$ACADMAINTVER\n 70\n%i\n", header.AcadMaintVer);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DWGCODEPAGE\n  3\n%s\n", header.DWGCodePage);
        fprintf (fp->fp, "  9\n$INSBASE\n 10\n%f\n 20\n%f\n 30\n%f\n", header.InsBase.x0, header.InsBase.y0, header.InsBase.z0);
        fprintf (fp->fp, "  9\n$EXTMIN\n 10\n%f\n 20\n%f\n 30\n%f\n", header.ExtMin.x0, header.ExtMin.y0, header.ExtMin.z0);
        fprintf (fp->fp, "  9\n$EXTMAX\n 10\n%f\n 20\n%f\n 30\n%f\n", header.ExtMax.x0, header.ExtMax.y0, header.ExtMax.z0);
        fprintf (fp->fp, "  9\n$LIMMIN\n 10\n%f\n 20\n%f\n", header.LimMin.x0, header.LimMin.y0);
        fprintf (fp->fp, "  9\n$LIMMAX\n 10\n%f\n 20\n%f\n", header.LimMax.x0, header.LimMax.y0);
        fprintf (fp->fp, "  9\n$ORTHOMODE\n 70\n%i\n", header.OrthoMode);
        fprintf (fp->fp, "  9\n$REGENMODE\n 70\n%i\n", header.RegenMode);
        fprintf (fp->fp, "  9\n$FILLMODE\n 70\n%i\n", header.FillMode);
        fprintf (fp->fp, "  9\n$QTEXTMODE\n 70\n%i\n", header.QTextMode);
        fprintf (fp->fp, "  9\n$MIRRTEXT\n 70\n%i\n", header.MirrText);
        if (fp->acad_version_number <= AC1015) fprintf (fp->fp, "  9\n$DRAGMODE\n 70\n%i\n", header.DragMode);
        fprintf (fp->fp, "  9\n$LTSCALE\n 40\n%f\n", header.LTScale);
        if (fp->acad_version_number <= AC1014) fprintf (fp->fp, "  9\n$OSMODE\n 70\n%i\n", header.OSMode);
        fprintf (fp->fp, "  9\n$ATTMODE\n 70\n%i\n", header.AttMode);
        fprintf (fp->fp, "  9\n$TEXTSIZE\n 40\n%f\n", header.TextSize);
        fprintf (fp->fp, "  9\n$TRACEWID\n 40\n%f\n", header.TraceWid);
        fprintf (fp->fp, "  9\n$TEXTSTYLE\n  7\n%s\n", header.TextStyle);
        fprintf (fp->fp, "  9\n$CLAYER\n  8\n%s\n", header.CLayer);
        fprintf (fp->fp, "  9\n$CELTYPE\n  6\n%s\n", header.CELType);
        fprintf (fp->fp, "  9\n$CECOLOR\n 62\n%i\n", header.CEColor);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$CELTSCALE\n 40\n%f\n", header.CELTScale);
        if ((fp->acad_version_number == AC1012)
          || (fp->acad_version_number == AC1014)) fprintf (fp->fp, "  9\n$DELOBJ\n 70\n%i\n", header.DelObj);
        if (fp->acad_version_number <= AC1012) fprintf (fp->fp, "  9\n$DISPSILH\n 70\n%i\n", header.DispSilH);
        fprintf (fp->fp, "  9\n$DIMSCALE\n 40\n%f\n", header.DimSCALE);
        fprintf (fp->fp, "  9\n$DIMASZ\n 40\n%f\n", header.DimASZ);
        fprintf (fp->fp, "  9\n$DIMEXO\n 40\n%f\n", header.DimEXO);
        fprintf (fp->fp, "  9\n$DIMDLI\n 40\n%f\n", header.DimDLI);
        fprintf (fp->fp, "  9\n$DIMRND\n 40\n%f\n", header.DimRND);
        fprintf (fp->fp, "  9\n$DIMDLE\n 40\n%f\n", header.DimDLE);
        fprintf (fp->fp, "  9\n$DIMEXE\n 40\n%f\n", header.DimEXE);
        fprintf (fp->fp, "  9\n$DIMTP\n 40\n%f\n", header.DimTP);
        fprintf (fp->fp, "  9\n$DIMTM\n 40\n%f\n", header.DimTM);
        fprintf (fp->fp, "  9\n$DIMTXT\n 40\n%f\n", header.DimTXT);
        fprintf (fp->fp, "  9\n$DIMCEN\n 40\n%f\n", header.DimCEN);
        fprintf (fp->fp, "  9\n$DIMTSZ\n 40\n%f\n", header.DimTSZ);
        fprintf (fp->fp, "  9\n$DIMTOL\n 70\n%i\n", header.DimTOL);
        fprintf (fp->fp, "  9\n$DIMLIM\n 70\n%i\n", header.DimLIM);
        fprintf (fp->fp, "  9\n$DIMTIH\n 70\n%i\n", header.DimTIH);
        fprintf (fp->fp, "  9\n$DIMTOH\n 70\n%i\n", header.DimTOH);
        fprintf (fp->fp, "  9\n$DIMSE1\n 70\n%i\n", header.DimSE1);
        fprintf (fp->fp, "  9\n$DIMSE2\n 70\n%i\n", header.DimSE2);
        fprintf (fp->fp, "  9\n$DIMTAD\n 70\n%i\n", header.DimTAD);
        fprintf (fp->fp, "  9\n$DIMZIN\n 70\n%i\n", header.DimZIN);
        fprintf (fp->fp, "  9\n$DIMBLK\n  1\n%s\n", header.DimBLK);
        fprintf (fp->fp, "  9\n$DIMASO\n 70\n%i\n", header.DimASO);
        fprintf (fp->fp, "  9\n$DIMSHO\n 70\n%i\n", header.DimSHO);
        fprintf (fp->fp, "  9\n$DIMPOST\n  1\n%s\n", header.DimPOST);
        fprintf (fp->fp, "  9\n$DIMAPOST\n  1\n%s\n", header.DimAPOST);
        fprintf (fp->fp, "  9\n$DIMALT\n 70\n%i\n", header.DimALT);
        fprintf (fp->fp, "  9\n$DIMALTD\n 70\n%i\n", header.DimALTD);
        fprintf (fp->fp, "  9\n$DIMALTF\n 40\n%f\n", header.DimALTF);
        fprintf (fp->fp, "  9\n$DIMLFAC\n 40\n%f\n", header.DimLFAC);
        fprintf (fp->fp, "  9\n$DIMTOFL\n 70\n%i\n", header.DimTOFL);
        fprintf (fp->fp, "  9\n$DIMTVP\n 40\n%f\n", header.DimTVP);
        fprintf (fp->fp, "  9\n$DIMTIX\n 70\n%i\n", header.DimTIX);
        fprintf (fp->fp, "  9\n$DIMSOXD\n 70\n%i\n", header.DimSOXD);
        fprintf (fp->fp, "  9\n$DIMSAH\n 70\n%i\n", header.DimSAH);
        fprintf (fp->fp, "  9\n$DIMBLK1\n  1\n%s\n", header.DimBLK1);
        fprintf (fp->fp, "  9\n$DIMBLK2\n  1\n%s\n", header.DimBLK2);
        fprintf (fp->fp, "  9\n$DIMSTYLE\n  2\n%s\n", header.DimSTYLE);
        fprintf (fp->fp, "  9\n$DIMCLRD\n 70\n%i\n", header.DimCLRD);
        fprintf (fp->fp, "  9\n$DIMCLRE\n 70\n%i\n", header.DimCLRE);
        fprintf (fp->fp, "  9\n$DIMCLRT\n 70\n%i\n", header.DimCLRT);
        fprintf (fp->fp, "  9\n$DIMTFAC\n 40\n%f\n", header.DimTFAC);
        fprintf (fp->fp, "  9\n$DIMGAP\n 40\n%f\n", header.DimGAP);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMJUST\n 70\n%i\n", header.DimJUST);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMSD1\n 70\n%i\n", header.DimSD1);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMSD2\n 70\n%i\n", header.DimSD2);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMTOLJ\n 70\n%i\n", header.DimTOLJ);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMTZIN\n 70\n%i\n", header.DimTZIN);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMALTZ\n 70\n%i\n", header.DimALTZ);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMALTTZ\n 70\n%i\n", header.DimALTTZ);
        if ((fp->acad_version_number == AC1012)
          || (fp->acad_version_number == AC1014)) fprintf (fp->fp, "  9\n$DIMFIT\n 70\n%i\n", header.DimFIT);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMUPT\n 70\n%i\n", header.DimUPT);
        if ((fp->acad_version_number == AC1012) ||
          (fp->acad_version_number == AC1014)) fprintf (fp->fp, "  9\n$DIMUNIT\n 70\n%i\n", header.DimUNIT);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMDEC\n 70\n%i\n", header.DimDEC);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMTDEC\n 70\n%i\n", header.DimTDEC);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMALTU\n 70\n%i\n", header.DimALTU);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMALTTD\n 70\n%i\n", header.DimALTTD);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMTXSTY\n  7\n%s\n", header.DimTXSTY);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$DIMAUNIT\n 70\n%i\n", header.DimAUNIT);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMADEC\n 70\n%i\n", header.DimADEC);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMALTRND\n 40\n%f\n", header.DimALTRND);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMAZIN\n 70\n%i\n", header.DimAZIN);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMDSEP\n 70\n%i\n", header.DimDSEP);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMATFIT\n 70\n%i\n", header.DimATFIT);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMFRAC\n 70\n%i\n", header.DimFRAC);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMLDRBLK\n  1\n%s\n", header.DimLDRBLK);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMLUNIT\n 70\n%i\n", header.DimLUNIT);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMLWD\n 70\n%i\n", header.DimLWD);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMLWE\n 70\n%i\n", header.DimLWE);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$DIMTMOVE\n 70\n%i\n", header.DimTMOVE);
        fprintf (fp->fp, "  9\n$LUNITS\n 70\n%i\n", header.LUnits);
        fprintf (fp->fp, "  9\n$LUPREC\n 70\n%i\n", header.LUPrec);
        fprintf (fp->fp, "  9\n$SKETCHINC\n 40\n%f\n", header.Sketchinc);
        fprintf (fp->fp, "  9\n$FILLETRAD\n 40\n%f\n", header.FilletRad);
        fprintf (fp->fp, "  9\n$AUNITS\n 70\n%i\n", header.AUnits);
        fprintf (fp->fp, "  9\n$AUPREC\n 70\n%i\n", header.AUPrec);
        fprintf (fp->fp, "  9\n$MENU\n  1\n%s\n", header.Menu);
        fprintf (fp->fp, "  9\n$ELEVATION\n 40\n%f\n", header.Elevation);
        fprintf (fp->fp, "  9\n$PELEVATION\n 40\n%f\n", header.PElevation);
        fprintf (fp->fp, "  9\n$THICKNESS\n 40\n%f\n", header.Thickness);
        fprintf (fp->fp, "  9\n$LIMCHECK\n 70\n%i\n", header.LimCheck);
        if (fp->acad_version_number <= AC1014) fprintf (fp->fp, "  9\n$BLIPMODE\n 70\n%i\n", header.BlipMode);
        fprintf (fp->fp, "  9\n$CHAMFERA\n 40\n%f\n", header.ChamferA);
        fprintf (fp->fp, "  9\n$CHAMFERB\n 40\n%f\n", header.ChamferB);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$CHAMFERC\n 40\n%f\n", header.ChamferC);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$CHAMFERD\n 40\n%f\n", header.ChamferD);
        fprintf (fp->fp, "  9\n$SKPOLY\n 70\n%i\n", header.SKPoly);
        fprintf (fp->fp, "  9\n$TDCREATE\n 40\n%f\n", header.TDCreate);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$TDUCREATE\n 40\n%f\n", header.TDUCreate);
        fprintf (fp->fp, "  9\n$TDUPDATE\n 40\n%f\n", header.TDUpdate);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$TDUUPDATE\n 40\n%f\n", header.TDUUpdate);
        fprintf (fp->fp, "  9\n$TDINDWG\n 40\n%f\n", header.TDInDWG);
        fprintf (fp->fp, "  9\n$TDUSRTIMER\n 40\n%f\n", header.TDUSRTimer);
        fprintf (fp->fp, "  9\n$USRTIMER\n 70\n%i\n", header.USRTimer);
        fprintf (fp->fp, "  9\n$ANGBASE\n 50\n%f\n", header.AngBase);
        fprintf (fp->fp, "  9\n$ANGDIR\n 70\n%i\n", header.AngDir);
        fprintf (fp->fp, "  9\n$PDMODE\n 70\n%i\n", header.PDMode);
        fprintf (fp->fp, "  9\n$PDSIZE\n 40\n%f\n", header.PDSize);
        fprintf (fp->fp, "  9\n$PLINEWID\n 40\n%f\n", header.PLineWid);
        if (fp->acad_version_number <= AC1014) fprintf (fp->fp, "  9\n$COORDS\n 70\n%i\n", header.Coords);
        fprintf (fp->fp, "  9\n$SPLFRAME\n 70\n%i\n", header.SPLFrame);
        fprintf (fp->fp, "  9\n$SPLINETYPE\n 70\n%i\n", header.SPLineType);
        if (fp->acad_version_number <= AC1014) fprintf (fp->fp, "  9\n$ATTDIA\n 70\n%i\n", header.AttDia);
        if (fp->acad_version_number <= AC1014) fprintf (fp->fp, "  9\n$ATTREQ\n 70\n%i\n", header.AttReq);
        if (fp->acad_version_number <= AC1014) fprintf (fp->fp, "  9\n$HANDLING\n 70\n%i\n", header.Handling);
        fprintf (fp->fp, "  9\n$SPLINESEGS\n 70\n%i\n", header.SPLineSegs);
        fprintf (fp->fp, "  9\n$HANDSEED\n  5\n%s\n", header.HandSeed);
        fprintf (fp->fp, "  9\n$SURFTAB1\n 70\n%i\n", header.SurfTab1);
        fprintf (fp->fp, "  9\n$SURFTAB2\n 70\n%i\n", header.SurfTab2);
        fprintf (fp->fp, "  9\n$SURFTYPE\n 70\n%i\n", header.SurfType);
        fprintf (fp->fp, "  9\n$SURFU\n 70\n%i\n", header.SurfU);
        fprintf (fp->fp, "  9\n$SURFV\n 70\n%i\n", header.SurfV);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSBASE\n  2\n%s\n", header.UCSBase);
        fprintf (fp->fp, "  9\n$UCSNAME\n  2\n%s\n", header.UCSName);
        fprintf (fp->fp, "  9\n$UCSORG\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrg.x0, header.UCSOrg.y0, header.UCSOrg.z0);
        fprintf (fp->fp, "  9\n$UCSXDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSXDir.x0, header.UCSXDir.y0, header.UCSXDir.z0);
        fprintf (fp->fp, "  9\n$UCSYDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSYDir.x0, header.UCSYDir.y0, header.UCSYDir.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSORTHOREF\n  2\n%s\n", header.UCSOrthoRef);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSORTHOVIEW\n 70\n%i\n", header.UCSOrthoView);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSORGTOP\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgTop.x0, header.UCSOrgTop.y0, header.UCSOrgTop.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSORGBOTTOM\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgBottom.x0, header.UCSOrgBottom.y0, header.UCSOrgBottom.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSORGLEFT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgLeft.x0, header.UCSOrgLeft.y0, header.UCSOrgLeft.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSORGRIGHT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgRight.x0, header.UCSOrgRight.y0, header.UCSOrgRight.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSORGFRONT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgFront.x0, header.UCSOrgFront.y0, header.UCSOrgFront.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$UCSORGBACK\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgBack.x0, header.UCSOrgBack.y0, header.UCSOrgBack.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSBASE\n  2\n%s\n", header.PUCSBase);
        fprintf (fp->fp, "  9\n$PUCSNAME\n  2\n%s\n", header.PUCSName);
        fprintf (fp->fp, "  9\n$PUCSORG\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrg.x0, header.PUCSOrg.y0, header.PUCSOrg.z0);
        fprintf (fp->fp, "  9\n$PUCSXDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSXDir.x0, header.PUCSXDir.y0, header.PUCSXDir.z0);
        fprintf (fp->fp, "  9\n$PUCSYDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSYDir.x0, header.PUCSYDir.y0, header.PUCSYDir.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSORTHOREF\n  2\n%s\n", header.PUCSOrthoRef);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSORTHOVIEW\n 70\n%i\n", header.PUCSOrthoView);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSORGTOP\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgTop.x0, header.PUCSOrgTop.y0, header.PUCSOrgTop.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSORGBOTTOM\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgBottom.x0, header.PUCSOrgBottom.y0, header.PUCSOrgBottom.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSORGLEFT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgLeft.x0, header.PUCSOrgLeft.y0, header.PUCSOrgLeft.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSORGRIGHT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgRight.x0, header.PUCSOrgRight.y0, header.PUCSOrgRight.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSORGFRONT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgFront.x0, header.PUCSOrgFront.y0, header.PUCSOrgFront.z0);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PUCSORGBACK\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgBack.x0, header.PUCSOrgBack.y0, header.PUCSOrgBack.z0);
        fprintf (fp->fp, "  9\n$USERI1\n 70\n%i\n", header.UserI1);
        fprintf (fp->fp, "  9\n$USERI2\n 70\n%i\n", header.UserI2);
        fprintf (fp->fp, "  9\n$USERI3\n 70\n%i\n", header.UserI3);
        fprintf (fp->fp, "  9\n$USERI4\n 70\n%i\n", header.UserI4);
        fprintf (fp->fp, "  9\n$USERI5\n 70\n%i\n", header.UserI5);
        fprintf (fp->fp, "  9\n$USERR1\n 40\n%f\n", header.UserR1);
        fprintf (fp->fp, "  9\n$USERR2\n 40\n%f\n", header.UserR2);
        fprintf (fp->fp, "  9\n$USERR3\n 40\n%f\n", header.UserR3);
        fprintf (fp->fp, "  9\n$USERR4\n 40\n%f\n", header.UserR4);
        fprintf (fp->fp, "  9\n$USERR5\n 40\n%f\n", header.UserR5);
        fprintf (fp->fp, "  9\n$WORLDVIEW\n 70\n%i\n", header.WorldView);
        fprintf (fp->fp, "  9\n$SHADEDGE\n 70\n%i\n", header.ShadEdge);
        fprintf (fp->fp, "  9\n$SHADEDIF\n 70\n%i\n", header.ShadeDif);
        fprintf (fp->fp, "  9\n$TILEMODE\n 70\n%i\n", header.TileMode);
        fprintf (fp->fp, "  9\n$MAXACTVP\n 70\n%i\n", header.MaxActVP);
        fprintf (fp->fp, "  9\n$PINSBASE\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PInsBase.x0, header.PInsBase.y0, header.PInsBase.z0);
        fprintf (fp->fp, "  9\n$PLIMCHECK\n 70\n%i\n", header.PLimCheck);
        fprintf (fp->fp, "  9\n$PEXTMIN\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PExtMin.x0, header.PExtMin.y0, header.PExtMin.z0);
        fprintf (fp->fp, "  9\n$PEXTMAX\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PExtMax.x0, header.PExtMax.y0, header.PExtMax.z0);
        fprintf (fp->fp, "  9\n$PLIMMIN\n 10\n%f\n 20\n%f\n", header.PLimMin.x0, header.PLimMin.y0);
        fprintf (fp->fp, "  9\n$PLIMMAX\n 10\n%f\n 20\n%f\n", header.PLimMax.x0, header.PLimMax.y0);
        fprintf (fp->fp, "  9\n$UNITMODE\n 70\n%i\n", header.UnitMode);
        fprintf (fp->fp, "  9\n$VISRETAIN\n 70\n%i\n", header.VisRetain);
        fprintf (fp->fp, "  9\n$PLINEGEN\n 70\n%i\n", header.PLineGen);
        fprintf (fp->fp, "  9\n$PSLTSCALE\n 70\n%i\n", header.PSLTScale);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$TREEDEPTH\n 70\n%i\n", header.TreeDepth);
        if ((fp->acad_version_number == AC1012)
          || (fp->acad_version_number == AC1014)) fprintf (fp->fp, "  9\n$PICKSTYLE\n 70\n%i\n", header.PickStyle);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$CMLSTYLE\n  2\n%s\n", header.CMLStyle);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$CMLJUST\n 70\n%i\n", header.CMLJust);
        if (fp->acad_version_number >= AC1012) fprintf (fp->fp, "  9\n$CMLSCALE\n 40\n%f\n", header.CMLScale);
        if (fp->acad_version_number >= AC1014) fprintf (fp->fp, "  9\n$PROXYGRAPHICS\n 70\n%i\n", header.ProxyGraphics);
        if (fp->acad_version_number >= AC1014) fprintf (fp->fp, "  9\n$MEASUREMENT\n 70\n%i\n", header.Measurement);
        if (fp->acad_version_number == AC1012) fprintf (fp->fp, "  9\n$SAVEIMAGES\n 70\n%i\n", header.SaveImages);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$CELWEIGHT\n370\n%i\n", header.CELWeight);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$ENDCAPS\n280\n%i\n", header.EndCaps);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$JOINSTYLE\n280\n%i\n", header.JoinStyle);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$LWDISPLAY\n290\n%i\n", header.LWDisplay);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$INSUNITS\n 70\n%i\n", header.InsUnits);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$HYPERLINKBASE\n  1\n%s\n", header.HyperLinkBase);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$STYLESHEET\n  1\n%s\n", header.StyleSheet);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$XEDIT\n290\n%i\n", header.XEdit);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$CEPSNTYPE\n380\n%i\n", header.CEPSNType);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PSTYLEMODE\n290\n%i\n", header.PStyleMode);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$FINGERPRINTGUID\n  2\n%s\n", header.FingerPrintGUID);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$VERSIONGUID\n  2\n%s\n", header.VersionGUID);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$EXTNAMES\n290\n%i\n", header.ExtNames);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$PSVPSCALE\n 40\n%f\n", header.PSVPScale);
        if (fp->acad_version_number >= AC1015) fprintf (fp->fp, "  9\n$OLESTARTUP\n290\n%i\n", header.OLEStartUp);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$SORTENTS\n280\n%i\n", header.SortEnts);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$INDEXCTL\n280\n%i\n", header.IndexCtl);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$HIDETEXT\n280\n%i\n", header.HideText);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$XCLIPFRAME\n290\n%i\n", header.XClipFrame);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$HALOGAP\n280\n%i\n", header.HaloGap);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$OBSCOLOR\n 70\n%i\n", header.ObsColor);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$OBSLTYPE\n280\n%i\n", header.ObsLType);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$INTERSECTIONDISPLAY\n280\n%i\n", header.InterSectionDisplay);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$INTERSECTIONCOLOR\n 70\n%i\n", header.InterSectionColor);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$DIMASSOC\n280\n%i\n", header.DimASSOC);
        if (fp->acad_version_number >= AC1018) fprintf (fp->fp, "  9\n$PROJECTNAME\n  1\n%s\n", header.ProjectName);
        dxf_endsec_write (fp);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}

int
dxf_header_read_parse_string
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        const char *temp_string,
        const char *header_var,
        char **value_string,
        int version_expression
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char tstring[255];
        int n, ret = SUCCESS;
        if (strcmp (temp_string, header_var) == 0 && version_expression)
        {
                ret = FOUND;
                dxf_read_scanf (fp, "%i\n%s\n", &n, tstring);
                if (dxf_read_is_string(n))
                {
                        *value_string = strdup(tstring);
                }
                else
                        ret = FAIL;
        }
        else
                ret = SUCCESS;
                
#if DEBUG
        DXF_DEBUG_END
#endif
        return ret;
}

int
dxf_header_read_parse_int
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        const char *temp_string,
        const char *header_var,
        int *value,
        int version_expression
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int f, tvar, n, ret = SUCCESS;
        /* test for header_var and version number. -3 makes it version agnostic */
        if (strcmp (temp_string, header_var) == 0  && version_expression)
        {
                f = dxf_read_scanf (fp, "%i\n%i\n", &n, &tvar);
                if (f > 0 && dxf_read_is_int(n))
                {
                        *value = tvar;
                        ret = FOUND;                                
                }
                else
                        ret = FAIL;
        }
        else
                ret = SUCCESS;

#if DEBUG
        DXF_DEBUG_END
#endif
        return ret;
}

static int
dxf_read_header_parse_n_double
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        const char *temp_string,
        const char *header_var,
        int version_expression,
        int quant,
        ...
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int f, n, i, ret = SUCCESS;
        double *dvar;
        double tvar;
        va_list dlist;

        /* test for header_var and version number. -3 makes it version agnostic */
        if (strcmp (temp_string, header_var) == 0  && version_expression)
        {
                ret = FOUND;
                va_start (dlist, quant);
                for (i = 1; i <= quant; i++)
                {
                        dvar = va_arg(dlist, double *);
                        /* prepare the string to read all vars */
                        f = dxf_read_scanf (fp, "%d\n%'lf\n", &n, &tvar);
                        if (f > 0 && dxf_read_is_double (n))
                        {
                                *dvar = tvar;
                        }
                        else
                        {
                                ret = FALSE;
                                break;
                        }
                }
                va_end(dlist);
        }
        else
                ret = SUCCESS;

#if DEBUG
        DXF_DEBUG_END
#endif
        return ret;
}

/*!
 * \brief Parses the header from a DXF file, with no particulary order.
 */
static int
dxf_read_header_parser
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        DxfHeader header,
                /*!< DXF header to be initialized.\n */
        char * temp_string,
        int acad_version_number
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int ret;
        /*!
        * \todo: add some kind of control to what we have already read
        * and check if we read all header data.
        */
        ret = dxf_header_read_parse_int (fp, temp_string, "$ACADMAINTVER",
                                         &header.AcadMaintVer,
                                         acad_version_number > AC1014);
        dxf_return(ret);
                
        ret = dxf_header_read_parse_string (fp, temp_string, "$DWGCODEPAGE",
                                            &header.DWGCodePage,
                                            acad_version_number >= AC1012);
        dxf_return(ret);
        
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$INSBASE",
                                              TRUE,
                                              3,
                                              &header.InsBase.x0,
                                              &header.InsBase.y0,
                                              &header.InsBase.z0);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$EXTMIN",
                                              TRUE,
                                              3,
                                              &header.ExtMin.x0,
                                              &header.ExtMin.y0,
                                              &header.ExtMin.z0);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$EXTMAX",
                                              TRUE,
                                              3,
                                              &header.ExtMax.x0,
                                              &header.ExtMax.y0,
                                              &header.ExtMax.z0);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$LIMMIN",
                                              TRUE,
                                              2,
                                              &header.LimMin.x0,
                                              &header.LimMin.y0);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$LIMMAX",
                                              TRUE,
                                              2,
                                              &header.LimMax.x0,
                                              &header.LimMax.y0);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$ORTHOMODE",
                                         &header.OrthoMode,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$REGENMODE",
                                         &header.RegenMode,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$FILLMODE",
                                         &header.FillMode,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$QTEXTMODE",
                                         &header.QTextMode,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$MIRRTEXT",
                                         &header.MirrText,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$DRAGMODE",
                                         &header.MirrText,
                                         acad_version_number < AC1015);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$LTSCALE",
                                              TRUE,
                                              1,
                                              &header.LTScale);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$OSMODE",
                                         &header.OSMode,
                                         acad_version_number <= AC1014);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$ATTMODE",
                                         &header.AttMode,
                                         TRUE);
        dxf_return(ret);
    
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$TEXTSIZE",
                                              TRUE,
                                              1,
                                              &header.TextSize);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$TRACEWID",
                                              TRUE,
                                              1,
                                              &header.TraceWid);
        dxf_return(ret);

        ret = dxf_header_read_parse_string (fp, temp_string, "$TEXTSTYLE",
                                            &header.TextStyle,
                                            TRUE);
        dxf_return(ret);

        ret = dxf_header_read_parse_string (fp, temp_string, "$CLAYER",
                                            &header.CLayer,
                                            TRUE);
        dxf_return(ret);

        ret = dxf_header_read_parse_string (fp, temp_string, "$CELTYPE",
                                            &header.CELType,
                                            TRUE);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$CECOLOR",
                                         &header.CEColor,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$CELTSCALE",
                                              acad_version_number >= AC1012,
                                              1,
                                              &header.CELTScale);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$DELOBJ",
                                         &header.DelObj,
                                         (acad_version_number == AC1012)
                                         || (acad_version_number == AC1014));
        dxf_return(ret);

        /*! \todo FIXME: changed from AC1012 to AC1015 */
        ret = dxf_header_read_parse_int (fp, temp_string, "$DISPSILH",
                                         &header.DispSilH,
                                         acad_version_number <= AC1015);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMSCALE",
                                              TRUE,
                                              1,
                                              &header.DimSCALE);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMASZ",
                                              TRUE,
                                              1,
                                              &header.DimASZ);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMEXO",
                                              TRUE,
                                              1,
                                              &header.DimEXO);
        dxf_return(ret);

        /*
        fprintf (fp, "  9\n$DIMDLI\n 40\n%f\n", header.DimDLI);
        fprintf (fp, "  9\n$DIMRND\n 40\n%f\n", header.DimRND);
        fprintf (fp, "  9\n$DIMDLE\n 40\n%f\n", header.DimDLE);
        */
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMEXE",
                                              TRUE,
                                              1,
                                              &header.DimEXE);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$DIMTP\n 40\n%f\n", header.DimTP);
        fprintf (fp, "  9\n$DIMTM\n 40\n%f\n", header.DimTM);
        */
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMTXT",
                                              TRUE,
                                              1,
                                              &header.DimTXT);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$DIMCEN\n 40\n%f\n", header.DimCEN);
        fprintf (fp, "  9\n$DIMTSZ\n 40\n%f\n", header.DimTSZ);
        fprintf (fp, "  9\n$DIMTOL\n 70\n%i\n", header.DimTOL);
        fprintf (fp, "  9\n$DIMLIM\n 70\n%i\n", header.DimLIM);
        fprintf (fp, "  9\n$DIMTIH\n 70\n%i\n", header.DimTIH);
        fprintf (fp, "  9\n$DIMTOH\n 70\n%i\n", header.DimTOH);
        fprintf (fp, "  9\n$DIMSE1\n 70\n%i\n", header.DimSE1);
        fprintf (fp, "  9\n$DIMSE2\n 70\n%i\n", header.DimSE2);
        fprintf (fp, "  9\n$DIMTAD\n 70\n%i\n", header.DimTAD);
        fprintf (fp, "  9\n$DIMZIN\n 70\n%i\n", header.DimZIN);
        fprintf (fp, "  9\n$DIMBLK\n  1\n%s\n", header.DimBLK);
        fprintf (fp, "  9\n$DIMASO\n 70\n%i\n", header.DimASO);
        fprintf (fp, "  9\n$DIMSHO\n 70\n%i\n", header.DimSHO);
        fprintf (fp, "  9\n$DIMPOST\n  1\n%s\n", header.DimPOST);
        fprintf (fp, "  9\n$DIMAPOST\n  1\n%s\n", header.DimAPOST);
        fprintf (fp, "  9\n$DIMALT\n 70\n%i\n", header.DimALT);
        fprintf (fp, "  9\n$DIMALTD\n 70\n%i\n", header.DimALTD);
        fprintf (fp, "  9\n$DIMALTF\n 40\n%f\n", header.DimALTF);
        fprintf (fp, "  9\n$DIMLFAC\n 40\n%f\n", header.DimLFAC);
        fprintf (fp, "  9\n$DIMTOFL\n 70\n%i\n", header.DimTOFL);
        fprintf (fp, "  9\n$DIMTVP\n 40\n%f\n", header.DimTVP);
        fprintf (fp, "  9\n$DIMTIX\n 70\n%i\n", header.DimTIX);
        fprintf (fp, "  9\n$DIMSOXD\n 70\n%i\n", header.DimSOXD);
        fprintf (fp, "  9\n$DIMSAH\n 70\n%i\n", header.DimSAH);
        fprintf (fp, "  9\n$DIMBLK1\n  1\n%s\n", header.DimBLK1);
        fprintf (fp, "  9\n$DIMBLK2\n  1\n%s\n", header.DimBLK2);
        */
        ret = dxf_header_read_parse_string (fp, temp_string, "$DIMSTYLE",
                                            &header.DimSTYLE,
                                            TRUE);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$DIMCLRD\n 70\n%i\n", header.DimCLRD);
        fprintf (fp, "  9\n$DIMCLRE\n 70\n%i\n", header.DimCLRE);
        fprintf (fp, "  9\n$DIMCLRT\n 70\n%i\n", header.DimCLRT);
        fprintf (fp, "  9\n$DIMTFAC\n 40\n%f\n", header.DimTFAC);
        */
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMGAP",
                                              TRUE,
                                              1,
                                              &header.DimGAP);
        dxf_return(ret);
        /*
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMJUST\n 70\n%i\n", header.DimJUST);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMSD1\n 70\n%i\n", header.DimSD1);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMSD2\n 70\n%i\n", header.DimSD2);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTOLJ\n 70\n%i\n", header.DimTOLJ);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTZIN\n 70\n%i\n", header.DimTZIN);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTZ\n 70\n%i\n", header.DimALTZ);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTTZ\n 70\n%i\n", header.DimALTTZ);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$DIMFIT\n 70\n%i\n", header.DimFIT);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMUPT\n 70\n%i\n", header.DimUPT);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$DIMUNIT\n 70\n%i\n", header.DimUNIT);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMDEC\n 70\n%i\n", header.DimDEC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTDEC\n 70\n%i\n", header.DimTDEC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTU\n 70\n%i\n", header.DimALTU);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTTD\n 70\n%i\n", header.DimALTTD);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTXSTY\n  7\n%s\n", header.DimTXSTY);
        */
        ret = dxf_header_read_parse_int (fp, temp_string, "$DIMAUNIT",
                                         &header.DimAUNIT,
                                         acad_version_number >= AC1012);
        dxf_return(ret);
    
        ret = dxf_header_read_parse_int (fp, temp_string, "$DIMADEC",
                                         &header.DimADEC,
                                         acad_version_number >= AC1015);
        dxf_return(ret);
        /*
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMALTRND\n 40\n%f\n", header.DimALTRND);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMAZIN\n 70\n%i\n", header.DimAZIN);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMDSEP\n 70\n%i\n", header.DimDSEP);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMATFIT\n 70\n%i\n", header.DimATFIT);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMFRAC\n 70\n%i\n", header.DimFRAC);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLDRBLK\n  1\n%s\n", header.DimLDRBLK);
        */
        ret = dxf_header_read_parse_int (fp, temp_string, "$DIMLUNIT",
                                         &header.DimLUNIT,
                                         acad_version_number >= AC1015);
        dxf_return(ret);
        /*
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLWD\n 70\n%i\n", header.DimLWD);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLWE\n 70\n%i\n", header.DimLWE);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMTMOVE\n 70\n%i\n", header.DimTMOVE);
        */
        ret = dxf_header_read_parse_int (fp, temp_string, "$LUNITS",
                                         &header.LUnits,
                                         TRUE);
        dxf_return(ret);
        
        ret = dxf_header_read_parse_int (fp, temp_string, "$LUPREC",
                                         &header.LUPrec,
                                         TRUE);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$SKETCHINC\n 40\n%f\n", header.Sketchinc);
        fprintf (fp, "  9\n$FILLETRAD\n 40\n%f\n", header.FilletRad);
        */
        ret = dxf_header_read_parse_int (fp, temp_string, "$AUNITS",
                                         &header.AUnits,
                                         TRUE);
        dxf_return(ret);
    
        ret = dxf_header_read_parse_int (fp, temp_string, "$AUPREC",
                                         &header.AUPrec,
                                         TRUE);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$MENU\n  1\n%s\n", header.Menu);
        fprintf (fp, "  9\n$ELEVATION\n 40\n%f\n", header.Elevation);
        fprintf (fp, "  9\n$PELEVATION\n 40\n%f\n", header.PElevation);
        fprintf (fp, "  9\n$THICKNESS\n 40\n%f\n", header.Thickness);
        fprintf (fp, "  9\n$LIMCHECK\n 70\n%i\n", header.LimCheck);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$BLIPMODE\n 70\n%i\n", header.BlipMode);
        fprintf (fp, "  9\n$CHAMFERA\n 40\n%f\n", header.ChamferA);
        fprintf (fp, "  9\n$CHAMFERB\n 40\n%f\n", header.ChamferB);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CHAMFERC\n 40\n%f\n", header.ChamferC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CHAMFERD\n 40\n%f\n", header.ChamferD);
        fprintf (fp, "  9\n$SKPOLY\n 70\n%i\n", header.SKPoly);
        fprintf (fp, "  9\n$TDCREATE\n 40\n%f\n", header.TDCreate);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$TDUCREATE\n 40\n%f\n", header.TDUCreate);
        fprintf (fp, "  9\n$TDUPDATE\n 40\n%f\n", header.TDUpdate);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$TDUUPDATE\n 40\n%f\n", header.TDUUpdate);
        fprintf (fp, "  9\n$TDINDWG\n 40\n%f\n", header.TDInDWG);
        fprintf (fp, "  9\n$TDUSRTIMER\n 40\n%f\n", header.TDUSRTimer);
        fprintf (fp, "  9\n$USRTIMER\n 70\n%i\n", header.USRTimer);
        fprintf (fp, "  9\n$ANGBASE\n 50\n%f\n", header.AngBase);
        fprintf (fp, "  9\n$ANGDIR\n 70\n%i\n", header.AngDir);
        fprintf (fp, "  9\n$PDMODE\n 70\n%i\n", header.PDMode);
        fprintf (fp, "  9\n$PDSIZE\n 40\n%f\n", header.PDSize);
        fprintf (fp, "  9\n$PLINEWID\n 40\n%f\n", header.PLineWid);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$COORDS\n 70\n%i\n", header.Coords);
        fprintf (fp, "  9\n$SPLFRAME\n 70\n%i\n", header.SPLFrame);
        fprintf (fp, "  9\n$SPLINETYPE\n 70\n%i\n", header.SPLineType);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$ATTDIA\n 70\n%i\n", header.AttDia);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$ATTREQ\n 70\n%i\n", header.AttReq);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$HANDLING\n 70\n%i\n", header.Handling);
        */
        ret = dxf_header_read_parse_int (fp, temp_string, "$SPLINESEGS",
                                         &header.SPLineSegs,
                                         TRUE);
        dxf_return(ret);
        
        ret = dxf_header_read_parse_string (fp, temp_string, "$HANDSEED",
                                            &header.HandSeed,
                                            TRUE);
        dxf_return(ret);
    /*
        fprintf (fp, "  9\n$SURFTAB1\n 70\n%i\n", header.SurfTab1);
        fprintf (fp, "  9\n$SURFTAB2\n 70\n%i\n", header.SurfTab2);
        fprintf (fp, "  9\n$SURFTYPE\n 70\n%i\n", header.SurfType);
        fprintf (fp, "  9\n$SURFU\n 70\n%i\n", header.SurfU);
        fprintf (fp, "  9\n$SURFV\n 70\n%i\n", header.SurfV);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSBASE\n  2\n%s\n", header.UCSBase);
        fprintf (fp, "  9\n$UCSNAME\n  2\n%s\n", header.UCSName);
        fprintf (fp, "  9\n$UCSORG\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrg.x0, header.UCSOrg.y0, header.UCSOrg.z0);
        fprintf (fp, "  9\n$UCSXDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSXDir.x0, header.UCSXDir.y0, header.UCSXDir.z0);
        fprintf (fp, "  9\n$UCSYDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSYDir.x0, header.UCSYDir.y0, header.UCSYDir.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORTHOREF\n  2\n%s\n", header.UCSOrthoRef);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORTHOVIEW\n 70\n%i\n", header.UCSOrthoView);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGTOP\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgTop.x0, header.UCSOrgTop.y0, header.UCSOrgTop.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGBOTTOM\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgBottom.x0, header.UCSOrgBottom.y0, header.UCSOrgBottom.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGLEFT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgLeft.x0, header.UCSOrgLeft.y0, header.UCSOrgLeft.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGRIGHT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgRight.x0, header.UCSOrgRight.y0, header.UCSOrgRight.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGFRONT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgFront.x0, header.UCSOrgFront.y0, header.UCSOrgFront.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGBACK\n 10\n%f\n 20\n%f\n 30\n%f\n", header.UCSOrgBack.x0, header.UCSOrgBack.y0, header.UCSOrgBack.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSBASE\n  2\n%s\n", header.PUCSBase);
        fprintf (fp, "  9\n$PUCSNAME\n  2\n%s\n", header.PUCSName);
        fprintf (fp, "  9\n$PUCSORG\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrg.x0, header.PUCSOrg.y0, header.PUCSOrg.z0);
        fprintf (fp, "  9\n$PUCSXDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSXDir.x0, header.PUCSXDir.y0, header.PUCSXDir.z0);
        fprintf (fp, "  9\n$PUCSYDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSYDir.x0, header.PUCSYDir.y0, header.PUCSYDir.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORTHOREF\n  2\n%s\n", header.PUCSOrthoRef);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORTHOVIEW\n 70\n%i\n", header.PUCSOrthoView);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGTOP\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgTop.x0, header.PUCSOrgTop.y0, header.PUCSOrgTop.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGBOTTOM\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgBottom.x0, header.PUCSOrgBottom.y0, header.PUCSOrgBottom.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGLEFT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgLeft.x0, header.PUCSOrgLeft.y0, header.PUCSOrgLeft.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGRIGHT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgRight.x0, header.PUCSOrgRight.y0, header.PUCSOrgRight.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGFRONT\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgFront.x0, header.PUCSOrgFront.y0, header.PUCSOrgFront.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGBACK\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PUCSOrgBack.x0, header.PUCSOrgBack.y0, header.PUCSOrgBack.z0);
        fprintf (fp, "  9\n$USERI1\n 70\n%i\n", header.UserI1);
        fprintf (fp, "  9\n$USERI2\n 70\n%i\n", header.UserI2);
        fprintf (fp, "  9\n$USERI3\n 70\n%i\n", header.UserI3);
        fprintf (fp, "  9\n$USERI4\n 70\n%i\n", header.UserI4);
        fprintf (fp, "  9\n$USERI5\n 70\n%i\n", header.UserI5);
        fprintf (fp, "  9\n$USERR1\n 40\n%f\n", header.UserR1);
        fprintf (fp, "  9\n$USERR2\n 40\n%f\n", header.UserR2);
        fprintf (fp, "  9\n$USERR3\n 40\n%f\n", header.UserR3);
        fprintf (fp, "  9\n$USERR4\n 40\n%f\n", header.UserR4);
        fprintf (fp, "  9\n$USERR5\n 40\n%f\n", header.UserR5);
        fprintf (fp, "  9\n$WORLDVIEW\n 70\n%i\n", header.WorldView);
        fprintf (fp, "  9\n$SHADEDGE\n 70\n%i\n", header.ShadEdge);
        fprintf (fp, "  9\n$SHADEDIF\n 70\n%i\n", header.ShadeDif);
        fprintf (fp, "  9\n$TILEMODE\n 70\n%i\n", header.TileMode);
        fprintf (fp, "  9\n$MAXACTVP\n 70\n%i\n", header.MaxActVP);
        fprintf (fp, "  9\n$PINSBASE\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PInsBase.x0, header.PInsBase.y0, header.PInsBase.z0);
        fprintf (fp, "  9\n$PLIMCHECK\n 70\n%i\n", header.PLimCheck);
        fprintf (fp, "  9\n$PEXTMIN\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PExtMin.x0, header.PExtMin.y0, header.PExtMin.z0);
        fprintf (fp, "  9\n$PEXTMAX\n 10\n%f\n 20\n%f\n 30\n%f\n", header.PExtMax.x0, header.PExtMax.y0, header.PExtMax.z0);
        */
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$PLIMMIN",
                                              TRUE,
                                              2,
                                              &header.PLimMin.x0,
                                              header.PLimMin.y0);
        dxf_return(ret);
    
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$PLIMMAX",
                                              TRUE,
                                              2,
                                              &header.PLimMax.x0,
                                              header.PLimMax.y0);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$UNITMODE\n 70\n%i\n", header.UnitMode);
        fprintf (fp, "  9\n$VISRETAIN\n 70\n%i\n", header.VisRetain);
        fprintf (fp, "  9\n$PLINEGEN\n 70\n%i\n", header.PLineGen);
        fprintf (fp, "  9\n$PSLTSCALE\n 70\n%i\n", header.PSLTScale);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$TREEDEPTH\n 70\n%i\n", header.TreeDepth);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$PICKSTYLE\n 70\n%i\n", header.PickStyle);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLSTYLE\n  2\n%s\n", header.CMLStyle);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLJUST\n 70\n%i\n", header.CMLJust);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLSCALE\n 40\n%f\n", header.CMLScale);
        if (acad_version_number >= AC1014) fprintf (fp, "  9\n$PROXYGRAPHICS\n 70\n%i\n", header.ProxyGraphics);
        if (acad_version_number >= AC1014) fprintf (fp, "  9\n$MEASUREMENT\n 70\n%i\n", header.Measurement);
        if (acad_version_number == AC1012) fprintf (fp, "  9\n$SAVEIMAGES\n 70\n%i\n", header.SaveImages);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$CELWEIGHT\n370\n%i\n", header.CELWeight);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$ENDCAPS\n280\n%i\n", header.EndCaps);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$JOINSTYLE\n280\n%i\n", header.JoinStyle);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$LWDISPLAY\n290\n%i\n", header.LWDisplay);
        */
        ret = dxf_header_read_parse_int (fp, temp_string, "$INSUNITS",
                                         &header.InsUnits,
                                         acad_version_number >= AC1015);
        dxf_return(ret);
        /*
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$HYPERLINKBASE\n  1\n%s\n", header.HyperLinkBase);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$STYLESHEET\n  1\n%s\n", header.StyleSheet);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$XEDIT\n290\n%i\n", header.XEdit);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$CEPSNTYPE\n380\n%i\n", header.CEPSNType);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PSTYLEMODE\n290\n%i\n", header.PStyleMode);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$FINGERPRINTGUID\n  2\n%s\n", header.FingerPrintGUID);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$VERSIONGUID\n  2\n%s\n", header.VersionGUID);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$EXTNAMES\n290\n%i\n", header.ExtNames);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PSVPSCALE\n 40\n%f\n", header.PSVPScale);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$OLESTARTUP\n290\n%i\n", header.OLEStartUp);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$SORTENTS\n280\n%i\n", header.SortEnts);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INDEXCTL\n280\n%i\n", header.IndexCtl);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$HIDETEXT\n280\n%i\n", header.HideText);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$XCLIPFRAME\n290\n%i\n", header.XClipFrame);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$HALOGAP\n280\n%i\n", header.HaloGap);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$OBSCOLOR\n 70\n%i\n", header.ObsColor);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$OBSLTYPE\n280\n%i\n", header.ObsLType);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INTERSECTIONDISPLAY\n280\n%i\n", header.InterSectionDisplay);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INTERSECTIONCOLOR\n 70\n%i\n", header.InterSectionColor);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$DIMASSOC\n280\n%i\n", header.DimASSOC);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$PROJECTNAME\n  1\n%s\n", header.ProjectName);        
*/
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$GRIDUNIT",
                                              acad_version_number >= AC1009,
                                              2,
                                              &header.GridUnit.x0,
                                              &header.GridUnit.y0);
        dxf_return(ret);

        ret = dxf_header_read_parse_int (fp, temp_string, "$GRIDMODE",
                                         &header.GridMode,
                                         acad_version_number >= AC1009);
        dxf_return(ret);
#if DEBUG
        DXF_DEBUG_END
#endif
       return FALSE;
}

/*!
 * \brief Reads the header from a DXF file.
 */
int
dxf_header_read
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        DxfHeader header
                /*!< DXF header to be initialized.\n */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char temp_string[255];
        int n, acad_version_number, ret;

        /* first of all we MUST read the version number */
        dxf_read_scanf (fp, "%i\n%s\n", &n, temp_string);
        ret = dxf_header_read_parse_string (fp, temp_string,
                                            "$ACADVER", &header.AcadVer,
                                            TRUE);
        dxf_return_val_if_fail (ret, FALSE);
        /* turn the acad_version into an integer */
        acad_version_number= acad_version_from_string (header.AcadVer);
    
        /* \FIXME: stores the autocad version as int */
        header._AcadVer = acad_version_number;
    
        /* a loop to read all the header with no particulary order */
        while (!feof(fp->fp))
        {
                /* reads the next header content */
                dxf_read_scanf (fp, "%i\n%s\n", &n, temp_string);
                /* if it is a valid line */
                if (n == 9)
                {
                        /* parses the header content and extract info to the header struct */
                        ret = dxf_read_header_parser(fp, header,
                                                     temp_string,
                                                     acad_version_number);
                        dxf_return_val_if_fail(ret, FALSE);
                        if (ret != FOUND)
                                return FALSE;
                }
                /* or it can be the end of the section */
                else if (n == 0 && strcmp(temp_string, "ENDSEC") == 0)
                {
#if DEBUG
                        fprintf (stderr,
                          (_("[File: %s: line: %d] read_header :: Section Ended.\n")),
                          __FILE__, __LINE__);
#endif
                        return TRUE;
                }        
                else
                {
                        return FALSE;
                }
        }

#if DEBUG
        DXF_DEBUG_END
#endif
        return FALSE;
}

/* EOF */
