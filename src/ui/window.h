#include <QMainWindow>
#include <QLabel>

class GridWidget;
class InfoBar;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void setupUi();

    GridWidget *m_gridWidget = nullptr;
    InfoBar *m_infoBar = nullptr;
};