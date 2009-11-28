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
#include "thinklightplugin.h"

#include "kopete_thinklight.h"

#include <kopete/kopetechatsessionmanager.h>
#include <kopete/kopeteinfoevent.h>

#include <kgenericfactory.h>

#include <QFileInfo>

ThinklightPlugin *ThinklightPlugin::s_pPlugin = 0;

typedef KGenericFactory<ThinklightPlugin> ThinkLightPluginFactory;
K_EXPORT_COMPONENT_FACTORY( kopete_thinklight, ThinkLightPluginFactory( "kopete_thinklight" )  )

ThinklightPlugin::ThinklightPlugin( QObject *parent, const QStringList & /* args */ ) :
	Kopete::Plugin( ThinkLightPluginFactory::componentData(), parent ),
	m_toggles( 0 ),
	m_initProcess( this )
{
	if ( s_pPlugin != 0 )
		return;

	s_pPlugin = this;

	connect( Kopete::ChatSessionManager::self() , SIGNAL( aboutToReceive( Kopete::Message & ) ) , this, SLOT( handleEvent() ) );

	connect( this , SIGNAL( settingsChanged() ) , this , SLOT( settingsChanged() ) );

	connect( &m_timer, SIGNAL( timeout() ), SLOT( toggle() ) );

	connect( &m_initProcess, SIGNAL( finished( int, QProcess::ExitStatus ) ), SLOT( initFinished( int, QProcess::ExitStatus ) ) );
	connect( &m_initProcess, SIGNAL( error( QProcess::ProcessError ) ), SLOT( initError( QProcess::ProcessError ) ) );

	m_initProcess.start( ThinklightKcfg::self()->initScript() );
}

void ThinklightPlugin::settingsChanged()
{
	ThinklightKcfg::self()->readConfig();

	// Apply duration changes
	if ( m_timer.isActive() )
		m_timer.setInterval( ThinklightKcfg::self()->duration() );

	// confirm by flashing the thinklight
	handleEvent();
}

void ThinklightPlugin::initFinished( int exitCode, QProcess::ExitStatus exitStatus )
{
	if ( !QFileInfo( ThinklightKcfg::self()->path() ).exists() )
	{
		Kopete::InfoEvent *pEvent = new Kopete::InfoEvent();
		pEvent->setText( i18n( "%1 does not exist. If you have a Thinkpad laptop, please do a \"modprobe ibm_acpi\" as root.", ThinklightKcfg::self()->path() ) );
		pEvent->sendEvent();
	}
	else if ( !QFileInfo( ThinklightKcfg::self()->path() ).isWritable() )
	{
		Kopete::InfoEvent *pEvent = new Kopete::InfoEvent();
		pEvent->setText( i18n( "%1 cannot be written to. Thinklight plugin could not initialize correctly. Please contact your system administrator.", ThinklightKcfg::self()->path() ) );
		pEvent->sendEvent();
	}
}

void ThinklightPlugin::initError( QProcess::ProcessError error )
{
	Kopete::InfoEvent *pEvent = new Kopete::InfoEvent();

	switch ( error )
	{
	case QProcess::FailedToStart:
		pEvent->setText( i18n( "The program \"kopete_thinklght_fixpermissons\" failed to start. Please contact your system administrator." ) );
		break;
	default:
		pEvent->setText( i18n( "The program \"kopete_thinklght_fixpermissons\" failed with error %1. Please contact your system administrator.", error ) );
		break;
	}

	pEvent->sendEvent();
}

void ThinklightPlugin::handleEvent()
{
	m_toggles += 2 * ThinklightKcfg::self()->numFlashes();

	if ( !m_timer.isActive() )
		m_timer.start( ThinklightKcfg::self()->duration() );

	toggle();
}

void ThinklightPlugin::toggle()
{
	QFile lightFile( ThinklightKcfg::self()->path() );
	lightFile.open( QFile::ReadWrite );

	QString str = QTextStream( &lightFile ).readLine();

	if ( str.indexOf( "on" ) != -1 )
		lightFile.write( "off\n", 4 );
	else if ( str.indexOf( "off" ) != -1 )
		lightFile.write( "on\n", 3 );

	m_toggles--;

	if ( m_toggles == 0 )
		m_timer.stop();
}

#include "thinklightplugin.moc"
