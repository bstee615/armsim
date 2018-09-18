/* hexspinbox.h
 * Source: https://stackoverflow.com/questions/26581444/qspinbox-with-unsigned-int-for-hex-input
 **/

#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QSpinBox>
#include <QKeyEvent>

class HexSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    HexSpinBox(bool only16Bits, QWidget *parent = 0);
    unsigned int hexValue() const
    {
        return u(value());
    }
    void setHexValue(unsigned int value)
    {
        setValue(i(value));
    }

    void keyPressEvent(QKeyEvent *event);

protected:
    QString textFromValue(int value) const
    {
        return QString::number(u(value), 16).toUpper();
    }
    int valueFromText(const QString &text) const
    {
        return i(text.toUInt(0, 16));
    }
    QValidator::State validate(QString &input, int &pos) const;

private:
    bool m_only16Bits;
    inline unsigned int u(int i) const
    {
        return *reinterpret_cast<unsigned int *>(&i);
    }
    inline int i(unsigned int u) const
    {
        return *reinterpret_cast<int *>(&u);
    }

signals:
    void returnPressed();

};


#endif // HEXSPINBOX_H
