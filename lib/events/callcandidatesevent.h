/******************************************************************************
 * Copyright (C) 2017 Marius Gripsgard <marius@ubports.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include "roomevent.h"
#include <QtCore/QJsonArray>

namespace QMatrixClient
{
    class CallCandidatesEvent: public RoomEvent
    {
        public:
            DEFINE_EVENT_TYPEID("m.call.candidates", CallCandidatesEvent)

            explicit CallCandidatesEvent(const QJsonObject& obj);

            explicit CallCandidatesEvent(const QString& callId,
                                         const QJsonArray& candidates);

            bool isStateEvent() const override { return true; }

            const QJsonArray& candidates() const { return _candidates; }
            const QString& callId() const { return _callId; }
            const int version() const { return _version; }

            QJsonObject toJson() const
            {
                QJsonObject obj;
                obj.insert("call_id", _callId);
                obj.insert("version", _version);
                obj.insert("candidates", _candidates);
                return obj;
            }

        private:
            QJsonArray _candidates;
            QString _callId;
            int _version;
    };

    REGISTER_EVENT_TYPE(CallCandidatesEvent)
    DEFINE_EVENTTYPE_ALIAS(CallCandidates, CallCandidatesEvent)
}
