/***************************************************************************
 *   Copyright (C) 2009 - 2013 by Artem 'DOOMer' Galichkin                 *
 *   doomer3d@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SCREENGRAB_H
#define SCREENGRAB_H

#ifndef STR_PROC
#define STR_PROC "screengrab-qt"
#endif

#include "config.h"
#include "regionselect.h"

#include "modulemanager.h"

#include "ui/mainwindow.h"

#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <QClipboard>
#include <QTime>
#include <QByteArray>
#include <QRect>
#include <QProcess>
#include <QX11Info>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <QDebug>

struct StateNotifyMessage {
    QString header;
    QString message;

    StateNotifyMessage()
    {
        header = "";
        message = "";
    };

    StateNotifyMessage(QString h, QString m)
    {
        header = h;
        message = m;
    };
};

class Core : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    void coreQuit();
    void setScreen();

    void screenShot(bool first = false);
    void autoSave();

public:
    static Core* instance();
    ~Core();

    void initWindow(const QString& ipcMessage = QString());


    void sleep(int msec = 350);
    static QString getVersionPrintable();

    QPixmap* getPixmap();
    QByteArray getScreen();

    void updatePixmap();
    QString getTempFilename(const QString& format);
    void killTempFile();
    bool writeScreen(QString& fileName, QString& format, bool tmpScreen = false);
    void copyScreen();
    void openInExtViewer();

    ModuleManager* modules();
    void addCmdLineOption(const QCommandLineOption& option);
    bool checkCmdLineOption(const QCommandLineOption& option);
    bool checkCmdLineOptions(const QStringList& options);
    void processCmdLineOpts(const QStringList& arguments);

    bool runAsMinimized();

    QString getSaveFilePath(QString format);
    QString getDateTimeFileName();
    Config* config();

private:
    Core();
    Core(const Core &);
    Core& operator=(const Core &);

    static Core *corePtr;

    void checkAutoSave(bool first = false);

    void getActiveWindow();

    bool checkExsistFile(QString path);
    QString copyFileNameToCliipboard(QString file);
    QPixmap *_pixelMap; // pixel map
    RegionSelect *_selector; // region grabber widget
    QRect _lastSelectedArea;

    QCommandLineParser _cmdLine;
    ModuleManager _modules;
    QString _tempFilename;
    Config *_conf;
    MainWindow *_wnd;

    bool _hided;
    bool _firstScreen;

    QList<QCommandLineOption> _screenTypeOpts;

private Q_SLOTS:
    void regionGrabbed(bool grabbed);
    void closeExtViewer(int exitCode, QProcess::ExitStatus exitStatus);

};

#endif // SCREENGRAB_H
