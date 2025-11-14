
//Autoria de Augusto Antonio Kolb Schiavini (GRR 20232337) e João Eduardo Zangari Ambrosio(GRR 20232344)|
#include "Message.hpp"
#include <sstream>
#include <stdexcept>

//Message::Message
//Message::toJson
//Message::toString
//Message::getName
//Message::getType
//Message::getValue
//Message::getComment
//Message::setName
//Message::setType
//Message::setValue
//Message::setComment
//Message::typeToString
//Message::stringToType
//------------------------------------------------------------
Message::Message() : type(Type::UNKNOWN) {}

//------------------------------------------------------------
Message::Message(const std::string &name,
                 const std::string &value,
                 const std::string comment,
                 Type type)
    : name(name), value(value), comment(comment), type(type) {}

//------------------------------------------------------------
Message::Message(const std::string &jsonStr)
{
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream s(jsonStr);
    Json::Value root;

    if (!Json::parseFromStream(builder, s, &root, &errs))
    {
        throw std::runtime_error("Erro ao parsear JSON: " + errs);
    }

    this->name = root.get("name", "").asString();
    this->value = root.get("value", "").asString();
    this->comment = root.get("comment","").asString();
    this->type = stringToType(root.get("type", "").asString());
}

//------------------------------------------------------------
std::string Message::toString() const
{
    Json::Value root;
    root["name"] = this->name;
    root["value"] = this->value;
    root["comment"] = this->comment;
    root["type"] = typeToString(this->type);

    Json::StreamWriterBuilder writer;
    writer["indentation"] = "";
    return Json::writeString(writer, root);
}

//------------------------------------------------------------
Json::Value Message::toJson() const
{
    Json::Value root;
    root["name"] = this->name;
    root["value"] = this->value;
    root["comment"] = this->comment;
    root["type"] = typeToString(this->type);
    return root;
}

//------------------------------------------------------------
const std::string Message::getName() const { return this->name; }
const std::string Message::getValue() const { return this->value; }
const std::string Message::getComment() const { return this->comment; }
Type Message::getType() const { return this->type; }

//------------------------------------------------------------
void Message::setName(const std::string &n) { this->name = n; }
void Message::setValue(const std::string &v) { this->value = v; }
void Message::setComment(const std::string &c) { this->comment = c; }
void Message::setType(Type t) { this->type = t; }

//------------------------------------------------------------
std::string Message::typeToString(Type t)
{
    switch (t)
    {
    case Type::INIT: return "INIT";
    case Type::WITHDRAW: return "WITHDRAW";
    case Type::DEPOSIT: return "DEPOSIT";
    case Type::REFUSED: return "REFUSED";
    case Type::LOGGEDIN: return "LOGGEDIN";
    default: return "UNKNOWN";
    }
}

//------------------------------------------------------------
Type Message::stringToType(const std::string &s)
{
    if (s == "INIT") return Type::INIT;
    if (s == "WITHDRAW") return Type::WITHDRAW;
    if (s == "DEPOSIT") return Type::DEPOSIT;
    if (s == "REFUSED") return Type::REFUSED;
    if (s == "LOGGEDIN") return Type::LOGGEDIN;
    return Type::UNKNOWN;
}
//------------------------------------------------------------
