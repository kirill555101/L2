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

class Command
{
protected:
    std::shared_ptr<Exhibit> exhibit;

public:
    Command() = default;

    Command(std::shared_ptr<Command> command)
    {
        exhibit = command->exhibit;
    }

    virtual ~Command() = default;

    virtual void execute() = 0;
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
        exhibit = std::make_shared<Exhibit>(Exhibit{_special_name, _metal_type, _currency_name,
                                                    _count_of_currency, _count_of_coins});
    }
};

class ShowCommand : public Command
{
public:
    ShowCommand(std::shared_ptr<Command> command) : Command(command)
    {
    }

    void execute() override
    {
        std::cout << "Special name: " << exhibit->special_name << std::endl;
        std::cout << "Metal type: " << exhibit->metal_type << std::endl;
        std::cout << "Currency name: " << exhibit->currency_name << std::endl;
        std::cout << "Count of currency: " << exhibit->count_of_currency << std::endl;
        std::cout << "Count of coins: " << exhibit->count_of_coins << std::endl;

        std::cout << std::endl;
    }
};

class Invoker
{
private:
    std::list<std::shared_ptr<Command>> _history;

    std::shared_ptr<Command> _command;

public:
    void insert(const std::string &special_name, MetalType metal_type, const std::string &currency_name,
                int count_of_currency, int count_of_coins)
    {
        _command = std::make_shared<InsertCommand>(special_name, metal_type, currency_name,
                                                   count_of_currency, count_of_coins);
        _command->execute();
        _history.push_back(_command);
    }

    void show()
    {
        for (const auto &command : _history)
        {
            _command = std::make_shared<ShowCommand>(command);
            _command->execute();
        }
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
