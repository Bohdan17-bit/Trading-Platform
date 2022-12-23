#include "singleuser.h"

SingleUser *SingleUser::singleUser = nullptr;


SingleUser::SingleUser(const QString name)
    :user_name(name)
{

}

SingleUser *SingleUser::GetInstance()
{
    return singleUser;
}

SingleUser *SingleUser::CreateInstance(QString name)
{
    if(singleUser == nullptr)
    {
        singleUser = new SingleUser(name);
    }
    return singleUser;
}

QString SingleUser::getActiveUser() const
{
    return user_name;
}

