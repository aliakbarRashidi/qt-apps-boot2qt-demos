/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of Qt for Device Creation.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
import QtQuick 2.0

Rectangle {
    id: root
    height: 50
    signal urlAccepted(string text)
    color: "#cc222222"
    Behavior on opacity { NumberAnimation{} }
    onOpacityChanged: {
        if (opacity == 1)
            urlInput.focus = true
        else if (opacity == 0)
            urlInput.focus = false
    }

    Keys.onEscapePressed: root.opacity = 0

    MouseArea {
        anchors.fill: parent
        onClicked: root.opacity = 0
    }

    Text {
        anchors.bottom: urlBar.top
        anchors.left: urlBar.left
        anchors.bottomMargin: 8
        text: "Enter URL"
        color: "white"
        font.pixelSize: 20
    }

    BorderImage {
        id: urlBar
        source: "images/ControlBar.png"
        border.top: 12
        border.bottom: 12
        border.left: 12
        border.right: 12
        height: 70
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -170
        width: 600

        Rectangle {
            anchors.fill: parent
            anchors.margins: 16
            color: "#66ffffff"
            border.color: "#bbffffff"
            radius: 2
            antialiasing: true

            TextInput {
                id: urlInput
                selectionColor: "#aaffffff"
                selectedTextColor: "black"
                selectByMouse: true
                anchors.fill: parent
                anchors.margins: 5
                font.pixelSize: 24
                color: "black"
                text: "http://"
                onAccepted: root.urlAccepted(urlInput.text);

            }
        }
    }

//    Rectangle {
//        anchors.right: urlBar.left
//        anchors.rightMargin: 32
//        anchors.verticalCenter: urlBar.verticalCenter
//        height: 70
//        width: 70
//        color: "gray"
//        MouseArea {
//            anchors.fill: parent
//            onClicked: { urlInput.text = ""; urlInput.paste(); }
//        }
//    }
}
