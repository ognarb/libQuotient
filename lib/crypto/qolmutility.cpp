// SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
//
// SPDX-License-Identifier: LGPL-2.1-or-later

#ifdef Quotient_E2EE_ENABLED
#include "crypto/qolmutility.h"
#include "olm/olm.h"

using namespace Quotient;

// Convert olm error to enum
QOlmError lastError(OlmUtility *utility) {
    const std::string error_raw = olm_utility_last_error(utility);

    return fromString(error_raw);
}

QOlmUtility::QOlmUtility()
{
    auto utility = new uint8_t[olm_utility_size()];
    m_utility = olm_utility(utility);
}

QOlmUtility::~QOlmUtility()
{
    olm_clear_utility(m_utility);
    delete[](reinterpret_cast<uint8_t *>(m_utility));
}

QString QOlmUtility::sha256Bytes(const QByteArray &inputBuf) const
{
    const auto outputLen = olm_sha256_length(m_utility);
    QByteArray outputBuf(outputLen, '0');
    olm_sha256(m_utility, inputBuf.data(), inputBuf.length(),
            outputBuf.data(), outputBuf.length());

    return QString::fromUtf8(outputBuf);
}

QString QOlmUtility::sha256Utf8Msg(const QString &message) const
{
    return sha256Bytes(message.toUtf8());
}

std::variant<bool, QOlmError> QOlmUtility::ed25519Verify(const QByteArray &key,
        const QByteArray &message, QByteArray &signature)
{
    const auto error = olm_ed25519_verify(m_utility, key.data(), key.length(),
            message.data(), message.length(), signature.data(), signature.length());

    if (error == olm_error()) {
        return lastError(m_utility);
    }
    return error == 0;
}


#endif