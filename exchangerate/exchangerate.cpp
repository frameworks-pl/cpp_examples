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

    protected:
        string name;
        map<string, double> exchangeRates;

};

class CurrencyMap {

    public:

        map<string, Currency*> currencies;

        void build(const std::vector<ExchangeRate>& exchangeRates) {
            vector<ExchangeRate>::const_iterator it;
            for (it = exchangeRates.begin(); it < exchangeRates.end(); it++) {
                map<string, Currency*>::iterator currIt = currencies.find(it->toCurrency);
                if (currIt != currencies.end()) {
                    currIt->second->updateRate(it->toCurrency, it->rate);
                } else {
                    Currency* pCurrency = new Currency(it->fromCurrency);
                    pCurrency->updateRate(it->toCurrency, it->rate);
                    currencies.insert(map<string, Currency*>::value_type(it->fromCurrency, pCurrency));
                }
            }

        }

};




TEST(ExchangeRate, buildGraph) {

    std::vector<ExchangeRate> exchangeRates {
        ExchangeRate("USD", "GBP", 0.78),
        ExchangeRate("GBP", "JPY", 182.78)
    };    

    CurrencyMap currencyMap;
    currencyMap.build(exchangeRates);

    
    ASSERT_EQ(2, currencyMap.currencies.size());
    //ASSERT_TRUE(abs(currencyMap.currencies["USD"]->getExchangeRate('GBP') - 0.78) > std::numeric_limits<double>::epsilon());

    ASSERT_TRUE(abs(currencyMap.currencies["USD"]->getExchangeRate("GBP") - 0.78) < std::numeric_limits<double>::epsilon());
    ASSERT_TRUE(abs(currencyMap.currencies["GBP"]->getExchangeRate("JPY") - 182.78) < std::numeric_limits<double>::epsilon());

    //testing non existing exchange rates
    ASSERT_TRUE(abs(currencyMap.currencies["USD"]->getExchangeRate("JPY") + 1) < std::numeric_limits<double>::epsilon());


}


// TEST(ExchangeRate, simpleScenario) {

//     std::vector<CurrencyExchangeRate> exchangeRates {
//         CurrencyExchangeRate("USD", "GBP", 0.78),
//         CurrencyExchangeRate("GBP", "JPY", 182.78)
//     };

//     ASSERT_TRUE(calculateRate(exchangeRates, "USD", "JPY") - 142.5684 > 0.0001);

// }

