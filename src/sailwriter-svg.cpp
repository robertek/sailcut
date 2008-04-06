/*
 * Copyright (C) 1993-2008 Robert & Jeremy Laine
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

// for HAVE_QSVGGENERATOR
#include "sailcutqt.h"

#include "sailwriter-svg.h"
#include "sailprinter.h"
#ifdef HAVE_QSVGGENERATOR
#include <QSvgGenerator>
#endif

/** Write sail to SVG format.
 *
 * @param filename the file to write to
 */
void CSailSvgWriter::write(const CPanelGroup &sail, const QString &filename) const
{
#ifdef HAVE_QSVGGENERATOR
    // SVG generator
    QSvgGenerator generator;
    generator.setFileName(filename);

    CTextPainter painter(&generator);
    CSailDrawingPrinter(sail, false).print(&painter, 0);
#endif
}
