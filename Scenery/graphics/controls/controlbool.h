#ifndef CONTROLBOOL_H
#define CONTROLBOOL_H

#include <QCheckBox>

class ControlBool : public QCheckBox
{
    Q_OBJECT
public:
    explicit ControlBool(bool &data);

private:
    bool &data;

public slots:
    void slotChange();

};

#endif // CONTROLBOOL_H
