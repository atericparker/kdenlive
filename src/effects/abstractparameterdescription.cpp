/*
Copyright (C) 2012  Till Theato <root@ttill.de>
This file is part of kdenlive. See www.kdenlive.org.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
*/

#include "abstractparameterdescription.h"
#include <mlt++/Mlt.h>
#include <QDomElement>
#include <QString>
#include <QLocale>
#include <KLocale>


AbstractParameterDescription::AbstractParameterDescription(ParameterType type, QDomElement parameter, QLocale locale) :
    m_type(type),
    m_valid(true)
{
    m_name = parameter.attribute("name");

    m_displayNameOrig = m_name;
    QDomElement displayNameElement = parameter.firstChildElement("name");
    if (!displayNameElement.isNull()) {
        m_displayNameOrig = displayNameElement.text().simplified().toUtf8().constData();
    }
    m_displayName = i18n(m_displayNameOrig.toUtf8());

    m_commentOrig = QString();
    QDomElement commentElement = parameter.firstChildElement("comment");
    if (!commentElement.isNull()) {
        m_commentOrig = commentElement.text().simplified().toUtf8().constData();
    }
    m_comment = i18n(m_commentOrig.toUtf8());
}

AbstractParameterDescription::AbstractParameterDescription(ParameterType type, Mlt::Properties& properties, QLocale locale) :
    m_type(type),
    m_valid(true)
{
    m_name = properties.get("identifier");
    m_displayNameOrig = properties.get("title");
    m_displayName = i18n(m_displayNameOrig.toUtf8());

    m_commentOrig = properties.get("description");
    m_comment = i18n(m_commentOrig.toUtf8());
}


AbstractParameterDescription::~AbstractParameterDescription()
{
}

QString AbstractParameterDescription::getName() const
{
    return m_name;
}

ParameterType AbstractParameterDescription::getType() const
{
    return m_type;
}

QString AbstractParameterDescription::getDisplayName() const
{
    return m_displayName;
}

QString AbstractParameterDescription::getComment() const
{
    return m_comment;
}

bool AbstractParameterDescription::isValid() const
{
    return m_valid;
}
