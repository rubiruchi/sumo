/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2006-2019 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    MFXIconComboBox.cpp
/// @author  Jakob Erdmann
/// @date    2018-12-19
/// @version $Id$
///
//
/****************************************************************************/

/* =========================================================================
 * included modules
 * ======================================================================= */
#include <config.h>

#ifdef WIN32
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#endif

#include "MFXIconComboBox.h"


#define SIDE_SPACING             6    // Left or right spacing between items
#define ICON_SPACING             4    // Spacing between icon and label

FXIMPLEMENT(MFXListItem, FXListItem, nullptr, 0)
FXIMPLEMENT(MFXIconComboBox, FXComboBox, nullptr, 0)

void MFXListItem::draw(const FXList* list, FXDC& dc, FXint xx, FXint yy, FXint ww, FXint hh) {
    // almost the same code as FXListItem::draw except for using custom background color
    register FXFont* font = list->getFont();
    register FXint ih = 0, th = 0;
    if (icon) {
        ih = icon->getHeight();
    }
    if (!label.empty()) {
        th = font->getFontHeight();
    }
    if (isSelected()) {
        dc.setForeground(list->getSelBackColor());
    } else if (bgColor != FXRGBA(0, 0, 0, 0)) {
        dc.setForeground(bgColor);     // custom code here
    } else {
        dc.setForeground(list->getBackColor());
    }
    dc.fillRectangle(xx, yy, ww, hh);
    if (hasFocus()) {
        dc.drawFocusRectangle(xx + 1, yy + 1, ww - 2, hh - 2);
    }
    xx += SIDE_SPACING / 2;
    if (icon) {
        dc.drawIcon(icon, xx, yy + (hh - ih) / 2);
        xx += ICON_SPACING + icon->getWidth();
    }
    if (!label.empty()) {
        dc.setFont(font);
        if (!isEnabled()) {
            dc.setForeground(makeShadowColor(list->getBackColor()));
        } else if (isSelected()) {
            dc.setForeground(list->getSelTextColor());
        } else {
            dc.setForeground(list->getTextColor());
        }
        dc.drawText(xx, yy + (hh - th) / 2 + font->getFontAscent(), label);
    }
}


MFXIconComboBox::MFXIconComboBox(
    FXComposite* p, FXint cols, FXObject* tgt,
    FXSelector sel, FXuint opts,
    FXint x, FXint y, FXint w, FXint h,
    FXint pl, FXint pr, FXint pt, FXint pb):
    FXComboBox(p, cols, tgt, sel, opts, x, y, w, h, pl, pr, pt, pb)
{}

FXint
MFXIconComboBox::appendIconItem(const FXString& text, FXIcon* icon, FXColor bgColor,  void* ptr) {
    FXint index = list->appendItem(new MFXListItem(text, icon, bgColor, ptr));
    if (isItemCurrent(getNumItems() - 1)) {
        field->setText(text);
    }
    recalc();
    return index;
}

