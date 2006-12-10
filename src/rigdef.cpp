/*
 * Copyright (C) 1993-2006 Robert & Jeremy Laine
 * See AUTHORS file for a full list of contributors.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "rigdef.h"


/** Constructs a CRigDef object.
 */
CRigDef::CRigDef()
{
    // default values for member variables are set here
    rigID = "Test rig 1";
    foreI  = 5500;    // height of fore triangle
    foreJ  = 2000;    // base of fore triangle
    MHeight = 8000;   // mast height
    MCord = 140;
    MWidth = 70;
    MRakeM = 200;
    MRakeD = 0;
    MRnd = 0;
    MRndPos = 50;
    CSH = 7000;   // cap shroud height
    CSB = 900;
    LSB = 800;
    SPNB = 3;     // number of spreaders
    SPH[1] = 2000;
    SPW[1] = 800;
    SPH[2] = 4000;
    SPW[2] = 600;
    SPH[3] = 6000;
    SPW[3] = 400;
}


/** Assignment operator.
 * 
 * @param copy the rig definition to copy from
 * @return CRigDef&
 */
CRigDef & CRigDef::operator=( const CRigDef &copy )
{
    if (&copy == this)
        return *this;
    // else
    rigID = copy.rigID;
    foreI  = copy.foreI;    // height of fore triangle
    foreJ  = copy.foreJ;    // base of fore triangle
    MHeight = copy.MHeight; // mast height
    MCord = copy.MCord;
    MWidth = copy.MWidth;
    MRakeM = copy.MRakeM;
    MRakeD = copy.MRakeD;
    CSH = copy.CSH;  // outer shroud height
    CSB = copy.CSB;
    LSB = copy.LSB;
    SPNB = copy.SPNB; // number of spreaders
    SPH[0] = copy.SPH[0];
    SPW[0] = copy.SPW[0];
    SPH[1] = copy.SPH[1];
    SPW[1] = copy.SPW[1];
    SPH[2] = copy.SPH[2];
    SPW[2] = copy.SPW[2];
    SPH[3] = copy.SPH[3];
    SPW[3] = copy.SPW[3];
    
    return *this;
}


