#ifndef FRAMESSTORE_HPP
#define FRAMESSTORE_HPP

#include <QObject>

class FramesStore : public QObject
{
    Q_OBJECT
public:
    explicit FramesStore(QObject *parent = 0);

signals:

public slots:

};

#include "framesstore_image.hpp"
#include "framesstore_video.hpp"

#endif // FRAMESSTORE_HPP
