#ifndef BLACK_BOARD_H
#define BLACK_BOARD_H

#include <memory> // for shared_ptr
#include <string>
#include <vector>
#include <yarp/os/Property.h> // the blackboard is a yarp property
#include <cmath> //double_t, int_t etc
class BlackBoard
{
public:
    BlackBoard();

    //template< typename T >
    //void SetValue(const std::string& name,const std::string& type, const T& data)
    void SetValue(const std::string& name,const std::string& type, yarp::os::Value data)
    {
//        for(std::shared_ptr<Property> p : content_)
//        {
//            /*Finds the variable in the blackboard. If exists, it checks that the type is correct.
//            If it does not exists, it creates the new variable in the blackboard*/
//            if (name == p.get()->name())
//            {
//                if (p.get()->type() == type)
//                {
//                    Property* ptr = p.get();
//                    ((TypedProperty<T>*)ptr)->set_data(data);
//                    return;
//                }
//                else
//                {
//                    std::string error_message = "The variable " + name + " exists already as type" + type;
//                    throw std::invalid_argument(error_message.c_str());
//                    return;
//                }
//            }
//        }


        //TODO check
        //the variable is new
        yarp::os::Value value = content_2.find(name);
        /*Finds the variable in the blackboard. If exists, it checks that the type is correct.
                    If it does not exists, it creates the new variable in the blackboard*/
        if(value.isNull())
        {
            std::cout << "setting new variable " << name<< "Value: " << data.asString()<< std::endl;
            content_2.put(name,data);
            std::cout << content_2.toString() << std::endl;



        }
        else
        {
            std::cout << "setting existing variable" << std::endl;

            content_2.unput(name);
            content_2.put(name,data);
        }
    }

    //void PrintContent();
    template< typename T >
    void PrintContent()
    {
//        for(std::shared_ptr<Property> p : content_)
//        {
//            std::string name = p.get()->name();
//            Property* ptr = p.get();
//            T value = ((TypedProperty<T>*)ptr)->data();
//            std::cout << name << " Has Value " << value <<std::endl;
//        }
    }

    void PrintBlackBoard();
    //    void DeclareVariable(std::string name, std::string type);
//    template< typename T >
//    T GetValueOf(std::string name)
//    {
//        for(std::shared_ptr<Property> p : content_)
//        {
//            if (name == p.get()->name())
//            {
//                Property* ptr = p.get();
//                return ((TypedProperty<T>*)ptr)->data();
//            }
//        }
//    }


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
    //std::vector< std::shared_ptr<Property> > content_;
    yarp::os::Property content_2;
    //template< typename T >
    //void SetNew(const std::string& name,const std::string& type, const T& value) //used by SetValue is variable is new
    void SetNew(const std::string& name, yarp::os::Value value) //used by SetValue is variable is new

    {
        //            std::shared_ptr<TypedProperty<T>> new_element (new TypedProperty<T>(name, type, data));
        //            content_.push_back(new_element);
        content_2.put(name,value);
    }

};



#endif // BLACK_BOARD_H
