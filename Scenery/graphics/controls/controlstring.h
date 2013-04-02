#ifndef CONTROLSTRING_H
#define CONTROLSTRING_H

#include <QComboBox>
#include <QStringList>

class ControlString : public QComboBox
{
    Q_OBJECT
public:
    explicit ControlString(QString &string, QStringList list);
    
private:
    QString &string;
    
public slots:
    void slotChange();

};

#endif // CONTROLSTRING_H
