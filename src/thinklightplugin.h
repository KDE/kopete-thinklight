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
#ifndef THINKLIGHTPLUGIN_H
#define THINKLIGHTPLUGIN_H

#include <kopete/kopeteplugin.h>

#include <QTimer>
#include <QProcess>

/**
 * @author Bernhard Beschow <bbeschow @ cs.tu-berlin.de>
 *
 * @short Kopete Thinklight Plugin.
 */
class ThinklightPlugin : public Kopete::Plugin
{
	Q_OBJECT
public:
	ThinklightPlugin( QObject *parent, const QStringList &args );

protected slots:
	/**
	 * @short Starts flashing thinklight on Kopete::ChatSessionManager::aboutToReceive() events.
	 */
	void handleEvent();

	/**
	 * @short Toggles Thinkpad light on or off.
	 */
	void toggle();

	/**
	 * @short Re-read plugin configuration and immediately apply changes.
	 */
	void settingsChanged();

	/**
	 * @short Check if initialization script finished successfully.
	 */
	void initFinished( int exitCode, QProcess::ExitStatus exitStatus );

	/**
	 * @short Notify user about error.
	 */
	void initError( QProcess::ProcessError error );

private:
	QTimer m_timer;
	int m_toggles;

	QProcess m_initProcess;

	static ThinklightPlugin *s_pPlugin;
};

#endif
