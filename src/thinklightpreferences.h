/*
 * Copyright (C) 2006 Bernhard Beschow <bbeschow @ cs.tu-berlin.de>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */
#ifndef THINKLIGHTPREFERENCES_H
#define THINKLIGHTPREFERENCES_H

#include <kcmodule.h>
#include "ui_thinklightpreferencesui.h"

/**
 * @short Preferences KCModule for ThinklightPlugin for Kopete.
 *
 * @author Bernhard Beschow
 */
class ThinklightPreferences : public KCModule, private Ui::ThinklightPreferencesUI
{
	Q_OBJECT
public:
	ThinklightPreferences( QWidget *parent = 0, const QVariantList &args = QVariantList() );
};

#endif
