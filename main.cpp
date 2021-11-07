#include <iostream>
#include <list>
#include <memory>

enum MetalType
{
    RARE,
    HEAVY,
    LIGHT
};

struct Exhibit
{
    std::string special_name;

    MetalType metal_type;

    std::string currency_name;

    int count_of_currency, count_of_coins;
};

class Receiver
{
private:
    std::list<Exhibit> _exhibition;

public:
    Receiver() = default;

    void insert(const std::string& special_name, MetalType metal_type, const std::string& currency_name,
                int count_of_currency, int count_of_coins)
    {
        _exhibition.push_back(Exhibit{ special_name, metal_type, currency_name, count_of_currency, count_of_coins });
    }

    void show()
    {
        for (const auto& exhibit : _exhibition)
        {
            std::cout << "Special name: " << exhibit.special_name << std::endl;
            std::cout << "Metal type: " << exhibit.metal_type << std::endl;
            std::cout << "Currency name: " << exhibit.currency_name << std::endl;
            std::cout << "Count of currency: " << exhibit.count_of_currency << std::endl;
            std::cout << "Count of coins: " << exhibit.count_of_coins << std::endl;

            std::cout << std::endl;
        }
    }
};

class Command
{
protected:
    std::shared_ptr<Receiver> receiver;

public:
    Command() = default;

    virtual ~Command() = default;

    virtual void execute() = 0;

    void setReceiver(std::shared_ptr<Receiver> receiver)
    {
        this->receiver = receiver;
    }
};

class InsertCommand : public Command
{
private:
    std::string _special_name;

    MetalType _metal_type;

    std::string _currency_name;

    int _count_of_currency, _count_of_coins;

public:
    InsertCommand(const std::string &special_name, MetalType metal_type,
                  const std::string &currency_name, int count_of_currency, int count_of_coins)
        : _special_name(special_name), _metal_type(metal_type), _currency_name(currency_name),
          _count_of_currency(count_of_currency), _count_of_coins(count_of_coins)
    {
    }

    void execute() override
    {
        receiver->insert(_special_name, _metal_type, _currency_name, _count_of_currency, _count_of_coins);
    }
};

class ShowCommand : public Command
{
public:
    ShowCommand() = default;

    void execute() override
    {
        receiver->show();
    }
};

class Invoker
{
private:
    std::shared_ptr<Receiver> _receiver;

    std::shared_ptr<Command> _command;

    std::list<std::shared_ptr<Command>> _history;

public:
    Invoker()
    {
        _receiver = std::make_shared<Receiver>();
    }

    void insert(const std::string& special_name, MetalType metal_type, const std::string& currency_name,
                int count_of_currency, int count_of_coins)
    {
        _command = std::make_shared<InsertCommand>(special_name, metal_type, currency_name, count_of_currency,
                                                    count_of_coins);
        _command->setReceiver(_receiver);
        _command->execute();
        _history.push_back(_command);
    }

    void show()
    {
        _command = std::make_shared<ShowCommand>();
        _command->setReceiver(_receiver);
        _command->execute();
    }
};

int main()
{
    Invoker invoker;

    invoker.insert("name3", RARE, "RU", 70, 10);
    invoker.insert("name2", HEAVY, "RU", 60, 20);
    invoker.insert("name1", LIGHT, "RU", 50, 30);

    invoker.show();

    return 0;
}
