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
#include "thinklightpreferences.h"

#include "kopete_thinklight.h"

#include <kgenericfactory.h>

K_PLUGIN_FACTORY( ThinklightPreferencesFactory, registerPlugin<ThinklightPreferences>(); )
K_EXPORT_PLUGIN( ThinklightPreferencesFactory( "kcm_kopete_thinklight" ) )

ThinklightPreferences::ThinklightPreferences( QWidget *parent, const QVariantList &args ) :
	KCModule( ThinklightPreferencesFactory::componentData(), parent, args )
{
	setupUi( this );

	addConfig( ThinklightKcfg::self(), this );
	ThinklightKcfg::self()->readConfig();
	load();
}


