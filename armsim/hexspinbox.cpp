#include "hexspinbox.h"

HexSpinBox::HexSpinBox(bool only16Bits, QWidget *parent) : QSpinBox(parent), m_only16Bits(only16Bits)
{
    setPrefix("0x");
    setDisplayIntegerBase(16);
    if (only16Bits)
        setRange(0, 0xFFFF);
    else
        setRange(INT_MIN, INT_MAX);
}

QValidator::State HexSpinBox::validate(QString &input, int &pos) const
{
    QString copy(input);
    if (copy.startsWith("0x"))
        copy.remove(0, 2);
    pos -= copy.size() - copy.trimmed().size();
    copy = copy.trimmed();
    if (copy.isEmpty())
        return QValidator::Intermediate;
    input = QString("0x") + copy.toUpper();
    bool okay;
    unsigned int val = copy.toUInt(&okay, 16);
    if (!okay || (m_only16Bits && val > 0xFFFF))
        return QValidator::Invalid;
    return QValidator::Acceptable;
}
