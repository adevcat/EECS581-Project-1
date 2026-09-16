#include <QWidget>
#include <QVector>

class Tile;

class GridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GridWidget(QWidget *parent = nullptr);

    static constexpr int kGridSize = 10;


signals:
    void tileClicked(Tile *tile, Qt::MouseButton clickType);
    
private slots:
    void handleTileClicked(Tile *tile, Qt::MouseButton clickType);

private:
    void setupUi();
    
    QVector<QVector<Tile*>> m_tiles;
};