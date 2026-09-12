#include <QMainWindow>

class GridWidget;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

private:
    void setupUi();

    GridWidget *m_gridWidget = nullptr;
};