/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DFONTINFO_H
#define DFONTINFO_H

#include <QObject>
#include <QMap>

#include <ft2build.h>
#include FT_FREETYPE_H

struct DFontInfo {
    QString filePath;
    QString familyName;
    QString styleName;
    QString type;
    QString version;
    QString copyright;
    QString description;
    QString sysVersion;
    //new font info
    QString fullname;
    QString psname;
    QString trademark;


    bool isInstalled {false};
    bool isError {false};;
    bool isSystemFont {true};  // Default is system font

    bool operator==(const DFontInfo &info)
    {
        return info.familyName == familyName && info.styleName == styleName;
    }

    QString toString() const
    {
        return "FontInfo : " + familyName + ", " + styleName + ", psname = " + psname + ", trademark = " + trademark
               + ", fullname = " + fullname;
    }
};

class DFontInfoManager : public QObject
{
    Q_OBJECT

public:
    static DFontInfoManager *instance();
    DFontInfoManager(QObject *parent = nullptr);
    ~DFontInfoManager();

    void refreshList();
    QStringList getAllFontPath() const;
    QStringList getAllChineseFontPath() const;
    QStringList getAllMonoSpaceFontPath() const;
    QString getFontType(const QString &filePath);
    DFontInfo getFontInfo(const QString &filePath, bool force = true);
    bool isFontInstalled(DFontInfo data);

private:
    QMap<QString, DFontInfo> m_fontInfoMap;
    FT_Library m_library;
    FT_Face m_face;
};

#endif
