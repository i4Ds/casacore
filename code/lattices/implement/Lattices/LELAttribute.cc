//# LELAttribute.cc:  this defines LELAttribute.cc
//# Copyright (C) 1997,1998
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id$

#include <trial/Lattices/LELAttribute.h>
#include <aips/Utilities/Assert.h>
#include <aips/Exceptions/Error.h> 


LELAttribute::LELAttribute()
: isScalar_p(True)
{}

LELAttribute::LELAttribute(const IPosition& shape,
			   const IPosition& tileShape,
			   const LatticeCoordinates& coordinates)
: isScalar_p  (False),
  shape_p     (shape),
  tileShape_p (tileShape),
  coords_p    (coordinates)
{}

LELAttribute::LELAttribute(const LELAttribute& other)
: isScalar_p  (other.isScalar_p),
  shape_p     (other.shape_p),
  tileShape_p (other.tileShape_p),
  coords_p    (other.coords_p)
{}

LELAttribute::LELAttribute(const LELAttribute& leftAttr,
			   const LELAttribute& rightAttr)
{
   isScalar_p = False;
   if (leftAttr.isScalar()) {
      if (rightAttr.isScalar()) {
         isScalar_p = True;
      } else {
         shape_p     = rightAttr.shape();
	 tileShape_p = rightAttr.tileShape();
	 coords_p    = rightAttr.coordinates();
      }
   } else {
      shape_p     = leftAttr.shape();
      tileShape_p = leftAttr.tileShape();
      coords_p    = leftAttr.coordinates();
      if (!rightAttr.isScalar()) {
         AlwaysAssert (leftAttr.shape().isEqual(rightAttr.shape()), AipsError);
	 if (rightAttr.coordinates().hasCoordinates()) {
	    if (coords_p.hasCoordinates()) {
		AlwaysAssert (leftAttr.coordinates().conform
			      (rightAttr.coordinates()), AipsError);
	    } else {
		coords_p = rightAttr.coordinates();
	    }
	 } 
      }
   }
}
                    
LELAttribute::~LELAttribute()
{}


LELAttribute& LELAttribute::operator= (const LELAttribute& other)
{
    if (this != &other) {
       isScalar_p  = other.isScalar_p;
       shape_p.resize (other.shape_p.nelements());
       tileShape_p.resize (other.tileShape_p.nelements());
       shape_p     = other.shape_p;
       tileShape_p = other.tileShape_p;
       coords_p    = other.coords_p;
    }
    return *this;
}
