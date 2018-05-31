/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt 3D Studio Demos.
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

#ifndef UTILS_H
#define UTILS_H

#include "demodatapoint.h"

#include <QtKnx/QKnxAddress>
#include <QtKnx/QKnxNpduFactory>

QKnxTunnelFrame createRequestFrame(const QKnxAddress &address, const QKnxNpdu &npdu,
    quint8 ctrl = 0xac, quint8 extCtrl = 0xe0)
{
    QKnxTunnelFrame frame(QKnxTunnelFrame::MessageCode::DataRequest);
    frame.setControlField(QKnxControlField(ctrl));
    frame.setExtendedControlField(QKnxExtendedControlField(extCtrl));
    frame.setSourceAddress({ QKnxAddress::Type::Group, 0 });
    frame.setDestinationAddress(address);
    frame.setNpdu(npdu);
    return frame;
}

void sendGroupValueWrite(QmlKnxTunnel &tunnel, const QKnxAddress &address,
    const QByteArray &data, quint8 ctrl = 0xa4, quint8 extCtrl = 0xe0)
{
    tunnel.sendTunnelFrame(createRequestFrame(address,
        QKnxNpduFactory::Multicast::createGroupValueWriteNpdu(data), ctrl, extCtrl));
}

void sendColorLedGroupValueWriteFrames(QmlKnxTunnel &tunnel, const DemoColorLed *const dpt)
{
    if (dpt) {
        tunnel.sendTunnelFrame(createRequestFrame(QKnxAddress::createGroup(0, 0, 12),
            QKnxNpduFactory::Multicast::createGroupValueWriteNpdu(dpt->redBytes())));

        tunnel.sendTunnelFrame(createRequestFrame(QKnxAddress::createGroup(0, 0, 13),
            QKnxNpduFactory::Multicast::createGroupValueWriteNpdu(dpt->greenBytes())));

        tunnel.sendTunnelFrame(createRequestFrame(QKnxAddress::createGroup(0, 0, 14),
            QKnxNpduFactory::Multicast::createGroupValueWriteNpdu(dpt->blueBytes())));
    }
}

void initBoard(EtsDevelopmentBoard &board, QmlKnxTunnel &tunnel)
{
    auto npdu = QKnxNpduFactory::Multicast::createGroupValueReadNpdu();
    for (int i = 1; i <= board.size(); ++i) {
        if (i >= 9 && i <= 12)
            continue; // skip red leds readings because they are not indicating the state!
        if ((i == 7) || (i == 8) || (i == 16))
            continue; // skip checking blinds state

        if (QKnxAddress::createGroup(0, 0, 12) == board.getAddress(i)) {
            tunnel.sendTunnelFrame(createRequestFrame(QKnxAddress::createGroup(0, 0, 12), npdu));
            tunnel.sendTunnelFrame(createRequestFrame(QKnxAddress::createGroup(0, 0, 13), npdu));
            tunnel.sendTunnelFrame(createRequestFrame(QKnxAddress::createGroup(0, 0, 14), npdu));
        } else {
            tunnel.sendTunnelFrame(createRequestFrame(board.getAddress(i), npdu, 0xa4));
        }
    }
}

#endif
