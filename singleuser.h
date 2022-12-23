#ifndef SINGLEUSER_H
#define SINGLEUSER_H
#include <QString>


class SingleUser
{
private:
    SingleUser(const QString name);
    static SingleUser *singleUser;
    QString user_name;
public:
    SingleUser(SingleUser &user) = delete;
    void operator = (const SingleUser user) = delete;
    static SingleUser *GetInstance();
    static SingleUser *CreateInstance(QString name);
    QString getActiveUser() const;
};
#endif // SINGLEUSER_H
