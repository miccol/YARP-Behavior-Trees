#ifndef BLACK_BOARD_H
#define BLACK_BOARD_H

#include<memory> // for shared_ptr
#include<string>
#include<vector>
#include <typed_property.h>
class BlackBoard
{
public:
    BlackBoard();
    template< typename T >
    void SetNew(const std::string& name,const std::string& type, const T& data)
    {
        std::shared_ptr<TypedProperty<T>> new_element (new TypedProperty<T>(name, type, data));
        content_.push_back(new_element);
    }

    template< typename T >
    void SetValue(const std::string& name,const std::string& type, const T& data)
    {
        for(std::shared_ptr<Property> p : content_)
        {
            /*Finds the variable in the blackboard. If exists, it checks that the type is correct.
            If it does not exists, it creates the new variable in the blackboard*/
            if (name == p.get()->name())
            {
                if (p.get()->type() == type)
                {
                    Property* ptr = p.get();
                    ((TypedProperty<T>*)ptr)->set_data(data);
                    return;
                }
                else
                {
                    std::cout << "ERROR! The variable "<< name << " exists already as type" << type << std::endl;
                }
            }
        }
        //the variable is new
        SetNew(name,type,data);
    }

    //void PrintContent();
    template< typename T >
    void PrintContent()
    {
        for(std::shared_ptr<Property> p : content_)
        {
            std::string name = p.get()->name();
            Property* ptr = p.get();
            T value = ((TypedProperty<T>*)ptr)->data();
            std::cout << name << " Has Value " << value <<std::endl;
        }
    }

    void PrintBlackBoard();
    //    void DeclareVariable(std::string name, std::string type);
    template< typename T >
    T GetValueOf(std::string name)
    {

        for(std::shared_ptr<Property> p : content_)
        {
            if (name == p.get()->name())
            {
                Property* ptr = p.get();
                return ((TypedProperty<T>*)ptr)->data();
            }
        }
    }


public:
    int GetInt(std::string name);
    int16_t GetI16(std::string name);
    int32_t GetI32(std::string name);
    int64_t GetI64(std::string name);
    int8_t GetByte(std::string name);
    bool GetBool(std::string name);
    double_t GetDouble(std::string name);
    std::string GetString(std::string name);


private:
        std::vector< std::shared_ptr<Property> > content_;
};



#endif // BLACK_BOARD_H
