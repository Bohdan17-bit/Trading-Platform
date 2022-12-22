#include "singleuser.h"

SingleUser *SingleUser::singleUser = nullptr;


SingleUser::SingleUser(const QString name)
    :user_name(name)
{

}

SingleUser *SingleUser::GetInstance(const QString name)
{
    if(singleUser == nullptr)
    {
        singleUser = new SingleUser(name);
    }
    return singleUser;
}

QString SingleUser::value() const
{
    return user_name;
}

