#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<algorithm>

struct Order
{
    int64_t price ;
    int id ;
    int quantity ;
} ;


struct BuyComparator {
    bool operator()(const Order& a, const Order& b) const {

    if( a.price != b.price )
    {
        return a.price < b.price;
    }

    return a.id > b.id ;
    }
};


struct SellComparator {
    bool operator()(const Order& a, const Order& b) const {

    if( a.price != b.price )
    {
        return a.price > b.price;
    }

    return a.id > b.id ;
    }
};

int buyer_id=0 , seller_id=0 ;

int main()
{
    std::priority_queue<Order, std::vector<Order>, BuyComparator> buy;
    std::priority_queue<Order, std::vector<Order>, SellComparator> sell;


    std::string action ;
    int64_t amount ;
    int qty ;

    std::cout<< "Make your Order\n" ;

    while (true)
    {
      Order tmp_order ;

      std::cin>>action ;

      if ( action == "stop" || action == "exit" )
      {
         return 0;
      }

      std::cin >> amount >> qty ;

      if ( action == "buy")
      {
         buyer_id++ ;

         while ( !sell.empty() && amount >= sell.top().price && qty > 0 )
         {
            int min_qty = std::min(qty,sell.top().quantity) ;

            qty -= min_qty ;
            tmp_order = sell.top() ;
            tmp_order.quantity -= min_qty ;
            sell.pop() ;

            std::cout<<"\n\nBOUGHT  " << "BUYER ID:"<< buyer_id << " | " << "SELLER ID:" << tmp_order.id << " | " << "PRICE:" << tmp_order.price << " | " << "QUANTITY:" << min_qty << "\n\n";

            if( tmp_order.quantity > 0)
            {
               sell.push(tmp_order) ;
            }

         }

         if (qty > 0)
         {
            buy.push({amount,buyer_id,qty}) ;
         }

      } 
      else if ( action == "sell")
      {
         seller_id++ ;

         while ( !buy.empty() && amount <= buy.top().price && qty > 0 )
         {
            int min_qty = std::min(qty,buy.top().quantity) ;

            qty -= min_qty ;
            tmp_order = buy.top() ;
            tmp_order.quantity = buy.top().quantity - min_qty ;
            buy.pop() ;

            std::cout<<"\n\nSOLD  " << "SELLER ID:"<< seller_id << " | " << "BUYER ID:" << tmp_order.id << " | " << "PRICE:" << tmp_order.price << " | " << "QUANTITY:" << min_qty << "\n\n";

            if( tmp_order.quantity > 0)
            {
               buy.push(tmp_order) ;
            }

         }

         if (qty > 0)
         {
            sell.push({amount,seller_id,qty}) ;
         }

      }
      else
      {
         std::cout<<"Invalid Input\n" ;
         return 0 ;
      }



    }
    return 0 ;
}
