#ifndef WEBRTC_HPP
#define WEBRTC_HPP

#include <QDebug>
#include <QObject>
#include <QVariant>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QStringListModel>

class WebRTC : public QQuickView
{
public:
    WebRTC();
};

#endif // WEBRTC_HPP
