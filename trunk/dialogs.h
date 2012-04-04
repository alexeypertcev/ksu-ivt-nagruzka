#ifndef MESSAGEDIALOGS_H
#define MESSAGEDIALOGS_H

#include <QDialog>

namespace Ui {
    class MessageDialog;
}

class MessageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MessageDialog(QWidget *parent = 0);
    ~MessageDialog();
    bool setMessage(QString message);
private:
    Ui::MessageDialog *ui;
};

#endif // MESSAGEDIALOGS_H
