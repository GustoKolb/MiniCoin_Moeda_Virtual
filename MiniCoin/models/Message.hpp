
#pragma once
#include <drogon/drogon.h>
#include <string>

enum class Type {
    INIT,
    WITHDRAW,
    DEPOSIT,
    REFUSED,
    UNKNOWN
}

class Message {
    private:
        std::string name;
        std::string value;
        Type type;
        std::string comment;

    public:

        Message();
        Message(const std::string &name,
                const std::string &value,
                const std::string comment,
                Type type);
        explicit Message(const std::string &jsonStr);


        std::string toString() const;
        Json::Value toJson() const;


        const std::string getName() const;
        const std::string getValue() const;
        const std::string getComment() const;
        Type getType() const;


        void setName(const std::string &n);
        void setValue(const std::string &v);
        void setComment(const std::string &c);
        void setType(Type t);


        static std::string typeToString(MessageType t);
        static MessageType stringToType(const std::string &s);
};
