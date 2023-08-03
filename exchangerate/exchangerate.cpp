#include <..\include\gtest\gtest.h>
#include <tuple>
#include <string>
#include <map>
#include <vector>

using namespace std;
/*
 We have collection of exchnage rates experssed as:
 1. Source currency
 2. Target currency
 3. Exchange rate
 Function shuold take in that collection and also two currencies
 from which to which we want to find exchange rate
 Return value should be exchange rate between those two currencies
 */

struct ExchangeRate {

    ExchangeRate(string _fromCurrency, string _toCurrency, double _rate) {
        fromCurrency = _fromCurrency;
        toCurrency = _toCurrency;
        rate = _rate;
    }

    string fromCurrency;
    string toCurrency;
    double rate;

};


class Currency {

    public:
        Currency(const string _name) {
            name = _name;
        }

        void updateRate(const string& _name, double _rate) {
            map<string, double>::iterator it = exchangeRates.find(_name);
            if (it != exchangeRates.end()) {
                it->second = _rate;
            } else {
                exchangeRates.insert(map<string, double>::value_type(_name, _rate));
            }
        }

        const string& getName() { return this->name; }

        const double getExchangeRate(const string& _name) {
            map<string, double>::iterator it = exchangeRates.find(_name);
            if (it != exchangeRates.end()) {
                return it->second;
            }

            return -1;
        } 

        double getRate(map<string, Currency*>& currencies,const string& _toCurrency, double _rate = 1.0) {

            map<string, double>::iterator it = exchangeRates.find(_toCurrency);
            if (it != exchangeRates.end()) {
                //our currency has exchange rate to target currency (we are done)
                return _rate * it->second;
            } else {
                //let's check if we have rates of 
                for (it = exchangeRates.begin(); it != exchangeRates.end(); it ++) {

                    //find currency in map
                    map<string, Currency*>::iterator currIt = currencies.find(it->first);
                    if (currIt != currencies.end()) {
                        double rate = currIt->second->getRate(currencies, _toCurrency, _rate*it->second);
                        if (rate > 0) {
                            return rate;
                        }
                    }                
                }

            }

            return -1;
        }

    protected:
        string name;
        map<string, double> exchangeRates;

};

class CurrencyMap {

    public:

        CurrencyMap(const std::vector<ExchangeRate>& exchangeRates) {
            build(exchangeRates);
        }

        map<string, Currency*> currencies;

        void build(const std::vector<ExchangeRate>& exchangeRates) {
            vector<ExchangeRate>::const_iterator it;
            for (it = exchangeRates.begin(); it < exchangeRates.end(); it++) {
                map<string, Currency*>::iterator currIt = currencies.find(it->toCurrency);

                if (currIt != currencies.end()) {
                    //Currency already in the map, we will just update rate
                    currIt->second->updateRate(it->toCurrency, it->rate);
                } else {
                    //Currency not in the map, adding it
                    Currency* pCurrency = new Currency(it->fromCurrency);
                    pCurrency->updateRate(it->toCurrency, it->rate);
                    currencies.insert(map<string, Currency*>::value_type(it->fromCurrency, pCurrency));
                }
            }

        }

        double getRate(const string& fromCurrency, const string& toCurrency) {
            
            map<string, Currency*>::iterator it = currencies.find(fromCurrency);

            //check if we even have the 'from' currency
            if (it != currencies.end()) {
                return it->second->getRate(currencies, toCurrency);                
            }

            return -1;

        }

};


TEST(ExchangeRate, buildGraph) {

    std::vector<ExchangeRate> exchangeRates {
        ExchangeRate("USD", "GBP", 0.78),
        ExchangeRate("GBP", "JPY", 182.78)
    };    

    CurrencyMap currencyMap(exchangeRates);

    ASSERT_EQ(2, currencyMap.currencies.size());

    ASSERT_TRUE(abs(currencyMap.currencies["USD"]->getExchangeRate("GBP") - 0.78) < std::numeric_limits<double>::epsilon());
    ASSERT_TRUE(abs(currencyMap.currencies["GBP"]->getExchangeRate("JPY") - 182.78) < std::numeric_limits<double>::epsilon());

    //testing non existing exchange rates
    ASSERT_TRUE(abs(currencyMap.currencies["USD"]->getExchangeRate("JPY") + 1) < std::numeric_limits<double>::epsilon());

}

TEST(ExchangeRate, findRate) {

    std::vector<ExchangeRate> exchangeRates {
        ExchangeRate("USD", "GBP", 0.78),
        ExchangeRate("GBP", "JPY", 182.78)
    };    

    CurrencyMap currencyMap(exchangeRates);

    ASSERT_TRUE(currencyMap.getRate("USD", "JPY") - .78 * 182.78 < std::numeric_limits<double>::epsilon());
}


