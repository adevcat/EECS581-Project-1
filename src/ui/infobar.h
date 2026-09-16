#include <QLabel>

class InfoBar : public QLabel
{
    Q_OBJECT

public:
    explicit InfoBar(QWidget *parent = nullptr);

    void setMineCount(int count);
    void setTime(int seconds);

private:
    int m_mineCount = 0;
    int m_time = 0;

    void updateText();
};