/*
 * Copyright (C) 2002-2006 Jeremy Laine
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

#include <geocpp/subspace.h>

/*******************************************************
 
               Construction / destruction
 
********************************************************/

/** Constructs a CSubSpace of the specified dimension.
 *
 * @param dim_space dimension of the Euclidian vector space we are working in
 * @param dim_sub dimension of the subspace to be created
 */
CSubSpace::CSubSpace(unsigned int dim_space, unsigned int dim_sub)
        : p(dim_space)
{
    m = CMatrix( dim_sub , p.getdim() );
}


/** Constructs a CSubSpace from a point and either the equations or
 * a base of the subspace.
 *
 * @param pi a point in the subspace
 * @param mi a matrix containing the equations or the base of the subspace
 * @param createflags specifies whether we were given the equations or the base of the subspace
 */
CSubSpace::CSubSpace(const CVector &pi, const CMatrix &mi, subspaceflags_t createflags)
        : p(pi)
{
    switch ( createflags )
    {
    case GEOCPP_FROM_EQS:
        // equations are given in lines
        if ( (mi.getnrow() > 0) && (mi.getncol() != pi.getdim()) )
            throw CException("CSubSpace::CSubSpace(p,m,GEOCPP_FROM_EQS) : dimension mismatch between p and m");

        m = mi;
        break;
    case GEOCPP_FROM_BASE:
        // base is given in column format
        if ( (mi.getncol() > 0) && (mi.getnrow() != pi.getdim()) )
            throw CException("CSubSpace::CSubSpace(p,m,GEOCPP_FROM_BASE) : dimension mismatch between p and m");

        m = mi.transp().kern(pi.getdim()).transp();
        break;
    default:
        throw CException("CSubSpace::CSubspace(p,m,createflags) : unknown creation flags");
    }
}


/** Test whether the CSubSpace contains a given point.
 */
bool CSubSpace::contains(const CVector &point)
{
    CVector prod = m*(point-p);

    return ( prod.norm() < EPS );
}


/** Performs the intersection of two CSubSpace objects.
 */
CSubSpace CSubSpace::intersect(const CSubSpace &h2) const
{
    if ( (getdim() < 0) || (h2.getdim() < 0) )
        return CSubSpace(0 , 0);

    if ( p.getdim() != h2.p.getdim() )
        throw CException("CSubSpace::intersect : dimension mismatch on points");

    CVector b1 = m*p;
    CVector b2 = h2.m*h2.p;
    CVector bb( m.getnrow() + h2.m.getnrow() );
    CMatrix mm( m.getnrow() + h2.m.getnrow(), p.getdim() );
    for ( unsigned int i = 0 ; i < mm.getnrow() ; i++ )
    {
        if ( i < m.getnrow() )
        {
            for( unsigned int j = 0 ; j < mm.getncol() ; j++ )
                mm(i,j) = m(i,j);
            bb.m_data[i] = b1.m_data[i];
        }
        else
        {
            for( unsigned int j = 0 ; j < mm.getncol() ; j++ )
                mm(i,j) = h2.m(i-m.getnrow() , j);
            bb.m_data[i] = b2.m_data[i-m.getnrow()];
        }
    }
    //cout << "mm" << endl << mm << endl;
    //cout << "bb" << endl << bb << endl;

    return  mm.solve(bb);
}


/*******************************************************
 
                      Other functions
 
********************************************************/

/** Outputs a CMatrix to a stream.
 */
ostream& operator<< (ostream &o, const CMatrix &m)
{
    o << "[";
    for ( unsigned int i = 0 ; i < m.getnrow() ; i++ )
    {
        o << m.row(i);
        if ( i != m.getnrow()-1 )
            o << endl;
    }
    o << "]";
    return o;
}


/** Outputs the definition of a CSubSpace to a stream.
 */
ostream& operator<< (ostream &o, const CSubSpace &h)
{
    o << "--------------------------------" << endl;
    o << "     subspace : ";
    switch (h.getdim())
    {
    case -1:
        o << "empty" << endl;
        break;
    case 0:
        o << "point" << endl;
        break;
    case 1:
        o << "line" << endl;
        break;
    case 2:
        o << "plane" << endl;
        break;
    default:
        o << "dim=" << h.getdim() << endl;
    }
    o << "--------------------------------" << endl;
    if ( h.getdim() >= 0 )
    {
        o << "point:" << endl << h.getp() << endl;
        if (h.getdim()>0)
        {
            o << "------" << endl;
            o << "base vectors (in columns): " << endl << h.getm().kern(h.getp().getdim()) << endl << "------" << endl;
            o << "equations (coeffs in lines): " << endl << h.getm() << endl;
        }
        o << "--------------------------------" << endl;
    }
    return o;
}

