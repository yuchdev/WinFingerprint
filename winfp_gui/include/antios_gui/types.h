#pragma once

#include <QString>
#include <QMetaType>
#include <QTextStream>

struct Item 
{
    Item() = default;
    virtual ~Item() = default;

    Item(const QString& param_name, const QString& title, const QString& before, const QString& after)
        : param_name_   (param_name)
        , title_        (title)
        , before_       (before)
        , after_        (after)
    { }

    Item(QString&& param_name, QString&& title, QString&& before, QString&& after)
        : param_name_   (std::move(param_name))
        , title_        (std::move(title))
        , before_       (std::move(before))
        , after_        (std::move(after))
    { }

    Item& operator =(const Item& item) {
        param_name_ = item.param_name_;
        title_      = item.title_;
        before_     = item.before_;
        after_      = item.after_;
        return *this;
    }


    QString toString() {
        QString result;
        QTextStream stream(&result);
        stream << "Param: '"    << param_name_    << "'"
               << " Title: '"   << title_         << "'"
               << " Before: '"  << before_        << "'"
               << " After: '"   << after_         << "'";
        return result;
    }


    QString param_name_;
    QString title_;
    QString before_;
    QString after_;
};

Q_DECLARE_METATYPE(Item)

struct Product_id 
{
    QString field1_;
    QString field2_;
    QString field3_;
    QString field4_;

    QString getProductID() {
        return QString("%1-%2-%3-%4")
                .arg(field1_)
                .arg(field2_)
                .arg(field3_)
                .arg(field4_);
    }
};

Q_DECLARE_METATYPE(Product_id)

