/*
 * Copyright (C) 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     wangchunlin<wangchunlin@uniontech.com>
 *
 * Maintainer: wangchunlin<wangchunlin@uniontech.com>
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
#ifndef MAINWINDOW_P_H
#define MAINWINDOW_P_H

#include "mainwindow.h"

#include <DRegionMonitor>

#include <QWidget>

class EntranceWidget;
class ExhibitionWidget;
DWIDGET_BEGIN_NAMESPACE
class DLabel;
DWIDGET_END_NAMESPACE
class QVBoxLayout;
class MainWindowPrivate
{
public:
    explicit MainWindowPrivate(MainWindow *parent);

    MainWindow *q_p = nullptr;
    EntranceWidget *m_entranceWidget = nullptr;
    ExhibitionWidget *m_exhibitionWidget = nullptr;
    Dtk::Widget::DLabel *m_searchNoContentWidget = nullptr;
    Dtk::Gui::DRegionMonitor *m_regionMonitor = nullptr;
    QVBoxLayout *m_mainLayout = nullptr;

    bool m_showMenu = false;
    QRect m_menuRect;           // 菜单显示区域，用于判断鼠标点击位置是否在菜单区域内
};

#endif // MAINWINDOW_P_H
