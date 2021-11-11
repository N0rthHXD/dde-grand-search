/*
 * Copyright (C) 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     zhangyu<zhangyub@uniontech.com>
 *
 * Maintainer: zhangyu<zhangyub@uniontech.com>
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

#include "text-preview/textview.h"

#include <QLayout>
#include <QStackedWidget>
#include <QPaintEvent>
#include <QMouseEvent>

#include <stubext.h>

#include <gtest/gtest.h>

TEST(TextView, ut_initUI)
{
    TextView tv;
    EXPECT_EQ(tv.layout(), nullptr);
    EXPECT_EQ(tv.m_errLabel, nullptr);
    EXPECT_EQ(tv.m_stackedWidget, nullptr);
    EXPECT_EQ(tv.m_browser, nullptr);

    tv.initUI();
    ASSERT_NE(tv.layout(), nullptr);
    ASSERT_NE(tv.m_errLabel, nullptr);
    ASSERT_NE(tv.m_stackedWidget, nullptr);
    ASSERT_NE(tv.m_browser, nullptr);

    EXPECT_EQ(tv.layout()->contentsMargins(), QMargins(20,0,10,0));
    EXPECT_EQ(tv.m_browser->document()->documentMargin(), 10);
    EXPECT_TRUE(tv.m_browser->isReadOnly());
}

TEST(TextView, ut_setSource)
{
    TextView tv;
    tv.initUI();

    stub_ext::StubExt stub;
    auto openFunc = (bool (*)(QFile *, QIODevice::OpenMode))(bool (QFile::*)(QIODevice::OpenMode))&QFile::open;
    auto readFunc = (QByteArray (QFile::*)(qint64))&QFile::read;
    stub.set_lamda(openFunc,[](QFile *fp, QIODevice::OpenMode){
        return fp->fileName() == QString("/test");
    });
    stub.set_lamda(readFunc,[](){return QByteArray("test");});
    tv.setSource("/test");
    EXPECT_EQ(tv.m_stackedWidget->currentWidget(), tv.m_browser);
    EXPECT_EQ(tv.layout()->contentsMargins(), QMargins(20,0,10,0));
    EXPECT_EQ(tv.m_browser->toPlainText(), QString("test"));

    tv.setSource("/test2");
    EXPECT_EQ(tv.layout()->contentsMargins(), QMargins(10,0,0,0));
    EXPECT_EQ(tv.m_stackedWidget->currentWidget(), (QWidget *)tv.m_errLabel);
}

TEST(TextView, ut_paintEvent)
{
    TextView tv;
    tv.initUI();
    QPaintEvent e(QRect(0,0,10,10));

    EXPECT_NO_FATAL_FAILURE(tv.paintEvent(&e));
}

TEST(PlainTextEdit, ut_mouseMoveEvent)
{
   PlainTextEdit edit;
   QMouseEvent e(QMouseEvent::MouseMove, QPointF(0,0), QPointF(0,0), QPointF(0,0),
                 Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventNotSynthesized);
   EXPECT_NO_FATAL_FAILURE(edit.mouseMoveEvent(&e));
}

