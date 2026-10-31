#include<iostream>
#include<cstdint>
#include<vector>
#include<string>
#include<sstream>
#include<string_view>
#include<algorithm>

enum class Command
{
    BUY,
    SELL,
    CANCEL,
    EXIT,
    INVALID
};

Command decode(std::string_view action)
{
    if (action == "BUY")
       return Command::BUY;
    if (action == "SELL")
       return Command::SELL;
    if (action == "CANCEL")
       return Command::CANCEL;
    if (action == "EXIT" || action == "STOP" || action == "QUIT")
       return Command::EXIT;

    return Command::INVALID;
};

Command cmd ;

struct Order
{
    uint64_t amount ;
    uint32_t id ;
    uint32_t quantity ;

} tmp_book;

uint32_t order_id = 0 ;
std::vector<Order> buy_book , sell_book ;
std::vector<std::pair<char,uint32_t>> tracker ;


bool priority(Order a , Order b , bool is_buy)
{
    if ( a.amount != b.amount )
    {
	if (is_buy)
            return a.amount > b.amount ;
        else
            return a.amount < b.amount ;
    }

    return a.id < b.id ;
};

void swapp(std::vector<Order>& book,uint32_t i , uint32_t j )
{
    tmp_book = book[i] ;
    book[i] = book[j] ;
    book[j] = tmp_book ;

    tracker[book[i].id].second =  i;
    tracker[book[j].id].second =  j;
};

void heap_up(uint32_t child , bool is_buy)
{

    if (is_buy)
    {
        while (child>0)
        {
            uint32_t parent = (child-1)/2 ;

            if ( priority(buy_book[child],buy_book[parent],1) )
            {
                swapp(buy_book,child,parent) ;
                child = parent ;
            }
            else
            {
                break ;
            }
        }
    }
    else
    {
        while (child>0)
        {
            uint32_t parent = (child-1)/2 ;

            if ( priority(sell_book[child],sell_book[parent],0) )
            {
                swapp(sell_book,child,parent) ;
                child = parent ;
            }
            else
            {
                break ;
            }
        }
    }
}


void heap_down(uint32_t parent , bool is_buy)
{
    if (is_buy)
    {
        while (2*parent+1 < buy_book.size())
        {
            uint32_t left = 2*parent+1 ;
            uint32_t right = 2*parent+2 ;
            uint32_t best = left ;

            if ( right < buy_book.size() && priority(buy_book[right],buy_book[left],1) )
            {
                best = right ;
            }

            if ( priority(buy_book[best],buy_book[parent],1) )
            {
	            swapp(buy_book,best,parent) ;
                parent = best ;
            }
            else
            {
                break ;
            }
        }
    }
    else
    {
        while (2*parent+1 < sell_book.size())
        {
            uint32_t left = 2*parent+1 ;
            uint32_t right = 2*parent+2 ;
            uint32_t best = left ;

            if ( right < sell_book.size() && priority(sell_book[right],sell_book[left],0) )
            {
                best = right ;
            }

            if (priority(sell_book[best],sell_book[parent],0) )
            {
                swapp(sell_book,best,parent) ;
                parent = best ;
            }
            else
            {
                break ;
            }
        }
    }

};

