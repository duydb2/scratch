#ifndef QDECVIEWPORT_H
#define QDECVIEWPORT_H

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

#include <QTimer>
#include <QFile>
#include <QString>
#include <QGLWidget>
#include <QDeclarativeItem>
#include <QGLFramebufferObject>
#include <QGraphicsSceneMouseEvent>

class QDecViewportItem : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(qint32 refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)

public:
    QDecViewportItem(QDeclarativeItem *parent = 0);
    void paint(QPainter *defPainter,
               const QStyleOptionGraphicsItem *style,
               QWidget *widget);

    qint32 refreshRate();
    void setRefreshRate(qint32 refreshRate);

signals:
    void refreshRateChanged();

public slots:
    void updateViewport();

protected:
    virtual void initViewport() = 0;
    virtual void drawViewport() = 0;

    bool m_initFailed;
    QString m_resPrefix;

private:
    bool m_initViewport;
    qint32 m_refreshRate;
    QTimer m_updateTimer;
    QGLFramebufferObject *m_frameBufferObj;
};

#endif