void cancel( uint32_t id );
void match(uint64_t price , uint32_t qty , bool is_buy)
{
    order_id++ ;

    if ( order_id >= tracker.size() )
    {
	    uint32_t new_size = tracker.size()*2 ;
        tracker.resize(new_size,{'\0',(uint32_t)-1}) ;
    }

    if ( is_buy )
    {
        uint32_t sell_id ;

        while ( !sell_book.empty() && price >= sell_book[0].amount && qty > 0 )
            {
            int min_qty = std::min(qty,sell_book[0].quantity) ;

                qty -= min_qty ;
                sell_book[0].quantity -= min_qty ;
                sell_id = sell_book[0].id ;

                std::cout << "TRADE : BUYER " << order_id
                        <<" BOUGHT " << min_qty << " STOCKS "
                        <<"@ " << sell_book[0].amount
                        <<" FROM SELLER " << sell_id << "\n" ;

                if ( sell_book[0].quantity == 0)
                {
                    cancel(sell_id) ;
                }

            }

        if ( qty>0 )
        {
            tmp_book = {price,order_id,qty} ;

            buy_book.push_back(tmp_book) ;
            tracker[order_id] = {'B',buy_book.size()-1} ;
            heap_up(buy_book.size()-1,1) ;
        }
    }
    else
    {
        uint32_t buy_id ;

        while ( !buy_book.empty() && price <= buy_book[0].amount && qty > 0 )
        {
            int min_qty = std::min(qty,buy_book[0].quantity) ;

            qty -= min_qty ;
            buy_book[0].quantity -= min_qty ;
            buy_id = buy_book[0].id ;

            std::cout << "TRADE : SELLER " << order_id
                      <<" SOLD " << min_qty << " STOCKS "
                      <<"@ " << buy_book[0].amount
                      <<" TO BUYER " << buy_id << "\n" ;

            if ( buy_book[0].quantity == 0)
            {
                cancel(buy_id) ;
            }

        }

        if ( qty>0 )
        {
            tmp_book = {price,order_id,qty} ;

            sell_book.push_back(tmp_book) ;
            tracker[order_id] = {'S',sell_book.size()-1} ;
            heap_up(sell_book.size()-1,0) ;
        }
    }
};

void buy(std::stringstream& ss)
{
    uint64_t price ;
    uint32_t qty ;

    ss >> price ;
    ss >> qty ;

    match(price,qty,1) ;
};

void sell(std::stringstream& ss )
{
    uint64_t price ;
    uint32_t qty ;

    ss >> price ;
    ss >> qty ;

    match(price,qty,0) ;

};

void cancel( uint32_t id )
{
    if ( id < tracker.size() )
    {
        uint32_t target_id = tracker[id].second ;

        if ( tracker[id].first == 'B' )
        {
            tracker[id] = {'X',(uint32_t)-1} ;

            if ( cmd == Command::CANCEL )
            {
                std::cout << "CANCEL : ORDER " << id << " CANCELLED\n" ;
            }

            if ( buy_book.size() > 1)
            {
                    swapp(buy_book,target_id,buy_book.size()-1) ;
                    buy_book.pop_back() ;

                    if ( target_id < buy_book.size() )
                    {
                        heap_down(target_id,1) ;
                        heap_up(target_id,1) ;
                    }
            }
            else
            {
                    buy_book.pop_back() ;
            }
        }
        else if ( tracker[id].first == 'S' )
        {
            tracker[id] = {'X',(uint32_t)-1} ;

            if ( cmd == Command::CANCEL )
            {
                std::cout << "CANCEL : ORDER " << id << " CANCELLED\n" ;
            }

            if ( sell_book.size() > 1)
            {
                swapp(sell_book,target_id,sell_book.size()-1) ;
                sell_book.pop_back() ;

                if ( target_id < sell_book.size() )
                {
                    heap_down(target_id,0) ;
                    heap_up(target_id,0) ;
                }
            }
            else
            {
                sell_book.pop_back() ;
            }
        }
        else
        {
	        std::cout << "CANCEL REJECT: ORDER " << id << " NOT FOUND\n";
        }
    }
    else
    {
	        std::cout << "CANCEL REJECT: ORDER " << id << " NOT FOUND\n";
    }
};

int main()
{

    std::cout<<"MAKE YOUR ORDER\n" ;

    buy_book.reserve(25) ;
    sell_book.reserve(25) ;
    tracker.resize(50,{'\0',(uint32_t)-1}) ;

    std::string line ;

    while (true)
    {
        if (!std::getline(std::cin, line) || line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string act;
        ss >> act;

        std::string_view action = act;
        cmd = decode(action);

        switch (cmd)
        {
            case Command::EXIT:
                return 0;

            case Command::CANCEL:
                uint32_t id ;
                ss >> id ;
                cancel(id);

                break;

            case Command::BUY:
                buy(ss);
                break;

            case Command::SELL:
                sell(ss);
                break;

            case Command::INVALID:
            default:
                std::cout << "ERROR!\n";
                return 0 ;
        }
    }



}
